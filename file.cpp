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
#include "overwritefile_dialogue.h"
#include <QDateTime>


File::File()
{
    HeaderLength = 10;
    ColumnCount = -1;
    xcolumn = 0;
    ycolumn = 2;
    maxdatapoints = 10000000; //used to be 100000
    charperline = 24;
    maxlinesperstream = maxdatapoints;
    totaldatapoints = 0;
    streamprecision = 10;

    onestreamonly = false;

    fileloaded = false;

    directory = "/home/preston/Desktop/Science/Research/QtApplications/eventfinder/ATFFiles";

    //Sentinel value initialization
    frequency = -1;
    period = -1;

};

void File::OpenFile( QString FileName)
{




    InputFile = FileName;

    InputFile_f.setFileName(InputFile);
    InputFile_f.open( QIODevice::ReadOnly );
    InputStream.setDevice( &InputFile_f );

    //calculateTotaldatapointsFAST();



    TemporaryFile_f.open();
    TemporaryStream.setDevice( &TemporaryFile_f );

    /*OUTPUTFILE FOR LAURA*/
    FileName.chop(4);
    QString OutputFileName = FileName + "_events";

    if( QFile(OutputFileName).exists() == true)
    {
        OverwriteFile_Dialogue overwritedialogue(0, OutputFileName );
        overwritedialogue.setModal(true);
        overwritedialogue.exec();
        if( overwritedialogue.overwritefile == true )
        {
            QFile(OutputFileName).remove();
        }
    }


    OutputFile_f.setFileName(OutputFileName);


    OutputFile_f.open( QIODevice::ReadWrite );
    OutputStream.setDevice( &OutputFile_f );
    OutputStream.seek(0);
    OutputStream << "Event #\tStart\tEnd\tBaseline\tPeaks>>>\n";
    OutputFile_f.flush();

    processHeadernew();//
    calculatePeriod();//
    //calculateTotaldatapointsFAST();//

    calculateTotaldatapoints();
    //processHeadernew();
    //calculatePeriod();

    createStreamlist();

    return;

}

void File::addEventline(int index, double starttime, double endtime, double baseline)
{
    std::cerr << "adding event " << index << "\n";
    QString qstringjunk;
    while( OutputStream.atEnd() == false)
    {

        OutputStream >> qstringjunk;
    }
    OutputStream << "\n";
    OutputStream << index + 1 << "\tstarttime:\t" << starttime << "\tendtime:\t" << endtime << "\tbaseline:\t" << baseline << "\t";
    OutputFile_f.flush();
    return;
}

void File::findEventline(int index)
{
    QString qstringjunk;
    int intjunk;
    OutputStream.seek(0);
    OutputStream.readLine();

    while( OutputStream.atEnd() == false)
    {
        OutputStream >> intjunk;
        if( intjunk == index + 1)
        {
            OutputStream.readLine();
            OutputStream.seek(OutputStream.pos() - 1);
            std::cerr << "eventline " << intjunk << " found\n";
            break;
        }
        OutputStream.readLine();
    }



    return;
}

void File::writeCursor1data(double time, double amplitude)
{
    std::cerr << "writing cursor data\n";
    OutputStream << "\t" << time << "\t" << amplitude << "\t";
    OutputFile_f.flush();
    return;
}

void File::writeIntegrationdata(double integration_)
{
    OutputStream << "Integration:\t" << integration_ << "\t";
    OutputFile_f.flush();
    return;
}


void File::transferDatanew()
{

    if(onestreamonly == false)
    {
        moveDatatostreamlist();
        InputFile_f.close();
        std::cerr << "Period = " << period;
        std::cerr << "\nFrequency = " << frequency << "\n";
        fileloaded = true;
    }
    fileloaded = true;
    return;
}

void File::calculateTotaldatapoints()
{
    InputStream.seek(0);

    int i = 0;

    while( !InputStream.atEnd() )
    {
        i++;
        InputStream.readLine();
    }

    totaldatapoints = i - HeaderLength;

    if(maxdatapoints > totaldatapoints)
    {
        maxdatapoints = totaldatapoints;
    }

    InputStream.seek(0);
    std::cerr << "totallines = " << totaldatapoints << "\n";
    return;
}

