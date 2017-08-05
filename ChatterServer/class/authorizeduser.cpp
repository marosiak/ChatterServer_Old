#include "authorizeduser.h"

QString AuthorizedUser::getToken() const { return token; }

void AuthorizedUser::setToken(const QString& value) { token = value; }

QString AuthorizedUser::getName() const { return name; }

void AuthorizedUser::setName(const QString& value) { name = value; }

short AuthorizedUser::getTime() const { return time; }

void AuthorizedUser::setTime(short value) { time = value; }
