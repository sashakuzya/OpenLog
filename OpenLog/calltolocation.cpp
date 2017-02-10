#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QStringList>
#include "calltolocation.h"

/*!
 * \brief Default constructor
 * \param parent Parent object
 */
CallToLocation::CallToLocation(QObject *parent) : QObject(parent)
{
    locationList.clear();
}

/*!
 * \brief Return enable flag
 * \details If there no any callsign prefix than class is not ready for
 * conversion.
 */
void CallToLocation::isEnable(bool* enableFlag)
{
    if(locationList.count() > 0)
        *enableFlag = true;
    else
        *enableFlag = false;
}

/*!
 * \brief Load prefixes from .list file
 * \param dataFilePath File path
 */
void CallToLocation::loadData(QString dataFilePath)
{
    // Check for exist
    QFileInfo checkedFile(dataFilePath);
    if(checkedFile.exists() && checkedFile.isFile())
    {
        QFile inFile(dataFilePath);
        if(inFile.open(QIODevice::ReadOnly))
        {
            locationList.clear();
            QTextStream in(&inFile);
            while(!in.atEnd())
            {
                QString dataForDecode = in.readLine();
                // Ignore empty lines
                if(dataForDecode.length() == 0)
                    continue;
                // and ignore comments lines
                if(dataForDecode[0] == '#')
                    continue;
                int spaceIndex = dataForDecode.indexOf(" ");
                // no space = uncorrect data, ignore it too
                if(spaceIndex == -1)
                    continue;
                // space is a last symbol on line = uncorrect data, ignore it
                if(dataForDecode.length() == spaceIndex - 1)
                    continue;
                QString prefix = dataForDecode.left(spaceIndex);
                // first symbol is space = uncorrect data, ignore it
                if(prefix.length() == 0)
                    continue;
                PrefixRange pr;
                if(prefix.contains('-'))
                {
                    QStringList splitedRange = prefix.split('-');
                    // more than one minuse = uncorrect data, ignore it
                    if(splitedRange.count() != 2)
                        continue;
                    pr.from = splitedRange[0];
                    pr.from = pr.from.toLower();
                    pr.to = splitedRange[1];
                    pr.to = pr.to.toLower();
                    pr.isRange = true;
                    // check for correct
                    for(qint32 i=0; i<pr.from.length(); i++)
                    {
                        if(pr.from[i].digitValue() > pr.to[i].digitValue())
                            continue;
                    }
                }
                else
                {
                    pr.from = prefix.toLower();
                    pr.to = "";
                    pr.isRange = false;
                }
                // check for correct
                if(pr.from.length() != pr.to.length() || pr.from.length() <= 0)
                    continue;

                pr.location = dataForDecode.mid(spaceIndex + 1);
                locationList.push_back(pr);
            }
            inFile.close();
        } // if
    } // if
}

/*!
 * \brief Get location by callsign
 * \param callsign Callsign or part of them
 * \param location Pointer to location string. Location string is empty if data
 * not found.
 * \param wasFoundFlag Founde flag. TRUE = location if found!
 */
void CallToLocation::getLocation(QString callsign,
                                 QString* location,
                                 bool* wasFoundFlag)
{
    if(locationList.count() <= 0)
    {
        *wasFoundFlag = false;
        location->clear();
        return;
    }

    callsign = callsign.toLower();
    for(qint32 i=0; i<locationList.count(); i++)
    {
        QString from = locationList.at(i).from;
        // prefix should be not less than callsign
        if(from.length() > callsign.length())
            continue;
        QString to = locationList.at(i).to;
        bool findeFlag = true;
        for(qint32 j=0; j<from.length(); j++)
        {
            if(locationList.at(i).isRange == false)
            {
                if(callsign[j].digitValue() == from[j].digitValue())
                    continue;
                else
                {
                    findeFlag = false;
                    break;
                }
            } // if
            else
            {
                if(callsign[j].digitValue() < from[j].digitValue() ||
                   callsign[j].digitValue() > to[j].digitValue())
                {
                    findeFlag = false;
                    break;
                } // if
            } // else if
        } // for j
        if(findeFlag == true)
        {
            *wasFoundFlag = true;
            *location = locationList.at(i).location;
            return;
        } // if
    }// for i

    *wasFoundFlag = false;
    location->clear();
}

/* END OF FILE */
