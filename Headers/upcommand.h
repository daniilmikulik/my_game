#ifndef UPCOMMAND_H
#define UPCOMMAND_H

#include "Headers/command.h"
namespace Strategy{
    class UpCommand : public Command{
    public:
        void Execute(Board::MapIterator  *const iter) override{
            iter -> NextUp();
        }
        virtual ~UpCommand(){};
    };
}
#endif // UPCOMMAND_H
