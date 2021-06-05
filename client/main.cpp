#include "mainwindow.h"
#include <QApplication>
#include <QLayout>
#include <QFileInfo>
#include <QDir>
#include "settings.h"
#include "helper.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    helper::theme::applyCurrent(Settings::instance());

    // Path to database.
    QString path = Settings::instance().getDatabasePath();


    QString folder = QFileInfo(path).absoluteDir().path();
    Storage::instance().setPath(path);

    MainWindow w;
    w.layout()->invalidate();

    w.setAttribute(Qt::WA_WState_ExplicitShowHide, false);
    w.setAttribute(Qt::WA_WState_Hidden, true);
    w.show();

    return a.exec();
}
