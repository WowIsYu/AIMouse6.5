#ifndef MARKINGTESTER_H
#define MARKINGTESTER_H

#include <QDialog>
#include <QThread>

namespace Ui {
class MarkingTester;
}

class MarkingTester : public QDialog
{
    Q_OBJECT

public:
    explicit MarkingTester(QWidget *parent = nullptr);
    ~MarkingTester();

private slots:
    void on_manualMarkBtn_clicked();        ///按下手动打标按钮
signals:
    /**
     * @brief emitManualMarking  手动打标信号
     */
    void emitManualMarking(int);

private:
    Ui::MarkingTester *ui;
    int m_markflag = 0;                    ///标记信号
private:
    class MyThread : public QThread{

    };
};

#endif // MARKINGTESTER_H
