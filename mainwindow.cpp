#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include <QDataStream>
#include <QFile>
#include <QLineEdit>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    connect(ui->MainPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress(QMouseEvent*)));

    parameterdirectory = "/home/preston/Desktop/Science/Research/QTApplications/eventfinder/parameters/";
    averagelength = 50;
    leftnoisetolerance = 5;
    leftnoisemultiplier = 4;
    rightnoisemultiplier = 0.5;
    rightnoisetolerance = 75;
    aftereventdelay = 100;
    rightsecondarynoisemultiplier = 1.5;
    autorejectlength = 10;
    autoreject = true;

    errorreturnvalue = -1;

    plot.custplot = ui->MainPlot;
    setWindowTitle("EventFinder");
    statusBar()->clearMessage();

    disableWidgets();

    SetUpScrollBars();

    SetUpCursors();

    SetUpLabels();

    SetUpFields();

    eventmanager.setPotentialevent(NULL);
    ui->MainPlot->setInteractions(QCP::iSelectItems);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetUpScrollBars()
{


    xsliderconstant = 1/20.0;
    xbarrange = 20000;
    ui->xbar->setRange(0, xbarrange);

    ysliderconstant = 1/20.0;
    ybarrange = 20000;
    ui->ybar->setRange(0, ybarrange);
    return;
}

void MainWindow::SetUpCursors()
{
    cursor1.setColor(Qt::black);
    cursor2.setColor(Qt::black);
    cursor1.setDashed(true);
    cursor2.setDashed(true);
    eventcursor1.setColor(Qt::blue);
    eventcursor2.setColor(Qt::blue);
    eventcursor1.setDashed(true);
    eventcursor2.setDashed(true);

    ui->LeftLineText->setReadOnly(true);
    ui->RightLineText->setReadOnly(true);
    ui->LeftLineText->setFrameStyle(QFrame::NoFrame);
    ui->RightLineText->setFrameStyle(QFrame::NoFrame);
    ui->LeftLineText->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->RightLineText->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->LeftLineText->setTextColor(cursor1.getColor());
    ui->RightLineText->setTextColor(cursor2.getColor());
    ui->LeftLineText->viewport()->setAutoFillBackground(false);
    ui->RightLineText->viewport()->setAutoFillBackground(false);
    ui->LeftLineText->setAlignment(Qt::AlignCenter);
    ui->RightLineText->setAlignment(Qt::AlignCenter);
    return;
}

void MainWindow::SetUpLabels()
{
    ui->EventActions_Label->setReadOnly(true);

    ui->AverageLength_Label->setReadOnly(true);
    ui->NoiseTolerance_Label->setReadOnly(true);

    ui->NoiseMultiplier_Label->setReadOnly(true);

    ui->EventActions_Label->viewport()->setAutoFillBackground(false);
    ui->AverageLength_Label->viewport()->setAutoFillBackground(false);
    ui->NoiseTolerance_Label->viewport()->setAutoFillBackground(false);
    ui->NoiseMultiplier_Label->viewport()->setAutoFillBackground(false);

    ui->EventActions_Label->setFrameStyle(QFrame::NoFrame);
    ui->AverageLength_Label->setFrameStyle(QFrame::NoFrame);
    ui->NoiseTolerance_Label->setFrameStyle(QFrame::NoFrame);
    ui->NoiseMultiplier_Label->setFrameStyle(QFrame::NoFrame);

    ui->TotalEvents_Label->viewport()->setAutoFillBackground(false);
    ui->TotalEvents_Label->setFrameStyle(QFrame::NoFrame);
    ui->TotalEvents_Label->setReadOnly(true);


    ui->TotalEvents_Field->viewport()->setAutoFillBackground(false);
    ui->TotalEvents_Field->setFrameStyle(QFrame::NoFrame);
    ui->TotalEvents_Field->setReadOnly(true);

    ui->Accepted_Label->viewport()->setAutoFillBackground(false);
    ui->Accepted_Label->setFrameStyle(QFrame::NoFrame);
    ui->Accepted_Label->setReadOnly(true);

    ui->Accepted_Field->viewport()->setAutoFillBackground(false);
    ui->Accepted_Field->setFrameStyle(QFrame::NoFrame);
    ui->Accepted_Field->setReadOnly(true);

    ui->Neutral_Label->viewport()->setAutoFillBackground(false);
    ui->Neutral_Label->setFrameStyle(QFrame::NoFrame);
    ui->Neutral_Label->setReadOnly(true);

    ui->Neutral_Field->viewport()->setAutoFillBackground(false);
    ui->Neutral_Field->setFrameStyle(QFrame::NoFrame);
    ui->Neutral_Field->setReadOnly(true);

    ui->Rejected_Label->viewport()->setAutoFillBackground(false);
    ui->Rejected_Label->setFrameStyle(QFrame::NoFrame);
    ui->Rejected_Label->setReadOnly(true);

    ui->Rejected_Field->viewport()->setAutoFillBackground(false);
    ui->Rejected_Field->setFrameStyle(QFrame::NoFrame);
    ui->Rejected_Field->setReadOnly(true);

    ui->TargetedEvent_Label->viewport()->setAutoFillBackground(false);
    ui->TargetedEvent_Label->setFrameStyle(QFrame::NoFrame);
    ui->TargetedEvent_Label->setReadOnly(true);

    ui->TargetedEvent_Field->viewport()->setAutoFillBackground(false);
    ui->TargetedEvent_Field->setFrameStyle(QFrame::NoFrame);
    ui->TargetedEvent_Field->setReadOnly(true);


    return;


}

void MainWindow::SetUpFields()
{
    ui->AverageLength_Field->setText(QString::number(averagelength));
    ui->L_NoiseTolerance_Field->setText(QString::number(leftnoisetolerance));
    ui->L_NoiseMultiplier_Field->setText(QString::number(leftnoisemultiplier));
    ui->R_NoiseTolerance_Field->setText(QString::number(rightnoisetolerance));
    ui->R_NoiseMultiplier_Field->setText(QString::number(rightnoisemultiplier));
    ui->TotalEvents_Field->setText("0");
    ui->Accepted_Field->setText("0");
    ui->Neutral_Field->setText("0");
    ui->Rejected_Field->setText("0");
    ui->TargetedEvent_Field->setText("n/a");
    return;
}

void MainWindow::SetUpButtons()
{

    ui->Accept_Event->setAutoFillBackground(true);

    ui->Reject_Event->setAutoFillBackground(true);

    return;
}

