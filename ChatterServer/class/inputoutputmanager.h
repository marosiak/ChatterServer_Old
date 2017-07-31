#ifndef INPUTOUTPUTMANAGER_H
#define INPUTOUTPUTMANAGER_H
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <thread>
#include <QCharRef>
#include <QString>
#include <QDebug>

class InputOutputManager {

public:
    InputOutputManager();
    void print(const std::string& message) const;
    void setHeaderText(const std::string &value);
    void endl();

private:
    HANDLE hOut;
    std::string headerText;
};

#endif // INPUTOUTPUTMANAGER_H
