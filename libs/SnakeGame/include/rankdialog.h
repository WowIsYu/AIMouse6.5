#ifndef RANKDIALOG_H
#define RANKDIALOG_H

#include <QDialog>

#include <QFile>
#include <QTextStream>

namespace Ui {
class RankDialog;
}

class RankDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RankDialog(QWidget *parent = nullptr, QString rankFile = QString());
    ~RankDialog();
    void rankAndShow();

private:
    Ui::RankDialog *ui;
    QString rankFile;
};

#endif // RANKDIALOG_H
