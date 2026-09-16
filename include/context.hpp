#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <memory>

#include "sensor_data.hpp"
#include "state.hpp"

enum class StateType
{
    NORMAL,
    WARNING,
    EMERGENCY_BRAKE
};

class AEBContext
{
private:
    std::unique_ptr<State> currentState;
    StateType currentStateType;

    int safeSampleCount;

    void transitionTo(StateType newState);
    bool isValidData(const SensorData& data) const;
    void resetSafeSampleCount();

public:
    AEBContext();

    void update(const SensorData& data);
    void executeCurrentState();

    StateType getCurrentState() const;
};

#endif