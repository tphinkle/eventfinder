#include "mainwindow.h"
#include <QMainWindow>
#include "/usr/src/QT/Extras/qcustomplot/qcustomplot.h"
#include <stdlib.h>
#include <math.h>
#include <string>
#include <sstream>
#include <iostream>
#include <QVector>
#include <QTextStream>
#include <QString>
#include <QFileDialog>
#include <memory>


File::File()
{
    HeaderLength = 10;
    ColumnCount = 4;
    xcolumn = 0;
    ycolumn = 2;
    maxdatapoints = 100000;

    //Sentinel value initialization
    Frequency = -1;
    Period = -1;
    TotalDataPoints = -1;

};


void File::OpenFile( QString FileName)
{
    InputFile = FileName;



    //InputFile_f = new QFile(InputFile);
    InputFile_f.setFileName(InputFile);
    InputFile_f.open( QIODevice::ReadOnly );
    InputStream.setDevice( &InputFile_f );

    getPeriod( );

    TemporaryFile_f.open();
    TemporaryStream.setDevice( &TemporaryFile_f );

    Skip_Lines( InputStream, HeaderLength );


    Copy_Data( InputStream, TemporaryStream );
    CurrentStream = &TemporaryStream;
    InputFile_f.close();
    TemporaryStream.setRealNumberNotation(QTextStream::ScientificNotation);
    TemporaryStream.setRealNumberPrecision(3);

}


void File::Copy_Data( QTextStream& Stream1, QTextStream& Stream2 )
{
    QString qjunk;
    double junk;

    while( !Stream1.atEnd() )
        {
            Stream2.setRealNumberNotation(QTextStream::ScientificNotation);
            Stream2.setRealNumberPrecision(5);


            for(int i = 0; i < ColumnCount; i++)
                {

                    if( i == xcolumn )
                        {
                            Stream1 >> qjunk;
                            junk = qjunk.toDouble();

                            Stream2 << junk << " ";
                        }
                    else if( i == ycolumn )
                    {
                        Stream1 >> qjunk;
                        junk = qjunk.toDouble();
                        if( junk > MaxValue )
                        {
                            MaxValue = junk;
                        }
                        if( junk < MinValue )
                        {
                            MinValue = junk;
                        }



                        Stream2 << junk << "\n";
                    }



                    else
                        {
                            Stream1 >> qjunk;
                        }
                }
        }

    Stream2.seek(0);

}

void File::Copy_Data( int startline, QVector<double>& x, QVector<double>& y )
{
    qint64 position = CurrentStream->pos();
    CurrentStream->seek(startline);
    for( int i = 0; i < maxdatapoints; i++ )
    {
        *CurrentStream >> x[i];
        *CurrentStream >> y[i];        
    }


    CurrentStream->seek(position);
    return;

}

void File::Copy_Data( QTextStream Stream, QVector<double>& x, QVector<double>& y )
{
    qint64 position = Stream.pos();
    Stream.seek(0);

    while( !Stream.atEnd() )
    {
        for( int i = 0; i < ColumnCount; i++ )
        {
            if( i == xcolumn )
            {
                Stream >> x[i];
            }
            if( i == ycolumn )
            {
                Stream >> y[i];

            }


        }
    }
    Stream.seek(position);
    return;
}

void File::Copy_Data_High( QVector<double>& x, QVector<double>& y )
{

        char c;
        int charperline = 22 + 2;
       /* CurrentStream->seek(0);
        for( int i = 0; i < 100*charperline; i++ )
            {
            CurrentStream->seek(i);
            *CurrentStream >> c;
            std::cerr << c;
            }
    std::cerr << "\n";

    CurrentStream->seek(0);*/
        if( charperline*(x[maxdatapoints - 1]/getPeriod() + maxdatapoints/2 < 0))
        {
            CurrentStream->seek(0 + charperline*(TotalDataPoints - maxdatapoints));
        }
        else
        {
            CurrentStream->seek(0 + charperline*(x[maxdatapoints-1]/getPeriod() - maxdatapoints/2));
        }


    for( int i = 0; i < maxdatapoints; i++ )
    {

        *CurrentStream >> x[i];
        *CurrentStream >> y[i];


    }

/*
    for( int j = 0; j < 10; j++)
    {
        std::cerr << "x[" << j << "] = " << x[j] << "\n";
        std::cerr << "y[" << j << "] = " << y[j] << "\n";
    }
    for( int j = 10; j > 0; j--)
    {
        std::cerr << "x[" << maxdatapoints - j << "] = " << x[maxdatapoints - j] << "\n";
        std::cerr << "y[" << maxdatapoints - j << "] = " << y[maxdatapoints - j] << "\n";
    }

    //std::cerr << "xmin: " << x[0] << "    xhigh: " << x[maxdatapoints - 1] << "\n\n";
*/
    return;
};

void File::Copy_Data_Low( QVector<double>& x, QVector<double>& y )
{
    qint64 position = CurrentStream->pos();
    std::cerr << position << "\n";
    int charperline = 22 + 2;
    if( charperline*(x[0]/getPeriod() - maxdatapoints/2) <= 0)
    {
        CurrentStream->seek(0);
    }
    else
    {
    CurrentStream->seek(0 + charperline*(x[0]/getPeriod() - maxdatapoints/2));
    }

    for( int i = 0; i < maxdatapoints; i++ )
    {
        *CurrentStream >> x[i];
        *CurrentStream >> y[i];
    }

    return;
};

int File::getTotalDataPoints( )
{
    if( TotalDataPoints == -1 )
    {
        int i = 0;
        qint64 position = CurrentStream->pos();

        CurrentStream->seek(0);

        while( !CurrentStream->atEnd() )
        {
            CurrentStream->readLine();
            i++;
        }
        TotalDataPoints = i;
        CurrentStream->seek(position);
    }

    return TotalDataPoints;
}

double File::getPeriod( )
{
    if( Period == -1 )
    {
        double doublejunk;
        double t1;
        double t2;
        qint64 position = InputStream.pos();
        InputStream.seek(0);
        Skip_Lines( InputStream, HeaderLength );
        for( int i = 0; i < ColumnCount; i++ )
        {
            InputStream >> doublejunk;
            if( i == 0 )
            {
                t1 = doublejunk;
            }
        }

        for( int j = 0; j < ColumnCount; j++ )
        {
            InputStream >> doublejunk;
             if( j == 0 )
            {
                t2 = doublejunk;
            }
        }

        Period = t2 - t1;
        Frequency = 1.0/Period;

        InputStream.seek(position);
    }

    return Period;

}

int File::getFrequency( )
{
    return Frequency;
}

void File::Skip_Lines( QTextStream& Stream, int lineskip )
{
    QString qjunk;
    std::string junk;
    for( int i = 0; i < lineskip; i++ )
        {
            Stream.readLine();
        }
    /*
    while( !InputStream->atEnd() )
        {
            qjunk = InputStream->readLine();
            junk = qjunk.toUtf8().constData();
            std::cerr << junk << "\n";
        }
        */
    return;
}


/*void File::Read_Lines( int linecount, QVector<double> &xx )
{
    for( int i = 0; i < linecount; i++ )
        {
            *InputStream >> xx[i];
        }
    return;
}*/

/*double File::FindxMax( )
{
    double xMax;
    CurrentStream->seek(getTotalDataPoints() * 2 - 2); //2 for two columns, -2 for going to beginning of line


}*/

void File::setInputFile( QString inputfile )
{
    InputFile = inputfile;
    return;
}

QString File::getInputFile()
{
    return InputFile;
}
