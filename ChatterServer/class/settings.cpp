#include "settings.h"

Settings::Settings() {}

quint16 Settings::getPort() const { return port; }

void Settings::setPort(int value) { port = value; }

int Settings::getTimeOut() const { return timeOut; }

void Settings::setTimeOut(int value) { timeOut = value; }
