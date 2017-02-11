#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql/QtSql>
#include <QFileInfo>
#include <QList>

#include "types.h"

class Database : public QObject
{
    Q_OBJECT
private:
    QSqlDatabase sdb;
public:
    explicit Database(QObject *parent = 0);
    ~Database() { sdb.close(); }
    bool open(QString dbPath);
signals:

public slots:
    void qsoAdd(QSO qso);
    void qsoRemove(quint16 id);
    void qsoCount(quint32* count);
    void qsoListByCallsign(QList<QSO>* qsoList);
};

#endif // DATABASE_H
