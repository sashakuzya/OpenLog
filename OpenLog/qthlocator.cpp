#include "qthlocator.h"
#include <QtMath>

/*!
 * \brief QthLocator::QthLocator
 * \param parent
 */
QthLocator::QthLocator(QObject *parent) : QObject(parent)
{
    _myQthLocator.clear();
}

/*!
 * \brief Set my QTH locator
 * \param String - QTH locator
 * \return Operation status. TRUE = SUCCESS
 */
bool QthLocator::setMyLocator(QString qthLocator)
{
    bool isCorrect = false;
    qthLocator = normalyse(qthLocator, &isCorrect);
    if(isCorrect == true)
        _myQthLocator = qthLocator;
    else _myQthLocator = "";
    return isCorrect;
}

/*!
 * \brief Return my QTH locator
 * \return String - QTH locator
 */
QString QthLocator::myLocator()
{
    return _myQthLocator;
}

/*!
 * \brief Normalyse QTH locator string
 * \param qthLocator Input QTH locator string (not normalysed)
 * \param isOk Operation result flag. TRUE = SUCCESS
 * \return Normalysed QTH locator string (if operation successed) ar empty
 * string (is operation WRONG)
 */
QString QthLocator::normalyse(QString qthLocator, bool* isOk)
{
    if(qthLocator.length() > 6 || qthLocator.length() == 0)
    {
        *isOk = false;
        return "";
    }

    for(quint8 i=0; i<qthLocator.length(); i++)
    {
        switch(i)
        {
        case 0:
            qthLocator[i] = qthLocator[i].toUpper();
            break;
        case 1:
            qthLocator[i] = qthLocator[i].toUpper();
            break;
        case 4:
            qthLocator[i] = qthLocator[i].toLower();
            break;
        case 5:
            qthLocator[i] = qthLocator[i].toLower();
            break;
        } // switch
    } // for

    *isOk = isCorrect(qthLocator);
    return qthLocator;
}

/*!
 * \brief Check locator for correct
 * \param String - QTH locator
 * \return Result. TRUE = locator is correct.
 */
bool QthLocator::isCorrect(QString qthLocator)
{
    if(qthLocator.length() != 6)
        return false;

    for(quint8 i=0; i<6; i++)
    {
        int tmp = qthLocator[i].toLatin1();
        if(i == 0 || i == 1)
        {
            if(tmp < QChar('A').toLatin1() || tmp > QChar('R').toLatin1())
                return false;
        }
        else if(i == 2 || i == 3)
        {
            if(tmp < QChar('0').toLatin1() || tmp > QChar('9').toLatin1())
                return false;
        }
        else
        {
            if(tmp < QChar('a').toLatin1() || tmp > QChar('x').toLatin1())
                return false;
        }
    }

    return true;
}

/*!
 * \brief Convert geographical coordinates to QTH locator
 * \param coordinate Coordinates struct
 * \param isOk Pointer to operation result
 * \return String - QTH locator
 */
QString QthLocator::coordinateToLocator(Coordinate coordinate, bool* isOk)
{
    QString loc = "";

    double tmpLat = coordinate.lattitude + 90.0;
    double tmpLon = coordinate.longitude + 180.0;

    if(tmpLat > 180.0 || tmpLon > 360.0)
    {
        *isOk = false;
        return "";
    }

    quint8 mainSectorLat = tmpLat / 10.0;
    tmpLat -= mainSectorLat * 10.0;
    quint8 mainSectorLon = tmpLon / 20.0;
    tmpLon -= mainSectorLon * 20.0;
    loc += QChar(mainSectorLon + 0x41);
    loc += QChar(mainSectorLat + 0x41);

    quint8 bigSectorLat = (quint8)tmpLat;
    tmpLat -= bigSectorLat;
    quint8 bigSectorLon = tmpLon / 2.0;
    tmpLon -= bigSectorLon * 2;
    loc += QChar(bigSectorLon + 0x30);
    loc += QChar(bigSectorLat + 0x30);

    quint8 littleSectorLat = tmpLat / (2.5/60.0);
    quint8 littleSectorLon = tmpLon / (5.0/60.0);
    loc += QChar(littleSectorLon + 0x61);
    loc += QChar(littleSectorLat + 0x61);

    return loc;
}

/*!
 * \brief Convert QTH locator to geographical coordinates
 * \param qthLocator String - QTH locator
 * \param isOk Pointer to operation result flag
 * \return Coordinates
 */
Coordinate QthLocator::locatorToCoordinate(QString qthLocator, bool* isOk)
{
    Coordinate cord;
    cord.lattitude = 0.0;
    cord.longitude = 0.0;

    if(!isCorrect(qthLocator))
    {
        *isOk = false;
        return cord;
    }

    cord.longitude = (qthLocator.at(0).toLatin1() - 0x41) * 20.0;
    cord.longitude += (qthLocator.at(2).toLatin1() - 0x30) * 2.0;
    cord.longitude += (qthLocator.at(4).toLatin1() - 0x61) * (5.0/60.0) + (5.0/120.0);

    cord.lattitude = (qthLocator.at(1).toLatin1() - 0x41) * 10.0;
    cord.lattitude += (qthLocator.at(3).toLatin1() - 0x30);
    cord.lattitude += (qthLocator.at(5).toLatin1() - 0x61) * (2.5/60.0) + (2.5/120);

    cord.longitude -= 180.0;
    cord.lattitude -= 90.0;

    *isOk = true;
    return cord;
}

/*!
 * \brief Calculate distance betwen two coordinate points
 * \param from First point
 * \param to Second point
 * \return Distance
 */
double QthLocator::distance(Coordinate from, Coordinate to)
{
    const quint16 R = 6371;  // Earth radius in km.
    double dLat = qDegreesToRadians(to.lattitude - from.lattitude);
    double dLon = qDegreesToRadians(to.longitude - from.longitude);
    double tmp_1 = qPow(qSin(dLat/2), 2) + \
                   qCos(qDegreesToRadians(from.lattitude)) * \
                   qCos(qDegreesToRadians(to.lattitude)) * \
                   qPow(qSin(dLon/2), 2);
    double tmp_2 = 2 * qAtan2(qSqrt(tmp_1), qSqrt(1 - tmp_1));
    double tmp_3 = R * tmp_2;
    return tmp_3;
}

/*!
 * \brief Calculate distance betwen two QTH locators
 * \param fromLocator First locator
 * \param toLocator Second locator
 * \return Distance
 */
double QthLocator::distance(QString fromLocator, QString toLocator)
{
    bool isOk = false;
    Coordinate from = locatorToCoordinate(fromLocator, &isOk);
    if(!isOk)
        return -1.0;
    Coordinate to = locatorToCoordinate(toLocator, &isOk);
    if(!isOk)
        return -1.0;
    return distance(from, to);
}

/*!
 * \brief Distance betwen my position anl some QTH locator
 * \param toQthLocator Remote QTH locator
 * \return Distance
 */
double QthLocator::distance(QString toQthLocator)
{
    return distance(_myQthLocator, toQthLocator);
}

/* END OF FILE */
