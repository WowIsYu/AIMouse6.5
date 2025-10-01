#include "vmousemainwindow.h"
#include "ui_vmousemainwindow.h"
#include <QMouseEvent>
#include <QTimer>
#include <QDebug>
#include <windows.h>
#pragma comment(lib,"user32")

#include <QMenuBar>


VMouseMainWindow::VMouseMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VMouseMainWindow)
{
    ui->setupUi(this);

    // 获取当前窗口的标志
    Qt::WindowFlags flags = windowFlags();

    // 将Qt::FramelessWindowHint标志添加到flags中，这会使窗口没有边框
    flags |= Qt::FramelessWindowHint;

    // 添加Qt::WindowSystemMenuHint标志，为窗口提供一个系统菜单（通常是窗口左上角的菜单，包含最小化、最大化、关闭等选项）
    flags |= Qt::WindowSystemMenuHint;          // 为窗口修饰一个窗口菜单系统

    // 添加Qt::WindowMinMaxButtonsHint标志，为窗口添加最大化和最小化按钮（尽管没有边框，但可能通过其他方式显示这些按钮）
    flags |= Qt::WindowMinMaxButtonsHint;       // 为窗口添加最大化和最小化按钮

    // 添加Qt::Tool标志，使窗口表现为一个工具窗口。工具窗口通常没有任务栏图标，并且可能在某些情况下有不同的行为
    flags |= Qt::Tool;

    // 添加Qt::WindowStaysOnTopHint标志，使窗口总是保持在其他窗口之上
    flags |= Qt::WindowStaysOnTopHint;

    // 添加Qt::X11BypassWindowManagerHint标志（特定于X11窗口系统），这可能会绕过窗口管理器的某些控制，允许更直接的控制窗口行为
    // 注意：这个标志的使用可能会依赖于特定的平台（如Linux上的X11），并且可能会带来不可预见的行为
    flags |= Qt::X11BypassWindowManagerHint;

    // 使用更新后的flags设置窗口的标志
    setWindowFlags(flags);

    this->setAttribute(Qt::WA_TranslucentBackground, true);
    m_width = GetSystemMetrics(SM_CXCURSOR);//
    m_height = GetSystemMetrics(SM_CYCURSOR);//
    //禁止窗口调节大小（右下角拉伸）
    //32 20
    m_width=m_width*20/32.0;
    m_height=m_height*20/32.0;
    setFixedSize(m_width, m_height);
    show();

    m_pTimer = new QTimer();
    //m_pTimer->start(300); //程序每隔300毫秒置顶一次
    connect(m_pTimer, &QTimer::timeout, [=]{
        //        SetWindowPos((HWND)this->winId(),HWND_TOPMOST,this->pos().x(),this->pos().y(),this->width(),this->height(), SWP_NOACTIVATE | SWP_SHOWWINDOW);
        QScreen* screen = QApplication::primaryScreen();
        qreal scaleFactor = screen->devicePixelRatio();
        SetWindowPos((HWND)this->winId()
                     ,HWND_TOPMOST
                     ,this->pos().x()* scaleFactor
                     ,this->pos().y()* scaleFactor
                     ,this->width()* scaleFactor,this->height()* scaleFactor
                     , SWP_NOACTIVATE | SWP_SHOWWINDOW);

    });


    //setStyleSheet("background-color:red");

    // 创建一个QLabel来显示图片
    backgroundLabel = new QLabel(this);
    backgroundLabel->setPixmap(QPixmap(":/img/mouse_pointer_red.png")); // 使用资源路径或文件路径
    backgroundLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); // 使QLabel能够扩展
    backgroundLabel->setScaledContents(true); // 使图片适应QLabel的大小（如果图片和QLabel大小不同）
    // 将QLabel设置为central widget
    setCentralWidget(backgroundLabel);

    //ShowWindow((HWND)this->winId(), SW_HIDE);

}

VMouseMainWindow::~VMouseMainWindow()
{
    m_pTimer->stop();

    delete m_pTimer;
    delete ui;
}

