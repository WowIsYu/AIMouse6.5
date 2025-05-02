#ifndef DIFFICULTY_H
#define DIFFICULTY_H

enum class Difficulty
{
    Low,
    Medium,
    High
};

struct DifficultySettings
{
    int rows;
    int cols;
    int blockSize;
    int wallWidth;
    int scale;
};

inline DifficultySettings getSettingsForDifficulty(Difficulty level)
{
    switch (level)
    {
    case Difficulty::Low:
        return {10, 6, 72, 5, 3};  // 比例大一点，格子少
    case Difficulty::Medium:
        return {15, 10, 48, 4, 2};
    case Difficulty::High:
        return {30, 20, 24, 2, 1};
    default:
        return {15, 10, 48, 4, 2};
    }
}

#endif // DIFFICULTY_H
