#pragma once

#include <QObject>
	
#include <QGraphicsScene>

class Scene : public QGraphicsScene {
	Q_OBJECT
public:
	explicit Scene(QObject* parent = nullptr);

	void drawLines(int i, int j, int i2, int ij,int counts1,int counts2, int commonP1, int commonP2,int maxP,int minP,int c,int c1);
	void addElement(int i,int j, QString str1, QString str2,bool isEmpty, int counts);
	void setMaxCount(int _maxCount);
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	void drawSimpleLine(int x1, int y1, int x2, int y2);
	void drawConnector(int x, int y, int type = 0);
	QPoint convertCoordSystem(QPoint p, int counts);
	void drawBack();
	int w = 200;
	int h = (0.575 * (double)w);
	int _x;
	int _y;
	int maxCount;


};