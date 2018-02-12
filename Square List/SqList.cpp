/*
File: SqList.cpp
Author: Adrianne Santinor
Date: 10/01/2017
E-mail: santa1@umbc.edu
Description: cpp file that contains member implementations of SqList.h
*/

/***

I DON'T CARE ANYMORE I'M TURNING IT IN IT'S GOT HELLA BUGS I'M SORRY CHANG

***/

#include <iostream>
#include <stdexcept>
#include <iterator>
#include "SqList.h"
using namespace std;

SqList::SqList() {
  //so i don't have to worry about special cases when SqList is empty
  L.push_front(m_firstL);
  m_mainIt = L.begin();
  m_numElements = 0;
}

SqList::~SqList() {
  //clear all the lists in SqList
  for (m_mainIt = L.begin(); m_mainIt != L.end(); m_mainIt++)
    m_mainIt->clear();
}

SqList::SqList(const SqList& other) {
  m_numElements = other.m_numElements;
  //need this bc object being passed in is const
  list< list<Int341> >::const_iterator otherMainIt = other.L.begin();

  //push back empty lists into new SqList object being copied
  //bc in order to use overloaded assignment operator we need existing lists
  for (int i = 0; i < other.L.size(); i++){
    list<Int341> addOn;
    L.push_back(addOn);
  }

  //have main iterator point to beginning of L
  m_mainIt = L.begin();

  //LIST HAS IT'S OWN OVERLOADED ASSIGNMENT OPERATOR OH MY GOODDDDDD
  for (int i = 0; i < L.size(); i++){
    *m_mainIt = *otherMainIt;
    m_mainIt++;
    otherMainIt++;
  }
}

//so i don't have to keep traversing
void SqList::traverse(int pos){
  //have iterators point to the right places
  m_mainIt = L.begin();
  m_subIt = m_mainIt->begin();

  for (int i = 0; i < pos; i++){
    m_subIt++;
    //if index is at the end of an inner list, increment main iterator
    if (i == m_mainIt->size() - 1){
      m_mainIt++;
      m_subIt = m_mainIt->begin();
    }
  }
}

Int341& SqList::operator[](int pos) {
  traverse(pos);	
  return *m_subIt;
}

void SqList::consolidate() {
  //keep track of adjacent short lists
  bool prevShort = false;
  bool currShort;

  for (m_mainIt = L.begin(); m_mainIt != L.end(); m_mainIt++){
    //if this list empty
    if (m_mainIt->empty()){
      list< list<Int341> >::iterator emptyIt = m_mainIt;
      m_mainIt++;
      L.erase(emptyIt);    //YEET!
      currShort = true;
    }
    //THIS WORKS!!!
    else if ((m_mainIt->size()-1)*(m_mainIt->size()-1) > 4*m_numElements){
      list<Int341> addOn;	//list to splice into
      m_subIt = m_mainIt->begin();
      //have m_subIt point to middle of list
      advance(m_subIt, m_mainIt->size()/2);
      addOn.splice(addOn.begin(), *m_mainIt, m_subIt, m_mainIt->end());
      L.insert(m_mainIt, addOn);
    }
    //not this one tho....
    else if (4*(m_mainIt->size()+1)*(m_mainIt->size()+1) <= m_numElements){
      currShort = true;
      if (prevShort == true){
	//have iterator keep track of list before current list (i.e. previous list) 
	list< list<Int341> >::iterator currList = m_mainIt;
	currList++;
	currList->splice(currList->begin(), *m_mainIt);	//splice that shit boi
      }
      else
	currShort = false;
    }
    prevShort = currShort;
  }
}

void SqList::addFirst(const Int341& x) {
  ++m_numElements;
  L.begin()->push_front(x);
  consolidate();
}

void SqList::addLast(const Int341& x) {
  ++m_numElements;
  //point to back of list (can't use .end() bc it returns past the last index)
  list< list<Int341> >::reverse_iterator backIt = L.rbegin();
  backIt->push_back(x);
  consolidate();
}

Int341 SqList::removeFirst() {
  m_mainIt = L.begin();
  if (m_mainIt->empty())
    throw out_of_range("List is empty.");
  --m_numElements;
  //have temp point to item we're deleting so we can return it
  Int341 temp = m_mainIt->front();
  m_mainIt->pop_front();
  consolidate();
  return temp;
}

Int341 SqList::removeLast() {
  //can't point to .end() bc it returns past the last index so we use a reverse
  //iterator
  list< list<Int341> >::reverse_iterator backIt = L.rbegin();
  if (backIt->empty())
    throw out_of_range("List is empty.");
  --m_numElements;
  Int341 temp = backIt->back();
  backIt->pop_back();
  consolidate();
  return temp;
}

void SqList::add(int pos, const Int341& data) {
  if (pos <= 0 || pos >= m_numElements)
    throw out_of_range("Position not valid.");
  ++m_numElements;
  //have m_mainIt and m_subIt point to the right place
  traverse(pos);
  m_mainIt->insert(m_subIt, data);
  consolidate();
}

Int341 SqList::remove(int pos) {
  if (pos <= 0 || pos >= m_numElements)
    throw out_of_range("Position not valid.");
  --m_numElements;
  //have m_subIt point to position
  traverse(pos);
  Int341 temp = *m_subIt;
  m_mainIt->erase(m_subIt);
  consolidate();
  return temp;
}

int SqList::indexOf(const Int341& data) {
  for (int i = 0; i < m_numElements; i++){
    //have m_subIt point to the right index
    traverse(i);
    if (data.m_data == m_subIt->m_data)
      return i;
  }
  return -1;
}

int SqList::numItems() {return m_numElements;}

void SqList::dump() {	
  int i = 0;	//inner lists counter
  cout << "Number of Items: " << numItems() << endl;
  
  for (m_mainIt = L.begin(); m_mainIt != L.end(); m_mainIt++){
    cout << i << " (" << m_mainIt->size() << ") : ";
    for (m_subIt = m_mainIt->begin(); m_subIt != m_mainIt->end(); m_subIt++)
      cout << m_subIt->m_data << " ";
    i++;
    cout << endl;
  }
}

const SqList& SqList::operator=(const SqList& rhs) {
  m_numElements = rhs.m_numElements;
  //need this bc object being passed in is const
  list< list<Int341> >::const_iterator rhsMainIt = rhs.L.begin();
  m_mainIt = L.begin();

  //need to take away 1 from size to compensate for empty list pushed back in
  //SqList constructor
  for (int i = 0; i < rhs.L.size()-1; i++){
    list<Int341> addOn;
    L.push_back(addOn);
  }

  m_mainIt = L.begin();

  for (int i = 0; i < L.size(); i++){
    *m_mainIt = *rhsMainIt;
    m_mainIt++;
    rhsMainIt++;
  }
  
  return *this;
}
