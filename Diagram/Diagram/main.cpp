#include "Diagram.h"
#include <QtWidgets/QApplication>
#include "scene.h"
#include <QGraphicsView>
#include <QtWidgets>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Diagram w;    
    w.show(); 

    return a.exec();
}
