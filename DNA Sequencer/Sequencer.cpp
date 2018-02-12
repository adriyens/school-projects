/*File: Sequencer.cpp
Project: CMSC 202 Project 3, Spring 2017
Author: Adrianne Santinor
Section: 15
E-mail: santa1@umbc.edu
Description: These are the functions for the Sequencer class.
*/

#include "Sequencer.h"

//linked list where m_head & m_tail point to NULL and m_size = SizeOf()
Sequencer::Sequencer(string fileName) {
  m_fileName = fileName;
  readFile();
  cout << "New Sequencer loaded\n" << endl;
  mainMenu();
}

//linked list is deallocated (and nucleotides)
Sequencer::~Sequencer() {
  m_dna.Clear();
}

//populates linked list with file contents of nucleotides
void Sequencer::readFile() {
  char key;

  ifstream inputStream;
  inputStream.open(m_fileName.c_str());

  while (inputStream >> key) 
    m_dna.InsertEnd(key);

  inputStream.close();
}

void Sequencer::mainMenu() {
  int userChoice;

  cout << "Choose an option: \n"
       << "1. Display sequencer (leading strand)\n"
       << "2. Display sequencer (base pairs)\n"
       << "3. Inventory basic amino acids\n"
       << "4. Sequence entire DNA strand\n"
       << "5. Exit\n"
       << endl;

  do {
    cout << "Enter a number 1 - 5: "; cin >> userChoice;

    switch (userChoice) {
    case 1:
    case 2:
      m_dna.Display(userChoice);
      break;
    case 3:
      m_dna.NumAmino("Tryptophan", "TGG");
      m_dna.NumAmino("Phenylalanine", "TTT");
      m_dna.NumAmino("Arginine", "CGT");
      m_dna.NumAmino("Lysine", "AAG");
      m_dna.NumAmino("Histidine", "CAT");
      cout << endl;
      break;
    case 4:
      m_dna.Sequence();
      break;
    case 5:
      m_dna.Clear();
      exit(1);
    }
  } while (userChoice > 0 or userChoice < 5);
}
