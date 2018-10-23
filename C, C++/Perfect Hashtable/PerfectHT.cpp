// File: PerfectHT.cpp
// Author(s): Professor Chang & Adrianne Santinor
// UMBC CMSC 341 Fall 2017 Project 5
//
// Implementation of HashFunction, SecondaryHT & PerfectHT classes.
//
// Version: 2017-11-30
//

#include <stdexcept>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace std ;

#include "PerfectHT.h"
#include "primes.h"


// =====================================================================
// HashFunction class implementation 
// =====================================================================


// By default do not print info to screen
//
bool HashFunction::m_debug = false ;


// Constructor.
// The constructor picks the smallest prime # greater than
// or equal to n for the table size. 
// Default value of n defined in header.
//  
// Initializes other hash function parameters randomly.
//
HashFunction::HashFunction(int n /* =100*/ ) {

   // note: maxPrime defined in prime.h
   //
   if (n > maxPrime) throw out_of_range("HashTable size too big.\n") ;

   m_tsize = findPrime(n) ;
   m_factor = ( rand() % (m_tsize - 1) ) + 1 ;
   m_shift =  rand() % m_tsize ;
   m_multiplier = 33 ;  // magic number from textbook
   m_reboots = 0 ;

}


// Function that maps string to unsigned int.
// Return value can be much larger than table size.
// Uses m_multiplier data member.
// Return value must be unsgined for overflow to work correctly.
//
unsigned int HashFunction::hashCode(const char *str) const {

   unsigned int val = 0 ; 

   int i = 0 ;
   while (str[i] != '\0') {
      val = val * m_multiplier + str[i] ;
      i++ ;
   }
   return val ; 
}


// Getter for table size
//
int HashFunction::tableSize() const {
   return m_tsize ;
}


// Overloaded () operator that makes this a "functor" class.
// Returns the slot in the hash table for str.
// Uses the MAD method: h(x) = (ax + b) % m where 
// the parameters are:
//   a = m_factor
//   b = m_shift
//   m = m_tsize
//
unsigned int HashFunction::operator() (const char *str) const {
   return ( m_factor * hashCode(str) + m_shift ) % m_tsize ;
}


// Pick new parameters for MAD method and the hashCode function.
// Note: can change table size.
//
void  HashFunction::reboot() {

   // Implement the reboot function
   // pick new values for m_factor and m_shift each reboot
   //   make sure you get *different* values
   // change m_multiplier to next odd number  every 3rd reboot
   // increase table size to next prime # every 5th reboot
  
  m_reboots++;
  
  //every third reboot change m_multiplier
  if (m_reboots % 3 == 0)
      m_multiplier += 2;
  
  //every fifth reboot change table size to NEXT prime num
  //adding 1 ensures we don't just get the same size again
  if (m_reboots % 5 == 0) 
    m_tsize = findPrime(m_tsize + 1);
  
  //make sure factor and shift are under 10
  m_factor = ( rand() % (m_tsize - 1) ) + 1 ;
  m_shift =  rand() % m_tsize ;
  
  if (m_debug) {
    cout << "---- reboot " << m_reboots 
         << ": | m_tsize = " << m_tsize
         << " | m_multiplier = " << m_multiplier 
         << " | m_factor = " << m_factor 
         << " | m_shift = " << m_shift << endl;
  }
  
}


// Set random seed for the random number generator.
// Call once at the start of the main program.
// Uses srand() and rand() from cstdlib which is
// shared with other code. For compatibility with
// C++98, it does not have a private random number 
// generator (e.g., mt19337).
//
void HashFunction::setSeed(unsigned int seed) {
   srand(seed) ;
}

void HashFunction::searchArray(int& num, int start, int end){
  
  //ensure indices are within range
  if (start <= end){
    //split array in half
    int bi = start + (end - start) / 2;
    
    if (num == primes[bi])
      num = primes[bi];
    //returns next prime number
    if (primes[bi - 1] < num && primes[bi] > num)
      num = primes[bi];
    //searches upper half of array
    if (num > primes[bi])
      searchArray(num, bi + 1, end);
    //searches lower half of array
    if (num < primes[bi])
      searchArray(num, 0, bi - 1);
  
  }
  
}

// Find the smallest prime number greater than or equal to m.  

int HashFunction::findPrime(int m) {

   // Prime numbers are in global array primes[]
   // included from "primes.h"
   //
   // Use binary search!!
  
  if (m > maxPrime)
    throw out_of_range("Number is too big.");
  
  searchArray(m, 0, numPrimes);
  
  return m;
}


// =====================================================================
// SecondaryHT class implementation 
// =====================================================================


// By default do not print debugging info 
bool SecondaryHT::m_debug = false ;


