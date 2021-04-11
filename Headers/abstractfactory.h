#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

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

namespace Factory {


    class AbstractFactory{
    public:
        virtual Board::AbstractTile* CreateFieldTile(int x, int y) const = 0;
        virtual Board::AbstractTile* CreateLakeTile(int x, int y) const = 0;
        virtual Board::AbstractTile* CreateForestTile(int x, int y) const = 0;
        virtual Board::AbstractTile* CreateRockTile(int x, int y) const = 0;
        virtual Board::AbstractTile* CreateFortressTile(int x, int y) const = 0;
        virtual Board::AbstractTile* CreateVillageTile(int x, int y) const = 0;
        virtual Board::AbstractTile* CreateTowerTile(int x, int y) const = 0;
        virtual Board::AbstractTile* CreateMillTile(int x, int y) const = 0;
        virtual Board::AbstractTile* CreateStartTile(int x, int y) const = 0;
        virtual Board::AbstractTile* CreateStopTile(int x, int y) const = 0;
    };

    class ConcreteFactory : public AbstractFactory{
    public:
        Board::AbstractTile* CreateFieldTile(int x, int y) const override{
            return new Board::Field(x, y);
        }

        Board::AbstractTile* CreateLakeTile(int x, int y) const override{
            return new Board::Lake(x, y);
        }

        Board::AbstractTile* CreateForestTile(int x, int y) const override{
            return new Board::Forest(x, y);
        }

        Board::AbstractTile* CreateRockTile(int x, int y) const override{
            return new Board::Rock(x, y);
        }

        Board::AbstractTile* CreateFortressTile(int x, int y) const override{
            return new Board::Fortress(x, y);
        }

        Board::AbstractTile* CreateVillageTile(int x, int y) const override{
            return new Board::Village(x, y);
        }

        Board::AbstractTile* CreateTowerTile(int x, int y) const override{
            return new Board::Tower(x, y);
        }

        Board::AbstractTile* CreateMillTile(int x, int y) const override{
            return new Board::Mill(x, y);
        }

        Board::AbstractTile* CreateStartTile(int x, int y) const override{
            return new Board::Start(x, y);
        }

        Board::AbstractTile* CreateStopTile(int x, int y) const override{
            return new Board::Stop(x, y);
        }
    };
}
#endif // ABSTRACTFACTORY_H
