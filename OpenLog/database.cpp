#include "database.h"

/*!
 * \brief Default constructor
 * \param parent Parent object
 */
Database::Database(QObject *parent) : QObject(parent)
{
    sdb = QSqlDatabase::addDatabase("QSQLITE");
}

/*!
 * \brief Open database
 * \param dbPath Database file path
 * \return Operation status. TRUE = SUCCESS.
 */
bool Database::open(QString dbPath)
{
    // if file exist
    QFileInfo checkedFile(dbPath);
    if(checkedFile.exists() && checkedFile.isFile())
    {
        sdb.setDatabaseName(dbPath);
        return sdb.open();
    }
    return false;
}

void Database::qsoAdd(QSO qso)
{

}

void Database::qsoRemove(quint16 id)
{

}

/*!
 * \brief QSO count in database
 * \param count Pointer to QSO count value
 */
void Database::qsoCount(quint32* count)
{
    QSqlQuery query("SELECT COUNT() FROM logbook");
    while(query.next())
    {
        *count = query.value(0).toUInt();
        return;
    }
    *count = 0;
}

void Database::qsoListByCallsign(QList<QSO>* qsoList)
{

}