// Create a secondary hash table using the char * strings
// stored in "words". Makes copy of each item in words.
//
SecondaryHT::SecondaryHT(vector<const char *> words) {

   //
   // Keep trying until a table with no collisions is found
   // 
   // wrap debugging statements in "if (m_debug) { ... }"
   //
   // remember that calling HashFunction::reboot() can change 
   // the table size!
   //
   // use strdup to copy char * strings
   //
  
  if (m_debug){cout << "===== Called SecondaryHT =====" << endl;}
  
  //make T2's size n^2 where n is the amount of words in vector
  //want size to be a prime number though so we find next prime
  hash.m_tsize = HashFunction::findPrime(words.size() * words.size());
  
  //create a dynamically allocated array of ints to keep track of where collisions occur
  int *space = new int[hash.tableSize()];
  //initialize everything to 0
  for (int i = 0; i < hash.tableSize(); i++) {space[i] = 0;}
  
  m_attempts = m_size = 0;
  
  //iterate through words vector so we can add it to T2 later
  for (unsigned int i = 0; i < words.size(); i++){
    
    //get index words would go into
    int hashkey = hash(words.at(i));

    //if there's already a value at T2 (collision!!)
    //only reboot if we haven't exceeded 20 attempts
    if (space[hashkey] == 1){
      delete[] space;
      if (m_attempts >= maxAttempts) 
        throw very_unlucky("You done goofed.");
      hash.reboot();  //get different hash function
      space = new int[hash.tableSize()];
      for (int j = 0; j < hash.tableSize(); j++) {space[j] = 0;}
      m_attempts++;
      i = -1;         //should reloop through array???
    }
    else {
      //indicate that that index will have a string in it
      space[hashkey] = 1;
    }
    
  }
  
  m_attempts++;
  
  delete[] space;     //we don't need this anymore
  
  //now that we have a collision free hash function we can populate T2
  T2 = new char*[hash.tableSize()];
  //initialize everything to NULL
  for (int i = 0; i < hash.tableSize(); i++) {T2[i] = NULL;}
  
  for (unsigned int i = 0; i < words.size(); i++){
    int hashkey = hash(words.at(i));
    char *value = strdup(words.at(i));
    T2[hashkey] = value;
    m_size++;
  }
  
  if (m_debug){cout << "Number of attempts: " << m_attempts << endl;}
  
}


// Copy constructor. Remember to strdup.
//
SecondaryHT::SecondaryHT(const SecondaryHT& other) {
  
  m_attempts = other.m_attempts;
  m_size = other.m_size;
  hash = other.hash;
  T2 = new char*[other.tableSize()];
  
  for (unsigned int i = 0; i < other.tableSize(); i++){
    if (other.T2[i] != NULL) {T2[i] = strdup(other.T2[i]);}
    else {T2[i] = NULL;}
  }
  
}


// Destructor. Use free() to free strings.
//
SecondaryHT::~SecondaryHT() {
  
  //iterate through T2
  for (unsigned int i = 0; i < tableSize(); i++){
    //ensure we don't double free a pointer
    if (T2[i] != NULL)
      free(T2[i]);  //free memory used by strings
  }
  
  delete[] T2;      //delete T2 pointer
  T2 = NULL;

}


// Assignment operator. Remember to use strdup() and free()
//
const SecondaryHT& SecondaryHT::operator=(const SecondaryHT& rhs) {
  
  //free all the strings in the current T2 array
  for (unsigned int i = 0; i < tableSize(); i++){
    if (T2[i] != NULL)
      free(T2[i]);
  }
  
  delete[] T2;      //delete T2 pointer
  
  hash = rhs.hash;
  m_attempts = rhs.m_attempts;
  m_size = rhs.m_size;
  
  T2 = new char*[rhs.tableSize()];
  
  for (unsigned int i = 0; i < rhs.tableSize(); i++){
    if (rhs.T2[i] != NULL) {T2[i] = strdup(rhs.T2[i]);}
    else {T2[i] = NULL;}
  }
  
  return *this;

}


// returns whether given word is in this hash table.
//
bool SecondaryHT::isMember (const char *word) const {

   int slot = hash(word);

   assert ( 0 <= slot && slot < hash.tableSize() ) ;

   if (T2[slot] == NULL) return false ;

   if ( strcmp(word, T2[slot]) != 0 ) return false ;

   return true ; 
}


// getter. Actually, the hash function has the size.
//
int SecondaryHT::tableSize() const {
   return hash.tableSize() ;
}


// Pretty print for debugging
//
void SecondaryHT::dump() const {
   cout << "=== Secondary Hash Table Dump: ===\n" ;
   cout << "Table size = " << hash.tableSize() << endl ;
   cout << "# of items = " << m_size << endl ;
   cout << "# of attempts = " << m_attempts << endl ;
 
   for (int i=0 ; i < hash.tableSize() ; i++) {
      cout << "T2[" << i << "] = " ;
      if (T2[i] != NULL) cout << T2[i] ;
      cout << endl ;
   }

   cout << "==================================\n" ;
}



// =====================================================================
// PerfectHT class implementation 
// =====================================================================


// by default, do not print debugging info
//
bool PerfectHT::m_debug = false ;


