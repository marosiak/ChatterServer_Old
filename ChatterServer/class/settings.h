#ifndef SETTINGS_H
#define SETTINGS_H

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
    int getPort() const;
    void setPort(int value);

    int getTimeOut() const;
    void setTimeOut(int value);

private:
    int port;
    int timeOut;
};

#endif  // SETTINGS_H
