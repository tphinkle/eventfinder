#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include <QDataStream>
#include <QFile>
#include <QLineEdit>
//#include <QTextStream>

Data::Data()
{
    maxdatapoints = 100000;
}

void Data::resize( int datapoints )
{
    x.resize(datapoints);
    y.resize(datapoints);
    return;
}

double Data::gety( double xx )
{
    int datapoint = (int) ((xx - x[0])*Frequency);
    return y[datapoint];
}

double Data::Integrate(double x1, double x2)
{
    int startdatapoint;
    int enddatapoint;
    if( x2 < x1 )
    {
        startdatapoint = (int) ((x2 - x[0])*Frequency);
        enddatapoint = (int) ((x1 - x[0])*Frequency);
    }
    else
    {
        startdatapoint = (int) ((x1 - x[0])*Frequency);
        enddatapoint = (int) ((x2 - x[0])*Frequency);
    }
    double average = 0;
    for( int i = startdatapoint; i < enddatapoint; i++ )
    {
        average = average + y[i];
    }
    average = average/(enddatapoint - startdatapoint);
    std::cerr << "average = " << average << "\n";
    return average;
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->MainPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress(QMouseEvent*)));

    ui->LeftLineText->setReadOnly(true);
    ui->RightLineText->setReadOnly(true);
    ui->LeftLineText->setFrameStyle(QFrame::NoFrame);
    ui->RightLineText->setFrameStyle(QFrame::NoFrame);
    ui->LeftLineText->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->RightLineText->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->LeftLineText->setTextColor(Qt::blue);
    ui->RightLineText->setTextColor(Qt::red);
    ui->LeftLineText->viewport()->setAutoFillBackground(false);
    ui->RightLineText->viewport()->setAutoFillBackground(false);

    //Set-up plot environment

    plot.custplot = ui->MainPlot;
    setWindowTitle("EventFinder");
    statusBar()->clearMessage();

    xbarrange = 2000;
    ui->xbar->setRange(0, xbarrange);
    ybarrange = 2000;
    ui->ybar->setRange(0, ybarrange);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::mousePress(QMouseEvent* click)
{
    int textboxposX;
    int textboxposY;
    QString xstring;
    QString ystring;
    QString totalstring;

    QCustomPlot * MainPlot = ui->MainPlot;
    static QCPItemLine * yCursor1, * yCursor2;
    static QCPItemLine * xCursor1, *xCursor2;
    double x = MainPlot->xAxis->pixelToCoord(click->pos().x());




    if( click->button() == Qt::LeftButton)
    {
        cursor1pos = x;
        //Line cursor functions
        if( yCursor1 )   //?????
        {
            MainPlot->removeItem( yCursor1 );
        }
        if( xCursor1 )
        {
            MainPlot->removeItem( xCursor1 );
        }

        yCursor1 = new QCPItemLine(MainPlot);
        xCursor1 = new QCPItemLine(MainPlot);

        QPen pen1;
        pen1.setColor( Qt::blue );
        yCursor1->setPen( pen1 );
        xCursor1->setPen( pen1 );
        MainPlot->addItem(yCursor1);
        MainPlot->addItem(xCursor1);

        xCursor1->start->setCoords(x - xCursorWidth/2, data.gety(x));
        xCursor1->end->setCoords(x + xCursorWidth/2, data.gety(x));
        yCursor1->start->setCoords(x, QCPRange::minRange);
        yCursor1->end->setCoords(x, QCPRange::maxRange);


        //Textbox functions
        textboxposX = ui->MainPlot->x() + click->x() - ui->LeftLineText->width()/2;
        textboxposY = ui->LeftLineText->y();
        ui->LeftLineText-> move( textboxposX, textboxposY);
        xstring = xstring.QString::setNum(x, 'g', 6);
        ystring = ystring.QString::setNum(data.gety(x), 'g', 6);
        std::cerr << "gety(x): " << data.gety(x) << "\n";
        totalstring = xstring + ", " + ystring;
        ui->LeftLineText->setPlainText( totalstring );

    }

    if( click->button() == Qt::RightButton)
    {
        cursor2pos = x;
        if( yCursor2 )   //?????
        {
            MainPlot->removeItem(yCursor2);
        }

        if( xCursor2 )
        {
            MainPlot->removeItem( xCursor2 );
        }
        yCursor2 = new QCPItemLine(MainPlot);
        xCursor2 = new QCPItemLine(MainPlot);

        QPen pen2;
        pen2.setColor( Qt::red );

        yCursor2->setPen( pen2 );
        xCursor2->setPen( pen2 );


        MainPlot->addItem(yCursor2);
        MainPlot->addItem(xCursor2);
        yCursor2->start->setCoords(x, QCPRange::minRange);
        yCursor2->end->setCoords(x, QCPRange::maxRange);
        xCursor2->start->setCoords(x - xCursorWidth/2, data.gety(x) );
        xCursor2->end->setCoords(x + xCursorWidth /2, data.gety(x) );
        textboxposX = ui->MainPlot->x() + click->x() - ui->RightLineText->width()/2;
        textboxposY = ui->RightLineText->y();
        xstring = xstring.QString::setNum(x, 'g', 6);

        ystring = ystring.QString::setNum(data.gety(x), 'g', 6);
        totalstring = xstring + ", " + ystring;
        ui->RightLineText->setPlainText( totalstring );
        ui->RightLineText-> move( textboxposX, textboxposY);
    }



    MainPlot->replot();

}

