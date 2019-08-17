#include "settings.h"
#include "helper.h"
#include <QSettings>
#include <QStringList>
#include <QFile>
#include <QFileInfo>
#include <QDir>

Settings::Settings()
{
    load();
}

Settings::~Settings()
{
    save();
}

QVariantMap& Settings::data()
{
    return mData;
}

void Settings::save()
{
    QSettings settings(helper::path::pathToSettings(), QSettings::IniFormat);
    settings.clear();
    for (const QString& e: data().keys())
    {
        settings.setValue(e, data().value(e));
    }
}

void Settings::load()
{
    // Path to settings file
    QString path = helper::path::pathToSettings();

    // Check if directory exists at all
    QString dir = QFileInfo(path).absoluteDir().path();

    if (!QDir(dir).exists())
        QDir().mkdir(dir);

    // Load data itself
    QSettings settings(helper::path::pathToSettings(), QSettings::IniFormat);
    mData.clear();
    const QStringList keys = settings.allKeys();
    for (const QString& k: keys)
    {
        mData[k] = settings.value(k);
    }

    // Show seconds is on by default
    if (mData.find(KEY_SHOW_SECONDS) == mData.end())
        mData[KEY_SHOW_SECONDS] = true;
}

static Settings* GInstance = nullptr;
Settings& Settings::instance()
{
    if (!GInstance)
    {
        GInstance = new Settings();
        GInstance->load();
    }
    return *GInstance;
}
