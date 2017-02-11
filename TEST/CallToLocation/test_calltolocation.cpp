#include "../../OpenLog/calltolocation.h"
#include<QtTest/QtTest>

class TestCallToLocation: public QObject
{
    Q_OBJECT;
private slots:
    void fileNotExist();
    void fileExist();
    void notFindeLocation();
    void findeLocation();
};

void TestCallToLocation::fileNotExist()
{
    CallToLocation locConverter;
    bool isEnable = false;
    locConverter.loadData("../../OpenLog/file_not_exist.list");
    locConverter.isEnable(&isEnable);
    QVERIFY(isEnable == false);
}

void TestCallToLocation::fileExist()
{
    CallToLocation locConverter;
    bool isEnable = false;
    locConverter.loadData("../../OpenLog/prefix.list");
    locConverter.isEnable(&isEnable);
    QVERIFY(isEnable == true);
}

void TestCallToLocation::notFindeLocation()
{
    CallToLocation locConverter;
    locConverter.loadData("../../OpenLog/prefix.list");
    QString location = "Some trash here!";
    bool wasFounde = false;
    locConverter.getLocation("00000", &location, &wasFounde);
    QVERIFY(wasFounde == false);
    QVERIFY(location.length() == 0);
}

void TestCallToLocation::findeLocation()
{
    CallToLocation locConverter;
    locConverter.loadData("../../OpenLog/prefix.list");
    QString location = "";
    bool wasFounde = false;
    locConverter.getLocation("RN3DDZ", &location, &wasFounde);
    QVERIFY(wasFounde == true);
    QVERIFY(location.length() != 0);
}

QTEST_MAIN(TestCallToLocation)
#include "test_calltolocation.moc"

/* END OF FILE */
