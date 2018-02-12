/*File: proj1.cpp
Project: CMSC 202 Project 1, Spring 2017
Author: Adrianne Santinor
Date: 2/10/2017
Section: 15
E-mail: santa1@umbc.edu
Description: This program simulates a manhunt through the use of arrays and
user input */

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>

using namespace std;

const int MAP_SIZE = 10;

void startMenu();
void coordinates(char loadSim[], int startPoints[]);
void searchMenu();
void createMap(char map[][MAP_SIZE], int xTom, int yTom, int xJerry, int yJerry, int end[]);
void printMap(char map[][MAP_SIZE], int xTom, int yTom, int direction, int finish[]);
void searchMap(int xTom, int yTom, int end[], int direction);

int main() {
  int userChoice, searchChoice = 0;
  int xInvestigator, yInvestigator, xTarget, yTarget;
  char fileName[100];
  int spawnPoints[4];
  int finish[2];
  char field[MAP_SIZE][MAP_SIZE];

  cout << "Welcome to Manhunt!" << endl;

  startMenu();
  cout << "Enter a number 1 - 3: "; cin >> userChoice;

  while (userChoice != 0) {
    //determines what function to run based on user input
    switch(userChoice) {
    case 1: 
      cout << "What is the file name? "; cin >> fileName;
      coordinates(fileName, spawnPoints);
      //assigns the contents of the spawn points array to the x, y coordinates
      //of the investigator and target
      xInvestigator = spawnPoints[0];
      yInvestigator = spawnPoints[1];
      xTarget = spawnPoints[2];
      yTarget = spawnPoints[3];
      //exits the switch statement
      userChoice = 0;
      break;
    case 2:
      cout << "What is the X axis of the investigator?: "; cin >> xInvestigator;
      cout << "What is the Y axis of the investigator?: "; cin >> yInvestigator;
      cout << "What is the X axis of the target?: "; cin >> xTarget;
      cout << "What is the Y axis of the target?: "; cin >> yTarget;
      userChoice = 0;
      break;
    case 3:
      cout << "Aight, deuces." << endl;
      exit(1);
      break;
    default:
      cout << "Enter a number 1 - 3: "; cin >> userChoice;
      break;
    }
  }
  
  createMap(field, xInvestigator, yInvestigator, xTarget, yTarget, finish);
  
  searchMenu();
  cout << "Enter a number 1 - 6: "; cin >> searchChoice;

  while (searchChoice != 0) {
    switch(searchChoice) {
    case 1: 
      xInvestigator--;
      searchMap(xInvestigator, yInvestigator, finish, searchChoice);
      printMap(field, xInvestigator, yInvestigator, searchChoice, finish);
      searchMenu();
      cout << "Enter a number 1 - 6: "; cin >> searchChoice;
      break;
    case 2:
      yInvestigator++;
      searchMap(xInvestigator, yInvestigator, finish, searchChoice);
      printMap(field, xInvestigator, yInvestigator, searchChoice, finish);
      searchMenu();
      cout << "Enter a number 1 - 6: "; cin >> searchChoice;
      break;
    case 3:
      xInvestigator++;
      searchMap(xInvestigator, yInvestigator, finish, searchChoice);
      printMap(field, xInvestigator, yInvestigator, searchChoice, finish);
      searchMenu();
      cout << "Enter a number 1 - 6: "; cin >> searchChoice;
      break;
    case 4:
      yInvestigator--;
      searchMap(xInvestigator, yInvestigator, finish, searchChoice);
      printMap(field, xInvestigator, yInvestigator, searchChoice, finish);
      searchMenu();
      cout << "Enter a number 1 - 6: "; cin >> searchChoice;
      break;
    case 5:
      printMap(field, xInvestigator, yInvestigator, searchChoice, finish);
      searchMenu();
      cout << "Enter a number 1 - 6: "; cin >> searchChoice;
      break;
    case 6:
      cout << "Aight, deuces." << endl;
      exit(1);
    default:
      cout << "Enter a number 1 - 6: "; cin >> searchChoice;
    }
  }

  return 0;
}