// Create a Perfect Hashing table using the first n strings 
// from the words array.
//
PerfectHT::PerfectHT (const char *words[], int n) {

   // Implement constructor for PerfectHT here.
   //
   // You will need an array of vectors of char * strings.
   // Something like;
   //
   //    vector<const char *> *hold = new vector<const char *>[m] ;
   //
   // Each hold[i] is a vector that holds the strings
   // that hashed to slot i. Then hold[i] can be passed
   // to the SecondaryHT constructor.
   //
 
  hash.m_tsize = HashFunction::findPrime(n);
  
  //use to keep track of collisions
  vector<const char*> *hold = new vector<const char*>[tableSize()];
  
  //hash every word in char array into hold
  for (int i = 0; i < n; i++){
    int hashkey = hash(words[i]);
    hold[hashkey].push_back(words[i]);
  }
  
  //create arrays for PHT1&2 and initialize everything to NULL
  PHT1 = new char*[tableSize()];
  for (int i = 0; i < tableSize(); i++) {PHT1[i] = NULL;}
  PHT2 = new SecondaryHT*[tableSize()];
  for (int i = 0; i < tableSize(); i++) {PHT2[i] = NULL;}
  
  for (int i = 0; i < tableSize(); i++){
    //if there's only one char in the vector then put it into PHT1
    if (hold[i].size() == 1)
      PHT1[i] = strdup(hold[i].at(0));
    //if there's more than one, pass whole vector into a new SecondaryHT
    if (hold[i].size() > 1)
      PHT2[i] = new SecondaryHT(hold[i]);
  }

  delete[] hold;  //don't need this anymore

}


// Copy constructor. Use strdup or SecondaryHT copy constructor.
//
PerfectHT::PerfectHT(const PerfectHT& other) {
 
  //get proper table size by copying HashFunctions
  hash = other.hash;
  PHT1 = new char*[hash.tableSize()];
  PHT2 = new SecondaryHT*[hash.tableSize()];

  //populate PHT1 and PHT2 with values
  for (int i = 0; i < hash.tableSize(); i++){
    //use strdup() to copy strings
    if (other.PHT1[i] != NULL){PHT1[i] = strdup(other.PHT1[i]);}
    else {PHT1[i] = NULL;}
    //use SecondaryHT copy constructor
    if (other.PHT2[i] != NULL) {PHT2[i] = new SecondaryHT(*other.PHT2[i]);}
    else {PHT2[i] = NULL;}
  }
  
}


// Destructor. Remember to use free() for strdup-ed strings.
//
PerfectHT::~PerfectHT() {
  
  for (int i = 0; i < tableSize(); i++){
    //PHT1 is the one with the strdup()-ed cstrings so we gotta free 'em
    if (PHT1[i] != NULL) {free(PHT1[i]);}
    //gotta call the destructor on every SecondaryHT object
    if (PHT2[i] != NULL) {delete PHT2[i];}
  }
  
  delete[] PHT1;
  PHT1 = NULL;
  delete[] PHT2;
  PHT2 = NULL;
  
}


// Assignment operator. Use strdup() and free() for strings.
//
const PerfectHT& PerfectHT::operator=(const PerfectHT& rhs) {
  
  //delete everything in PHT1 and PHT2 before assigning
  for (int i = 0; i < tableSize(); i++){
    if (PHT1[i] != NULL)
      free(PHT1[i]);
    if (PHT2[i] != NULL)
      delete PHT2[i];
  }
  
  delete[] PHT1;
  PHT1 = NULL;
  delete[] PHT2;
  PHT2 = NULL;
  
  //just use copy constructor
  hash = rhs.hash;
  PHT1 = new char*[hash.tableSize()];
  PHT2 = new SecondaryHT*[hash.tableSize()];

  for (int i = 0; i < hash.tableSize(); i++){
    if (rhs.PHT1[i] != NULL){PHT1[i] = strdup(rhs.PHT1[i]);}
    else {PHT1[i] = NULL;}
    
    if (rhs.PHT2[i] != NULL) {PHT2[i] = new SecondaryHT(*rhs.PHT2[i]);}
    else {PHT2[i] = NULL;}
  }
  
  return *this;
  
}

// Returns whether word is stored in this hash table.
//
bool PerfectHT::isMember(const char * str) const {
   int slot = hash(str) ; 

   if (PHT1[slot] == NULL && PHT2[slot] == NULL) return false ;

   if (PHT1[slot] != NULL) return strcmp(str,PHT1[slot]) == 0 ;

   return PHT2[slot]->isMember(str) ;
}


int PerfectHT::tableSize() const{return hash.tableSize();}


// Pretty print for debugging.
//
void PerfectHT::dump() const {
   int m = hash.tableSize() ;   

   cout << "------------- PerfectHT::dump()  -------------\n" ;
   cout << "table size = " << hash.tableSize() << endl ;
   cout << endl ;
   for (int j=0 ; j < m ; j++) {
      cout << "[" << j << "]:  " ;
      if (PHT1[j] != NULL) cout << PHT1[j] ;
      if (PHT2[j] != NULL) {
         cout << endl ;
         PHT2[j]->dump() ;
      }
      cout << endl ;
   }

   cout << "----------------------------------------------\n" ;
}
