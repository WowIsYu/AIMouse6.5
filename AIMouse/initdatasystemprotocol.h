#ifndef INITDATASYSTEMPROTOCOL_H
#define INITDATASYSTEMPROTOCOL_H
#pragma execution_character_set("utf-8")
#include <QDialog>
#include "HMultiControlSDK/include/dataset.h"

namespace Ui {
class InitDataSystemProtocol;
}

class InitDataSystemProtocol : public QDialog
{
    Q_OBJECT
public:
    explicit InitDataSystemProtocol(QWidget *parent = nullptr);
    ~InitDataSystemProtocol();

signals:
    void button_Clicked(int arg1,int arg2);
    void notifyClicked(hnnk::DSNETTYPE netPro, hnnk::DSPROTOCOLTYPE dataPro);

private slots:
    void init_Argv();
    void on_buttonBox_accepted();

private:
    Ui::InitDataSystemProtocol *ui;
};

#endif // INITDATASYSTEMPROTOCOL_H