void MainWindow::disableWidgets()
{
    ui->xbar->setEnabled(false);
    ui->ybar->setEnabled(false);

    ui->xZoomIn->setEnabled(false);
    ui->xZoomOut->setEnabled(false);
    ui->yZoomIn->setEnabled(false);
    ui->yZoomOut->setEnabled(false);
    ui->Center_On_Data->setEnabled(false);

    ui->AverageLength_Field->setEnabled(false);
    ui->L_NoiseTolerance_Field->setEnabled(false);
    ui->R_NoiseTolerance_Field->setEnabled(false);
    ui->L_NoiseMultiplier_Field->setEnabled(false);
    ui->R_NoiseMultiplier_Field->setEnabled(false);
    ui->Save_Parameters->setEnabled(false);
    ui->Load_Parameters->setEnabled(false);

    ui->Accept_Event->setEnabled(false);
    ui->Reject_Event->setEnabled(false);

    ui->Retry_Search->setEnabled(false);
    ui->Find_Next_Event->setEnabled(false);

    ui->Integrate->setEnabled(false);

    ui->Save_Left_Cursor->setEnabled(false);

    ui->First_Event->setEnabled(false);
    ui->Previous_Event->setEnabled(false);
    ui->Next_Event->setEnabled(false);
    ui->Last_Event->setEnabled(false);


    return;
}

void MainWindow::enableWidgets()
{
    ui->xbar->setEnabled(true);
    ui->ybar->setEnabled(true);

    ui->xZoomIn->setEnabled(true);
    ui->xZoomOut->setEnabled(true);
    ui->yZoomIn->setEnabled(true);
    ui->yZoomOut->setEnabled(true);
    ui->Center_On_Data->setEnabled(true);

    ui->AverageLength_Field->setEnabled(true);
    ui->L_NoiseTolerance_Field->setEnabled(true);
    ui->R_NoiseTolerance_Field->setEnabled(true);
    ui->L_NoiseMultiplier_Field->setEnabled(true);
    ui->R_NoiseMultiplier_Field->setEnabled(true);
    ui->Save_Parameters->setEnabled(true);
    ui->Load_Parameters->setEnabled(true);

    ui->Accept_Event->setEnabled(true);
    ui->Reject_Event->setEnabled(true);

    ui->Retry_Search->setEnabled(true);
    ui->Find_Next_Event->setEnabled(true);

    ui->Integrate->setEnabled(true);

    ui->Save_Left_Cursor->setEnabled(true);

    ui->First_Event->setEnabled(true);
    ui->Previous_Event->setEnabled(true);
    ui->Next_Event->setEnabled(true);
    ui->Last_Event->setEnabled(true);

    return;
}


void MainWindow::on_actionOpen_File_triggered()
{

    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open file"),
                file.getDirectory(), tr("Axon Text Files (*.atf)"));

    if( filename != NULL )
    {
        file.OpenFile(filename);
    }

    else
    {
        return;
    }


    if( file.getColumncount() > 2 )
    {
        columnselect_dialogue cdialogue(0, file.getColumncount() );
        cdialogue.setModal(true);
        cdialogue.exec();
        file.ycolumn = cdialogue.ycolumn;
    }
    else
    {
        file.ycolumn = 1;
    }

    enableWidgets();

    file.transferDatanew();

    setWindowTitle(file.getInputFile());

    plot.SetupPlot(file.getPeriod(), file.getTotaldatapoints(), file.getMaxValue(), file.getMinValue());

    data.SetupData(file.getPeriod(), file.getFrequency(), file.getMaxdatapoints() );

    xbarrange = (int)(plot.xfullrangehigh/(xsliderconstant*plot.xrange));

    plot.SetPlotRange(ui->xbar->value(), ui->ybar->value(), xbarrange, ybarrange);

    std::cerr << "299\n";

    file.Copy_Data_New(data.x, data.y, plot.xrangelow);

    plot.SetData(data.x, data.y);

    on_Center_On_Data_clicked();

    on_xZoomIn_clicked();

    return;
}


void MainWindow::on_xbar_valueChanged(int value)
{
    //NEW CHANGE! Shouldn't have to ui->MainPlot->graph(0)->setData(data.x, data.y) every time! This will slow things down a LOT


    plot.xrangelow = (plot.xfullrangehigh-plot.xfullrangelow - plot.xrange)*1.0*value/xbarrange;
    plot.xrangehigh = plot.xrangelow + plot.xrange;
    plot.custplot->xAxis->setRange(plot.xrangelow, plot.xrangehigh);

    if( plot.xrangehigh > data.x[data.getMaxDataPoints() - 1] + file.getPeriod() * 0.1 )
    {
        std::cerr << "loading new data...\n";
        file.Copy_Data_New( data.x, data.y, plot.xrangelow );
        ui->MainPlot->graph(0)->setData(data.x, data.y);
    }

    if( plot.xrangelow < data.x[0] )
    {
        std::cerr << "loading new data...\n";
        file.Copy_Data_New( data.x, data.y, plot.xrangelow );
        ui->MainPlot->graph(0)->setData(data.x, data.y);
    }

    ui->MainPlot->replot();

    return;

}

void MainWindow::on_xbar_sliderMoved(int position)
{

    on_xbar_valueChanged(position);
    return;
}

void MainWindow::on_xZoomIn_clicked()
{

    double xstationary = plot.xrangelow + plot.xrange/2.0;



    plot.xrange = .5*plot.xrange;




    xbarrange = (int)(plot.xfullrange/(plot.xrange*xsliderconstant));

    ui->xbar->setMaximum(xbarrange);

    int newvalue = (int)((xbarrange)*((xstationary - plot.xrange/2.0)/(plot.xfullrange-plot.xrange)));


    ui->xbar->setValue(newvalue);

    return;
}

void MainWindow::on_xZoomOut_clicked()
{
    double xstationary = plot.xrangelow + plot.xrange/2.0;

    plot.xrange = 1.5*plot.xrange;
    double doublejunk = (3.0/4)*data.getMaxDataPoints()*file.getPeriod();
    if(plot.xrange > doublejunk)
    {
        plot.xrange = doublejunk;
    }

    xbarrange = (int)(plot.xfullrange/(plot.xrange*xsliderconstant));

    int newvalue = (int)((xbarrange)*((xstationary - plot.xrange/2.0)/(plot.xfullrange-plot.xrange)));

    if(newvalue < 0)
    {
        newvalue = 0;
        if(ui->xbar->value() == newvalue )
        {
            on_xbar_valueChanged(newvalue);
            ui->xbar->setMaximum(xbarrange );
            return;
        }
    }

    else if(newvalue > xbarrange)
    {
        newvalue = xbarrange;
        if(ui->xbar->value() == newvalue)
        {
            on_xbar_valueChanged(newvalue);
            ui->xbar->setMaximum(xbarrange );
            return;
        }
    }

    ui->xbar->setValue(newvalue);
    ui->xbar->setMaximum(xbarrange );

    return;

}

void MainWindow::changeYrange(int value)
{

    //plot.yrangehigh = plot.yfullrangehigh - (plot.yfullrange*value)/ybarrange;
    plot.yrangehigh = 1.0*(ybarrange - value)*plot.yfullrange/ybarrange + plot.yfullrangelow;
    plot.yrangelow = plot.yrangehigh - plot.yrange;

    ui->MainPlot->yAxis->setRange(plot.yrangelow, plot.yrangehigh);
    ui->MainPlot->replot();
    return;
}

