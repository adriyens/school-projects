// File: Int341.h
// 
// UMBC Fall 2017 CMSC 341 Project 2 
//
// Int341 is basically an int.
// Having it defined as a class allows us to track the number of times
// data items are copied for the SqList data structure for Project 2.
//

#ifndef _INT341_H_
#define _INT341_H_

class Int341 {

public:

   // constructor, default value = 0
   //
   Int341(int n=0) ;    

   // destructor. (No actual memory dealloction, here.)
   //
   ~Int341() ;		

   // copy constructor
   //
   Int341(const Int341& other) ;    

   // assignment opeartor
   //
   const Int341& operator=(const Int341& rhs) ;    

   // data "payload" is just an int
   //
   int m_data ;

   // print out # of calls to constructor, copy constructor, 
   // destructor and assignment operator
   // 
   static void report() ;

   // turn on debugging output??
   static bool m_debug ;

private:
   static int m_constructor_calls ;
   static int m_copy_constr_calls ;
   static int m_destructor_calls  ;
   static int m_assignment_calls  ;

} ;

#endif