void File::calculateTotaldatapointsFAST()
{
    double endtime = 0;
    InputStream.seek(0);
    InputStream.seek(InputFile_f.size() - 100);

    std::vector<QString> qstringvec;

    int i = 0;

    while(InputStream.atEnd() == false)
    {
        qstringvec.push_back(InputStream.readLine());
        std::cerr << "NEW!: " << qstringvec[i].toStdString() << "\n\n";
        i++;
    }

    QStringList linelist = qstringvec[qstringvec.size() - 1].split(QRegExp("\\s"));


    totaldatapoints = (int) (linelist[0].toDouble()*frequency) + 1;

    std::cerr << "period = " << period << "\n";
    std::cerr << "totaldatapoints = " << totaldatapoints << "\n";

    if(maxdatapoints > totaldatapoints)
    {
        maxdatapoints = totaldatapoints;
    }

    InputStream.seek(0);

    return;

}

void File::processHeadernew()
{
    InputStream.seek(0);
    Skip_Lines( InputStream, 1);
    setColumncount();
    Skip_Lines(InputStream, HeaderLength - 2);

    std::string columntitle;
    QString tempqstring1, tempqstring2, tempqstring3;

    //Time column in .atf file
    InputStream >> tempqstring1;
    InputStream >> tempqstring2;
    columntitlelist.push_back(tempqstring1 + " " + tempqstring2);

    for(int i = 1; i < ColumnCount; i++ )
    {
        InputStream >> tempqstring1;
        InputStream >> tempqstring2;
        InputStream >> tempqstring3;
        columntitlelist.push_back(tempqstring1 + " " + tempqstring2 + " " + tempqstring3);
    }

    for(int i = 0; i < ColumnCount; i++ )
    {
        columntitle = columntitlelist[i].toStdString();
        std::cerr << columntitle << "\n";
    }
    InputStream.seek(0);
    return;
}

int File::getTotaldatapoints()
{
    return totaldatapoints;
}


void File::calculatePeriod()
{
    InputStream.seek(0);
    double doublejunk, t1 = 0, t2 = 0;

    Skip_Lines(InputStream, HeaderLength);
    for(int i = 0; i < ColumnCount; i++ )
    {
        InputStream >> doublejunk;
        if( i == 0 )
        {
            t1 = doublejunk;
        }
    }

    for(int i = 0; i < ColumnCount; i++ )
    {
        InputStream >> doublejunk;
        if( i == 0 )
        {
            t2 = doublejunk;
        }
    }
    period = t2 - t1;
    frequency = 1/(t2 - t1);
    return;

}

void File::createStreamlist()
{


    streamcount = totaldatapoints/maxlinesperstream + 1;

    /*
    if(streamcount == 1)
    {
        onestreamonly = true;
        return;
    }*/

    streamlist.resize(streamcount);
    streamlist_f.resize(streamcount);
    for(int i = 0; i < streamcount; i++)
    {
        streamlist_f[i] = new QTemporaryFile();
        streamlist_f[i]->open();
        streamlist[i] = new QTextStream();
        streamlist[i]->setDevice(streamlist_f[i]);
        streamlist[i]->setRealNumberPrecision(streamprecision);
    }
    std::cerr << "total number of streams: " << streamcount << "\n";
    return;
}

void File::moveDatatostreamlist()
{
    int datapoints;
    double doublejunk;

    InputStream.seek(0);

    Skip_Lines(InputStream, HeaderLength);
    for(int i = 0; i < ColumnCount; i++ )
    {
        InputStream >> doublejunk;
        if( i == ycolumn )
        {
            MinValue = doublejunk;
            MaxValue = doublejunk;
        }
    }




    InputStream.seek(0);
    Skip_Lines(InputStream, HeaderLength);

    for(int i = 0; i < streamcount; i++ )
    {
        if( i == streamcount - 1 )
        {
            datapoints = totaldatapoints%maxlinesperstream;
            std::cerr << "datapoints " << datapoints << "\n";
        }
        else
        {
            datapoints = maxlinesperstream;
        }

        for(int j = 0; j < datapoints; j++)
        {
            for( int k = 0; k < ColumnCount; k++ )
            {
                InputStream >> doublejunk;
                if( k == 0)
                {
                    *streamlist[i] << doublejunk << " ";
                }
                else if( k == ycolumn )
                {
                    *streamlist[i] << doublejunk << "\n";
                    if (doublejunk < MinValue )
                    {
                        MinValue = doublejunk;
                    }
                    else if (doublejunk > MaxValue)
                    {
                        MaxValue = doublejunk;
                    }
                }
           }

        }

    }

    for(int i = 0; i < streamcount; i++)
    {
        streamlist[i]->seek(0);
    }



    return;
}