//prints out the menu that greets the user when they first launch the program
void startMenu() {
  cout << "What would you like to do?\n"
       << "1. Load a simulation from file\n"
       << "2. Start a new simulation\n"
       << "3. Exit\n"
       << endl;
}

//prints out the menu that asks the user which direction they'd like to search
void searchMenu() {
  cout << "What would you like to do?\n"
       << "1. Search north\n"
       << "2. Search east\n"
       << "3. Search south\n"
       << "4. Search west\n"
       << "5. See map\n"
       << "6. Exit\n"
       << endl;
}

//takes in a file from user input and populates an array with contents from 
//that file
void coordinates(char loadSim[], int startPoints[]) {
  ifstream inputStream;
  inputStream.open(loadSim);

  //populates the array startPoints with the contents from text file line by 
  //line
  inputStream >> startPoints[0];
  inputStream >> startPoints[1];
  inputStream >> startPoints[2];
  inputStream >> startPoints[3];
  
  inputStream.close();
}

//creates a 2d list named map through nested for loops and assigns the 
//coordinates of the target to an array
void createMap(char map[][MAP_SIZE], int xTom, int yTom, int xJerry, int yJerry, int end[]) {
  for (int i = 0; i < MAP_SIZE; i++) {
    for (int j = 0; j < MAP_SIZE; j++) {
      map[i][j] = '_';
    }
  }

  //populates array with target coordinates
  end[0] = xJerry;
  end[1] = yJerry;

  map[xTom][yTom] = 'I';

  for (int i = 0; i < MAP_SIZE; i++) {
    for (int j = 0; j < MAP_SIZE; j++) {
      cout << map[i][j] << " ";
    }
    cout << endl;
  }
}

//prints out the map with the investigator placed on the appropriate 
//coordinates
void printMap(char map[][MAP_SIZE], int xTom, int yTom, int direction, int end[]) {

  map[xTom][yTom] = 'I';
  
  //changes the '_' on the map to a '*' to indicate that the investigator has
  //already been there
  if (direction == 1) {
    map[++xTom][yTom] = '*'; }
  else if (direction == 2) {
    map[xTom][--yTom] = '*'; }
  else if (direction == 3) {
    map[--xTom][yTom] = '*'; }
  else if (direction == 4) {
    map[xTom][++yTom] = '*'; }
  
  for (int i = 0; i < MAP_SIZE; i++) {
    for (int j = 0; j < MAP_SIZE; j++) {
      cout << map[i][j] << " ";
    }
    cout << endl;
  }
}

//compares the coordinates of the investigator & the target, and prints
//out hints on which direction the user should go
void searchMap(int xTom, int yTom, int end[], int direction) {

  //if the coordinates of the investigator & target match then it
  //tells the user and exits the program
  if (xTom == end[0] and yTom == end[1]) {
    cout << "Found em!" << endl;
    exit(1);
  }

  //makes sure the investigator stays inside the field
  if (xTom < 0 or xTom >= MAP_SIZE or yTom < 0 or yTom >= MAP_SIZE) {
      cout << "Out of bounds." << endl;
      searchMenu();
      cout << "Enter a number 1 - 6: "; cin >> direction;
    }

  //compares the coordinates of the investigator & target so it
  //can tell which direction the user should go
  if (yTom < end[1]) {
    cout << "Try searching east." << endl;
  }
  else if (yTom > end[1]) {
    cout << "Try searching west." << endl;
    }
  //when the investigator & target are on the same column
  else if (yTom == end[1]) {
      if (xTom < end[0]) {
	cout << "Try searching south." << endl;
      }
      else if (xTom > end[0]) {
	cout << "Try searching north." << endl;
      }
    }
}
