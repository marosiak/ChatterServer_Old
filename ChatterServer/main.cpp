#include <QCoreApplication>
#include <string>

#include <./class/inputoutputmanager.h>
#include <./class/authserver.h>
#include <./class/database.h>

int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);

    AuthServer authServer;
    authServer.setPort(3433);
    authServer.start();




    return a.exec();
}
