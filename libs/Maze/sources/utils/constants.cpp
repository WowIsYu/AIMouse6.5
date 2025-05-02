#include "utils/constants.h"
#include "utils/difficulty.h"

// 静态变量初始化
int MapProperties::BORDER = 16;
int MapProperties::ROWS = 15;
int MapProperties::COLS = 10;
int MapProperties::BLOCK_SIZE = 48;
int MapProperties::WALL_WIDTH = 4;
int MapProperties::VISIBLE_RADIUS = 150;

void MapProperties::applyDifficulty(const DifficultySettings& settings)
{
    ROWS = settings.rows;
    COLS = settings.cols;
    BLOCK_SIZE = settings.blockSize;
    WALL_WIDTH = settings.wallWidth;
}
