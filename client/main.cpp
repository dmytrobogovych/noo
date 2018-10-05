#include "mainwindow.h"
#include <QApplication>
#include <QLayout>
#include "settings.h"
#include "helper.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ThemeHelper::applyCurrentTheme(Settings::instance());

    MainWindow w;
    w.layout()->invalidate();

    w.setAttribute(Qt::WA_WState_ExplicitShowHide, false);
    w.setAttribute(Qt::WA_WState_Hidden, true);
    w.show();

    return a.exec();
}
