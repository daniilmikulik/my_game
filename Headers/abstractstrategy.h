#ifndef ABSTRACTSTRATEGY_H
#define ABSTRACTSTRATEGY_H

#include "Headers/abstracttile.h"
#include "Headers/field.h"
#include "Headers/tower.h"
#include "Headers/rock.h"
#include "Headers/lake.h"
#include "Headers/forest.h"
#include "Headers/fortress.h"
#include "Headers/start.h"
#include "Headers/stop.h"
#include "Headers/mill.h"
#include "Headers/village.h"
//#include "Headers/player.h"

namespace Hero{
class Player;
}

namespace Strategy {


    class AbstractStrategy{
    public:

        virtual void Interact(Hero::Player* unit) = 0;
    };
}

#endif // ABSTRACTSTRATEGY_H
