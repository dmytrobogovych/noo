#include "mainwindow.h"
#include <QApplication>
#include <QLayout>
#include <QFileInfo>
#include <QDir>
#include "settings.h"
#include "helper.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    helper::theme::applyCurrent(Settings::instance());

    QFont f = app.font();
    f.setFamily("Monaco");
    f.setPointSize(16);
    app.setFont(f);

    // Path to database.
    QString path = Settings::instance().getDatabasePath();


    QString folder = QFileInfo(path).absoluteDir().path();
    Storage::instance().setPath(path);

    MainWindow w;
    w.layout()->invalidate();

    w.setAttribute(Qt::WA_WState_ExplicitShowHide, false);
    w.setAttribute(Qt::WA_WState_Hidden, true);
    w.setWindowIcon(MainWindow::getAppIcon());
    w.show();

    return app.exec();
}
