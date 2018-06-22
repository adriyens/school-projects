/*
File: CBCB.cpp
Project: CMSC 341 Project 1, Fall 2017
Author: Adrianne Santinor
Date: 09/12/2017
E-mail: santa1@umbc.edu
Description: This is the .cpp file for the CBofCB.h file
 */

#include "CBofCB.h"
#include <iostream>
#include <stdexcept>
using namespace std;

CBofCB::CBofCB() {
	
  m_buffers[0] = new InnerCB();
 	m_oldest = m_newest = 0;
	m_obSize = 1;	//always have one inner buffer in the outer buffer
	
}

//use InnerCB copy constructor hmm...
CBofCB::CBofCB(const CBofCB& other) {
	
	m_obSize = other.m_obSize;
	m_oldest = other.m_oldest;
	m_newest = other.m_newest;
	
	if (m_newest >= m_oldest) {
		for (int i = m_oldest; i <= m_newest; i++)
			m_buffers[i] = new InnerCB(*other.m_buffers[i]);
	}
	else {
		for (int i = m_oldest; i < m_obCapacity; i++)
			m_buffers[i] = new InnerCB(*other.m_buffers[i]);
		for (int i = 0; i <= m_newest; i++)
			m_buffers[i] = new InnerCB(*other.m_buffers[i]);
	}
	
}

CBofCB::~CBofCB() {
	
	if (m_newest >= m_oldest) {
		for (int i = m_oldest; i <= m_newest; i++)
			delete m_buffers[i];
	}
	else {
		for (int i = m_oldest; i < m_obCapacity; i++)
			delete m_buffers[i];
		for (int i = 0; i <= m_newest; i++)
			delete m_buffers[i];
	}
	
}

void CBofCB::enqueue(int data) {
	
  if (isEmpty())
		m_buffers[m_oldest]->enqueue(data);
  //if buffer at that index is full, we create a new one with twice the capacity
  else if (m_buffers[m_newest]->isFull()) {
		m_buffers[(m_newest + 1) % m_obCapacity] = new InnerCB(m_buffers[m_newest]->capacity() * 2); //creates new one with twice the capacity
		m_newest = (m_newest + 1) % m_obCapacity;
		m_buffers[m_newest]->enqueue(data);
		m_obSize++;	//only time we increment outer buffer is in this instance since we're adding another array
  }
  else if (isFull())
		throw overflow_error("Outer buffer is full.");
  else 
		m_buffers[m_newest]->enqueue(data);

}

int CBofCB::dequeue() {
  
  int retValue = m_buffers[m_oldest]->dequeue();
  
	if (isEmpty())
		throw underflow_error("Outer buffer is empty.");
	//checks if inner buffer m_oldest is pointing to is empty
  else if (m_buffers[m_oldest]->isEmpty()) {
		delete m_buffers[m_oldest];
		m_buffers[m_oldest] = NULL;
		m_oldest = (m_oldest+1)%m_obCapacity;
		--m_obSize;	//only time we decrement size of outer buffer
	}
	
  return retValue;
}

bool CBofCB::isFull() {
  if (m_buffers[m_newest]->isFull() && m_obSize == m_obCapacity)
    return true;
  else 
    return false;
}

bool CBofCB::isEmpty() {
  if ( (m_oldest == m_newest) && (m_buffers[m_oldest]->isEmpty() ) )
    return true;
  else
    return false;
}

int CBofCB::size() {
  int CBsize = 0;
  
	if (m_newest >= m_oldest) {
  	for (int i = m_oldest; i <= m_newest; i++)
    	CBsize += m_buffers[i]->size();
	}
	else {
		for (int i = m_oldest; i < m_obCapacity; i++)
			CBsize += m_buffers[i]->size();
		for (int i = 0; i <= m_newest; i++)
			CBsize += m_buffers[i]->size();
	}
  
  return CBsize;
}

const CBofCB& CBofCB::operator=(const CBofCB& rhs) {
	
	m_obSize = rhs.m_obSize;
  m_oldest = rhs.m_oldest;
  m_newest = rhs.m_newest;
  
	if (m_newest >= m_oldest) {
		for (int i = m_oldest; i <= m_newest; i++)
			m_buffers[i] = new InnerCB(*rhs.m_buffers[i]);
	}
	else {
		for (int i = m_oldest; i < m_obCapacity; i++)
			m_buffers[i] = new InnerCB(*rhs.m_buffers[i]);
		for (int i = 0; i <= m_newest; i++)
			m_buffers[i] = new InnerCB(*rhs.m_buffers[i]);
	}
	
  return *this;
}

void CBofCB::dump() {
	
	cout << "OuterCB dump() || m_obSize = " << m_obSize << endl;
	
  if (m_newest >= m_oldest){
		for (int i = m_oldest; i <= m_newest; i++){
			cout << "[" << i << "] ";
			m_buffers[i]->dump();
		}
  }
  else {
		for (int i = m_oldest; i < m_obCapacity; i++){
			cout << "[" << i << "] ";
			m_buffers[i]->dump();
		}
		for (int i = 0; i <= m_newest; i++) {
			cout << "[" << i << "] ";
			m_buffers[i]->dump();
		}
  }
}