void File::setPeriod()
{
    CurrentStream->seek(0);
    double time1;
    double time2;
    double junk;
    *CurrentStream >> time1;
    *CurrentStream >> junk;
    *CurrentStream >> time2;
    CurrentStream->seek(0);

    period = time2 - time1;
    frequency = (int) (1/period);
    return;

}

//new

void File::Copy_Data_New(QVector<double> &x, QVector<double> &y, double time )
{
    /*if(onestreamonly == true)
    {
        Copy_Data_NewNew(x, y);
        return;
    }*/

    int startline = (int) ((time*frequency) - maxdatapoints/2);
    if( startline < 0 )
    {
        startline = 0;
    }

    else if( startline + maxdatapoints > totaldatapoints - 1 )
    {
        startline = (totaldatapoints - maxdatapoints)%totaldatapoints;
    }


    int transferstreams = (int) ((startline + maxdatapoints)/maxlinesperstream - startline/maxlinesperstream + 1);
    //int transferstreams = (int) (maxdatapoints/maxlinesperstream) + 1;
    int firststreamint = (int) (startline/maxlinesperstream);

    std::cerr << "transferstreams = " << transferstreams << "\n";
    std::cerr << "firststreamint = " << firststreamint << "\n";
    //Move streams to correct position



    for( int i = 0; i < transferstreams; i++ )
    {
        streamlist[firststreamint + i]->seek(0);
    }
    Skip_Lines(*streamlist[firststreamint], startline%maxlinesperstream);
    //

    int streamint = 0;

    for(int i = 0; i < maxdatapoints; i++ )
    {
        streamint = (int) ((i + startline)/maxlinesperstream);
        *streamlist[streamint] >> x[i];
        *streamlist[streamint] >> y[i];
    }

    std::cerr << "streamint = " << streamint << "\n";


    return;

}
/*
void File::Copy_Data_NewNew(QVector<double> &x, QVector<double> &y)
{
    int i = 0;
    double junk;
    InputStream.seek(0);
    Skip_Lines(InputStream, HeaderLength);
    while(InputStream.atEnd() == false)
    {
        InputStream >> x[i];
        for(int j = 0; j < ColumnCount; j++)
        {
            InputStream >> junk;
            if( j == ycolumn )
            {
                y[i] = junk;
            }

        }
        i++;
    }

    return;
}*/

void File::Copy_Data_New(QVector<double> &x, QVector<double> &y, double time, double fraction)
{
    int startline = (int) ((time*frequency) - fraction*maxdatapoints);
    if( startline < 0 )
    {
        startline = 0;
    }

    else if( startline + maxdatapoints > totaldatapoints - 1 )
    {
        startline = (totaldatapoints - maxdatapoints)%totaldatapoints;
    }


    int transferstreams = (int) ((startline + maxdatapoints)/maxlinesperstream - startline/maxlinesperstream + 1);
    //int transferstreams = (int) (maxdatapoints/maxlinesperstream) + 1;
    int firststreamint = (int) (startline/maxlinesperstream);

    std::cerr << "transferstreams = " << transferstreams << "\n";
    std::cerr << "firststreamint = " << firststreamint << "\n";
    //Move streams to correct position



    for( int i = 0; i < transferstreams; i++ )
    {
        streamlist[firststreamint + i]->seek(0);
    }
    Skip_Lines(*streamlist[firststreamint], startline%maxlinesperstream);
    //

    int streamint = 0;

    for(int i = 0; i < maxdatapoints; i++ )
    {
        streamint = (int) ((i + startline)/maxlinesperstream);
        *streamlist[streamint] >> x[i];
        *streamlist[streamint] >> y[i];
    }

    std::cerr << "streamint = " << streamint << "\n";


    return;


}



