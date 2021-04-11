#ifndef PUBLISHER_H
#define PUBLISHER_H

namespace Strategy{
    class AbstractObserver;
    class Abstraction;
}

//namespace Hero{
    class Publisher{
    public:
        virtual void Subscribe(Strategy::Abstraction* abstraction/*AbstractObserver* observer*/) = 0;
        virtual void Unsubscribe(Strategy::Abstraction* abstraction/*AbstractObserver* observer*/) = 0;
        virtual void Notify() = 0;
    };
//}

#endif // PUBLISHER_H
