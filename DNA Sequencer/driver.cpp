/*File: driver.cpp
Project: CMSC 202 Project 3, Spring 2017
Author: Adrianne Santinor
Section: 15
E-mail: santa1@umbc.edu
Description: Given driver program to execute DNA and Sequencer functions 
(unedited)
*/

#include "Sequencer.h"
#include <iostream>
using namespace std;

//Uses command line arguments to pass the name of the data file to the sequencer
int main (int argc, char* argv[]) {
  if (argc < 2)
    {
      cout << "You are missing a data file." << endl;
      cout << "File 1 should be a file of half of the dna base pairs. " << endl;
    }
  else
    {
      Sequencer D = Sequencer(argv[1]);
    }
  return 0;
}