/*

void File::Copy_Data_New(QVector<double>& x, QVector<double>& y, double time )
{
    int startline = (int) ((time*frequency) - maxdatapoints/2);
    if(startline < 0)
    {
        startline = 0;
    }
    else if( startline + maxdatapoints > totaldatapoints )
    {
        startline = totaldatapoints - maxdatapoints;
    }
    int firststreamint = (int) (startline/maxlinesperstream);
    int secondstreamint = (int) ((startline + maxdatapoints)/maxlinesperstream);    //if data runs over two streams

    streamlist[firststreamint]->seek(0);
    streamlist[secondstreamint]->seek(0);

    if( firststreamint == secondstreamint )  //data over one stream only
    {
        Skip_Lines(*streamlist[firststreamint], startline%maxlinesperstream);
        for( int i = 0; i < maxdatapoints; i++ )
        {
            *streamlist[firststreamint] >> x[i];
            *streamlist[firststreamint] >> y[i];
        }
    }

    else
    {
        Skip_Lines(*streamlist[firststreamint], startline%maxlinesperstream);
        for(int i = 0; i < maxlinesperstream - startline%maxlinesperstream; i++ )
        {

            *streamlist[firststreamint] >> x[i];
            *streamlist[firststreamint] >> y[i];
        }

        for(int i = 0; i < maxdatapoints - maxlinesperstream + startline%maxlinesperstream; i++ )
        {

            *streamlist[secondstreamint] >> x[maxlinesperstream - startline%maxlinesperstream + i];
            *streamlist[secondstreamint] >> y[maxlinesperstream - startline%maxlinesperstream + i];
        }



    }

    return;
}

void File::Copy_Data_New(QVector<double>&x, QVector<double>& y, double time, double fraction)
{
    int startline = (int) ((time*frequency) - fraction*maxdatapoints);
    if(startline < 0)
    {
        startline = 0;
    }
    else if( startline + maxdatapoints > totaldatapoints )
    {
        startline = totaldatapoints - maxdatapoints;
    }
    int firststreamint = (int) (startline/maxlinesperstream);
    int secondstreamint = (int) ((startline + maxdatapoints)/maxlinesperstream);    //if data runs over two streams

    streamlist[firststreamint]->seek(0);
    streamlist[secondstreamint]->seek(0);

    if( firststreamint == secondstreamint )  //data over one stream only
    {
        Skip_Lines(*streamlist[firststreamint], startline%maxlinesperstream);
        for( int i = 0; i < maxdatapoints; i++ )
        {
            *streamlist[firststreamint] >> x[i];
            *streamlist[firststreamint] >> y[i];
        }
    }

    else
    {
        Skip_Lines(*streamlist[firststreamint], startline%maxlinesperstream);
        for(int i = 0; i < maxlinesperstream - startline%maxlinesperstream; i++ )
        {

            *streamlist[firststreamint] >> x[i];
            *streamlist[firststreamint] >> y[i];
        }

        for(int i = 0; i < maxdatapoints - maxlinesperstream + startline%maxlinesperstream; i++ )
        {

            *streamlist[secondstreamint] >> x[maxlinesperstream - startline%maxlinesperstream + i];
            *streamlist[secondstreamint] >> y[maxlinesperstream - startline%maxlinesperstream + i];
        }



    }

    return;

}
*/


















void File::transferData()
{
    processHeader();
    Copy_Data( InputStream, TemporaryStream );
    CurrentStream = &TemporaryStream;
    InputFile_f.close();
    setPeriod();
    std::cerr << "Period = " << period;
    std::cerr << "\nFrequency = " << frequency << "\n";
}

void File::processHeader()
{
    InputStream.seek(0);
    Skip_Lines( InputStream, 1);
    setColumncount();
    Skip_Lines(InputStream, HeaderLength - 2);

    std::string columntitle;
    QString tempqstring1, tempqstring2, tempqstring3;
    InputStream >> tempqstring1;
    InputStream >> tempqstring2;
    columntitlelist.push_back(tempqstring1 + " " + tempqstring2);

    for(int i = 1; i < ColumnCount; i++ )
    {
        InputStream >> tempqstring1;
        InputStream >> tempqstring2;
        InputStream >> tempqstring3;
        columntitlelist.push_back(tempqstring1 + " " + tempqstring2 + " " + tempqstring3);
    }

    for(int i = 0; i < ColumnCount; i++ )
    {
        columntitle = columntitlelist[i].toStdString();
        std::cerr << columntitle << "\n";
    }

    return;
}

