#include "context.hpp"

#include <cmath>
#include <iostream>

#include "emergency_brake_state.hpp"
#include "normal_state.hpp"
#include "ttc.hpp"
#include "warning_state.hpp"

namespace
{
    constexpr double WARNING_TTC = 3.0;
    constexpr double EMERGENCY_TTC = 1.5;

    constexpr double ZERO_SPEED_EPSILON = 0.01;

    constexpr double WARNING_DISTANCE_AT_ZERO_SPEED = 1.0;
    constexpr double EMERGENCY_DISTANCE_AT_ZERO_SPEED = 0.5;

    constexpr int REQUIRED_SAFE_SAMPLES = 3;
}

AEBContext::AEBContext()
    : currentState(std::make_unique<NormalState>()),
      currentStateType(StateType::NORMAL),
      safeSampleCount(0)
{
}

void AEBContext::transitionTo(StateType newState)
{
    switch (newState)
    {
    case StateType::NORMAL:
        currentState = std::make_unique<NormalState>();
        break;

    case StateType::WARNING:
        currentState = std::make_unique<WarningState>();
        break;

    case StateType::EMERGENCY_BRAKE:
        currentState = std::make_unique<EmergencyBrakeState>();
        break;
    }

    currentStateType = newState;
}

bool AEBContext::isValidData(const SensorData& data) const
{
    if (!std::isfinite(data.distance) ||
        !std::isfinite(data.speed))
    {
        return false;
    }

    if (data.distance < 0.0 ||
        data.speed < 0.0)
    {
        return false;
    }

    return true;
}

void AEBContext::resetSafeSampleCount()
{
    safeSampleCount = 0;
}

void AEBContext::update(const SensorData& data)
{
    // Kirli/geçersiz veri varsa karar verme.
    if (!isValidData(data))
    {
        std::cout << "Invalid sensor data ignored\n";
        return;
    }

    // Hız çok düşükse TTC hesaplama.
    // Önce doğrudan mesafeye bak.
    if (data.speed <= ZERO_SPEED_EPSILON)
    {
        if (data.distance <= EMERGENCY_DISTANCE_AT_ZERO_SPEED)
        {
            transitionTo(StateType::EMERGENCY_BRAKE);
            resetSafeSampleCount();
        }
        else if (data.distance <= WARNING_DISTANCE_AT_ZERO_SPEED)
        {
            transitionTo(StateType::WARNING);
            resetSafeSampleCount();
        }
        else
        {
            if (currentStateType != StateType::NORMAL)
            {
                safeSampleCount++;

                if (safeSampleCount >= REQUIRED_SAFE_SAMPLES)
                {
                    transitionTo(StateType::NORMAL);
                    resetSafeSampleCount();
                }
            }
            else
            {
                resetSafeSampleCount();
            }
        }

        return;
    }

    double ttc = calculateTTC(data);

    // Tehlikeye giriş: gecikmesiz.
    if (ttc <= EMERGENCY_TTC)
    {
        transitionTo(StateType::EMERGENCY_BRAKE);
        resetSafeSampleCount();
        return;
    }

    if (ttc <= WARNING_TTC)
    {
        transitionTo(StateType::WARNING);
        resetSafeSampleCount();
        return;
    }

    // Buraya geldiysek TTC güvenli bölgede.
    // Çıkışta hysteresis uyguluyoruz.
    if (currentStateType != StateType::NORMAL)
    {
        safeSampleCount++;

        if (safeSampleCount >= REQUIRED_SAFE_SAMPLES)
        {
            transitionTo(StateType::NORMAL);
            resetSafeSampleCount();
        }
    }
    else
    {
        resetSafeSampleCount();
    }
}

void AEBContext::executeCurrentState()
{
    currentState->execute();
}

StateType AEBContext::getCurrentState() const
{
    return currentStateType;
}