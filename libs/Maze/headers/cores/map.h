#ifndef __CORES_MAP_H__
#define __CORES_MAP_H__

#include <QRandomGenerator>
#include <QList>
#include <QStack>
#include <QQueue>
#include <QVector>

#include "cores/points.h"
#include "utils/constants.h"

using MapBlock = IntPoint;

class MapUnit
{
    private:
        int previousX;
        int previousY;
        int stepCount;

    private:
        bool wall[MapProperties::WALL_COUNT];
        bool visited;

    public:
        void reset();
        void removeWall(int direct);

    public:
        void setPreviousX(int previousX);
        void setPreviousY(int previousY);
        void setStepCount(int stepCount);
        void setVisited(bool visited);

    public:
        int getPreviousX();
        int getPreviousY();
        int getStepCount();

    public:
        bool hasWall(int direct);
        bool isVisited();
};

class Map
{
    private:
        // MapUnit units[MapProperties::ROWS][MapProperties::COLS];
        std::vector<std::vector<MapUnit>> units;

    private:
        void setPrevious(int x1, int y1, int x2, int y2);
        void setVisited(int x, int y);
        void removeWall(int x1, int y1, int x2, int y2);

    private:
        int getPreviousX(int x, int y);
        int getPreviousY(int x, int y);

    private:
        QList<MapBlock> getNeighbors(int x, int y);

    private:
        bool isInRange(int x, int y);
        bool hasWall(int x1, int y1, int x2, int y2);

    public:
        bool hasWall(int x, int y, int direct);
        void reset();
        void generateMaze();
        //初始化units
        // Map() : units(MapProperties::ROWS, std::vector<MapUnit>(MapProperties::COLS)) {}

    public:
        QList<MapBlock> getWayBlocks(int startX, int startY);
        QList<MapBlock> getWayBlocksAStar(int startX, int startY);
        int heuristic(int x1, int y1, int x2, int y2);

    public:
        Map() {
            // 根据当前 MapProperties 的值初始化 vector
            resize(MapProperties::ROWS, MapProperties::COLS);
        }

        // 添加 resize 方法
        void resize(int rows, int cols) {
            units.resize(rows);
            for (auto& row : units) {
                row.resize(cols);
            }
        }
};
#endif
