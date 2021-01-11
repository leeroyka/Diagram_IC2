#include "Unit.h"

Unit::Unit(QObject *parent)
	: QObject(parent)
{
}
Unit::Unit(QString n, QString p, int pi, int pj) {
	name = n;
	paramC = p;
	i = pi;
	j = pj;
}
Unit::~Unit()
{
}
bool Unit::isEmpty()
{
	return _isEmpty;
}
bool Unit::isSubUnit()
{
	return _isSubUnit;
}
void Unit::setEmpty()
{
	_isEmpty = true;
}