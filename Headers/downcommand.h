#ifndef DOWNCOMMAND_H
#define DOWNCOMMAND_H

#include "Headers/command.h"
namespace Strategy {
    class DownCommand : public Command{
    public:
        void Execute(Board::MapIterator  *const iter) override{
            iter -> NextDown();
        }
        virtual ~DownCommand(){};
    };
}

#endif // DOWNCOMMAND_H
