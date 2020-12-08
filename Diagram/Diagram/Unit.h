#pragma once

#include <QObject>

class Unit : public QObject
{
	Q_OBJECT
		
		
public:
	Unit(QObject *parent);
	Unit(QString n, QString p, int pi,int pj);
	~Unit();
	int i;
	int j;
	int ind = 0;
	QList<Unit*> parents;
	QList<Unit*> childs;
	QString name;
	QString paramC;
	bool isEmpty();
	bool isSubUnit();
	void setEmpty();
private:
	bool _isEmpty = false;
	bool _isSubUnit = false;
	
};
