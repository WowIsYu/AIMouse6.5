#include "nagano.h"
#include "qdir.h"
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QCursor>
#include <QMetaEnum>
#include <QTimer>

Nagano::Nagano(QWidget *parent)
    : QWidget(parent),
    timer(new QTimer(this)),
    menu(new QMenu(this)),
    remindTimer(new QTimer(this)), // 添加一个新的定时器
    showReminder(false) // 初始化提示框显示状态
{
    setGeometry(100, 100, 200, 275);

    Qt::WindowFlags flags = windowFlags();
    flags |= Qt::Tool;
    flags |= Qt::WindowStaysOnTopHint;
    setWindowFlags(flags);
    hide();

    this->setWindowFlag(Qt::FramelessWindowHint);   //去除窗口边框
    this->setAttribute(Qt::WA_TranslucentBackground);       //背景透明

    this->installEventFilter(new DragFilter);


    connect(timer, &QTimer::timeout, [this]() {
        static int index = 0;   //记录显示动作的当前图片索引
        auto paths = this->action_map.value(this->cur_role_act);
        this->cur_role_pix=paths[index++%paths.size()];

        this->update();
    });


    connect(remindTimer, &QTimer::timeout, [this]() {
        showReminder = false;
        showActAnimation(RoleAct::Read);
        remindTimer->stop();
        update();
    });

    initMenu();

    loadRoleActRes();

    if (!this->action_map.isEmpty()) {
        this->cur_role_act = RoleAct::Read;
        this->cur_role_pix = this->action_map.value(this->cur_role_act).first();
    }

    showActAnimation(RoleAct::Read);
}

Nagano::~Nagano() {}

void Nagano::showActAnimation(RoleAct k)
{
    timer->stop();

    this->cur_role_act = k;

    timer->start(100);
}

void Nagano::onMenuTiggered(QAction *act)
{
    QMetaEnum me = QMetaEnum::fromType<RoleAct>();

    bool ok;
    int k = me.keyToValue(act->text().toStdString().c_str(), &ok);
    if (!ok)
        return;

    showActAnimation(static_cast<RoleAct>(k));
}

void Nagano::onReceiveResult(double val)
{
    this->val = val * 100;
    if (val < 40) {
        showActAnimation(RoleAct::Angry);
        showReminder = true;
        remindTimer->start(5000); // 显示3秒钟后恢复
    }
    update();
}

void Nagano::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(this->cur_role_pix);

    // 缩小图片
    QSize targetSize(150, 150); // 您想要的图片显示尺寸
    QPixmap scaledPix = pix.scaled(targetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // 计算图片绘制位置
    int pixX = (width() - scaledPix.width()) / 2;
    int pixY = (height() - scaledPix.height()) / 2;

    // 绘制缩小后的图片
    painter.drawPixmap(pixX, pixY, scaledPix);


    // 设置方框的位置和大小，靠近图片
    QRect rect(pixX, pixY - 20, scaledPix.width(), 30); // 调整 y 坐标让方框更靠近图片

    // 设置深绿色的边框和淡绿色的背景
    QPen pen(QColor(0, 100, 0)); // 深绿色边框
    painter.setPen(pen);

    QBrush brush(QColor(144, 238, 144, 150)); // 淡绿色背景，带透明度
    painter.setBrush(brush);

    // 绘制具有指定颜色和圆角的矩形方框
    painter.drawRoundedRect(rect, 10, 10); // 圆角半径为 10

    // 设置字体和文本颜色
    QFont font = painter.font();
    font.setPointSize(12); // 设置字体大小
    painter.setFont(font);
    painter.setPen(Qt::black); // 设置文本颜色为黑色

    // 在方框中居中绘制文本
    QString text = QString::number(val, 'f', 2); // 使用 val 绘制值
    painter.drawText(rect, Qt::AlignCenter, text);


    // 如果需要显示提醒框
    if (showReminder) {
        QString reminderText = "注意力有点低哦，请不要走神!";

        QFontMetrics metrics(painter.font());
        int maxTextWidth = scaledPix.width(); // 设定最大宽度为图片宽度

        // 将文本分成多行
        QStringList lines;
        QString currentLine;
        for (const QChar &ch : reminderText) {
            currentLine += ch;
            if (metrics.horizontalAdvance(currentLine) > maxTextWidth) {
                lines.append(currentLine);
                currentLine.clear();
            }
        }
        if (!currentLine.isEmpty()) {
            lines.append(currentLine);
        }

        int reminderHeight = lines.size() * metrics.height() + 10; // 根据行数调整高度

        QRect reminderRect(pixX, pixY + scaledPix.height() + 10, maxTextWidth, reminderHeight);
        QBrush reminderBrush(QColor(255, 228, 181, 200)); // 浅色背景带透明度
        painter.setBrush(reminderBrush);
        painter.drawRoundedRect(reminderRect, 10, 10);

        QFont reminderFont = painter.font();
        reminderFont.setPointSize(10);
        painter.setFont(reminderFont);
        painter.setPen(Qt::black);

        int lineHeight = metrics.height();
        for (int i = 0; i < lines.size(); ++i) {
            QRect lineRect(reminderRect.x(), reminderRect.y() + i * lineHeight, reminderRect.width(), lineHeight);
            painter.drawText(lineRect, Qt::AlignCenter, lines[i]);
        }
    }
}

void Nagano::contextMenuEvent(QContextMenuEvent *event)
{
    this->menu->popup(QCursor::pos());
}

void Nagano::loadRoleActRes()
{
    auto addRes = [this](RoleAct k, QString path, int count) {
        QList<QString> paths;
        char buf[260];
        for (int i = 1; i <= count; ++i) {
            memset(buf, 0, sizeof(buf));
            // 格式化（数据，char*, ）
            sprintf(buf, path.toStdString(). c_str(), i);
            paths.append(QString::fromUtf8(buf));
        }
        action_map.insert(k, paths);
    };
    //:/NaganoAction/angry/2.png
    addRes(RoleAct::Angry, ":/NaganoAction/angry/%d.png", 21);
    addRes(RoleAct::Happy, ":/NaganoAction/happy/%d.png", 17);
    addRes(RoleAct::Normal, ":/NaganoAction/normal/%d.png", 16);
    addRes(RoleAct::Read, ":/NaganoAction/read/%d.png", 8);
}

void Nagano::initMenu()
{
    menu->addAction(tr("Angry"));
    menu->addAction(tr("Happy"));
    menu->addAction(tr("Normal"));
    menu->addAction(tr("Read"));

    QAction* act = new QAction(tr("Hide"));
    connect(act, &QAction::triggered, [this](){
        this->setVisible(false);
    });
    menu->addAction(act);

    connect(this->menu, &QMenu::triggered, this, &Nagano::onMenuTiggered);
}
