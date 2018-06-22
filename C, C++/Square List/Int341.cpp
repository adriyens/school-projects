#include <iostream>
#include "Int341.h"
using namespace std ;

int Int341::m_constructor_calls = 0 ;
int Int341::m_copy_constr_calls = 0;
int Int341::m_destructor_calls = 0 ;
int Int341::m_assignment_calls = 0 ;

bool Int341::m_debug = false ;   // do not debug

Int341::Int341(int n) {
   if (m_debug) cout << "__Int341__ Constructor called\n" ;
   m_data = n ;
   m_constructor_calls++ ;
}



Int341::Int341(const Int341& other) {

   if (m_debug) cout << "__Int341__ Copy constructor called\n" ;

   m_data = other.m_data ;
   m_copy_constr_calls++ ;
}



Int341::~Int341() {
   if (m_debug) cout << "__Int341__ Destructor called\n" ;
   m_data = 0 ;
   m_destructor_calls++ ;
}



const Int341& Int341::operator=(const Int341& rhs) {

   if (m_debug) cout << "__Int341__ Assignment operator called\n" ;

   m_data = rhs.m_data ;
   m_assignment_calls++ ;

   return *this ;  
}


void Int341::report() {
   cout << "__Int341__ Report usage:\n" ;
   cout << "__Int341__   # of calls to constructor         = " << m_constructor_calls << endl ;
   cout << "__Int341__   # of calls to copy constructor    = " << m_copy_constr_calls << endl ;
   cout << "__Int341__   # of calls to destructor          = " << m_destructor_calls  << endl ;
   cout << "__Int341__   # of calls to assignment operator = " << m_assignment_calls  << endl ;
    
}