bool VMouseMainWindow::nativeEvent(const QByteArray &eventType, void *message,long long *result)
{
    MSG* msg = (MSG*)message;
    switch(msg->message)
    {
    case 10001:
        exit(0);
        return true;
    case 10002:
        m_pTimer->stop();

        this->setFixedSize(1,1);
        ShowWindow((HWND)this->winId(), SW_HIDE);
        return true;
    case 10003:
        this->setFixedSize(20,20);
        ShowWindow((HWND)this->winId(), SW_SHOW);
        m_pTimer->start(300);
        return true;
    }

    return false;
}

void VMouseMainWindow::setBgColor(QColor color)
{
    if(color==Qt::red){
        //this->setStyleSheet("border-image: url(:/img/mouse_pointer_red.png);");
        //this->setStyleSheet("background-color:red");
            backgroundLabel->setPixmap(QPixmap(":/img/mouse_pointer_red.png")); // 使用资源路径或文件路径
    }
    if(color==Qt::green){
        backgroundLabel->setPixmap(QPixmap(":/img/mouse_pointer_green.png")); // 使用资源路径或文件路径
    }
    if(color==Qt::white){
        backgroundLabel->setPixmap(QPixmap(":/img/mouse_pointer.png")); // 使用资源路径或文件路径
    }
    if(color==Qt::yellow){
        backgroundLabel->setPixmap(QPixmap(":/img/mouse_pointer_yellow.png")); // 使用资源路径或文件路径
    }
}

void VMouseMainWindow::setVMouseVisible(bool visible)
{
    this->setVisible(visible);
    if(visible){
        this->setMinimumHeight(m_height);
        this->setMaximumHeight(m_height);
        this->setMaximumWidth(m_width);
        this->setMinimumWidth(m_width);
    }else{
        this->setMinimumHeight(0);
        this->setMaximumHeight(0);
        this->setMaximumWidth(0);
        this->setMinimumWidth(0);
    }
}

void VMouseMainWindow::showmouse(bool flag)
{
    if(flag){
        if(!m_pTimer->isActive()){
            m_pTimer->start(300);
            ShowWindow((HWND)this->winId(), SW_SHOW);
        }
    }else{
        if(m_pTimer->isActive()){
            m_pTimer->stop();
            ShowWindow((HWND)this->winId(), SW_HIDE);
        }
    }
}

void VMouseMainWindow::mousePressEvent(QMouseEvent *event)
{
    m_lastPos = event->globalPosition().toPoint();
    isPressedWidget = true; // 当前鼠标按下的即是QWidget而非界面上布局的其它控件
}

void VMouseMainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(isPressedWidget)
    {
        //qDebug() <<"isPressed" << event->globalPos();
        this->move(this->x() + (event->globalPosition().x() - m_lastPos.x()),
                   this->y() + (event->globalPosition().y() - m_lastPos.y()));
    }

    m_lastPos = event->globalPosition().toPoint();
}

void VMouseMainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    // 其实这里的mouseReleaseEvent函数可以不用重写
    m_lastPos = event->globalPosition().toPoint();
    isPressedWidget = false; // 鼠标松开时，置为false
}


void VMouseMainWindow::simulateMouseClick(double x, double y)
{
    //记录原始鼠标位置
    POINT originalPos;
    GetCursorPos(&originalPos);

    // 将控件局部坐标 (0, 0) 转换为全局坐标，即控件的左上角
    QPoint widgetPos = this->mapToGlobal(QPoint(0, 0));

    // 将鼠标移动到控件的左上角
    SetCursorPos(widgetPos.x(), widgetPos.y());

    // 如果希望点击特定位置 (x, y)，可以对 widgetPos 进行偏移
     SetCursorPos(widgetPos.x() + x / 2, widgetPos.y() + y / 2);

    // 获取屏幕的宽高
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN;
    input.mi.dx = y;
    input.mi.dy = x;

    // 模拟鼠标左键按下
    if (SendInput(1, &input, sizeof(INPUT)) == 0) {
        qDebug() << "SendInput failed with error code:" << GetLastError();
    }

    // 模拟鼠标左键释放
    input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP;
    if (SendInput(1, &input, sizeof(INPUT)) == 0) {
        qDebug() << "SendInput failed with error code:" << GetLastError();
    }

    //恢复原始鼠标位置
    SetCursorPos(originalPos.x, originalPos.y);

}
