#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define PI 3.14159

#include <QMainWindow>
#include "/usr/src/QT/Extras/qcustomplot/qcustomplot.h"    //QCustomPlot header files
#include <stdlib.h>
#include <math.h>
#include <string>
#include <sstream>
#include <iostream>
#include <QVector>
#include <QTextStream>
#include "file.h"
#include "plot.h"
#include "data.h"
#include "cursor.h"
#include <QLineEdit>
#include <QColor>
#include "eventmanager.h"
#include <QWidget>
#include "columnselect_dialogue.h"
#include "overwritefile_dialogue.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    //These are QT definitions; do not change!
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0 );
    ~MainWindow();
    QApplication * Qapp;


    /////////////////////////////////////////
    //These are written by the app programmer
    /////////////////////////////////////////

    /////////
    //Classes
    /////////

    File file;  //Class responsible for opening and managing the opened file.

    Data data;  //Holds the part of the data from the input file that is in scope (stored in std::vector)

    Plot plot;  //Contains plotting functions, functions to change data range, etc.

    Cursor cursor1, cursor2, eventcursor1, eventcursor2;  //Cursors that show on plot
    QCPItemLine* hScursor1, *vScursor1;  //Pointers to ui elements so cursors can be created/destroyed
    QCPItemLine* hScursor2, *vScursor2;
    QCPItemLine* eventScursor1, *eventScursor2;

    EventManager eventmanager;  //Contains information about events, a vector holding all events, etc.

    ///////////
    //Functions
    ///////////

    void disableWidgets();   //Disables all widgets until file is opened
    void enableWidgets();    //Activates all widgets for user interaction when file is opened

    void SetUpCursors();     //These SetUpXXXXX functions initialize the parameters for various ui elements,
    void SetUpScrollBars();  //some time after mainwindow initialization
    void SetUpLabels();
    void SetUpFields();
    void SetUpButtons();


    void changeYrange(int value_);                           //Changes y-axis plot range; e.g. called whenever
                                                             //y-scrollbar moved
    int getYbarvalue(double yvalue_);                           //Returns value() of ybar for given yvalue_

    void goTotime(double time_);                             //Moves plot range to time_
    void goToevent(Event* event_);                           //Centers the plot on event_
    void scopeData(double x1, double x2);

    void FindNextEvent();                                       //Starts at end of latest event, looks for next event
    void FindNextEvent(double searchstarttime_);
    void findPotentialeventstart(double searchstarttime);       //Looks for the start of event
    bool findPotentialeventend();                               //Looks for end of event
    bool findPotentialeventendnew();
    void findPeaks(Event* event);

    void acceptEvent(Event* event);                         //Sets the event's acceptance to accepted/neutral
    void rejectEvent(Event* event);                         //Sets the event's acceptance to rejected/neutral

    void setEventcursors(double t1, double t2);                 //Sets the event cursors at times t1, t2
    void setEventcursors(double t1, double t2, QColor color);   //Overloaded function; can also specify color

    void updateEventfields();            //Changes the labels for the event fields, e.g. number events accepted, etc.

    void setAcceptRejectbuttons();       //Changes cosmetics of accept/reject buttons based on event's acceptance
    void updateTargetedeventfield();     //Updates the targeted event field, which tells time of current event and etc.

    bool openOverwritefiledialog(QString filename);

private slots:
    //Slots are activated when gui receives user input

    void on_xbar_sliderMoved(int position);

    void on_xbar_valueChanged(int value);

    void on_xZoomIn_clicked();

    void on_xZoomOut_clicked();

    void on_yZoomIn_clicked();

    void on_yZoomOut_clicked();

    void on_ybar_sliderMoved(int position);

    void on_ybar_valueChanged(int value);

    void on_actionOpen_File_triggered();

    void mousePress(QMouseEvent* click);

    void on_actionFind_Next_Event_triggered();

    void on_Integrate_clicked();

    void on_Accept_Event_clicked();

    void on_Reject_Event_clicked();

    void on_Previous_Event_clicked();

    void on_Next_Event_clicked();

    void on_AverageLength_Field_returnPressed();

    void on_AverageLength_Field_textEdited(const QString &arg1);

    void on_L_NoiseTolerance_Field_textEdited(const QString &arg1);

    void on_L_NoiseMultiplier_Field_textEdited(const QString &arg1);

    void on_L_NoiseMultiplier_Field_cursorPositionChanged();

    void on_Find_Next_Event_clicked();

    void on_Retry_Search_clicked();

    void on_Last_Event_clicked();

    void on_First_Event_clicked();

    void on_R_NoiseMultiplier_Field_textEdited(const QString &arg1);

    void on_R_NoiseTolerance_Field_textEdited(const QString &arg1);

    void on_actionFind_All_Events_triggered();

    void on_Save_Left_Cursor_clicked();

    void on_Center_On_Data_clicked();

    void on_Save_Parameters_clicked();

    void on_Load_Parameters_clicked();

private:
    Ui::MainWindow *ui; //Pointer to ui, which contains all widget elements

    int xscrollres;
    int xbarrange;      //Number of clicks from one end of x-scroll to the other end
    double xsliderconstant;

    int ybarrange;      // ""    ""   ""    ""   ""  "" ""  y-scroll "" ""  ""    ""
    double ysliderconstant;

    //Event search parameters; see functions in main.cpp for an explanation for how events are found

    QString parameterdirectory;
    int averagelength;           //Time duration averaged for baseline; should be >= noise period

    int aftereventdelay;         //Time delay after event where search for next event starts

    int leftnoisetolerance;      //Number of data points that can be inside threshold w/o being considered back in baseline
    double leftnoisemultiplier;  //Multiples of baseline std dev; data can go this amount away from baseline before
                                 //considered out of baseline

    int rightnoisetolerance;     //Number of points averaged that must be within baseline +/- noise multiplier
    double rightnoisemultiplier; //Same as left, but for being considered back inside the baseline
    double rightsecondarynoisemultiplier;
    int autorejectlength;
    bool autoreject;

    bool endofsearch;   //Bool to determine if end of file is found

    int errorreturnvalue;

};

#endif // MAINWINDOW_H