void MainWindow::on_ybar_valueChanged(int value)
{
    changeYrange(value);

    return;
}

int MainWindow::getYbarvalue(double yvalue_)
{
/*
    std::cerr << "yvalue = " << yvalue_ << "\n";
    std::cerr << "plot.yfullrangelow = " << plot.yfullrangelow << "\n";
    std::cerr << "plot.yrange = " << plot.yrange << "\n";
    std::cerr << "ybarrange = " << ybarrange << "\n";
    std::cerr << "plot.yfullrangehigh = " << plot.yfullrangehigh << "\n";*/

    //int ybarvalue = ybarrange*((plot.yfullrangehigh - (yvalue_ - 0.5* plot.yrange))/(plot.yfullrangehigh - plot.yfullrangelow));

    int ybarvalue = ybarrange*(plot.yfullrangehigh - yvalue_)/plot.yfullrange;

    if(ybarvalue > ybarrange )
    {
        ybarvalue = ybarrange;
    }

    else if(ybarvalue < 0)
    {
        ybarvalue = 0;
    }

    return ybarvalue;
}

void MainWindow::on_ybar_sliderMoved(int position)
{
    changeYrange(position);
    return;
}

void MainWindow::on_yZoomIn_clicked()
{
    double ystationary = plot.yrangehigh - plot.yrange/2.0;

    plot.yrange = .5*plot.yrange;



    ybarrange = (int)(plot.yfullrange/(ysliderconstant*plot.yrange));

    //std::cerr << "ybarrange = " << ybarrange << "\n";

    ui->ybar->setMaximum(ybarrange);

    int newvalue = (int)((plot.yfullrangehigh - ystationary-plot.yrange/2)*ybarrange/plot.yfullrange);


    ui->ybar->setValue(newvalue);

    return;
}

void MainWindow::on_yZoomOut_clicked()
{
    double ystationary = plot.yrangehigh - plot.yrange/2.0;

    plot.yrange = 1.5*plot.yrange;



    ybarrange = (int)(plot.yfullrange/(ysliderconstant*plot.yrange));

    //std::cerr << "ybarrange = " << ybarrange << "\n";

    ui->ybar->setMaximum(ybarrange);

    int newvalue = (int)((plot.yfullrangehigh - ystationary-plot.yrange/2)*ybarrange/plot.yfullrange);

    if(newvalue < 0)
    {
        newvalue = 0;
        if(ui->ybar->value() == 0 )
        {
            on_ybar_valueChanged(newvalue);
        }
    }
    else if(newvalue > ybarrange)
    {
        newvalue = ybarrange;
        if(ui->ybar->value() == ybarrange)
        {
            on_ybar_valueChanged(ybarrange);
        }

    }

    ui->ybar->setValue(newvalue);

    return;

}


void MainWindow::mousePress(QMouseEvent* click)
{
    if( file.getFileLoaded() == false )
    {
        return;
    }

    int lefttextboxposX;
    int righttextboxposX;
    int xprecision;

    QString leftxstring;
    QString leftystring;
    QString lefttotalstring;
    QString rightxstring;
    QString rightystring;
    QString righttotalstring;
    QString deltat;

    double x = ui->MainPlot->xAxis->pixelToCoord(click->pos().x());


    if( x < ui->MainPlot->xAxis->range().lower  || x > ui->MainPlot->xAxis->range().upper )
    {
        return;
    }

    double y = data.gety(x);




    if( click->button() == Qt::LeftButton )
    {
        static QCPItemLine* hScursor1, *vScursor1;
        if(ui->MainPlot->xAxis->pixelToCoord(click->pos().x()) == cursor1.getposx())
        {
            cursor1.setposx(-1);
            ui->MainPlot->removeItem(hScursor1);
            ui->MainPlot->removeItem(vScursor1);
            ui->MainPlot->replot();
            ui->LeftLineText->setText("");
            ui->RightLineText->move(cursor2.getwindowposx() - ui->RightLineText->width()/2, ui->RightLineText->y());
            return;
        }

        cursor1.setPos(x, y);
        cursor1.setwindowposx(ui->MainPlot->x(), click->x());



        if(hScursor1 || vScursor1)
        {
            ui->MainPlot->removeItem(hScursor1);
            ui->MainPlot->removeItem(vScursor1);
        }



        hScursor1 = new QCPItemLine(ui->MainPlot);
        vScursor1 = new QCPItemLine(ui->MainPlot);

        hScursor1->setPen( cursor1.getPen() );
        vScursor1->setPen( cursor1.getPen() );

        ui->MainPlot->addItem(hScursor1);
        ui->MainPlot->addItem(vScursor1);


        vScursor1->start->setCoords(x, QCPRange::minRange);
        vScursor1->end->setCoords(x, QCPRange::maxRange);

        hScursor1->start->setCoords(QCPRange::minRange, y );
        hScursor1->end->setCoords(QCPRange::maxRange, y);


    }

    else if( click->button() == Qt::RightButton )
    {

        static QCPItemLine* hScursor2, *vScursor2;

        if(ui->MainPlot->xAxis->pixelToCoord(click->pos().x()) == cursor2.getposx())
        {
            cursor2.setposx(-1);
            ui->MainPlot->removeItem(hScursor2);
            ui->MainPlot->removeItem(vScursor2);
            ui->MainPlot->replot();
            ui->RightLineText->setText("");
            ui->LeftLineText->move(cursor1.getwindowposx() - ui->LeftLineText->width()/2, ui->LeftLineText->y());
            return;
        }

        cursor2.setPos(x, y);
        cursor2.setwindowposx(ui->MainPlot->x(), click->x());

        if(hScursor2 || vScursor2)
        {
            ui->MainPlot->removeItem(hScursor2);
            ui->MainPlot->removeItem(vScursor2);
        }

        hScursor2 = new QCPItemLine(ui->MainPlot);
        vScursor2 = new QCPItemLine(ui->MainPlot);
        hScursor2->setPen( cursor2.getPen() );
        vScursor2->setPen( cursor2.getPen() );
        ui->MainPlot->addItem(hScursor2);
        ui->MainPlot->addItem(vScursor2);

        vScursor2->start->setCoords(x, QCPRange::minRange);
        vScursor2->end->setCoords(x, QCPRange::maxRange);

        hScursor2->start->setCoords(QCPRange::minRange, y );
        hScursor2->end->setCoords(QCPRange::maxRange, y);


    }

    if(abs(cursor1.getwindowposx() - cursor2.getwindowposx()) >= ui->RightLineText->width())
    {
        lefttextboxposX = cursor1.getwindowposx() - ui->LeftLineText->width()/2;
        righttextboxposX = cursor2.getwindowposx() - ui->RightLineText->width()/2;
    }

    else if( cursor1.getwindowposx() < cursor2.getwindowposx())
    {
        lefttextboxposX =  cursor1.getwindowposx() - (ui->LeftLineText->width()  - abs(cursor1.getwindowposx() - cursor2.getwindowposx())/2);
        righttextboxposX =  cursor2.getwindowposx() - abs(cursor1.getwindowposx() - cursor2.getwindowposx())/2;
    }
    else if( cursor1.getwindowposx() > cursor2.getwindowposx())
    {
        righttextboxposX =  cursor2.getwindowposx() - (ui->RightLineText->width()  - abs(cursor1.getwindowposx() - cursor2.getwindowposx())/2);
        lefttextboxposX =  cursor1.getwindowposx() - abs(cursor1.getwindowposx() - cursor2.getwindowposx())/2;
    }


    ui->LeftLineText->move(lefttextboxposX, ui->LeftLineText->y());
    ui->RightLineText->move(righttextboxposX, ui->RightLineText->y());

    xprecision = (int) (-1.0*log10(file.getPeriod()) + 0.99);

    if ( x < 0.01 )
    {
        xprecision = xprecision - 2;
    }

    if( x < 0.1 )
    {
        xprecision = xprecision - 1;
    }

    if( x < 1 )
    {
        xprecision = xprecision + 0;
    }
    else if( x < 10 )
    {
        xprecision = xprecision + 1;
    }
    else if( x < 100 )
    {
        xprecision = xprecision + 2;
    }
    else if( x < 1000 )
    {
        xprecision = xprecision + 3;
    }
    else if( x < 10000 )
    {
        xprecision = xprecision + 4;
    }

    double deltatdoub;

    if(click->button() == Qt::LeftButton)
    {
        leftxstring = leftxstring.QString::setNum(x, 'g', xprecision);
        leftystring = leftystring.QString::setNum(y, 'g', 6);
        lefttotalstring = "t = " + leftxstring + " s\nI = " + leftystring + " pA\n";

        rightxstring = rightxstring.QString::setNum(cursor2.getposx(), 'g', xprecision);
        rightystring = rightystring.QString::setNum(data.gety(cursor2.getposx()), 'g', 6);
        righttotalstring = "t = " + rightxstring + " s\nI = " + rightystring + " pA\n";
        deltatdoub = cursor2.getposx() - x;
        if(deltatdoub < 0 )
        {
            deltatdoub = deltatdoub * (-1);
        }
        deltat = deltat.QString::setNum(deltatdoub, 'g', xprecision);

    }


    else if(click->button() == Qt::RightButton)
    {
        rightxstring = rightxstring.QString::setNum(x, 'g', xprecision);
        rightystring = rightystring.QString::setNum(y, 'g', 6);
        righttotalstring = "t = " + rightxstring + " s\nI = " + rightystring + " pA\n";

        leftxstring = leftxstring.QString::setNum(cursor1.getposx() , 'g', xprecision);
        leftystring = leftystring.QString::setNum(data.gety(cursor1.getposx()), 'g', 6);
        lefttotalstring = "t = " + leftxstring + " s\nI = " + leftystring + " pA\n";
        deltatdoub = cursor1.getposx() - x;
        if(deltatdoub < 0 )
        {
            deltatdoub = deltatdoub * (-1);
        }
        deltat = deltat.QString::setNum(deltatdoub, 'g', xprecision);

    }



    if( ui->LeftLineText->x() < ui->RightLineText->x())
    {
        righttotalstring = righttotalstring + "dt = " + deltat + " s";
    }
    else
    {
        lefttotalstring = lefttotalstring + "dt = " + deltat + " s";
    }

    ui->LeftLineText->setAlignment(Qt::AlignCenter);
    ui->LeftLineText->setPlainText( lefttotalstring );

    ui->RightLineText->setAlignment(Qt::AlignCenter);
    ui->RightLineText->setPlainText( righttotalstring );



    ui->MainPlot->replot();
    return;

}


