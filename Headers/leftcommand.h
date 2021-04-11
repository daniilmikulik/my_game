#ifndef LEFTCOMMAND_H
#define LEFTCOMMAND_H

#include "Headers/command.h"
namespace Strategy{
    class LeftCommand : public Command{
    public:
        void Execute(Board::MapIterator  *const iter) override{
            iter -> NextLeft();
        }
        virtual ~LeftCommand(){};
    };
}
#endif // LEFTCOMMAND_H
