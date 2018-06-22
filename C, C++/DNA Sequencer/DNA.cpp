/*File: DNA.cpp
Project: CMSC 202 Project 3, Spring 2017
Author: Adrianne Santinor
Section: 15
E-mail: santa1@umbc.edu
Description: These are the functions for DNA class.
*/

#include "DNA.h"
#include <vector>

//linked list where m_head and m_tail points to NULL and m_size is 0
DNA::DNA() {
  m_head = NULL;
  m_tail = NULL;
  m_size = 0;
}

DNA::~DNA() {
  Clear();
  m_head = NULL;
}

//adds new nucleotide (node) to end of strand of DNA (linked list)
void DNA::InsertEnd(char payload) {
  //new nucleotide we're adding to the end
  Nucleotide* addOn = new Nucleotide;
  addOn->m_payload = payload;
  addOn->m_next = m_head;;

  //if list is empty, head and tail both point to it
  if ( IsEmpty() ) { 
    m_head = addOn;
    m_tail = addOn;
  } else {
    //when there's only item in the list
    if (m_head == m_tail) 
      m_head->m_next = addOn;
    else
      m_tail->m_next = addOn;

    //have new nucleotide point to null and replace tail with it
    addOn->m_next = NULL;
    m_tail = addOn;
  }
  SizeOf();
}

//prints out 1) just the nucleotides or 2) nucleotides and its complement (base pair)
void DNA::Display(int numStrand) {
  if (numStrand == 1) {
    cout << "Strands:" << endl;

    for (Nucleotide* curr = m_head; curr != NULL; curr = curr->m_next) {
      cout << "\t" << curr->m_payload << endl;
    }

    cout << "\tEND\n" << endl;
    cout << m_size << " nucleotides listed." << endl;
    cout << m_size / TRINUCLEOTIDE_SIZE << " trinucleotides listed.\n" << endl;
  }
  else if (numStrand == 2) {
    cout << "Base pairs:" << endl;

    for (Nucleotide* curr = m_head; curr != NULL; curr = curr->m_next) {
      char pair;

      if (curr->m_payload == 'A')
	pair = 'T';
      else if (curr->m_payload == 'G')
	pair = 'C';
      else if (curr->m_payload == 'T')
        pair = 'A';
      else if (curr->m_payload == 'C')
        pair = 'G';

      cout << "\t" << curr->m_payload << "-" << pair << endl;
    }
    cout << "\tEND\n" << endl;
    cout << m_size << " base pairs listed." << endl;
    cout << m_size / TRINUCLEOTIDE_SIZE << " trinucleotides listed.\n" << endl;
  }
}

//searches linked list for specific sequence; outputs result
void DNA::NumAmino(string name, string trinucleotide) {
  //counter to keep track of how many instances of an amino acid with a certain
  //trinucleotide sequence is found in the list
  int trinucAmnt = 0;
  Nucleotide* curr = m_head;

  //iterates through linked list
  while (curr != NULL) {
    //want a new trinucleotide every time we go through loop
    char trinuc[TRINUCLEOTIDE_SIZE];

    //as we iterate through linked list, we populate char array trinuc with
    //nucleotides
    for (int i = 0; i < TRINUCLEOTIDE_SIZE; i++) {
      trinuc[i] = curr->m_payload;
      curr = curr->m_next;
    }
    //if the trinucleotide found matches the one we're searching for, we
    //increment counter by one
    if (trinuc == trinucleotide)
      trinucAmnt++;
  }

  cout << trinucAmnt << " instances of " << name << " (" << trinucleotide << ") found." << endl;
}

//takes in full genetic code of one polynucleotide and looks at one trinucleotide at a time. known amino acids are displayed, others are unknown. stored in dynamic array. displays either name of amino acid or unknown for each trinucleotide
void DNA::Sequence() {
  vector <string> sequenceList;
  Nucleotide* curr = m_head;
  
  while (curr != NULL) {
    char trinuc[TRINUCLEOTIDE_SIZE];
    
    for (int i = 0; i < TRINUCLEOTIDE_SIZE; i++) {
      trinuc[i] = curr->m_payload;
      curr = curr->m_next;
    }
    //once we have a full trinucleotide, we add it to our sequence vector
    sequenceList.push_back( Translate(trinuc) );
  }

  delete curr;
  
  cout << "Amino acids:" << endl;
  
  for (int j = 0; j < static_cast<int>(sequenceList.size()); j++)
    cout << "\t" << sequenceList.at(j) << endl;

  cout << sequenceList.size() << " amino acids found.\n" << endl;

}