void File::setColumn(int column_)
{
    ycolumn = column_;
    return;
}

void File::setColumncount()
{

    QString qstring;

    InputStream >> qstring;

    InputStream >> qstring;


    ColumnCount = qstring.toInt();
    return;
}


bool File::getFileLoaded()
{
    return fileloaded;
}


void File::setFileLoaded(bool fileloaded_)
{
    fileloaded = fileloaded_;
    return;
}


int File::getColumncount()
{
    return ColumnCount;
}

void File::Copy_Data(QVector<double>& x, QVector<double>&y, double starttime, double startfraction )
{
    int seekline = (int)(starttime/period) - (int)(startfraction*maxdatapoints);
    CurrentStream->seek(0);
    Skip_Lines(seekline);

    for( int i = 0; i < maxdatapoints; i++ )
    {
        *CurrentStream >> x[i];
        *CurrentStream >> y[i];

    }
    return;

};





double File::getPeriod( )
{
    return period;

}

int File::getFrequency( )
{
    return frequency;
}

void File::Skip_Lines( QTextStream& Stream, int lineskip )
{
    QString qjunk;
    std::string junk;
    for( int i = 0; i < lineskip; i++ )
        {
            Stream.readLine();
        }

    return;
}

void File::Skip_Lines( int lineskip )
{
    QString qjunk;
    std::string junk;
    for(int i = 0; i < lineskip; i++ )
    {
        CurrentStream->readLine();
    }
    return;
}

void File::setInputFile( QString inputfile )
{
    InputFile = inputfile;
    return;
}

QString File::getInputFile()
{
    return InputFile;
}

double File::getMinValue()
{
    return MinValue;
}

double File::getMaxValue()
{
    return MaxValue;
}

QString File::getDirectory()
{
    return directory;
}

int File::getMaxdatapoints()
{
    return maxdatapoints;
}




































//PRE-MULTI STREAMS

void File::Copy_Data_High_New( QVector<double>&x, QVector<double>& y, double xrangelow )
{

    int seekline = (int) (xrangelow/period) - (int)(0.25*maxdatapoints);
    CurrentStream->seek(0);

    Skip_Lines(seekline);

    for( int i = 0; i < maxdatapoints; i++ )
    {
        *CurrentStream >> x[i];
        *CurrentStream >> y[i];
    }
    return;
}

void File::Copy_Data_Low_New( QVector<double>&x, QVector<double>& y, double xrangelow )
{
    int seekline = (int) (xrangelow/period) - (int)(0.75*maxdatapoints);
    CurrentStream->seek(0);

    Skip_Lines(seekline);

    for(int i = 0; i < maxdatapoints; i++ )
    {
        *CurrentStream >> x[i];

        *CurrentStream >> y[i];
    }
    return;
}

void File::Copy_Data_High( QVector<double>& x, QVector<double>& y, double xrangelow )
{
    int seekpos = (int)(xrangelow*frequency - 0.25*maxdatapoints)*charperline;
    if(seekpos < 0)
    {
        seekpos = 0;
    }
    CurrentStream->seek(seekpos);


    for( int i = 0; i < maxdatapoints; i++ )
    {

        *CurrentStream >> x[i];
        *CurrentStream >> y[i];
    }

    return;
};

void File::Copy_Data( QTextStream& Stream1, QTextStream& Stream2 )
{
    QString qjunk;
    double junk;
    for(int i = 0; i < ColumnCount; i++)
    {
        Stream2.setRealNumberNotation(QTextStream::ScientificNotation);
        Stream2.setRealNumberPrecision(10);
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

            MaxValue = junk;


            MinValue = junk;
            Stream2 << junk << " ";

        }
        else
        {
            Stream1 >> qjunk;
        }
    }


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
void File::Copy_Data_Low( QVector<double>& x, QVector<double>& y, double xrangehigh )
{

    int seekpos = ((int)(xrangehigh*frequency) - (int)(0.75*maxdatapoints))*charperline;
    if(seekpos < 0)
    {
        seekpos = 0;
    }
    CurrentStream->seek(seekpos);

    for( int i = 0; i < maxdatapoints; i++ )
    {

        *CurrentStream >> x[i];
        *CurrentStream >> y[i];
    }

    return;
};



