#ifndef STATE_HPP
#define STATE_HPP

class State
{
public:
    virtual void execute() = 0;

    virtual ~State() = default;
};

#endif