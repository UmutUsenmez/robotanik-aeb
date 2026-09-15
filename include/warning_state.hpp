#ifndef WARNING_STATE_HPP
#define WARNING_STATE_HPP

#include "state.hpp"

class WarningState : public State
{
public:
    void execute() override;
};

#endif