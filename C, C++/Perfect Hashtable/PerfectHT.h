// File: PerfectHT.h
//
// UMBC CMSC 341 Fall 2017 Project 5
//
// Class declarations for HashFunction, 
// SecondaryHT and PerfectHT.
//
// Version: 2017-11-30
//

#ifndef _PERFECTHASH_H_
#define _PERFECTHASH_H_

#include <stdexcept>
#include <vector>
#include <string>

using namespace std ;
class SecondaryHT;
class PerfectHT;

// 
// "Functor" class for hash functions.
//
class HashFunction {
  
  friend class SecondaryHT;
  friend class PerfectHT;

public:

   // Constructor.
   // Pass in requested hash table size via parameter n.
   // The constructor picks the smallest prime # greater than
   // or equal to n for the table size.
   //  
   // Initializes other hash function parameters randomly.
   //
   HashFunction (int n=100) ;

   // Function that maps string to unsigned int.
   // Return value can be much larger than table size.
   // Uses m_multiplier data member.
   //
   unsigned int hashCode(const char *str) const ;

   // Getter for table size
   //
   int tableSize() const ;

   // Overloaded () operator that makes this a "functor" class.
   // Returns the slot in the hash table for str.
   // Uses the MAD method: h(x) = (ax + b) % m where 
   // the parameters are:
   //   a = m_factor
   //   b = m_shift
   //   m = m_tsize
   //
   unsigned int operator()(const char *str) const ;

   // Pick new parameters for MAD method and the hashCode function.
   // Note: can change table size.
   //
   void reboot() ;
  
   // Searches through array using recursion
   static void searchArray(int& num, int start, int end);

   // Find smallest prime number greater than or equal to m.
   // Relies on global array primes[].
   //
   static int findPrime(int m) ;
   
   // Set random seed for the random number generator.
   // Call once at the start of the main program.
   // Uses srand() and rand() from cstdlib which is
   // shared with other code. For compatibility with
   // C++98, it does not have a private random number 
   // generator (e.g., mt19337).
   //
   static void setSeed(unsigned int seed) ;

   static bool m_debug ;       // print debugging statements?

private:

   unsigned int m_tsize ;      // tablesize, must be prime #
   unsigned int m_factor ;     // must have 0 < m_factor < m_tsize
   unsigned int m_shift ;      // must have 0 <= m_shift < m_tsize
   unsigned int m_multiplier ; // used in hashCode function

   int m_reboots ;             // number of times reboot() was called 

} ;



// Derived exception class that is thrown when 
// SecondaryHT constructor fails to create a
// collision-free secondary hash table after
// many attempts.

class very_unlucky : public std::runtime_error {
public:
   very_unlucky(const string& what) : runtime_error(what) { /* do nothing else */ }
} ;


// Secondary hash table for PerfectHT class.
//
class SecondaryHT {
  
  friend class HashFunction;
  friend class PerfectHT;

public:
   // Create a secondary hash table using the char * strings
   // stored in "words". Makes copy of each item in words.
   //
   SecondaryHT(vector<const char *> words) ;

   // Copy constructor, destructor and assignment operator.
   // Just the usual.
   //
   SecondaryHT(const SecondaryHT& other) ;
   ~SecondaryHT() ;
   const SecondaryHT& operator=(const SecondaryHT& rhs) ;

   // returns whether given word is in this hash table.
   //
   bool isMember(const char* word) const ;

   // getter
   //
   int tableSize() const ;

   // Pretty print for debugging
   //
   void dump() const ;

   static bool m_debug ;   // print debugging info?

private:

   // number of attempts, before we give up.
   //
   static const int maxAttempts = 20 ;   

   // hash function from the functor class.
   //
   HashFunction hash ;

   // The actual hash table. Each entry points
   // to an array of null-terminated char string.
   //
   char **T2;

   // keep track number of attempts to reboot the
   // hash function to achieve collision-free
   // hashing.
   //
   int m_attempts ;  

   // number of items stored in this secondary hash table.
   //
   int m_size ;
} ;


// Perfect Hash Table class.
//
class PerfectHT {
  
  friend class HashFunction;
  friend class SecondaryHT;

public:

   // Create a Perfect Hashing table using the first n strings 
   // from the words array.
   //
   PerfectHT(const char * words[], int n) ;

   // Copy constructor, destructor and assignment operator.
   // Just the usual.
   //
   PerfectHT(const PerfectHT& other) ;
   ~PerfectHT() ;
   const PerfectHT& operator=(const PerfectHT& rhs) ;


   // Returns whether word is stored in this hash table.
   //
   bool isMember(const char * word) const ;

   // Returns number of items stored in this table.
   //
   int tableSize() const ;

   // Print stats for debugging.
   //
   void dump() const ;

   static bool m_debug ;   // print debugging info?

private:

   HashFunction hash ;    // hash function "functor" object

   // PHT = Perfect Hash Table, pronounced "fuut" with a long "oo".
   //
   // The following two arrays are arrays of pointers.
   //
   // If a primary hash slot contains only one char * string,
   // then the string is stored in PHT1.
   //
   // If a primary hash slot contains two or more char * strings,
   // then they are stored in a secondary hash table.
   //
   // Note that PHT2[i] is a POINTER to a SecondaryHT and not
   // a SecondaryHT object.
   // 
   // Space must be allocated for these two arrays.
   // Copies of the stored strings must be made using strdup().
   // Space for the array and for the strings must be deallocated
   // by the destructor.
   //

   char **PHT1 ;          // array of plain old char pointers
   SecondaryHT **PHT2 ;   // array of secondary hash table pointers

} ;


#endif 
