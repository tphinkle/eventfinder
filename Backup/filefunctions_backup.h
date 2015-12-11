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
//QFile InputFile_f;
//std::unique_ptr<QTextStream> InputStream;

QFile InputFile_f;
QTemporaryFile TemporaryFile_f;
//std::shared_ptr<QTextStream> InputStream;
QTextStream InputStream;
QTextStream TemporaryStream;
QTextStream* CurrentStream;

int HeaderLength;                        //Number of lines in header
int FileLength;                          //Number of lines in file total
int DataLength;                          //Number of lines that contain data
int ColumnCount;                         //Number of columns in data file
int xcolumn;                             //x-axis
int ycolumn;                             //y-axis
int maxdatapoints;                       //max number of data points that can be loaded into the vector (max on plot...)
double MaxValue, MinValue;               //Max y value of data; min y value of data

File();

void Skip_Lines( QTextStream& Stream, int linecount );                      //Moves CurrentStream ahead linecount lines

//void Skip_Lines( QTextStream Stream, int linecount );        //Moves Stream ahead linecount lines

void Copy_Data( QTextStream& Stream1, QTextStream& Stream2 );  //Copies data from Stream1 to Stream2

void Copy_Data( int startline, QVector<double>& x, QVector<double>& y );  //Copies data from CurrentStream to x

void Copy_Data( QTextStream Stream, QVector<double>& x, QVector<double>& y ); //Copies data from Stream to x

void Copy_Data_Low( QVector<double>& x, QVector<double>& y );

void Copy_Data_High( QVector<double>& x, QVector<double>& y );

//void Copy_Data( QTextStream Stream, QVector<double>& x, QVector<double>&y, ...)

void OpenFile( QString FileName );

double getPeriod(); //Calculates period of data in CurrentStream, returns CurrentStream to position

int getFrequency();

int getTotalDataPoints();  //Counts data points in CurrentStream, returns CurrentStream to beginning

int getTotalDataPoints( QTextStream* Stream ); //Counts data points in Stream, returns Stream to beginning

void Read_Lines( int linecount, QVector<double> &xx );

void setInputFile( QString qstring );

QString getInputFile();

private:
QString InputFile;

int TotalDataPoints;                     //Total number of data points in file; redundant with DataLength
double Frequency;                        //Sampling frequency of data file, e.g. 10000 Hz
double Period;                           //Period of data file, e.g. 0.00001 seconds

};
#endif // FILEFUNCTIONS_H

