#ifndef CONNECTDB_WIDGET_H
#define CONNECTDB_WIDGET_H

#include <QWidget>

namespace Ui {
class ConnectDbWidget;
}

class ConnectDbWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectDbWidget(QWidget *parent = nullptr);
    ~ConnectDbWidget();

private:
    Ui::ConnectDbWidget *ui;
};

#endif // CONNECTDB_WIDGET_H