void MainWindow::on_actionFind_Next_Event_triggered()
{
    FindNextEvent();
    return;
}



void MainWindow::FindNextEvent()
{
    double searchstarttime;


    if( eventmanager.potentialevent == NULL )
    {
        searchstarttime = 0;
    }

    else
    {
        int searchindex = eventmanager.eventlist.size();
        searchstarttime = eventmanager.eventlist[searchindex - 1]->getEndtime() + file.getPeriod() * aftereventdelay;
    }

    if(searchstarttime > file.getTotaldatapoints()*file.getPeriod())
    {
        endofsearch = true;
        return;
    }

    eventmanager.setPotentialevent(new Event(eventmanager.eventlist.size()));


    findPotentialeventstart(searchstarttime);

    if( findPotentialeventend() == true )
    {

        eventmanager.addEventtolist(eventmanager.potentialevent);                        //add event to eventlist vector

        eventmanager.potentialevent->setIndex(eventmanager.eventlist.size() - 1);            //set event's index

        goToevent( eventmanager.potentialevent );

        on_Center_On_Data_clicked();

        eventmanager.targetedevent = eventmanager.potentialevent;

        setEventcursors(eventmanager.potentialevent->getStarttime(), eventmanager.potentialevent->getEndtime());

        setAcceptRejectbuttons();

        eventmanager.incrementNumberofneutralevents();

        updateEventfields();


    }

    else
    {
        FindNextEvent(eventmanager.potentialevent->getEndtime());
    }

    return;

}


void MainWindow::FindNextEvent(double searchstarttime_)
{
    double searchstarttime = searchstarttime_;

    int searchindex = eventmanager.eventlist.size();


    if(searchstarttime > file.getTotaldatapoints()*file.getPeriod())
    {
        endofsearch = true;
        return;
    }

    eventmanager.setPotentialevent(new Event(eventmanager.eventlist.size()));


    findPotentialeventstart(searchstarttime);

    if( findPotentialeventend() == true )
    {

        eventmanager.addEventtolist(eventmanager.potentialevent);                        //add event to eventlist vector

        eventmanager.potentialevent->setIndex(eventmanager.eventlist.size() - 1);            //set event's index

        goToevent( eventmanager.potentialevent );

        on_Center_On_Data_clicked();

        eventmanager.targetedevent = eventmanager.potentialevent;

        setEventcursors(eventmanager.potentialevent->getStarttime(), eventmanager.potentialevent->getEndtime());

        setAcceptRejectbuttons();

        eventmanager.incrementNumberofneutralevents();

        updateEventfields();


    }

    else
    {
        FindNextEvent(eventmanager.potentialevent->getEndtime());
    }

    return;

}


