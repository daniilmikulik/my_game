#ifndef OBSERVER_H
#define OBSERVER_H

#include <fstream>


class Publisher;

namespace Strategy{
    class AbstractObserver{
    public:
        virtual void Update(Publisher* unit) = 0;
    };



    class Abstraction{
    protected:
        AbstractObserver* abstractObserver_;
    public:
        Abstraction(Strategy::AbstractObserver* observer) : abstractObserver_(observer) {}
        virtual void Operation(Publisher* unit) const {
            this->abstractObserver_->Update(unit);
        }
        virtual ~Abstraction() {}
    };
}
#endif // OBSERVER_H
