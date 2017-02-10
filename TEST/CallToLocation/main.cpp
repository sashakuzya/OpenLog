#include <QCoreApplication>
#include "../../OpenLog/calltolocation.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CallToLocation locConverter;
    locConverter.loadData("../../OpenLog/prefix.list");

    QString tmp = "";
    bool isFound = false;
    locConverter.getLocation("RN3DDZ", &tmp, &isFound);
    locConverter.getLocation("RN0DDZ", &tmp, &isFound);

    return a.exec();
}
