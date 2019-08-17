#include "config.h"
#include <QObject>
#include <QSettings>
#include <QDir>

namespace config {

static QSettings settings(
    QSettings::IniFormat,
    QSettings::UserScope,
    "org.donchak", "don-player"
);

static QString _lastPath;
static int _volume;

void init()
{
    _lastPath = settings.value("last-path", QDir::currentPath()).toString();
    _volume = settings.value("volume", 0).toInt();
}

QString lastPath()
{
    return _lastPath;
}

void setLastPath(const QString &path)
{
    _lastPath = path;
    settings.setValue("last-path", path);
}

int volume()
{
    return _volume;
}

void setVolume(const int value)
{
    _volume = value;
    settings.setValue("volume", value);
}

}
