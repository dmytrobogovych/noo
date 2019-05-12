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
    explicit ConnectDbWidget(const QString& msg = QString(), QWidget *parent = nullptr);
    ~ConnectDbWidget();

private:
    Ui::ConnectDbWidget *ui;

public slots:
    void onOk();
    void onCancel();

signals:
    void passwordEntered(const QString& password);
    void cancelled();
};

#endif // CONNECTDB_WIDGET_H