string DNA::Translate(string trinucleotide){
  if((trinucleotide=="ATT")||(trinucleotide=="ATC")||(trinucleotide=="ATA"))
    return ("Isoleucine");
  else if((trinucleotide=="CTT")||(trinucleotide=="CTC")||(trinucleotide=="CTA")||
          (trinucleotide=="CTG")|| (trinucleotide=="TTA")||(trinucleotide=="TTG"))
    return ("Leucine");
  else if((trinucleotide=="GTT")||(trinucleotide=="GTC")||
          (trinucleotide=="GTA")||(trinucleotide=="GTG"))
    return ("Valine");
  else if((trinucleotide=="TTT")||(trinucleotide=="TTC"))
    return ("Phenylalanine");
  else if((trinucleotide=="ATG"))
    return ("Methionine");
  else if((trinucleotide=="TGT")||(trinucleotide=="TGC"))
    return ("Cysteine");
  else if((trinucleotide=="GCT")||(trinucleotide=="GCC")||
          (trinucleotide=="GCA")||(trinucleotide=="GCG"))
    return ("Alanine");
  else if((trinucleotide=="GGT")||(trinucleotide=="GGC")||
          (trinucleotide=="GGA")||(trinucleotide=="GGG"))
    return ("Glycine");
  else if((trinucleotide=="CCT")||(trinucleotide=="CCC")||
          (trinucleotide=="CCA")||(trinucleotide=="CCG"))
    return ("Proline");
  else if((trinucleotide=="ACT")||(trinucleotide=="ACC")||
          (trinucleotide=="ACA")||(trinucleotide=="ACG"))
    return ("Threonine");
  else if((trinucleotide=="TCT")||(trinucleotide=="TCC")||
          (trinucleotide=="TCA")||(trinucleotide=="TCG")||
          (trinucleotide=="AGT")||(trinucleotide=="AGC"))
    return ("Serine");
  else if((trinucleotide=="TAT")||(trinucleotide=="TAC"))
    return ("Tyrosine");
  else if((trinucleotide=="TGG"))
    return ("Tryptophan");
  else if((trinucleotide=="CAA")||(trinucleotide=="CAG"))
    return ("Glutamine");
  else if((trinucleotide=="AAT")||(trinucleotide=="AAC"))
    return ("Asparagine");
  else if((trinucleotide=="CAT")||(trinucleotide=="CAC"))
    return ("Histidine");
  else if((trinucleotide=="GAA")||(trinucleotide=="GAG"))
    return ("Glutamic acid");
  else if((trinucleotide=="GAT")||(trinucleotide=="GAC"))
    return ("Aspartic acid");
  else if((trinucleotide=="AAA")||(trinucleotide=="AAG"))
    return ("Lysine");
  else if((trinucleotide=="CGT")||(trinucleotide=="CGC")||(trinucleotide=="CGA")||
          (trinucleotide=="CGG")||(trinucleotide=="AGA")||(trinucleotide=="AGG"))
    return ("Arginine");
  else if((trinucleotide=="TAA")||(trinucleotide=="TAG")||(trinucleotide=="TGA"))
    return ("Stop");
  else
    cout << "returning unknown" << endl;
  return ("Unknown");
}

//takes in linked list and checks if it's empty or not
bool DNA::IsEmpty() {
  if (m_size == 0)
    return true;
  else 
    return false;
}

//takes in linked list and populates m_size with total number of nucleotides (nodes)
void DNA::SizeOf() {
  m_size++;
}

//clears linked list
void DNA::Clear() {
  Nucleotide* temp = m_head;

  while (temp != NULL) {
    m_head = m_head->m_next;
    delete temp;
    m_size--;
    temp = m_head;
  }

  cout << "DNA sequence deleted from memory" << endl;
}
