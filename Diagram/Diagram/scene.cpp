#include "scene.h"

#include "scene.h"
#include <QGraphicsEllipseItem>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>

Scene::Scene(QObject* parent)
    : QGraphicsScene(parent) {
    //QBrush brush(QColor(240, 240, 240));
    //
    //brush.setStyle(Qt::TexturePattern);
    //
    ////brush.setTexture();
    //this->setBackgroundBrush(brush);
    drawBack();
    
}
void Scene::drawBack()
{

    QGraphicsItem* m_activeItem1;
   
    int sq = 50;
    for (int i = 0; i <= sq; i++)
    {
        m_activeItem1 = new QGraphicsRectItem(QRectF(i*w*1.5, 0, w*1.5, h* sq));
        
        static_cast<QGraphicsEllipseItem*>(m_activeItem1)->setPen(QColor(255, 255, 255));
        if (i % 2 == 0)
        {
            static_cast<QGraphicsEllipseItem*>(m_activeItem1)->setBrush(QBrush(QColor(240, 240, 240)));
        }
        else
        {
            static_cast<QGraphicsEllipseItem*>(m_activeItem1)->setBrush(QBrush(QColor(255, 255, 255)));
        }
        m_activeItem1->setFlag(QGraphicsItem::ItemIsSelectable, false);

        addItem(m_activeItem1);
    }
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsScene::mousePressEvent(event);



    
}