void MainWindow::on_xbar_valueChanged(int value)
{


    //file.CopyData(file.CurrentStream, data.x, data.y, )
    plot.xrangelow = (plot.xfullrangehigh - plot.xfullrangelow) * value/xbarrange;
    plot.xrangehigh = plot.xrangelow + plot.xrange;

    if( plot.xrangehigh > data.x[data.maxdatapoints - 1] )
    {
        file.Copy_Data_High( data.x, data.y );
        plot.custplot->graph(0)->setData(data.x, data.y);
    }

    if( plot.xrangelow < data.x[0] )
    {
        file.Copy_Data_Low( data.x, data.y );
        plot.custplot->graph(0)->setData(data.x, data.y);
    }

    plot.custplot->xAxis->setRange(plot.xrangelow, plot.xrangehigh);
    plot.custplot->replot();


}

void MainWindow::on_xbar_sliderMoved(int position)
{
    QApplication::processEvents();
    plot.xrangelow = (plot.xfullrangehigh - plot.xfullrangelow) * position/xbarrange;
    plot.xrangehigh = plot.xrangelow + plot.xrange;

    if( plot.xrangehigh > data.x[data.maxdatapoints - 1] )
    {
        file.Copy_Data_High( data.x, data.y );
        plot.custplot->graph(0)->setData(data.x, data.y);
    }

    if( plot.xrangelow < data.x[0] )
    {
        file.Copy_Data_Low( data.x, data.y );
        plot.custplot->graph(0)->setData(data.x, data.y);
    }

    plot.custplot->xAxis->setRange(plot.xrangelow, plot.xrangehigh);
    plot.custplot->replot();
}


void MainWindow::on_ybar_valueChanged(int value)
{

    plot.yrangelow = plot.yfullrange - (plot.yfullrangehigh - plot.yfullrangelow) *value/ybarrange;
    plot.yrangehigh = plot.yrangelow + plot.yrange;
    plot.custplot->yAxis->setRange(plot.yrangelow, plot.yrangehigh);
    plot.custplot->replot();

}

void MainWindow::on_ybar_sliderMoved(int position)
{

    //change yrangelow
        //needs info on value and range of ybar (from mainwindow)
    //change yrangehigh
    //call setRange function
    //replot

    plot.yrangelow = plot.yfullrange - (plot.yfullrangehigh - plot.yfullrangelow)*position/ybarrange;
    plot.yrangehigh = plot.yrangelow + plot.yrange;
    plot.custplot->yAxis->setRange(plot.yrangelow, plot.yrangehigh);
    plot.custplot->replot();

}



