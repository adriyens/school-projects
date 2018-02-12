/*
File: MedianHeap.cpp
Project: CMSC 341 FALL 2017 Project 4
Author: Adrianne Santinor
Date: November 1st, 2017
Description: median heaps yeet
*/

#include "MedianHeap.h"
#ifndef _MEDIANHEAP_CPP_
#define _MEDIANHEAP_CPP_

/********** MedianHeap class implementations **********/

template<class T>
MedianHeap<T>::MedianHeap(bool (*lt) (const T&, const T&), bool (*gt) (const T&, const T&), int cap){
  
  //assign function pointers in min/max heaps to user given ones
  m_minHeap.heap_lt = lt;
  m_maxHeap.heap_lt = lt;
  m_minHeap.heap_gt = gt;
  m_maxHeap.heap_gt = gt;
  
  m_medCapacity = cap;
  m_medSize = 0;
  
}

template <class T>
MedianHeap<T>::MedianHeap(const MedianHeap<T>& otherH){
  //copy constructor
}

template <class T>
MedianHeap<T>::~MedianHeap(){
  //destructor
}

template <class T>
const MedianHeap<T>& MedianHeap<T>::operator=(const MedianHeap<T>& rhs){
  //overloaded assignment operator
}

template <class T>
int MedianHeap<T>::size(){return m_medSize;}

template <class T>
int MedianHeap<T>::capacity(){return m_medCapacity;}

template <class T>
void MedianHeap<T>::insert(const T& item){
  
}

template <class T>
T MedianHeap<T>::getMedian(){
  
}

template <class T>
T MedianHeap<T>::getMin(){
  
}

template <class T>
T MedianHeap<T>::getMax(){
  
}

template <class T>
bool MedianHeap<T>::deleteItem(T& givenItem, bool (*equalTo) (const T&, const T&)){
 
}

template <class T>
void MedianHeap<T>::dump(){
  
}

template <class T>
int MedianHeap<T>::maxHeapSize(){return m_maxHeap.getHeapSize();}

template <class T>
int MedianHeap<T>::minHeapSize(){return m_minHeap.getHeapSize();}

template <class T>
T MedianHeap<T>::locateInMaxHeap(int pos){
  
}

template <class T>
T MedianHeap<T>::locateInMinHeap(int pos){
  
}
  



/********** Heap class implementations **********/

template <class T>
Heap<T>::Heap(){
  
  //make size of array greater than it needs to be just in case
  m_heapCapacity = (MedianHeap<T>::m_medCapacity / 2) + 2;
  m_heap = new T[m_heapCapacity];
  m_heapSize = m_end = 0;
  
}

template <class T>
Heap<T>::~Heap(){delete[] m_heap;}

template <class T>
void Heap<T>::swap(const T& x, const T& y){
  
}

template <class T>
int Heap<T>::getHeapSize(){return m_heapSize;}

template <class T>
void Heap<T>::heapInsert(const T& item){
  
}

template <class T>
void Heap<T>::heapRemove(){
  
}

template <class T>
void Heap<T>::locate(int i){
  
}

template <class T>
T Heap<T>::getParent(int i){return m_heap[i / 2];}

template <class T>
T Heap<T>::getLeftKid(int i){return m_heap[i * 2];}

template <class T>
T Heap<T>::getRightKid(int i){return m_heap[(i * 2) + 1];}

#endif