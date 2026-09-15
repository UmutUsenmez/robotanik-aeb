#ifndef STATE_HPP
#define STATE_HPP

class State {
    public :
        virtual void execute() = 0;     // her state'in kendisi için execute fonksiyonu olacak 
        virtual ~State() = default;    // virtual , Elimde genel olarak bi state var ama ben genel olarak tanımlıyorum.
};

#endif 