void MainWindow::findPotentialeventstart(double searchstarttime)
{

    bool inbaseline = true;

    int searchindex = data.getIndex(searchstarttime);

    if( searchindex == errorreturnvalue )
    {
        endofsearch = true;
        return;
    }
    int secondarymultiplier = 1;

    std::cerr << "Search start time = " << searchstarttime << "\n";
    std::cerr << "Search start index = " << searchindex << "\n";
    double secondaryaverage = 0;
    double leftbaselineaverage = 0;
    double leftbaselinestddev = 0;


    //NEW: 3-21:
    //
    //Need to get rid of file.Copy_Data_New(args args_) function call... too expensive.
    //Changes: Get rid of file.Copy_Data_New(args args_); this will mean that the data window is not moved to the beginning
    //of the search start time; as a result, all indices for data.x and data.y need an offset of searchstarttime/period.
    //this is done by changing searchindex initialization above.
    //file.Copy_Data_New(data.x, data.y, searchstarttime, 0);
    //
    //END NEW: 3-21

    for( int i = 0; i < averagelength; i++ )                                            //INITIAL AVERAGING
    {
        leftbaselineaverage += data.y[searchindex];
        leftbaselinestddev += pow(data.y[searchindex], 2);
        searchindex++;

        if( searchindex >= data.getMaxDataPoints() - 1 )
        {
            if(searchstarttime + searchindex*file.getPeriod() > file.getTotaldatapoints()*file.getPeriod())
            {
                endofsearch = true;
                return;
            }
            else
            {
                findPotentialeventstart(searchstarttime + searchindex*file.getPeriod() ) ;
                return;
            }
        }
    }

    leftbaselineaverage = leftbaselineaverage/averagelength;
    leftbaselinestddev = pow(leftbaselinestddev/averagelength - leftbaselineaverage*leftbaselineaverage, 0.5);


    while( inbaseline == true )                                                     //BEGIN LOOP
    {

        inbaseline = false;

        for( int i = 0; i < leftnoisetolerance; i++ )                               //SCAN BLOCK OF LENGTH LEFTNOISETOLERANCE
        {

            if( abs(data.y[searchindex] - leftbaselineaverage) <= leftnoisemultiplier*leftbaselinestddev )
            {
                inbaseline = true;
            }

            searchindex++;

            if(searchindex >= data.getMaxDataPoints() - 1)
            {
                if(searchstarttime + searchindex*file.getPeriod() > file.getTotaldatapoints()*file.getPeriod())
                {
                    endofsearch = true;
                    return;
                }
                else
                {
                    findPotentialeventstart(searchstarttime + searchindex*file.getPeriod() );
                    return;
                }
            }


        }





        if( inbaseline == false )
        {
            /*!NEW!*/
            /*
            int potentialstart = 0;
            potentialstart = searchindex - leftnoisetolerance;
            bool backinbaseline = false;
            while(backinbaseline == false)
            {
                if(data.y)
            }
            */

            /*!END NEW!*/


            leftbaselineaverage = 0;  //NEW
            leftbaselinestddev = 0;

            int startt = searchindex - 2*averagelength - leftnoisetolerance - 1;
            if(startt < 0)
            {
                startt = 0;
            }
            for( int j = 0; j < averagelength; j++ )
            {
                //ERROR HERE!


                //leftbaselineaverage += data.y[searchindex - 2*averagelength - leftnoisetolerance + j - 1];
                //leftbaselinestddev += pow(data.y[searchindex - 2*averagelength - leftnoisetolerance + j - 1], 2);

                leftbaselineaverage += data.y[startt + j];
                leftbaselinestddev += pow(data.y[startt + j], 2);
            }

            leftbaselineaverage = leftbaselineaverage/averagelength;
            leftbaselinestddev = pow(leftbaselinestddev/averagelength - leftbaselineaverage*leftbaselineaverage, 0.5);


            secondaryaverage = 0;

            for( int i = 0; i < leftnoisetolerance; i++ )
            {
                secondaryaverage += data.y[searchindex - leftnoisetolerance + i - 1];
            }

            secondaryaverage = secondaryaverage/leftnoisetolerance;

            if( abs(secondaryaverage - leftbaselineaverage) < secondarymultiplier*leftbaselinestddev )
            {
                inbaseline = true;
            }

            if( inbaseline == false )
            {
                //eventmanager.potentialevent->setStarttime(searchstarttime + searchindex*file.getPeriod());
                eventmanager.potentialevent->setStarttime(data.x[0] + searchindex*file.getPeriod() );
                eventmanager.potentialevent->setLeftbaselineaverage(leftbaselineaverage);
                eventmanager.potentialevent->setLeftbaselinestddev(leftbaselinestddev);


                return;
            }

        }

    }

    return;
}

bool MainWindow::findPotentialeventendnew()
{

    bool potentialendfound = false;
    double endtime;

    double inbaselinethreshold = rightnoisemultiplier*eventmanager.potentialevent->getLeftbaselinestddev();

    return true;
}

bool MainWindow::findPotentialeventend()
{


    bool potentialendfound = false;
    double endtime;

    double inbaselinethreshold = rightnoisemultiplier*eventmanager.potentialevent->getLeftbaselinestddev();
    //double secondaryrightnoisemultiplier = 1;
    double secondaryinbaselinethreshold = rightsecondarynoisemultiplier*eventmanager.potentialevent->getLeftbaselinestddev();


    //NEW: 3-21:
    //
    //Need to get rid of file.Copy_Data_New(args args_) function call... too expensive.
    //Changes: Get rid of file.Copy_Data_New(args args_); this will mean that the data window is not moved to the beginning
    //of the search start time; as a result, all indices for data.x and data.y need an offset of searchstarttime/period.
    //this is done by changing searchindex initialization above.
    //file.Copy_Data_New(data.x, data.y, searchstarttime, 0);
    //
    //END NEW: 3-21

    int i = data.getIndex(eventmanager.potentialevent->getStarttime()) + 1;  //was 0

    double maxsearchtime = 0.5;

    if( file.getMaxdatapoints() - i < maxsearchtime*file.getPeriod() )
    {
        std::cerr << "1022: shouldn't proc...\n";
        file.Copy_Data_New(data.x, data.y, eventmanager.potentialevent->getStarttime(), 0.5);
        i = data.getIndex(eventmanager.potentialevent->getStarttime()) + 1;
    }

    int maxi = data.getIndex(eventmanager.potentialevent->getStarttime() + maxsearchtime );

    std::cerr << "1029: i = " << i << "   maxi = " << maxi << "\n";

    double average = 0;

    std::cerr << "begin looking for event end...\n";

    while(i < maxi)
    {
        while( potentialendfound == false )
        {
            if( abs(data.y[i] - eventmanager.potentialevent->getLeftbaselineaverage()) < inbaselinethreshold )
            {
                potentialendfound = true;
            }

            i++;

            if( i >= maxi )
            {

                endtime = data.x[i];
                eventmanager.potentialevent->setEndtime(endtime);
                return true;
            }


        }

        average = 0;


        for( int j = 0; j < rightnoisetolerance; j++ )
        {
            if( i + j >= maxi)
            {
                endtime = data.x[i];
                eventmanager.potentialevent->setEndtime(endtime);
                return true;
            }
            average += data.y[i + j];
        }

        average = average/rightnoisetolerance;

        if( abs( average - eventmanager.potentialevent->getLeftbaselineaverage()) < secondaryinbaselinethreshold )
        {
            endtime = data.x[i];
            eventmanager.potentialevent->setEndtime(endtime);
            if( (eventmanager.potentialevent->getEndtime() - eventmanager.potentialevent->getStarttime() ) < autorejectlength*file.getPeriod())
            {
                eventmanager.potentialevent->setAcceptance(rejected);
                return false;   //try this...
            }




            return true;
        }
        else
        {
            potentialendfound = false;
        }
    }

    return true;
}

