#ifndef SETTINGS_H
#define SETTINGS_H
#include <QObject>

class Settings {
private:
    Settings(const Settings&);

public:
    Settings();
    static Settings& getSettings() {
        static Settings settings;
        return settings;
    }

public:
    quint16 getPort() const;
    void setPort(int value);

    int getTimeOut() const;
    void setTimeOut(int value);

private:
    quint16 port;
    int timeOut;
};

#endif  // SETTINGS_H
