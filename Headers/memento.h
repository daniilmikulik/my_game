#ifndef MEMENTO_H
#define MEMENTO_H

#include <string>
#include <vector>

class Facade;

class Memento{
    virtual std::string Date() = 0;

};



class Caretaker{
public:
    virtual void BackUp() = 0;
    virtual void Undo() = 0;

};

#endif // MEMENTO_H