void MainWindow::findPeaks(Event* event)
{
    event->peakmanager.erasePeaks();

    file.Copy_Data_New(data.x, data.y, event->getStarttime());

    std::vector<double> eventdatax(event->getDuration());
    std::vector<double> eventdatay(event->getDuration());

    for(int i = 0; i < event->getDuration(); i++)
    {
        eventdatax[i] = data.x[i];
        eventdatay[i] = data.y[i];
    }
    event->x = &eventdatax;
    event->y = &eventdatay;
    event->peakmanager.x = &eventdatax;
    event->peakmanager.y = &eventdatay;

    event->peakmanager.findAllpeaks();






    return;


}

void MainWindow::setEventcursors(double t1, double t2 )
{
    double x1 = t1;
    double x2 = t2;

    //double y1 = data.gety(x1);

    //eventcursor1.setPos(x, y);

    if(eventScursor1)
    {
        ui->MainPlot->removeItem(eventScursor1);
    }

    if(eventScursor2)
    {
        ui->MainPlot->removeItem(eventScursor2);
    }
    if(!eventScursor1)
    {
        delete eventScursor1;
    }
    if(!eventScursor2)
    {
        delete eventScursor2;
    }

    QColor color;
    if( eventmanager.targetedevent->getAcceptance() == accepted )
    {
        color = Qt::green;
    }
    else if( eventmanager.targetedevent->getAcceptance() == rejected )
    {
        color = Qt::red;
    }
    else if( eventmanager.targetedevent->getAcceptance() == neutral)
    {
        color = Qt::blue;
    }

    eventcursor1.setColor(color);
    eventcursor2.setColor(color);

    eventScursor1 = new QCPItemLine(ui->MainPlot);
    eventScursor1->setPen( eventcursor1.getPen() );
    eventScursor2 = new QCPItemLine(ui->MainPlot);
    eventScursor2->setPen( eventcursor2.getPen() );
    ui->MainPlot->addItem(eventScursor1);
    ui->MainPlot->addItem(eventScursor2);


    eventScursor1->start->setCoords(x1, QCPRange::minRange);
    eventScursor1->end->setCoords(x1, QCPRange::maxRange);
    eventScursor2->start->setCoords(x2, QCPRange::minRange);
    eventScursor2->end->setCoords(x2, QCPRange::maxRange);



    ui->MainPlot->replot();







    return;
}

void MainWindow::setEventcursors(double t1, double t2, QColor color)
{
    double x1 = t1;
    double x2 = t2;

    //double y1 = data.gety(x1);

    //eventcursor1.setPos(x, y);

    if(eventScursor1)
    {
        ui->MainPlot->removeItem(eventScursor1);
    }

    if(eventScursor2)
    {
        ui->MainPlot->removeItem(eventScursor2);
    }
    if(!eventScursor1)
    {
        delete eventScursor1;
    }
    if(!eventScursor2)
    {
        delete eventScursor2;
    }

    eventcursor1.setColor(color);
    eventcursor2.setColor(color);
    eventScursor1 = new QCPItemLine(ui->MainPlot);
    eventScursor1->setPen( eventcursor1.getPen() );
    eventScursor2 = new QCPItemLine(ui->MainPlot);
    eventScursor2->setPen( eventcursor2.getPen() );

    ui->MainPlot->addItem(eventScursor1);
    ui->MainPlot->addItem(eventScursor2);


    eventScursor1->start->setCoords(x1, QCPRange::minRange);
    eventScursor1->end->setCoords(x1, QCPRange::maxRange);
    eventScursor2->start->setCoords(x2, QCPRange::minRange);
    eventScursor2->end->setCoords(x2, QCPRange::maxRange);



    ui->MainPlot->replot();







    return;
}


void MainWindow::goTotime(double time)
{
    int newsliderposition = (int) ((time/(file.getTotaldatapoints()*file.getPeriod()))*xbarrange);
    ui->xbar->setSliderPosition(newsliderposition);
    on_xbar_valueChanged(newsliderposition);
    return;
}

void MainWindow::goToevent(Event* event)
{
    int n = 5;


    //file.Copy_Data_New(data.x, data.y, event->getStarttime());

    plot.xrange = n*(event->getEndtime() - event->getStarttime());

    double xstationary = 0.5*(event->getEndtime() + event->getStarttime());

    xbarrange = (int)(plot.xfullrange/(plot.xrange*xsliderconstant));

    int newvalue = (int)((xbarrange)*((xstationary - plot.xrange/2.0)/(plot.xfullrange-plot.xrange)));

    xbarrange = (int)(plot.xfullrange/(plot.xrange*xsliderconstant));

    ui->xbar->setMaximum(999999999);
    ui->xbar->setValue(newvalue);
    ui->xbar->setMaximum(xbarrange);

    return;
}

void MainWindow::scopeData(double x1, double x2)
{

    if( x2 - x1 > file.getMaxdatapoints()*file.getPeriod())
    {
        return;
    }

    if( x2 < data.x[file.getMaxdatapoints() - 1] && x1 > data.x[0])
    {
        return;
    }

    double centertime = (x1 + x2)/2.0;
    double newx = centertime - file.getMaxdatapoints()*file.getPeriod()/2.0;

    if( x1 < data.x[0] )
    {
        file.Copy_Data_New(data.x, data.y, newx);
    }

    else if( x2 > data.x[file.getMaxdatapoints() - 1])
    {
        file.Copy_Data_New(data.x, data.y, newx);
    }

    return;
}

void MainWindow::on_Accept_Event_clicked()
{
    if(!eventmanager.potentialevent)
    {
        return;
    }



    acceptEvent(eventmanager.targetedevent);
    return;
}

void MainWindow::acceptEvent(Event* event)
{
    if(event->getAcceptance() == accepted)  //return if event already accepted
    {
        event->setAcceptance(neutral);
        eventmanager.decrementNumberofacceptedevents();
        eventmanager.incrementNumberofneutralevents();
        setEventcursors(event->getStarttime(),event->getEndtime(), Qt::blue);
    }

    else if(event->getAcceptance() == neutral)
    {
        event->setAccepted();
        eventmanager.decrementNumberofneutralevents();
        eventmanager.incrementNumberofacceptedevents();
        setEventcursors(event->getStarttime(), event->getEndtime(), Qt::green);
    }

    else if(event->getAcceptance() == rejected)
    {
        event->setAccepted();
        eventmanager.decrementNumberofrejectedevents();
        eventmanager.incrementNumberofacceptedevents();
        setEventcursors(event->getStarttime(), event->getEndtime(), Qt::green);
    }
    setAcceptRejectbuttons();
    updateEventfields();

    file.addEventline(eventmanager.targetedevent->getIndex(), eventmanager.targetedevent->getStarttime(), eventmanager.targetedevent->getEndtime(), eventmanager.targetedevent->getLeftbaselineaverage());

    return;
}

