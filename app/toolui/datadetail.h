#ifndef DATADETAIL_H
#define DATADETAIL_H

#include <QWidget>

namespace Ui {
class DataDetail;
}

class DataDetail : public QWidget
{
    Q_OBJECT

public:
    explicit DataDetail(QWidget *parent = nullptr);
    ~DataDetail();

private:
    Ui::DataDetail *ui;
};

#endif // DATADETAIL_H
