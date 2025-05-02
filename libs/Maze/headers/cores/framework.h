#ifndef __CORES_FRAMEWORK_H__
#define __CORES_FRAMEWORK_H__

#include <QList>

#include "cores/map.h"
#include "cores/player.h"
#include "utils/difficulty.h"

class GameFramework
{
    private:
        Map* map;
        Player* player;
        Difficulty l;

    private:
        bool tracked;
        bool fogMode;
        bool gameover;

    public:
        GameFramework();
        ~GameFramework();

    public:
        void playerMove(QList<int>& directPriority);
        void restart();
        void switchFogMode();
        void setLevel(Difficulty l);

    public:
        QList<MapBlock> getWayBlocks();

    public:
        int getPlayerX();
        int getPlayerY();
        Difficulty getLevel();

    public:
        bool hasTracked();
        bool isFogMode();
        bool isPlaying();
        bool isGameover();
        bool isMapHaveWall(int x, int y, int direct);
        void setMapSize(int rows, int cols);
        void setPlayerSpeed(int scale);
};
#endif
