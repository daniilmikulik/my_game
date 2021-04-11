#ifndef RIGHTCOMMAND_H
#define RIGHTCOMMAND_H

#include "Headers/command.h"

namespace Strategy{
class RightCommand : public Strategy::Command{
public:
    void Execute(Board::MapIterator  *const iter) override{
        iter -> NextRight();
    }
    virtual ~RightCommand(){};
};
}
#endif // RIGHTCOMMAND_H
