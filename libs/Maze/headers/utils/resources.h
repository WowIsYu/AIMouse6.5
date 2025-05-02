#ifndef __UTILS_RESOURCES_H__
#define __UTILS_RESOURCES_H__

#include <QPixmap>

#include "utils/constants.h"

class GameResources
{
    private:
        QPixmap* finishPixmap;
        QPixmap* playerPixmap;
        QPixmap* wayPixmap;
        QPixmap* wallPixmaps[MapProperties::WALL_COUNT];

        int scale = 2;

        QPixmap* scaledPixmap(QPixmap* original);       //缩放Pixmap的方法

    public:
        GameResources();
        ~GameResources();

    public:
        const QPixmap* getFinishPixmap();
        const QPixmap* getPlayerPixmap();
        const QPixmap* getWayPixmap();
        const QPixmap* getWallPixmap(int directIndex);

        void setScale(int s);
};
#endif