void MainWindow::on_xZoomIn_clicked()
{

    plot.xrange = .5*plot.xrange;
    plot.xrangelow = (plot.xfullrangehigh-plot.xfullrangelow)*ui->xbar->value()/xbarrange;
    plot.xrangehigh = plot.xrangelow + plot.xrange;
    int newpagestep = (int)((ui->xbar->maximum() - ui->xbar->minimum() + ui->xbar->pageStep())*plot.xrange/(file.getTotalDataPoints()/file.getPeriod()));
    if( newpagestep < minimumpagestep )
    {
        newpagestep = minimumpagestep;
    }
    std::cerr << newpagestep << "\n\n";
    ui->xbar->setPageStep(newpagestep);
    plot.custplot->xAxis->setRange(plot.xrangelow, plot.xrangehigh);
    plot.custplot->replot();
}

void MainWindow::on_xZoomOut_clicked()
{

    plot.xrange = 1.5*plot.xrange;
    if( plot.xrange > file.getTotalDataPoints()*file.getPeriod() )
    {

        plot.xrange = file.getTotalDataPoints()*file.getPeriod();
    }
    int newpagestep = (int)((ui->xbar->maximum() - ui->xbar->minimum() + ui->xbar->pageStep())*plot.xrange/(file.getTotalDataPoints()/file.getPeriod()));
    if( newpagestep < minimumpagestep )
    {
        newpagestep = minimumpagestep;
    }
        std::cerr << newpagestep << "\n\n";
    plot.xrangelow = (plot.xfullrangehigh-plot.xfullrangelow)*ui->xbar->value()/xbarrange;
    plot.xrangehigh = plot.xrangelow + plot.xrange;
    plot.custplot->xAxis->setRange(plot.xrangelow, plot.xrangehigh);
    plot.custplot->replot();


}


void MainWindow::on_yZoomIn_clicked()
{
    plot.yrange = .5*plot.yrange;
    plot.yrangelow = plot.yfullrange - (plot.yfullrangehigh - plot.yfullrangelow) *ui->ybar->value()/ybarrange;

    plot.yrangehigh = plot.yrangelow + plot.yrange;
    plot.custplot->yAxis->setRange(plot.yrangelow, plot.yrangehigh);
    plot.custplot->replot();
}

void MainWindow::on_yZoomOut_clicked()
{

    plot.yrange = 1.5*plot.yrange;

    plot.yrangelow = plot.yfullrange - (plot.yfullrangehigh - plot.yfullrangelow) *ui->ybar->value()/ybarrange;
    plot.yrangehigh = plot.yrangelow + plot.yrange;
    plot.custplot->yAxis->setRange(plot.yrangelow, plot.yrangehigh);
    plot.custplot->replot();


}


void MainWindow::on_actionOpen_File_triggered()
{

    file.OpenFile( QFileDialog::getOpenFileName(
                this,
                tr("Open file"),
                "/home/preston/Desktop/Science/Research/QTApplications/eventfinder/test"

                ) );

    setWindowTitle(file.getInputFile());

    plot.SetupPlot(file.getPeriod(), file.getTotalDataPoints(), file.MaxValue, file.MinValue);

    data.Period = file.getPeriod();
    data.Frequency = file.getFrequency();

    data.resize( data.maxdatapoints );

    file.Copy_Data( 0, data.x, data.y );

    plot.xrangelow = (plot.xfullrangehigh-plot.xfullrangelow)*ui->xbar->value()/xbarrange;
    plot.xrangehigh = plot.xrangelow + plot.xrange;
    plot.yrangelow = (plot.yfullrangehigh-plot.yfullrangelow)*ui->ybar->value()/ybarrange;
    plot.yrangehigh = plot.yrangelow + plot.yrange;
    plot.custplot->xAxis->setRange(plot.xrangelow, plot.xrangehigh);
    plot.custplot->yAxis->setRange(plot.yrangelow, plot.yrangehigh);

    //plot.custplot->xAxis->setRange(0, file.getPeriod()*file.maxdatapoints);

    //plot.custplot->yAxis->setRange(plot.yrangelow, plot.yrangehigh);

    plot.custplot->graph(0)->setData(data.x, data.y);

    plot.custplot->replot();

}




void MainWindow::on_Accept_Event_clicked()
{
    data.Integrate(cursor1pos, cursor2pos);
}
