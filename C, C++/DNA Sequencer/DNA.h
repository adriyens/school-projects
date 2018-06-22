/*File: DNA.h
Project: CMSC 202 Project 3, Spring 2017
Author: Adrianne Santinor
Section: 15
E-mail: santa1@umbc.edu
Description: These are the given function prototypes for the DNA class.
 */

#ifndef DNA_H
#define DNA_H

#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//Constant number of nucleotides in trinucleotide
const int TRINUCLEOTIDE_SIZE = 3;

struct Nucleotide {
  char m_payload;
  Nucleotide *m_next;
};

class DNA {
 public:
  //name: DNA (default constructor)
  //pre: None
  //post: A linked list (DNA) where m_head and m_tail points to NULL
  DNA();
  //name: ~DNA (destructor)
  //pre: There is an existing linked list
  //post: A linked list (DNA) is deallocated (including all dynamically 
  //     allocated nucleotides) 
  //     to have no memory leaks!
 ~DNA();
  //name: InsertEnd
  //pre: Takes in a char. Creates new node (nucleotide). 
  //     Requires a linked list (strand of DNA)
  //post: Adds a new node (nucleotide) to the end of the linked list (strand of DNA).
  void InsertEnd(char payload);
  //name: Display
  //pre: Outputs the dna strand(s); Pass it 1 for just the nucleotides; 
  //     2 for the nucleotides and it's complement (base pair)
  //post: None
  void Display(int numStrand);
  //name: NumAmino
  //pre: Takes in an amino acid name and its trinucleotide codon
  //     Trinucleotides are just three nucleotides in a row.
  //post: Searches the linked list for specific sequence; outputs results
  void NumAmino(string name, string trinucleotide);
  //name: Sequence
  //pre: Takes in full genetic code of one polynucleotide and looks at 
  //     one trinucleotide at a time.
  //     Known amino acids are displayed, others are unknown. Stored in dynamic array.
  //post: Displays either name of amino acid or unknown for each trinucleotide
  void Sequence();
  //name: Translate (Provided)
  //pre: Takes in three nucleotides (must be G,C,T, or A)
  //post: Translates a trinucleotide to its amino acid
  string Translate(string trinucleotide);
  //name: IsEmpty
  //pre: Takes in a linked list (DNA)
  //post: Checks to see if the linked list (strand of DNA) is empty or not
  bool IsEmpty();
  //name: SizeOf
  //pre: Takes in a linked list (DNA)
  //post: Populates m_size with the total number of nucleotides loaded
  void SizeOf();
  //name Clear
  //pre: Takes in a linked list (DNA)
  //post: Clears out the linked list (all nodes too)
  void Clear();
 private:
  Nucleotide *m_head;
  Nucleotide *m_tail;
  int m_size;
};

#endif