void Scene::drawLines(int i, int j, int i2, int j2, int counts1, int counts2,int commonP1,int commonP2, int maxP, int minP,int c,int c1)
{

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // P1 -> Common P1 -> Common P2 -> P2
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Line 1: Box right -> P1 
    // Line 2: P1 -> Common P1
    // Line 3: Common P1 -> center
    // Line 4: center -> Common P2
    // Line 5: Common P2 -> P2
    // Line 6: P2 -> Box left
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*i--;
    j--;
    _x = j * w * 1.5 + w / 4;
    _y = i * h * 1.5;
    _y += h / 2;

    _x += w;
    _y += h/2;*/

    QPoint p1, p2;
    p1 = convertCoordSystem(QPoint(i, j), counts1);
    p2 = convertCoordSystem(QPoint(i2, j2), counts2);
    int x1, y1, x2, y2;
    x1 = p1.x();
    y1 = p1.y();
    x2 = p2.x();
    y2 = p2.y();

    x1 += w;
    y1 += h / 2;

    y2 += h / 2;


    /*int _x2, _y2;
    i2--;
    j2--;
    _x2 = j2 * w * 1.5 + w / 4;
    _y2 = i2 * h * 1.5;

    _y2 += h;*/

    QPoint cP1, cP2;
    cP1 = convertCoordSystem(QPoint(commonP1, minP), c1);
    cP2 = convertCoordSystem(QPoint(commonP2,maxP), c);
    int cP1x = cP1.x()-w/8, cP1y = cP1.y()+h/2;
    int cP2x = cP2.x()+w/8+w, cP2y = cP2.y()+h/2;
    if (c % 2 == 0)
        cP2y += h*1.5;
    if (c1 % 2 == 0)
        cP1y += h*1.5;
    int x, y;
    ////////////////// Line 1
    x = x2 - w / 16;
    y = y2;
    drawSimpleLine(x2, y2, x, y);
    ////////////////// Line 2
    drawSimpleLine(x, y, cP1x, y);
    drawSimpleLine(cP1x, y, cP1x, cP1y);
    x = cP1x;
    y = cP1y;
    ////////////////// Line 6
    int lx, ly;
    lx = x1 + w /16;
    ly = y1;
    drawSimpleLine(x1, y1, lx, ly);
    ////////////////// Line 5
    drawSimpleLine(lx, ly, cP2x, ly);
    drawSimpleLine(cP2x, ly, cP2x, cP2y);
    lx = cP2x;
    ly = cP2y;
    drawSimpleLine(lx, ly, lx + w / 16, ly);
    drawSimpleLine(x, y, x - w / 16, y);
    ////////////////// 
    int cX, cY;
    cX = (x + lx) / 2;
    cY = (y + ly) / 2;
    ////////////////// Line 3
    drawSimpleLine(x, y, cX, y);
    drawSimpleLine(cX, y, cX, cY);
    ////////////////// Line 4
    drawSimpleLine(lx, ly, cX, ly);
    drawSimpleLine(cX, ly, cX, cY);
    
    int debug = 0;
    debug++;
   
}
QPoint Scene::convertCoordSystem(QPoint p,int counts)
{
    int x=p.x(),y=p.y();
    int x2, y2;
    QPoint p2;

    int hi = maxCount;
    hi = hi - counts + 1 + 2 * x;
    x--;
    y--;
    x2 = y * w * 1.5 + w / 4;
    y2 = hi * h * 1.5;
    y2 += h / 2;
    p2.setX(x2);
    p2.setY(y2);
    return p2;
}
void Scene::drawSimpleLine(int x1, int y1, int x2, int y2)
{
    QGraphicsItem* m_activeItem1;
    m_activeItem1 = new QGraphicsLineItem(QLineF(x1, y1, x2, y2));
    QColor color(0, 0, 0);
    QPen pen(color);
    pen.setWidth(2);
    static_cast<QGraphicsLineItem*>(m_activeItem1)->setPen(pen);
    addItem(m_activeItem1);
}
void Scene::setMaxCount(int _maxCount) {
    maxCount = _maxCount;
}
void Scene::addElement(int i, int j, QString str1, QString str2, bool isEmpty, int counts) {
    int hi = maxCount;
    hi = hi - counts+1 + 2*i;
    i--;
    j--;
    _x = j* w * 1.5+w/4; 
    _y = hi* h * 1.5;
    _y += h / 2;



    //QPointF pos = event->scenePos();
    QPointF pos;
    pos.setX(_x);
    pos.setY(_y);
    QColor color(0, 0, 0);
    QPen pen(color);
    pen.setWidth(2);
    QGraphicsItem* m_activeItem1;
    QGraphicsItem* m_activeItem2;
    QGraphicsItem* m_activeItem3;

    m_activeItem1 = new QGraphicsRectItem(QRectF(0, 0, w, h));
    static_cast<QGraphicsRectItem*>(m_activeItem1)->setPen(pen);
    static_cast<QGraphicsRectItem*>(m_activeItem1)->setBrush(QBrush(QColor(255, 255, 255)));
    if (isEmpty)
        m_activeItem1->setVisible(false);
    addItem(m_activeItem1);
    m_activeItem1->setPos(pos);
    m_activeItem2 = new QGraphicsSimpleTextItem(str1, m_activeItem1);
    addItem(m_activeItem2);
    m_activeItem2->setPos(w / 2 - (m_activeItem2->boundingRect().width() / 2), h / 2 - (m_activeItem2->boundingRect().height() / 2));

    m_activeItem3 = new QGraphicsSimpleTextItem(str2, m_activeItem1);
    addItem(m_activeItem3);
    m_activeItem3->setPos(5, h - 5 - (m_activeItem3->boundingRect().height()));
    m_activeItem1->setFlag(QGraphicsItem::ItemIsSelectable, true);
    //m_activeItem1->setSelected();

}

void Scene::keyPressEvent(QKeyEvent* event) {
    QGraphicsScene::keyPressEvent(event);
    
    if (event->key() == Qt::Key::Key_Space)
    {
       // addElement(1);
        
    }
    if (event->key() == Qt::Key::Key_W)
    {
     //   addElement(0);

    }

    /*QGraphicsItem* m_activeItem = itemAt();
    if (nullptr == m_activeItem)
        return;

    switch (event->key()) {
    case Qt::Key::Key_A:
        m_activeItem->moveBy(-5, 0);
        break;
    case Qt::Key::Key_S:
        m_activeItem->moveBy(0, 5);
        break;
    case Qt::Key::Key_D:
        m_activeItem->moveBy(5, 0);
        break;
    case Qt::Key::Key_W:
        m_activeItem->moveBy(0, -5);
        break;
    }*/
}
