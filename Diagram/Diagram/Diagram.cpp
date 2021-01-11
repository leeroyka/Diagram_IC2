#include "Diagram.h"

Diagram::Diagram(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    ui.graphicsView->setScene(&scene);
    ui.graphicsView->centerOn(0, 0);
    /*AddEl(1, "Test1", "Z1.1");
    AddEl(1, "Test2", "Z2.1");
    AddEl(1, "Test3", "Z3.1");
    AddEl(2, "Test4", "Z3.2");
    AddEl(1, "Test5", "Z4.1");
    AddEl(2, "Test6", "Z4.2");
    AddEl(2, "Test7", "Z4.3");
    AddEl(1, "Test8", "Z5.1");*/


    //
    ReadFromFile();
    fillMatrix();
    drawElemenets();

    //неправильно
    //for (int row = 1; row < csvModel->rowCount()-1; ++row) {
    //    QList<Unit*> col;
    //    for (int column = 1; column < csvModel->columnCount(); ++column) {
    //        //QStandardItem* item = new QStandardItem(QString("row %0, column %1").arg(row).arg(column));
    //        //model.setItem(row, column, item);
    //        QString str = csvModel->index(row, column).data().toString();
    //        if (column == 1 &&str[0]== '1' && row<csvModel->rowCount()-1)
    //        {
    //            Unit* un = new Unit("Test", str, row, column);
    //            un->setEmpty();
    //            col.append(un);
    //        }
    //        if (str[0] == 'c')
    //        {
    //            Unit* un = new Unit("Test", str, row, column);
    //            
    //            col.append(un);
    //        }
    //    }
    //    units.append(col);
    //   // qDebug() << str;
    //}

   // qDebug() << str;
}
void Diagram::drawElemenets()
{
    for (int _i = 0; _i < csvModel->rowCount(); _i++)
        counts.append(0);

    for (int _i = 0; _i < csvModel->rowCount(); _i++)
    {
        int count = 0;
        foreach(Unit * u, units)
        {
            if (u->j == _i)
            {

                u->ind = count;
                count++;
            }
        }
        if (count > maxCount)
            maxCount = count;
        counts[_i] = count;
    }
    scene.setMaxCount(maxCount);
    foreach(Unit * u, units)
    {
        AddEl(u->ind, u->j, u->name, u->paramC, u->isEmpty());
    }
    drawLines();
}
void Diagram::drawLines()
{
    foreach(Unit * u, units)
    {
        
        foreach(Unit * pu, u->parents)
        {
            //str += pu->paramC + " ";
            int commonP1 = 0;
            int c = 0;
            int maxP=0, minP=u->j;
            int sumP1 = 0;
            foreach(Unit * pu2, u->parents)
            {
                sumP1 += pu2->ind;
                if (pu2->j > maxP)
                    maxP = pu2->j;

                c++;
            }            
            commonP1 = sumP1 / c;
            int commonP2 = 0;
            int c1 = 0;
            foreach(Unit* pu2, pu->childs)
            {
                commonP2 += pu2->ind;
                if (pu2->j < minP)
                    minP = pu2->j;
                c1++;
            }
            commonP2 = commonP2 / c1;
            
            int debug = 0;
            if (u->paramC == "c33" && pu->paramC=="c31")
                debug++;
            scene.drawLines(pu->ind, pu->j, u->ind, u->j, counts[pu->j], counts[u->j],commonP2,commonP1,maxP,minP,c,c1);
            
            debug++;
        }

    }
    
}
void Diagram::fillMatrix()
{
    
    for (int row = 1; row < csvModel->rowCount() - 1; ++row) 
    {
        int count = 0;
            for (int column = 1; column < csvModel->columnCount(); ++column) 
            {
                
                QString str = csvModel->index(row, column).data().toString();
                if (column == 1 &&str[0]== '1' && row<csvModel->rowCount()-1)
                {
                    /*
                    str='e'+ QString::number(row) + QString::number(column);
                    Unit* un = new Unit("Test", str, row, column);
                    un->setEmpty();
                    units.insert(str, un);
                    */
                }
               
                if (str[0] == 'c' || str[0]=='с')
                {
                    

                    Unit* un = new Unit("Test", str, row, column);
                    un->ind = count;
                    units.insert(str, un);
                    count++;
                }
            }
            //counts.append(count);
    }
    fillFamily();
}
void Diagram::printDebug()
{
    QString str = "";
    foreach(Unit * u, units)
    {
        str = u->paramC +" ind: "+ QString::number(u->ind)+ " P: ";
        foreach(Unit *pu, u->parents)
        {
            str += pu->paramC + " ";
        }

        qDebug() << str;
    }
    str = "";
}
void Diagram::fillFamily()
{
    for (int row = 1; row < csvModel->rowCount() - 1; ++row)
    {

        for (int column = 1; column < csvModel->columnCount(); ++column)
        {

            QString str = csvModel->index(row, column).data().toString();
            if (column == 1 && str[0] == '1' && row < csvModel->rowCount() - 1)
            {
               
            }

            if (str[0] == 'c' || str[0] == 'с')
            {
                Unit* u = units.value(str);
                int iter = column;
                QString str2;
                while (iter > 1)
                {
                    iter--;
                    str2= csvModel->index(row, iter).data().toString();
                    if (iter == 1 && str2[0] == '1')
                    {
                        if (units.find('e' + QString::number(column - 1) + QString::number(column - 1)) == units.end())
                        {
                            QString str = 'e' + QString::number(column - 1) + QString::number(column-1);
                            Unit* un = new Unit("Test", str, column - 1, column - 1);
                            un->setEmpty();
                            units.insert(str, un);
                            u->parents.append(un);
                            un->childs.append(u);
                        }
                        else
                        {
                            u->parents.append(units.value('e' + QString::number(column - 1) + QString::number(column - 1)));
                            units.value('e' + QString::number(column - 1) + QString::number(column - 1))->childs.append(u);
                        }
                        
                    }
                    else if (str2[0] == '1' || str2[0] == '0')
                    {
                        str2.remove(QChar ('/'));
                        str2.remove(QChar('.'));
                        int length = str2.length();
                        int count = 0;
                        QString str3;
                        for (int i = 0; i < csvModel->rowCount() - 1; i++)
                        {
                            str3 = csvModel->index(i, iter).data().toString();
                            if (str3[0] == 'c' || str3[0] == 'с')
                            {
                                if (str2[count] == '1')
                                {
                                    u->parents.append(units.value(str3));
                                    units.value(str3)->childs.append(u);
                                }
                                count++;
                            }
                            if (count == length)
                                break;
                        }
                    }
                }
            }
        }
    }
    fillEmptyElements();
}
void Diagram::fillEmptyElements()
{
    QString str4 = 'e' + QString::number(csvModel->columnCount()) + QString::number(csvModel->columnCount());
    Unit* un = new Unit("Test", str4, csvModel->columnCount(), csvModel->columnCount());
    un->setEmpty();
    for (int row = 1; row < csvModel->rowCount(); ++row)
    {

        for (int column = 2; column < csvModel->columnCount(); ++column)
        {

            QString str = csvModel->index(row, column).data().toString();
            
            if (str[0] == '1' || str[0] == '0')
            {
                str.remove(QChar('/'));
                str.remove(QChar('.'));
                int length = str.length();
                int count = 0;
                QString str2;
                for (int i = column; i < csvModel->columnCount(); i++)
                {
                    str2 = csvModel->index(row, i).data().toString();
                    if (str2[0] == 'c' || str2[0] == 'с')
                        count++;
                }
                if (count == 0)
                {
                    
                    for (int i = 0; i < csvModel->rowCount() - 1; i++)
                    {
                        str2 = csvModel->index(i, column).data().toString();
                        if (str2[0] == 'c' || str2[0] == 'с')
                        {
                            if (str[count] == '1')
                            {
                                un->parents.append(units.value(str2));
                                units.value(str2)->childs.append(un);
                            }
                            count++;
                        }
                        if (count == length)
                            break;
                    }
                    units.insert(str4, un);
                }
            }
        }
    }

   // printDebug();
}
void Diagram::AddEl(int i, int j, QString str1, QString str2, bool isEmpty)
{
    
    printDebug();
    scene.addElement(i,j,str1,str2,isEmpty,counts[j]);
    if(!isEmpty)
    ui.listWidget->addItem("[" + str2+"] "+str1);
}
void Diagram::ReadFromFile()
{
    csvModel = new QStandardItemModel(this);
    QFile file("data4.csv");

    bool isFirst = true;
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "File not exists";
    }
    else {
        
        QTextStream in(&file);
        
        while (!in.atEnd())
        {
            
            QString line = in.readLine();
            
            QList<QStandardItem*> standardItemsList;
            
            for (QString item : line.split(";")) {
                standardItemsList.append(new QStandardItem(item));
            }
            if (isFirst)
            {
                isFirst = false;
                csvModel->setColumnCount(standardItemsList.count());
            }
            csvModel->insertRow(csvModel->rowCount(), standardItemsList);
        }
        file.close();
    }
}
