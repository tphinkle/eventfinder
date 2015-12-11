#ifndef FILEFUNCTIONS_H
#define FILEFUNCTIONS_H

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



class File
{
public:
File();

int ycolumn;                             //y-axis

void OpenFile( QString FileName);

void Skip_Lines( QTextStream& Stream, int linecount );         //Moves CurrentStream ahead linecount lines

void Skip_Lines( int linecount );

void Copy_Data( QTextStream& Stream1, QTextStream& Stream2 );             //Copies data from Stream1 to Stream2

void processHeader();

int getColumncount();

int getMaxdatapoints();

void setColumncount();

void setColumn(int column_);

void transferData();

//void Copy_Data( int startline, QVector<double>& x, QVector<double>& y );  //Copies data from CurrentStream to x

void Copy_Data_Low( QVector<double>& x, QVector<double>& y, double xrangehigh );

void Copy_Data_High( QVector<double>& x, QVector<double>& y, double xrangelow );

void Copy_Data_High_New( QVector<double>&x, QVector<double>& y, double xrangelow );

void Copy_Data_Low_New( QVector<double>&x, QVector<double>& y, double xrangelow );

void Copy_Data(QVector<double>& x, QVector<double>&y, double starttime, double startfraction );

void setPeriod(); //Sets period and frequency

double getPeriod(); //Calculates period of data in CurrentStream

int getFrequency(); //Calculates the frequency of the data in CurrentStream

int getTotaldatapoints();

double getMinValue();

double getMaxValue();

void Read_Lines( int linecount, QVector<double> &xx );

void setInputFile( QString qstring );

bool getFileLoaded();

void setFileLoaded(bool fileloaded_);

QString getInputFile();

QString getDirectory();

void calculateTotaldatapoints();

void calculateTotaldatapointsFAST();

void transferDatanew();

void createStreamlist();

void moveDatatostreamlist();

void processHeadernew();

void calculatePeriod();

void Copy_Data_New(QVector<double> & x, QVector<double> & y, double time );

void Copy_Data_New(QVector<double>&x, QVector<double>& y, double time, double fraction);

void Copy_Data_NewNew(QVector<double> &x, QVector<double> &y);

void addEventline(int index, double starttime, double endtime, double baseline);

void findEventline(int index);

void writeCursor1data(double time, double amplitude);

void writeIntegrationdata(double integration_);

std::vector<QString> columntitlelist;
std::vector<QTextStream*> streamlist;
int streamcount;
private:
QString InputFile;
int totaldatapoints;                     //Total number of data points in file; redundant with DataLength
double frequency;                        //Sampling frequency of data file, e.g. 10000 Hz
double period;                           //Period of data file, e.g. 0.00001 seconds
int charperline;
int maxlinesperstream;
int streamprecision;

bool onestreamonly;


bool fileloaded;

//used to be public
QFile InputFile_f;
QTemporaryFile TemporaryFile_f;
QTextStream InputStream;
QTextStream TemporaryStream;
QTextStream* CurrentStream;
QFile OutputFile_f;
QTextStream OutputStream;
QString directory;

std::vector<QTemporaryFile*> streamlist_f;


int HeaderLength;                        //Number of lines in header
int FileLength;                          //Number of lines in file total
int DataLength;                          //Number of lines that contain data
int ColumnCount;                         //Number of columns in data file
int xcolumn;                             //x-axis

int maxdatapoints;                       //max number of data points that can be loaded into the vector (max on plot...)
double MaxValue, MinValue;               //Max y value of data; min y value of data

};
#endif // FILEFUNCTIONS_H

