#include "cores/map.h"

#include <queue>
#include <vector>
#include <functional>

struct Node
{
    int x, y;   // 坐标
    int gCost;  // 从起点到当前点的代价（步数）
    int fCost;  // gCost + hCost：总代价

    //小顶堆，优先弹出f值比较小的，(std::greater 会调用它)
    bool operator>(const Node& other) const
    {
        return fCost > other.fCost;
    }
};


void MapUnit::reset()
{
    memset(wall, true, sizeof(wall));

    this->previousX = 0;
    this->previousY = 0;
    this->stepCount = 0;

    this->visited = false;
}

void MapUnit::setVisited(bool visited)
{
    this->visited = visited;
}

void MapUnit::setPreviousX(int previousX)
{
    this->previousX = previousX;
}

void MapUnit::setPreviousY(int previousY)
{
    this->previousY = previousY;
}

void MapUnit::setStepCount(int stepCount)
{
    this->stepCount = stepCount;
}

void MapUnit::removeWall(int direct)
{
    this->wall[direct] = false;
}

int MapUnit::getPreviousX()
{
    return previousX;
}

int MapUnit::getPreviousY()
{
    return previousY;
}

int MapUnit::getStepCount()
{
    return stepCount;
}

bool MapUnit::hasWall(int directIndex)
{
    return wall[directIndex];
}

bool MapUnit::isVisited()
{
    return visited;
}

void Map::reset()
{
    for (size_t x = 0; x < units.size(); x++) {
        for (size_t y = 0; y < units[x].size(); y++) {
            units[x][y].reset();
        }
    }
}

bool Map::isInRange(int x, int y)
{
    return x >= 0 && x < static_cast<int>(units.size()) &&
           y >= 0 && y < static_cast<int>(units[x].size());
}

QList<MapBlock> Map::getNeighbors(int x, int y)
{
    QList<MapBlock> neighbors;

    if (isInRange(x + 1, y) && !units[x + 1][y].isVisited())
    {
        neighbors.append(MapBlock(x + 1, y));
    }
    if (isInRange(x - 1, y) && !units[x - 1][y].isVisited())
    {
        neighbors.append(MapBlock(x - 1, y));
    }
    if (isInRange(x, y + 1) && !units[x][y + 1].isVisited())
    {
        neighbors.append(MapBlock(x, y + 1));
    }
    if (isInRange(x, y - 1) && !units[x][y - 1].isVisited())
    {
        neighbors.append(MapBlock(x, y - 1));
    }
    return neighbors;
}

void Map::setVisited(int x, int y)
{
    units[x][y].setVisited(true);
}

bool Map::hasWall(int x1, int y1, int x2, int y2)
{
    if (x2 == x1 && y2 < y1)
    {
        return units[x1][y1].hasWall(Directs::UP);
    }
    else if (x2 == x1 && y2 > y1)
    {
        return units[x1][y1].hasWall(Directs::DOWN);
    }
    else if (x2 < x1 && y2 == y1)
    {
        return units[x1][y1].hasWall(Directs::LEFT);
    }
    else if (x2 > x1 && y2 == y1)
    {
        return units[x1][y1].hasWall(Directs::RIGHT);
    }
    return true;
}

void Map::removeWall(int x1, int y1, int x2, int y2)
{
    if (x2 == x1 && y2 < y1)
    {
        units[x1][y1].removeWall(Directs::UP);
        units[x2][y2].removeWall(Directs::DOWN);
    }
    else if (x2 == x1 && y2 > y1)
    {
        units[x1][y1].removeWall(Directs::DOWN);
        units[x2][y2].removeWall(Directs::UP);
    }
    else if (x2 < x1 && y2 == y1)
    {
        units[x1][y1].removeWall(Directs::LEFT);
        units[x2][y2].removeWall(Directs::RIGHT);
    }
    else if (x2 > x1 && y2 == y1)
    {
        units[x1][y1].removeWall(Directs::RIGHT);
        units[x2][y2].removeWall(Directs::LEFT);
    }
}

void Map::setPrevious(int x1, int y1, int x2, int y2)
{
    units[x2][y2].setPreviousX(x1);
    units[x2][y2].setPreviousY(y1);
    units[x2][y2].setStepCount(units[x1][y1].getStepCount() + 1);
}

int Map::getPreviousX(int x, int y)
{
    return units[x][y].getPreviousX();
}

int Map::getPreviousY(int x, int y)
{
    return units[x][y].getPreviousY();
}

void Map::generateMaze()
{
    QStack<MapBlock> blockStack;

    int currentX = QRandomGenerator::global()->bounded(units.size());
    int currentY = QRandomGenerator::global()->bounded(units[0].size()); // 假设所有行等宽

    setVisited(currentX, currentY);
    blockStack.push(MapBlock(currentX, currentY));

    while (!blockStack.isEmpty())
    {
        QList<MapBlock> neighbors = getNeighbors(currentX, currentY);

        if (neighbors.isEmpty())
        {
            MapBlock currentBlock = blockStack.pop();

            currentX = currentBlock.getX();
            currentY = currentBlock.getY();

            continue;
        }
        MapBlock nextBlock = neighbors[QRandomGenerator::global()->bounded(neighbors.length())];

        int nextX = nextBlock.getX();
        int nextY = nextBlock.getY();

        removeWall(currentX, currentY, nextX, nextY);
        currentX = nextX;
        currentY = nextY;

        setVisited(nextX, nextY);
        blockStack.push(nextBlock);
    }
}

