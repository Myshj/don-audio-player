#ifndef CONFIG_H
#define CONFIG_H

class QString;

namespace config{

void init();

QString lastPath();
void setLastPath(const QString& path);

int volume();
void setVolume(const int value);
}

#endif // CONFIG_H
