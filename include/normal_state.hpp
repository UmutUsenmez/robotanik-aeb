#ifndef NORMAL_STATE_HPP
#define NORMAL_STATE_HPP

#include "state.hpp"    

class NormalState : public State {    // NormalState sınıfı State sınıfından türetiliyor "inheritance"
    public:
        void execute() override ;
}; 

#endif