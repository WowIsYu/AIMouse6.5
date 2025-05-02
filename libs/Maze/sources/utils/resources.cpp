#include "utils/resources.h"

GameResources::GameResources()
{
    playerPixmap = new QPixmap(":/images/player.png");
    finishPixmap = new QPixmap(":/images/finish.png");

    for (int index = 0; index < MapProperties::WALL_COUNT; index++)
    {
        wallPixmaps[index] = new QPixmap(QString(":/images/wall_%1.png").arg(index));
    }
    wayPixmap = new QPixmap(":/images/way.png");
}

GameResources::~GameResources()
{
    delete playerPixmap;
    delete finishPixmap;

    for (int index = 0; index < MapProperties::WALL_COUNT; index++)
    {
        delete wallPixmaps[index];
    }
    delete wayPixmap;
}


const QPixmap* GameResources::getWayPixmap()
{
    return scaledPixmap(wayPixmap);
}

const QPixmap* GameResources::getFinishPixmap()
{
    return scaledPixmap(finishPixmap);
}

const QPixmap* GameResources::getPlayerPixmap()
{
    return scaledPixmap(playerPixmap);
}

const QPixmap* GameResources::getWallPixmap(int index)
{
    return scaledPixmap(wallPixmaps[index]);
}



void GameResources::setScale(int s)
{
    this->scale = s;
}

QPixmap* GameResources::scaledPixmap(QPixmap* original)
{
    if (scale == 1.0f) return original;

    // 返回缩放后的 QPixmap
    return new QPixmap(original->scaled(original->width() * scale, original->height() * scale, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