bool Map::hasWall(int x, int y, int direct)
{
    return units[x][y].hasWall(direct);
}

QList<MapBlock> Map::getWayBlocks(int startX, int startY)
{
    QQueue<MapBlock> blockQueue;

    for (size_t x = 0; x < units.size(); x++)
    {
        for (size_t y = 0; y < units[0].size(); y++)
        {
            units[x][y].setVisited(false);
            units[x][y].setStepCount(0);
        }
    }
    int currentX = startX;
    int currentY = startY;

    setVisited(currentX, currentY);
    blockQueue.enqueue(MapBlock(currentX, currentY));

    while (!blockQueue.isEmpty())
    {
        MapBlock currentBlock = blockQueue.front();

        currentX = currentBlock.getX();
        currentY = currentBlock.getY();

        if (currentX == static_cast<int>(units.size() - 1) && currentY == static_cast<int>(units[0].size() - 1))
        {
            break;
        }
        for (MapBlock& neighborBlock : getNeighbors(currentX, currentY))
        {
            int neighborX = neighborBlock.getX();
            int neighborY = neighborBlock.getY();

            if (!hasWall(currentX, currentY, neighborX, neighborY))
            {
                blockQueue.enqueue(neighborBlock);

                setVisited(neighborX, neighborY);
                setPrevious(currentX, currentY, neighborX, neighborY);
            }
        }
        blockQueue.dequeue();
    }
    QList<MapBlock> wayBlocks;

    for (int step = units[currentX][currentY].getStepCount(); step >= 0; step--)
    {
        wayBlocks.append(MapBlock(currentX, currentY));

        int previousX = getPreviousX(currentX, currentY);
        int previousY = getPreviousY(currentX, currentY);

        currentX = previousX;
        currentY = previousY;
    }
    return wayBlocks;
}

QList<MapBlock> Map::getWayBlocksAStar(int startX, int startY)
{
    //初始化
    for (size_t x = 0; x < units.size(); x++)
    {
        for (size_t y = 0; y < units[0].size(); y++)
        {
            //false表示还没被访问过
            units[x][y].setVisited(false);
            units[x][y].setStepCount(INT_MAX);  // 初始化为最大步数
        }
    }

    //设置终点
    int goalX = units.size() - 1;
    int goalY = units[0].size() - 1;


    //初始化A*的OPEN SET
    // std::priority_queue: 优先队列容器，默认是最大堆
    // <队列中存储的元素类型， 用来存储容器的底层容器, 使用“小根堆”>
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openSet;
    openSet.push({startX, startY, 0, heuristic(startX, startY, goalX, goalY)});

    //标记起点为已经访问
    setVisited(startX, startY);
    units[startX][startY].setStepCount(0);

    while (!openSet.empty())
    {
        //从 openSet 中取出 f 最小的节点
        Node current = openSet.top();
        openSet.pop();

        //到达终点时，退出
        if (current.x == goalX && current.y == goalY)
        {
            break;
        }

        //遍历邻居， 上下左右
        for (MapBlock& neighbor : getNeighbors(current.x, current.y))
        {
            int nx = neighbor.getX();
            int ny = neighbor.getY();

            if (!hasWall(current.x, current.y, nx, ny))
            {
                //更新G值和f值
                int tentativeG = units[current.x][current.y].getStepCount() + 1;

                //如果邻居未被访问，或者这次走法更优秀，就更新该点状态
                if (!units[nx][ny].isVisited() || tentativeG < units[nx][ny].getStepCount())
                {
                    units[nx][ny].setStepCount(tentativeG);
                    int f = tentativeG + heuristic(nx, ny, goalX, goalY);

                    openSet.push({nx, ny, tentativeG, f});

                    setVisited(nx, ny);
                    setPrevious(current.x, current.y, nx, ny);
                }
            }
        }
    }

    // 构造路径
    QList<MapBlock> wayBlocks;
    int currentX = goalX, currentY = goalY;

    if (!units[currentX][currentY].isVisited())
    {
        return {};  // 无路径
    }

    for (int step = units[currentX][currentY].getStepCount(); step >= 0; step--)
    {
        wayBlocks.append(MapBlock(currentX, currentY));
        int previousX = getPreviousX(currentX, currentY);
        int previousY = getPreviousY(currentX, currentY);
        currentX = previousX;
        currentY = previousY;
    }

    // std::reverse(wayBlocks.begin(), wayBlocks.end());  // 起点到终点顺序
    return wayBlocks;
}



int Map::heuristic(int x1, int y1, int x2, int y2)
{
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

