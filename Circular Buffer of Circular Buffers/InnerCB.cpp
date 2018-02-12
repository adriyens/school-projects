/*
File: InnerCB.cpp
Project: CMSC 341 Project 1, Fall 2017
Author: Adrianne Santinor
Date: 09/12/2017
E-mail: santa1@umbc.edu
Description: This is the .cpp file for the InnerCB.h file
 */

#include "InnerCB.h"
#include <iostream>
#include <stdexcept>
using namespace std;

InnerCB::InnerCB(int n){

  m_buffer = new int[n];  
  m_start = m_end = m_size = 0;
  m_capacity = n;

}

InnerCB::InnerCB(const InnerCB& other){
  m_capacity = other.m_capacity;
  m_size = other.m_size;
  m_start = other.m_start;
  m_end = other.m_end;
  m_buffer = new int[m_capacity];

  //copies contents of array into new one
	if (m_end >= m_start) {
    for (int i = m_start; i <= m_end; i++)
      m_buffer[i] = other.m_buffer[i];
  }
  else {
    for (int i = m_start; i < m_capacity; i++)
      m_buffer[i] = other.m_buffer[i];
    for (int i = 0; i <= m_end; i++)
      m_buffer[i] = other.m_buffer[i];
  }  
}

InnerCB::~InnerCB(){

  delete[] m_buffer;
  m_buffer = NULL;

}

void InnerCB::enqueue(int data){

  if (isEmpty()) {
    //have both m_start and m_end point to one element
    m_buffer[m_start] = data;
  }
  else if (isFull()) {
    throw overflow_error("Inner buffer is full.");
  }
  else {
    m_end = (m_end+1) % m_capacity;
    m_buffer[m_end] = data;
  }
  
  m_size++;
}

int InnerCB::dequeue(){
  
  int retValue = m_buffer[m_start];
  
  if (isEmpty())
    throw underflow_error("Outer buffer is empty.");
  else {
    m_start = (m_start+1) % m_capacity;
    m_size--;
  }
  
  return retValue;
}

bool InnerCB::isFull(){

  if (size() == capacity())
    return true;
  else
    return false;

}

bool InnerCB::isEmpty(){
  
  if (size() == 0)
    return true;
  else
    return false;

}

int InnerCB::capacity(){return m_capacity;}

int InnerCB::size(){return m_size;}

const InnerCB& InnerCB::operator=(const InnerCB& rhs){
  m_capacity = rhs.m_capacity;
  m_size = rhs.m_size;
  m_start = rhs.m_start;
  m_end = rhs.m_end;
  m_buffer = new int[m_capacity];

  //copies contents of array into new one
  if (m_end > m_start) {
    for (int i = m_start; i <= m_end; i++)
      m_buffer[i] = rhs.m_buffer[i];
  }
  else {
    for (int i = m_start; i < m_capacity; i++)
      m_buffer[i] = rhs.m_buffer[i];
    for (int i = 0; i <= m_end; i++)
      m_buffer[i] = rhs.m_buffer[i];
  }
  
  return *this;
}

void InnerCB::dump(){
  
  cout << "InnerCB dump(): m_size = " << m_size << endl;
  
  if (m_end >= m_start){
    for (int i = m_start; i <= m_end; i++)
      cout << "[" << i << "] " << m_buffer[i];
  }
  else {
    for (int i = m_start; i < m_capacity; i++){
      cout << "[" << i << "] " << m_buffer[i];
    }
    for (int i = 0; i <= m_end; i++) {
      cout << "[" << i << "] " << m_buffer[i];
    }
  }
  
  cout << endl;
}
