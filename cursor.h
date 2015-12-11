#include <QLineEdit>
#include <QColor>

#ifndef CURSOR_H
#define CURSOR_H

#endif // CURSOR_H

#include "/usr/src/QT/Extras/qcustomplot/qcustomplot.h"    //QCustomPlot header files

struct VCursor
{
public:
    VCursor();
    double getPosx();
    void setPosx(double x);

private:
    double posx;



};
struct HCursor
{
public:
    HCursor();
    double getPosy();
    void setPosy(double y);

private:
    double posy;
};

class Cursor
{
public:




    Cursor();

    HCursor hcursor;
    VCursor vcursor;


    void setPos(double x, double y);
    void setposx();         //Moves the cursor
    double getposx();       //Returns the x-position of the cursor
    void setposx(double posx_);
    QPen getPen();
    void setwindowposx(double xclick, double xwindow);
    int getwindowposx();    //Returns the window x-position of the cursor


    void setColor(QColor color_);
    QColor getColor();
    void setDashed(bool dashed);

    //void createCursors();

    //QCPItemLine* xCursor, *yCursor;
    //QCustomPlot* custplot;

private:

    double posx;             //Position of cursor along x-axis

    int windowposx;          //Position of cursor w/ respect to main widget

    bool visible;            //Is cursor present on screen?
    QPen pen;

    QColor color;


};
