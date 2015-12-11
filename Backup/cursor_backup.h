#ifndef CURSOR_H
#define CURSOR_H

#endif // CURSOR_H

class Cursor
{
public:
    void setposx();
    double getposx();
    void setwindowposx();
    int getwindowposx();
    Cursor();

private:

    double posx;
    int windowposx;
    bool visible;
    bool infocus;



};
