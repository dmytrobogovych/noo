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

    // Check if database / password are available
    QString path = helper::path::pathToDatabase();

    // Find optional custom path to database
    if (Settings::instance().data()[KEY_DB_FILENAME_SPECIFIED].toBool())
        path = Settings::instance().data()[KEY_DB_FILENAME].toString();

    QString folder = QFileInfo(path).absoluteDir().path();
    Storage::instance().setPath(path);

    // Check if file exists at all
    /*if (!QFile::exists(path))
    {
        // Show dialog that requests database path
    }
    else
    {
        // Check if password is available
        if (Settings::instance().data()[KEY_AUTOSAVE_PASSWORD].toBool())
        {
            QString password = helper::password::load();
            if (password.isEmpty())
            {
                // Ask about password
            }
            else
            {
                Storage::instance().setKey(password);
                if (!Storage::instance().open())
                {
                    askDbPassword(tr("Invalid password, please try again."));
                }
                else
                    QApplication::postEvent(this, new UiInitEvent());
            }
        }
        else
            askDbPassword(QString());
    }*/


    MainWindow w;
    w.layout()->invalidate();

    w.setAttribute(Qt::WA_WState_ExplicitShowHide, false);
    w.setAttribute(Qt::WA_WState_Hidden, true);
    w.show();

    return a.exec();
}
