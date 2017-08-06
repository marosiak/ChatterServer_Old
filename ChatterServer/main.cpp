#include <./class/authserver.h>
#include <./class/database.h>
#include <./class/friendsmanager.h>
#include <./class/settings.h>
#include <QCoreApplication>
#include <QHostAddress>
#include <cstdlib>
#include <ctime>
#include <string>

int main(int argc, char* argv[]) {
    QCoreApplication a(argc, argv);
    srand(time(NULL));  // TODO tu trzeba będzie naprawić
    Settings::getSettings().setPort(3433);
    Settings::getSettings().setTimeOut(2);

    AuthServer::getAuthServer().setPort(Settings::getSettings().getPort());
    AuthServer::getAuthServer().setTimeOut(
        Settings::getSettings().getTimeOut());
    AuthServer::getAuthServer().start();

    return a.exec();
}
