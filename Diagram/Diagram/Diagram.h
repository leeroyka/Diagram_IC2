#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Diagram.h"
#include "scene.h"
#include "Unit.h"
#include <QtWidgets>
#include <QGraphicsView>
#include <QFile>
#include <QTextStream>
#include <qlist.h>
class Diagram : public QMainWindow
{
    Q_OBJECT

public:
    Diagram(QWidget *parent = Q_NULLPTR);
    
    Scene scene;
    void AddEl(int i,int j,QString str1, QString str2,bool isEmpty);
private:
    QList<int> counts;
    int maxCount = 0;
    Ui::DiagramClass ui;
    void ReadFromFile();
    QStandardItemModel* csvModel;
    QMap<QString,Unit*> units;
    void fillMatrix();
    void fillFamily();
    void fillEmptyElements();
    void printDebug();
    void drawElemenets();
    void drawLines();
};
