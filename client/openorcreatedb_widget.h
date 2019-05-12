#ifndef OPENORCREATEDB_WIDGET_H
#define OPENORCREATEDB_WIDGET_H

#include <QWidget>

namespace Ui {
class OpenOrCreateDbWidget;
}

class OpenOrCreateDbWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OpenOrCreateDbWidget(QWidget *parent = nullptr);
    ~OpenOrCreateDbWidget();

private:
    Ui::OpenOrCreateDbWidget *ui;

    QString mDbPath;
    void handleEnteredPasswords();
    void askForDatabase();

signals:
    void databaseChanged(const QString& path);
    void passwordEntered(const QString& password);
};

#endif // OPENORCREATEDB_WIDGET_H
