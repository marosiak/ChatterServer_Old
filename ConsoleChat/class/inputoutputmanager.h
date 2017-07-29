#ifndef INPUTOUTPUTMANAGER_H
#define INPUTOUTPUTMANAGER_H
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <QCharRef>
#include <QString>
#include <QDebug>

class InputOutputManager {

public:
    InputOutputManager();
    void print(std::string message);

    void setHeaderText(const std::string &value);

private:
    HANDLE hOut;
    std::string headerText;
};

#endif // INPUTOUTPUTMANAGER_H
