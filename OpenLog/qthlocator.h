#ifndef QTHLOCATOR_H
#define QTHLOCATOR_H

#include <QObject>
#include <QtTest/QTest>

#define DEFAULT_COORDINATE {0.0, 0.0}

struct Coordinate
{
    double lattitude;
    double longitude;
};

class QthLocator : public QObject
{
    Q_OBJECT
private:
    QString _myQthLocator;
public:
    explicit QthLocator(QObject *parent = 0);

    bool setMyLocator(QString qthLocator);
    QString myLocator();
    QString normalyse(QString qthLocator, bool* isOk);
    bool isCorrect(QString qthLocator);
    QString coordinateToLocator(Coordinate coordinate, bool* isOk);
    Coordinate locatorToCoordinate(QString qthLocator, bool* isOk);
    double distance(Coordinate from, Coordinate to);
    double distance(QString fromLocator, QString toLocator);
    double distance(QString toQthLocator);
signals:

public slots:

};

#endif // QTHLOCATOR_H

/* END OF FILE */
