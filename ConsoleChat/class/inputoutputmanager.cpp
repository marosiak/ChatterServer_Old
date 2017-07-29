#include "inputoutputmanager.h"

InputOutputManager::InputOutputManager(){

}

void InputOutputManager::print(const std::string& message) const{
    for(int i=0; i<=message.length(); i++){
        std::cout << message[i];
        std::this_thread::sleep_for(15ms); //should work with ""ms literal from chrono, if not, change to std::chrono::milliseconds(15)
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
