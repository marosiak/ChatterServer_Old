#include "inputoutputmanager.h"

InputOutputManager::InputOutputManager(){

}

void InputOutputManager::print(std::string message){
    for(int i=0; i<=message.length(); i++){
        std::cout << message[i];
        Sleep(15);
    }
    std::cout << std::endl;
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
}


void InputOutputManager::setHeaderText(const std::string &value){
    hOut = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( hOut, BACKGROUND_GREEN );
    std::cout << value << std::endl<<std::endl;
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
    headerText = value;
}
