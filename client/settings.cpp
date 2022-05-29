#include "settings.h"
#include "helper.h"
#include <QSettings>
#include <QStringList>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QRect>

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
    auto path = helper::path::pathToSettings();
    QSettings settings(path, QSettings::IniFormat);
    settings.clear();
    for (const QString& e: data().keys())
    {
        settings.setValue(e, data().value(e));
    }
}

void Settings::load()
{
    if (false == mData.isEmpty())
        return; // Already loaded

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

QString Settings::getDatabasePath()
{
    // Path to settings file
    QString path;// = helper::path::pathToSettings();

    QString stored_path = data()[KEY_DB_FILENAME].toString();
    if (!stored_path.isEmpty())
        path = stored_path;

    if (path.contains("~"))
        path.replace("~", QDir::homePath());

    return path;
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

AppGeometry::AppGeometry(Settings& settings)
    :mSettings(settings)
{}

AppGeometry::~AppGeometry()
{}

bool AppGeometry::isMaximized() const
{
    return mSettings.data().value(KEY_MAXIMIZED).toBool();
}

void AppGeometry::setMaximized(bool v)
{
    mSettings.data()[KEY_MAXIMIZED] = v;
}

QRect AppGeometry::windowRect() const
{
    QRect geom;
    auto& d = mSettings.data();
    if (d.contains(KEY_LEFT) && d.contains(KEY_TOP) && d.contains(KEY_WIDTH) && d.contains(KEY_HEIGHT))
    {
        geom.setLeft(d[KEY_LEFT].toInt());
        geom.setTop(d[KEY_TOP].toInt());
        geom.setWidth(d[KEY_WIDTH].toInt());
        geom.setHeight(d[KEY_HEIGHT].toInt());
    }
    return geom;
}

void AppGeometry::setWindowRect(QRect r)
{
    auto& d = mSettings.data();
    d[KEY_LEFT] = r.left();
    d[KEY_TOP] = r.top();
    d[KEY_WIDTH] = r.width();
    d[KEY_HEIGHT] = r.height();
}

std::tuple<int, int> AppGeometry::splitterPos(int splitterIdx) const
{
    auto& d = mSettings.data();
    auto splitter_name_1 = QString("splitter_%1_offset_%2").arg(splitterIdx).arg(0);
    auto splitter_name_2 = QString("splitter_%1_offset_%2").arg(splitterIdx).arg(1);

    if (d.contains(splitter_name_1) && d.contains(splitter_name_2))
        return std::make_tuple<int,int>(d[splitter_name_1].toInt(), d[splitter_name_2].toInt());

    return std::make_tuple(0,0);
}

void AppGeometry::setSplitterPos(int splitterIdx, std::tuple<int, int> v)
{
    auto& d = mSettings.data();
    auto splitter_name_1 = QString("splitter_%1_offset_%2").arg(splitterIdx).arg(0);
    auto splitter_name_2 = QString("splitter_%1_offset_%2").arg(splitterIdx).arg(1);

    auto [offset_1, offset_2] = v;
    d[splitter_name_1] = offset_1;
    d[splitter_name_2] = offset_2;
}
