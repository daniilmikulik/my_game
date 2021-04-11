#ifndef COMMAND_H
#define COMMAND_H

#include "map.h"

namespace Strategy{
    class Command{
    public:
        virtual void Execute(Board::MapIterator *const iter) = 0;
        virtual ~Command(){};
    };
}
#endif // COMMAND_H
