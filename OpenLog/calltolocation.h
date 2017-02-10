#ifndef CALLTOLOCATION_H
#define CALLTOLOCATION_H

#include <QObject>
#include <QMap>
#include <QList>

struct PrefixRange
{
    QString from;
    QString to;
    bool isRange;
    QString location;
};

class CallToLocation : public QObject
{
    Q_OBJECT
private:
    QList<PrefixRange> locationList;
public:
    explicit CallToLocation(QObject *parent = 0);
public slots:
    void loadData(QString dataFilePath);
    void getLocation(QString callsign, QString* location, bool* wasFoundFlag);
    void isEnable(bool* enableFlag);
};

#endif // CALLTOLOCATION_H

/* END OF FILE */
