#ifndef BROWSERWIDGET_H
#define BROWSERWIDGET_H

#include <QWidget>

namespace Ui {
class BrowserWidget;
}

class BrowserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BrowserWidget(QWidget *parent = 0);
    ~BrowserWidget();

private:
    Ui::BrowserWidget *ui;

public slots:
    void onNewRootTask();
    void onNewTask();
    void onNewSibling();
    void onMoveUp();
    void onMoveDown();
    void onRenameTask();
    void onDeleteTask();

};

#endif // BROWSERWIDGET_H
