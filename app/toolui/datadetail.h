#ifndef DATADETAIL_H
#define DATADETAIL_H

#include <QWidget>
#include <qabstractitemmodel.h>

namespace Ui {
class DataDetail;
}

class DataDetail : public QWidget
{
    Q_OBJECT

public:
    explicit DataDetail(QWidget *parent = nullptr);
    ~DataDetail();

    void setModel(QAbstractItemModel *model);

private:
    Ui::DataDetail *ui;
};

#endif // DATADETAIL_H
