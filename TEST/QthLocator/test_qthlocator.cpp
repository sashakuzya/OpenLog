#include "../../OpenLog/qthlocator.h"
#include<QtTest/QtTest>

class TestQthLocator: public QObject
{
    Q_OBJECT;
private slots:
    void setGetLocator();
    void locatorIsCorrect();
    void coordinateDistance();
};

void TestQthLocator::locatorIsCorrect()
{
    QthLocator loc;

    // Not full or empty
    QVERIFY(loc.isCorrect("")     == false);
    QVERIFY(loc.isCorrect("KO")   == false);
    QVERIFY(loc.isCorrect("KO86") == false);

    // Correct
    QVERIFY(loc.isCorrect("KO86nr") == true);
    QVERIFY(loc.isCorrect("AA00aa") == true);
    QVERIFY(loc.isCorrect("AR09ax") == true);
    QVERIFY(loc.isCorrect("RR99xx") == true);
    QVERIFY(loc.isCorrect("RA90xa") == true);

    // Uncorrect "Big sector"
    QVERIFY(loc.isCorrect("SA86nr") == false);
    QVERIFY(loc.isCorrect("AS86nr") == false);

    // Uncorrect "Little sector"
    QVERIFY(loc.isCorrect("KO86ay") == false);
    QVERIFY(loc.isCorrect("KO86ya") == false);

}

void TestQthLocator::setGetLocator()
{
    QthLocator loc;
    loc.setMyLocator("KO86NR");
    QVERIFY(loc.myLocator() == "KO86nr");
    loc.setMyLocator("ZZ00ZZ");
    QVERIFY(loc.myLocator() == "");
}

void TestQthLocator::coordinateDistance()
{
    QthLocator loc;
    Coordinate c1, c2;

    c1.lattitude = c2.lattitude = 0.0;
    c1.longitude = c2.longitude = 0.0;
    QVERIFY(loc.distance(c1, c2) == 0.0);
}

QTEST_MAIN(TestQthLocator)
#include "test_qthlocator.moc"

/* END OF FILE */
