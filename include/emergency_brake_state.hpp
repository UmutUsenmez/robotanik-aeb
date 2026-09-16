#ifndef EMERGENCY_BRAKE_STATE_HPP
#define EMERGENCY_BRAKE_STATE_HPP

#include "state.hpp"

class EmergencyBrakeState : public State
{
public:
    void execute() override;
};

#endif