void MainWindow::on_Reject_Event_clicked()
{
    if(!eventmanager.potentialevent)
    {
        return;
    }


    rejectEvent(eventmanager.targetedevent);

    return;
}

void MainWindow::rejectEvent(Event* event)
{


    if(event->getAcceptance() == rejected )
    {
        eventmanager.incrementNumberofneutralevents();
        eventmanager.decrementNumberofrejectedevents();
        setEventcursors(event->getStarttime(), event->getEndtime(), Qt::blue);
        event->setAcceptance(neutral);
    }

    else if(event->getAcceptance() == accepted)
    {
        eventmanager.decrementNumberofacceptedevents();
        eventmanager.incrementNumberofrejectedevents();
        event->setRejected();
        setEventcursors(event->getStarttime(), event->getEndtime(), Qt::red);
    }

    else if(event->getAcceptance() == neutral)
    {
        eventmanager.decrementNumberofneutralevents();
        eventmanager.incrementNumberofrejectedevents();
        event->setRejected();
        setEventcursors(event->getStarttime(), event->getEndtime(), Qt::red);
    }

    setAcceptRejectbuttons();
    updateEventfields();
    return;



}

void MainWindow::on_Previous_Event_clicked()
{

    if(eventmanager.eventlist.size() <= 1 )
    {
        return;
    }

    bool previouseventfound = false;

    unsigned int targetedint = eventmanager.targetedevent->getIndex();
    int previousint = targetedint;
    while (previouseventfound == false)
    {
        previousint = previousint - 1;
        if( previousint < 0 )
        {

            previousint = eventmanager.eventlist.size() - 1;
        }
        if( (previousint == int(eventmanager.eventlist.size() - 1)) || !(eventmanager.eventlist[previousint]->getAcceptance() == rejected))
        {
            previouseventfound = true;
        }
    }


    //std::cerr << "previousint = " << previousint << "\n";

    eventmanager.setTargetedevent(eventmanager.eventlist[previousint]);

    setAcceptRejectbuttons();
    updateEventfields();


    goToevent(eventmanager.targetedevent);

    setEventcursors(eventmanager.targetedevent->getStarttime(), eventmanager.targetedevent->getEndtime());
    return;
}

void MainWindow::on_Next_Event_clicked()
{
    if( eventmanager.eventlist.size() <= 1 )
    {
        return;
    }


    bool nexteventfound = false;
    unsigned int targetedint = eventmanager.targetedevent->getIndex();
    unsigned int nextint = targetedint;
    while (nexteventfound == false)
    {
        nextint = (nextint + 1)%(eventmanager.eventlist.size());
        if( (nextint == eventmanager.eventlist.size() - 1) || !(eventmanager.eventlist[nextint]->getAcceptance() == rejected))
        {
            nexteventfound = true;
        }
    }

    //std::cerr << "nextint = " << nextint << "\n";



    eventmanager.setTargetedevent(eventmanager.eventlist[nextint]);

    setAcceptRejectbuttons();
    updateEventfields();



    goToevent(eventmanager.targetedevent);
    setEventcursors(eventmanager.targetedevent->getStarttime(), eventmanager.targetedevent->getEndtime());



    return;
}

void MainWindow::on_Last_Event_clicked()
{
    if( eventmanager.eventlist.size() < 2 || eventmanager.targetedevent->getIndex() == (int) (eventmanager.eventlist.size() - 1))
    {
        return;
    }

    int lastint = eventmanager.eventlist.size() - 1;
    eventmanager.setTargetedevent(eventmanager.eventlist[lastint]);

    setAcceptRejectbuttons();

    goToevent(eventmanager.getTargetedevent());
    setEventcursors(eventmanager.getTargetedevent()->getStarttime(), eventmanager.getTargetedevent()->getEndtime());



    return;
}

void MainWindow::on_First_Event_clicked()
{
    if( eventmanager.eventlist.size() < 2 || eventmanager.targetedevent->getIndex() == 0)
    {
        return;
    }

    bool firsteventfound = false;
    int i = 0;
    int firstint;

    while( firsteventfound == false)
    {
        if( !(eventmanager.eventlist[i]->getAcceptance() == rejected) )
        {
            firsteventfound = true;

        }
        i++;
    }
    firstint = i - 1;
    eventmanager.setTargetedevent(eventmanager.eventlist[firstint]);

    setAcceptRejectbuttons();

    goToevent(eventmanager.getTargetedevent());
    setEventcursors(eventmanager.getTargetedevent()->getStarttime(), eventmanager.getTargetedevent()->getEndtime());



    return;
}

void MainWindow::setAcceptRejectbuttons()
{
    AcceptanceState acceptance;
    acceptance = eventmanager.targetedevent->getAcceptance();

    if(acceptance == accepted)
    {
        ui->Accept_Event->setFlat(true);
        ui->Reject_Event->setFlat(false);
    }
    else if(acceptance == neutral)
    {
        ui->Accept_Event->setFlat(false);
        ui->Reject_Event->setFlat(false);
    }
    else if(acceptance == rejected)
    {
        ui->Accept_Event->setFlat(false);
        ui->Reject_Event->setFlat(true);
    }
    return;

}

void MainWindow::on_AverageLength_Field_returnPressed()
{
    //averagelength = (ui->AverageLength_Field->text()).toInt();
    //std::cerr << "new average length is " << averagelength << "\n";
    //return;
}

void MainWindow::on_AverageLength_Field_textEdited(const QString &arg1)
{
    QString qstring = arg1;
    averagelength = (ui->AverageLength_Field->text()).toInt();
    return;
}

void MainWindow::on_L_NoiseTolerance_Field_textEdited(const QString &arg1)
{
    QString qstring = arg1;
    leftnoisetolerance = (ui->L_NoiseTolerance_Field->text()).toInt();
    return;
}


void MainWindow::on_L_NoiseMultiplier_Field_textEdited(const QString &arg1)
{
    QString qstring = arg1;
    leftnoisemultiplier = (ui->L_NoiseMultiplier_Field->text()).toDouble();
    return;
}

void MainWindow::on_L_NoiseMultiplier_Field_cursorPositionChanged()
{
    //leftnoisemultiplier = (ui->L_NoiseMultiplier_Field->text()).toDouble();
    return;

}

void MainWindow::on_Find_Next_Event_clicked()
{
    FindNextEvent();
    return;

}

