#include "config.h"
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

    app.setApplicationName(APPNAME);
    auto& settings = Settings::instance();
    QFont f;
    if (settings.data().count(KEY_APP_FONT) > 0)
    {
        if (f.fromString(settings.data()[KEY_APP_FONT].toString()))
            app.setFont(f);
    }

    // Path to database.
    QString path = settings.getDatabasePath();

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
