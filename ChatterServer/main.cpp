#include <QCoreApplication>
#include <string>

#include <./class/inputoutputmanager.h>
#include <./class/authserver.h>
#include <./class/database.h>
#include <./class/client.h>

int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);


    AuthServer authServer;
    Client client;
    authServer.setPort(3433);
    client.setPort(3433);
    client.setServerIp(QHostAddress::LocalHost);

    if (QString(argv[1]) == "-server") {
        authServer.start();
    } else {
        client.start();
        InputOutputManager ioManager;
        ioManager.setHeaderText("Please login");
        ioManager.print("type \"help\" for info about commands");
        ioManager.endl();
        while(true){
            std::string input;
            std::cin >> input;
            if(input == "help"){
                ioManager.print("Commands:\n"
                                "help - shows info about commands\n"
                                "register - make account\n"
                                "login - login to account which exist");
            }
            ioManager.endl();
            if(input == "register"){
                std::string login;
                std::string pass;
                ioManager.print("Enter login: ");
                std::cin >> login;
                ioManager.print("Enter password: ");
                std::cin >> pass;
                client.setLogin(QString(login.c_str()));
                client.setPassword(QString(pass.c_str()));
                client.registerRequest();
                break;
            }
            if(input == "login"){
                std::string login;
                std::string pass;
                ioManager.print("Enter login: ");
                std::cin >> login;
                ioManager.print("Enter password: ");
                std::cin >> pass;
                client.setLogin(QString(login.c_str()));
                client.setPassword(QString(pass.c_str()));
                client.loginRequest();
                system("cls");
                QString msg = QString("Logged as %1").arg(QString(login.c_str()));
                ioManager.setHeaderText(msg.toStdString());
                break;
            }

        }

    }
    return a.exec();

}
