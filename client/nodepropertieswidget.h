#ifndef NODEPROPERTIESWIDGET_H
#define NODEPROPERTIESWIDGET_H

#include <QWidget>
#include "task.h"

namespace Ui {
class NodePropertiesWidget;
}

class NodePropertiesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NodePropertiesWidget(QWidget *parent = nullptr);
    ~NodePropertiesWidget();

    void setTask(const PTask& task);
    PTask task() const;

private:
    Ui::NodePropertiesWidget *ui;

    void refresh();
    PTask mTask;
};

#endif // NODEPROPERTIESWIDGET_H