void MainWindow::on_Retry_Search_clicked()
{

    if( eventmanager.eventlist.size() <= 0 )
    {
        return;
    }


    eventmanager.potentialevent = eventmanager.targetedevent;
    if(eventmanager.targetedevent->getAcceptance() == rejected)
    {
        eventmanager.decrementNumberofrejectedevents();
        eventmanager.incrementNumberofneutralevents();
    }
    if(eventmanager.targetedevent->getAcceptance() == accepted)
    {
        eventmanager.decrementNumberofacceptedevents();
        eventmanager.incrementNumberofneutralevents();
    }

    updateEventfields();

    eventmanager.targetedevent->setAcceptance(neutral);

    setAcceptRejectbuttons();

    int previouseventindex = eventmanager.targetedevent->getIndex() - 1;
    double searchstarttime;
    if( eventmanager.eventlist.size() <= 1 || previouseventindex < 0)
    {
        static int i = 0;
        i++;
        searchstarttime = 0;
    }
    else
    {
        static int i = 0;
        searchstarttime = eventmanager.eventlist[previouseventindex]->getEndtime() + aftereventdelay*file.getPeriod();
        i++;
    }
    findPotentialeventstart(searchstarttime);
    findPotentialeventend();
    eventmanager.sortEvents();
    std::cerr << "(refound) start time: " << eventmanager.targetedevent->getStarttime() << " end time: " << eventmanager.targetedevent->getEndtime() << "\n";
    goToevent( eventmanager.potentialevent );
    setEventcursors(eventmanager.potentialevent->getStarttime(), eventmanager.potentialevent->getEndtime());

    return;

}

void MainWindow::on_R_NoiseMultiplier_Field_textEdited(const QString &arg1)
{
    QString qstring = arg1;
    //std::cerr << "new r multiplier = " << ui->R_NoiseMultiplier_Field->text() << "\n";
    //rightnoisemultiplier = (ui->R_NoiseMultiplier_Field->text()).toDouble();
    rightsecondarynoisemultiplier = (ui->R_NoiseMultiplier_Field->text()).toDouble();
    return;
}

void MainWindow::on_R_NoiseTolerance_Field_textEdited(const QString &arg1)
{
    QString qstring = arg1;
    //std::cerr << "new r tolerance = " << ui->R_NoiseMultiplier_Field->text() << "\n";
    rightnoisetolerance = (ui->R_NoiseTolerance_Field->text()).toDouble();
    return;
}

void MainWindow::on_actionFind_All_Events_triggered()
{


    while(endofsearch == false)
    {
        FindNextEvent();
    }
    return;
}

void MainWindow::updateEventfields()
{
    int totalint, acceptedint, neutralint, rejectedint;
    acceptedint = eventmanager.numberofacceptedevents;
    neutralint = eventmanager.numberofneutralevents;
    rejectedint = eventmanager.numberofrejectedevents;
    totalint = acceptedint + neutralint + rejectedint;
    ui->TotalEvents_Field->setText(QString::number(totalint));
    ui->Accepted_Field->setText(QString::number(acceptedint));
    ui->Neutral_Field->setText(QString::number(neutralint));
    ui->Rejected_Field->setText(QString::number(rejectedint));

    QString fieldstring;
    fieldstring = "#";
    fieldstring = fieldstring + QString::number(eventmanager.targetedevent->getIndex() + 1);
    fieldstring = fieldstring + ", ";
    fieldstring = fieldstring + QString::number(eventmanager.targetedevent->getStarttime());
    fieldstring = fieldstring + " to ";
    fieldstring = fieldstring + QString::number(eventmanager.targetedevent->getEndtime());
    fieldstring = fieldstring + " s";
    ui->TargetedEvent_Field->setText(fieldstring);

    return;
}


void MainWindow::updateTargetedeventfield()
{}

void MainWindow::on_Save_Left_Cursor_clicked()
{
    if(eventmanager.targetedevent->getAcceptance() == accepted)
    {
        //file.findEventline(eventmanager.targetedevent->getIndex());
        file.writeCursor1data(cursor1.getposx(), data.gety(cursor1.getposx()));
    }
    return;
}


void MainWindow::on_Integrate_clicked()
{
    if(eventmanager.targetedevent->getAcceptance() == accepted)
    {
        //file.findEventline(eventmanager.targetedevent->getIndex());
        file.writeIntegrationdata(data.Integrate(cursor1.getposx(), cursor2.getposx()));
    }

    std::cerr << "integration: " << data.Integrate(cursor1.getposx(), cursor2.getposx()) << "\n";
    return;
}

void MainWindow::on_Center_On_Data_clicked()
{

    double yvalue = data.gety(plot.xrangehigh - plot.xrange/2.0);

    int ybarvalue = getYbarvalue(yvalue + plot.yrange/2.0);
    ui->ybar->setValue(ybarvalue);
    //changeYrange(ybarvalue);

    return;
}

void MainWindow::on_Save_Parameters_clicked()
{
    QString filename = QFileDialog::getSaveFileName(
                this,
                tr("Open file"),
                parameterdirectory, tr("Parameter Files (*.par)"));


    if(filename == NULL)
    {
        return;
    }

    if(!filename.endsWith(".par"))
    {
           filename = filename + ".par";
    }

    QFile parameterfile_f(filename);

    bool savefile = false;

    if( parameterfile_f.exists() == true )
    {
        //prompt file replace dialogue;

        if( openOverwritefiledialog(filename) == true )
        {
            savefile = true;
        }
        else
        {
            savefile = false;
            return;
        }

    }
    else
    {
        savefile = true;
    }

    if( savefile == true )
    {

        parameterfile_f.open( QIODevice::WriteOnly);

        QTextStream parameterfile;

        parameterfile.setDevice(&parameterfile_f);

        parameterfile << averagelength << "\n";
        parameterfile << leftnoisetolerance << "\n";
        parameterfile << rightnoisetolerance << "\n";
        parameterfile << leftnoisemultiplier << "\n";
        parameterfile << rightsecondarynoisemultiplier << "\n";
        parameterfile_f.close();
    }

    return;
}

void MainWindow::on_Load_Parameters_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open file"),
                parameterdirectory, tr("Parameter Files (*.par)"));

    if(filename == NULL)
    {
        return;
    }

    QFile parameterfile_f(filename);

    parameterfile_f.open( QIODevice::ReadOnly);

    QTextStream parameterfile;

    parameterfile.setDevice(&parameterfile_f);

    parameterfile >> averagelength;
    ui->AverageLength_Field->setText(QString::number(averagelength));

    parameterfile >> leftnoisetolerance;
    ui->L_NoiseTolerance_Field->setText(QString::number(leftnoisetolerance));

    parameterfile >> rightnoisetolerance;
    ui->R_NoiseTolerance_Field->setText(QString::number(rightnoisetolerance));

    parameterfile >> leftnoisemultiplier;
    ui->L_NoiseMultiplier_Field->setText(QString::number(leftnoisemultiplier));

    parameterfile >> rightsecondarynoisemultiplier;
    ui->R_NoiseMultiplier_Field->setText(QString::number(rightsecondarynoisemultiplier));


    parameterfile_f.close();


    return;
}



bool MainWindow::openOverwritefiledialog(QString filename)
{
    OverwriteFile_Dialogue overwritedialogue(0, filename );
    overwritedialogue.setModal(true);
    overwritedialogue.exec();
    return overwritedialogue.overwritefile;
}

