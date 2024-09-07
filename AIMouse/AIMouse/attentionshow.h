#ifndef ATTENTIONSHOW_H
#define ATTENTIONSHOW_H

#include <QMainWindow>

namespace Ui {
class AttentionShow;
}

class AttentionShow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AttentionShow(QWidget *parent = nullptr);
    ~AttentionShow();
public slots:
    void onReceiveResult(double val);
private:
    Ui::AttentionShow *ui;
};

#endif // ATTENTIONSHOW_H
