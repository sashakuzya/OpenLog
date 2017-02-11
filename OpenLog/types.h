#ifndef TYPES_H
#define TYPES_H

#include <QString>
#include <QDateTime>

struct QSO{
	QString callsign;
	QDateTime dateTime;
	quint16 rstR;
	quint16 rstS;
	QString name;
	QString city;
	QString region;
	QString country;
	QString qthLocator;
	bool qslCardSend;
	bool qslCardReceved;
	QString note;
};

#endif

/* END OF FILE */
