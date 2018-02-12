/*
File: SqList.h
Author: Adrianne Santinor
Date: 09/28/2017
E-mail: santa1@umbc.edu
Description: header file that contains member functions and variables of SqList class
*/

#include "Int341.h"
#ifndef _SQLIST_H_
#define _SQLIST_H_
#include <list>
using namespace std;

class SqList{
  public:
    //must run in O(1) time
    SqList();
  
    //destructor
    ~SqList();

    //copy constructor
    SqList(const SqList& other);

    //traverse through 2d list with double iterators
    void traverse(int pos);
  
    //lists have no index so we gotta use this
    Int341& operator[](int pos);
  
    //splits and merges lists
    void consolidate();
  
    //add to beginning of a list
    void addFirst(const Int341& x);
  
    //add to end of list
    void addLast(const Int341& x);
  
    //return first int in list and then delete element
    Int341 removeFirst();
  
    //return last int in list and then delete element
    Int341 removeLast();
  
    //add lists to SqList
    void addList(const SqList& M, const list<Int341>& addOn);
  
    //add to particular place in list
    void add(int pos, const Int341& data);
  
    //return item at particular place in list and then delete element
    Int341 remove(int pos);
  
    //returns position of the first occurence of a value in SqList
    int indexOf(const Int341& data);
  
    //returns total number of elements in a list
    int numItems();
  
    //print out number of items in list followed by all its elements
    void dump();
  
    //grading shit. no touchy
    void inspector();
  
    //oh no
    const SqList& operator=(const SqList& rhs);
  
  private:
    list< list<Int341> > L;
    list<Int341> m_firstL;
    list< list<Int341> >::iterator m_mainIt;
    list<Int341>::iterator m_subIt;
    int m_numElements;
};

#endif
