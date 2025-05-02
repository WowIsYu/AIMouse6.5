#ifndef NAGANO_H
#define NAGANO_H

#include "qevent.h"
#include <QWidget>
#include <QMap>
#include <QList>
#include <QUrl>
#include <QTimer>
#include <QEvent>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QMenu>
#include <QPaintEvent>

class QPaintEvent;

namespace  Act {
Q_NAMESPACE

enum RoleAct{
    Angry,
    Happy,
    Read,
    Normal
};

Q_ENUM_NS(RoleAct)
}

using namespace Act;

class Nagano : public QWidget
{
    Q_OBJECT

public:
    Nagano(QWidget *parent = nullptr);
    ~Nagano();

public:
    void showActAnimation(RoleAct k);

public slots:
    void onMenuTiggered(QAction* act);
    void onReceiveResult(double val);

protected:
    void paintEvent(QPaintEvent *event) override;
    void contextMenuEvent(QContextMenuEvent* event) override;

private:
    void loadRoleActRes();
    void initMenu();
private:
    QMap<RoleAct, QList<QString>> action_map;
    QTimer *timer;
    RoleAct cur_role_act;
    QString cur_role_pix;
    QMenu* menu;

    double val = 0;

    QTimer *remindTimer;  // 添加提醒定时器
    bool showReminder = false;  // 控制是否显示提醒框
};

class DragFilter: public QObject {
public:
    bool eventFilter(QObject *obj, QEvent *event) {
        auto w = dynamic_cast<QWidget*>(obj);
        if (!w)
            return false;

        if (event->type() == QEvent::MouseButtonPress) {
            auto e = dynamic_cast<QMouseEvent*>(event);
            if (e) {
                pos=e->pos();
            }
        } else if (event->type() == QEvent::MouseMove) {
            auto e = dynamic_cast<QMouseEvent*>(event);
            if (e) {
                if (e->buttons() & Qt::MouseButton::LeftButton) {
                    w->move(e->globalPosition().toPoint()-pos);
                }
            }
        }
        return QObject::eventFilter(obj, event);
    }
private:
    QPoint pos;
};

#endif // NAGANO_H
