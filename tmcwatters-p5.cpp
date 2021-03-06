/****************************
Timothy McWatters
tmcwatters-p5.cpp
programming in C++ project 5

Program to read data from a file named "temperatures.txt".
then compute the average temp for each day and the stand dev 
in temps for each day. It will display this data to std out (screen).
*****************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <math.h>
using namespace std;

const int DATE_ELEMENTS = 20;
const int NUM_TEMPS = 24;

void readStrings(istream& inputFile, char string[]);
void readValues(istream& inputFile, double values[]);
void printStrings(char string[]);
void newLine(istream& inputFile);
double meanTemp(double temp[]);
double stdDeviation(double temp[]);
void formatedPrint(char date1[], char date2[], double temps1[], double temps2[]);

int main()
{
   char dateOne[DATE_ELEMENTS];
   char dateTwo[DATE_ELEMENTS];
   double tempOne[NUM_TEMPS];
   double tempTwo[NUM_TEMPS];
   
   ifstream inputFile;
   
   inputFile.open("temperatures.txt"); // Associates inputFile with "Sales.txt"
   // If opening the intput file fails, ERROR message and program closes.
   if (inputFile.fail( )) {
      cout << "Input file opening failed!" << endl;
      exit(1);
   }   
   
   readStrings(inputFile, dateOne);
   readValues(inputFile, tempOne);
   readStrings(inputFile, dateTwo);
   readValues(inputFile, tempTwo);

   formatedPrint(dateOne, dateTwo, tempOne, tempTwo);
   
   inputFile.close(); // Disassociates inputFile  
   
   return 0;
} // End of main

/*************************************
readStrings
   reads the input file and inputs the date into 
   a string of char's when called.
**************************************/
void readStrings(istream& inputFile, char string[])
{
   inputFile >> string;
   
   return;
} // End of readStrings

/*************************************
readValues
   reads the input file and inputs the temperature data 
   for each day into an array when called.
**************************************/
void readValues(istream& inputFile, double values[])
{
   newLine(inputFile);
   for (int i = 0; i < NUM_TEMPS; i++) {
      inputFile >> values[i];
   }
   
   return;
} // End of readValues

/*************************************
printStrings
   Prints the string holding the date.
**************************************/
void printStrings(char string[])
{
   cout << string;

   return;
} // End of printStrings

/*************************************
newLine
   Function to read the next input after a newline,
   but ignoring the input after its called up to the newline.
*************************************/
void newLine(istream& inputFile)
{
   char number;
   do {
      inputFile.get(number);
   } while (number != '\n');
   
   return;
} // End of newLine

/*************************************
meanTemp
   Function to calculate the mean temperature
   for the day.
   Mean (average) is the sum of temperatures divided
   by the number of temperatures.
************************************/
double meanTemp(double temp[])
{
   double sumTemp = 0.0;

   for (int i = 0; i < NUM_TEMPS; i++) {
      sumTemp = sumTemp + temp[i];
   }
   double avgTemp = sumTemp / NUM_TEMPS;
   
   return avgTemp;
} // End of meanTemp

/*************************************
stdDeviation
   Function to calculate the standard temperature
   deviation for the day.
   standard deviation is the sum of (current temperature 
   minus mean temperature, and squaring that result) divided
   by the number of temperatures.
************************************/
double stdDeviation(double temp[])
{
   double avgTemp = meanTemp(temp);
   double numerator = 0.0;
   double curMinusDev = 0.0;
   double squared = 0.0;
   double valUnderRadical = 0.0;
   double DailyStdDev = 0.0;

   for (int i = 0; i < NUM_TEMPS; i++) {
      curMinusDev = temp[i] - avgTemp;
      squared = curMinusDev * curMinusDev;
      numerator += squared;
   }
   valUnderRadical = numerator / NUM_TEMPS;
   DailyStdDev = sqrt(valUnderRadical);
   
   return DailyStdDev;
}

/*************************************
formatedPrint
   Function to print the program output in
   readable format.
************************************/
void formatedPrint(char date1[], char date2[], double temps1[], double temps2[])
{
   cout.setf(ios::fixed);
   cout.precision(0);
   
   cout << "Hour\t\t";
   printStrings(date1);
   cout << "\t";
   printStrings(date2);
   cout << endl;
   
   for (int i = 0; i < NUM_TEMPS; i++) {
      cout << " " << i + 1 << "\t\t   " << temps1[i] << "\t\t   " << temps2[i] << endl;
   }  
   cout << "*****************************************" << endl;

   cout << "Mean Temperature   " << meanTemp(temps1) << "\t\t   " << meanTemp(temps2) << endl;
   cout << "Standard Deviation " << stdDeviation(temps1) << "\t\t   " << stdDeviation(temps2) << endl;

   return;
} // End of formatedPrint