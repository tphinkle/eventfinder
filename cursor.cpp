#include "cursor.h"

VCursor::VCursor()
{}

double VCursor::getPosx()
{
    return posx;
}

void VCursor::setPosx(double x)
{
    posx = x;
    return;
}

HCursor::HCursor()
{}


double HCursor::getPosy()
{
    return posy;
}

void HCursor::setPosy(double y)
{
    posy = y;
    return;
}


Cursor::Cursor( )
{
    pen.setWidth(2);

}


QPen Cursor::getPen()
{
    return pen;
}

void Cursor::setPos(double x, double y)
{
    vcursor.setPosx(x);
    hcursor.setPosy(y);
    posx = x;
    return;
}

void Cursor::setDashed(bool dashed)
{
    if( dashed == true )
    {
        pen.setStyle(Qt::DotLine);
    }
    else
    {
        pen.setStyle(Qt::SolidLine);
    }
    return;
}

void Cursor::setwindowposx(double xclick, double xwindow)
{
    windowposx = xclick + xwindow;
    return;
}



void Cursor::setColor(QColor color_)
{
    color = color_;
    pen.setColor( color );
    return;
}

QColor Cursor::getColor()
{
    return color;
}

double Cursor::getposx()
{
    return posx;
}

void Cursor::setposx(double posx_)
{
    posx = posx_;
    return;
}

int Cursor::getwindowposx()
{
    return windowposx;
}
