/*
File: MedianHeap.h
Project: CMSC 341 FALL 2017 Project 4
Author: Adrianne Santinor
Date: November 1st, 2017
Description: median heaps yeet
*/

#ifndef _MEDIANHEAP_H_
#define _MEDIANHEAP_H_
#include <iostream>
#include <stdexcept>
using namespace std; 

template <class T>
class Heap;

template <class T>
class MedianHeap{
  
 template <class U>
 friend class Heap;
  
 public:
  MedianHeap();
  
  MedianHeap( bool (*lt) (const T&, const T&), bool (*gt) (const T&, const T&), int cap = 100 );
  
  MedianHeap(const MedianHeap<T>& otherH);
  
  ~MedianHeap();
  
  const MedianHeap<T>& operator=(const MedianHeap<T>& rhs);
    
  int size();
  
  int capacity();
  
  T locateInMaxHeap(int pos);
  T locateInMinHeap(int pos);
  
  void balance();
  
  void insert(const T& item);
  
  T getMedian();
  T getMin();
  T getMax();
  
  bool deleteItem(T& givenItem, bool (*equalTo) (const T&, const T&));
  
  void dump();
  
  int maxHeapSize();
  int minHeapSize();
  
 private:
  Heap<T> *m_minHeap;
  Heap<T> *m_maxHeap;
  
  //function pointers for comparison 
  bool (*lessThan)(const T&, const T&);
  bool (*greaterThan)(const T&, const T&);
  
  int m_medSize, m_medCapacity;
  T m_min, m_max;
  //so we don't have to search through heaps for new min/max if current one gets deleted
  T m_prevMin, m_prevMax;
};

template <class U>
class Heap{
  
 template <class T>
 friend class MedianHeap;
 
 public:
  Heap();
  
  Heap(int capacity, bool (*compare) (const U&, const U&));
  
  ~Heap();
  
  Heap(const Heap<U>& other);
  
  const Heap<U>& operator=(const Heap<U>& rhs);
  
  void swapT(U& x, U& y);
  
  U locate(int i);
  
  int heapSize();
  
  int heapCapacity();
  
  int getParent(int i);
  int getLeftKid(int i);
  int getRightKid(int i);
  
  void trickleDown(int i, bool (*compare) (const U&, const U&));
  
  void bubbleUp(int root, int bottom, bool (*compare) (const U&, const U&));
  
  void changeKey(int i, U newVal, bool (*compare) (const U&, const U&));
  
  U getRoot();
  
  void heapInsert(const U& item, bool (*compare) (const U&, const U&));
  
  bool heapRemove(U& givenItem, bool (*equalTo) (const U&, const U&));
  
  void dump();
  
 private:
  U *m_heap;  //pointer to heap array
  int m_end;  //keep track of end of heap
  int m_heapSize, m_heapCapacity;
  
  //function pointers for comparison
  // > for max heap; < for min heap
  bool (*cmp)(const U&, const U&);
};



/********** MedianHeap class implementations **********/

template<class T>
MedianHeap<T>::MedianHeap(bool (*lt) (const T&, const T&), bool (*gt) (const T&, const T&), int cap){
  
  //assign function pointers in min/max heaps to user given ones
  lessThan = lt;
  greaterThan = gt;
  
  m_medCapacity = cap;
  m_medSize = 0;
  
  m_minHeap = new Heap<T>(cap, lt);
  m_maxHeap = new Heap<T>(cap, gt);
  
}

template <class T>
MedianHeap<T>::MedianHeap(const MedianHeap<T>& otherH){
  
  m_medSize = otherH.m_medSize;
  m_medCapacity = otherH.m_medCapacity;
  m_min = otherH.m_min;
  m_max = otherH.m_max;
  m_prevMin = otherH.m_prevMin;
  m_prevMax = otherH.m_prevMax;
  greaterThan = otherH.greaterThan;
  lessThan = otherH.lessThan;
  m_minHeap = new Heap<T>(m_medCapacity, lessThan);
  m_maxHeap = new Heap<T>(m_medCapacity, greaterThan);

  /*
  for (int i = 1; i < otherH.m_minHeap->heapSize(); i++)
    m_minHeap->heapInsert(otherH.m_minHeap->locate(i), lessThan);
  for (int i = 1; i < otherH.m_maxHeap->heapSize(); i++)
    m_maxHeap->heapInsert(otherH.m_maxHeap->locate(i), greaterThan);
  */

  //using Heap's copy constructor
  //m_minHeap = new Heap<T>(otherH.m_minHeap);
  //m_maxHeap = new Heap<T>(otherH.m_maxHeap);
  
}

template <class T>
MedianHeap<T>::~MedianHeap(){
  
  delete m_minHeap;
  m_minHeap = NULL;
  delete m_maxHeap;
  m_maxHeap = NULL;
  
}

template <class T>
const MedianHeap<T>& MedianHeap<T>::operator=(const MedianHeap<T>& rhs){
 
  m_medSize = rhs.m_medSize;
  m_medCapacity = rhs.m_medCapacity;
  m_min = rhs.m_min;
  m_max = rhs.m_max;
  
  //using Heap's overloaded assignment operator
  m_minHeap = rhs.m_minHeap;
  m_maxHeap = rhs.m_maxHeap;
  
  return *this;
  
}

template <class T>
int MedianHeap<T>::size(){return m_medSize;}

template <class T>
int MedianHeap<T>::capacity(){return m_medCapacity;}

template <class T>
T MedianHeap<T>::locateInMaxHeap(int pos){
  
  if ((pos < 1) || (pos > m_maxHeap->heapSize()))
    throw out_of_range("Not a valid index in max heap.");
  
  return m_maxHeap->locate(pos);
  
}

template <class T>
T MedianHeap<T>::locateInMinHeap(int pos){
  
  if ((pos < 1) || (pos > m_minHeap->heapSize()))
    throw out_of_range("Not a valid index in min heap.");
  
  return m_minHeap->locate(pos);
  
}

template <class T>
void MedianHeap<T>::balance(){
  
  //making sure min and max sizes aren't the same
  if (m_minHeap->heapSize() == m_maxHeap->heapSize())
    return;
  //if min heap has more items, transfer root to max heap
  else if (m_minHeap->heapSize() > m_maxHeap->heapSize()){
    T add = m_minHeap->getRoot();
    //cout << "\n\tInserting into max heap." << endl;
    m_maxHeap->heapInsert(add, greaterThan);
  }
  //or vice versa
  else{
    T add = m_maxHeap->getRoot();
    //cout << "\n\tInserting into min heap." << endl;
    m_minHeap->heapInsert(add, lessThan);
  }
  
}

template <class T>
void MedianHeap<T>::insert(const T& item){
  
  if (m_medSize == m_medCapacity)
    throw out_of_range("Can't insert anything because Median Heap is full");
  
  //changing min/max values through comparisons
  if (greaterThan(item, m_max)){
    m_prevMax = m_max;
    m_max = item;
  }
  if (lessThan(item, m_min)){
    m_prevMin = m_min;
    m_min = item;
  }
  
  //first item is inserted into max heap 
  if (m_maxHeap->heapSize() == 0){
    //cout << "\n\tInserting first item into max heap." << endl;
    m_min = item; //used for comparison
    m_max = item; //used for comparison
    m_maxHeap->heapInsert(item, greaterThan);
  }
  
  else if (m_minHeap->heapSize() == 0){
    //insert into max heap if item is less than max root
    if (lessThan(item, m_maxHeap->locate(1))){
      //cout << "\n\tInserting into max heap." << endl;
      m_maxHeap->heapInsert(item, greaterThan);
    }
    //otherwise, put it in min heap
    else{
      //cout << "\n\tInserting first item into min heap." << endl;
      m_minHeap->heapInsert(item, lessThan);
    }
  }
  
  else{
    if (lessThan(item, m_maxHeap->locate(1))){
      //cout << "\n\tInserting into max heap." << endl;
      m_maxHeap->heapInsert(item, greaterThan);
    }
    else if (greaterThan(item, m_minHeap->locate(1))){
      //cout << "\n\tInserting into min heap." << endl;
      m_minHeap->heapInsert(item, lessThan);
    }
    //always put it in max heap if no other conditionals are met
    else{
      //cout << "\n\tInserting into max heap." << endl;
      m_maxHeap->heapInsert(item, greaterThan);
    }
  
  }
  
  //if min/max heap sizes differ by at least 2, transfer roots accordingly
  if ((m_minHeap->heapSize() > m_maxHeap->heapSize() + 1) || (m_maxHeap->heapSize() > m_minHeap->heapSize() + 1))
    balance();

  m_medSize++;
  
}

template <class T>
T MedianHeap<T>::getMedian(){
  
  if (m_medSize < 1)
    throw out_of_range("Can't get median because Median Heap is empty.");
  
  //if max heap size is greater than min heap
  if (maxHeapSize() > minHeapSize())
    return m_maxHeap->locate(1);  //get max root
  //if max heap size is greater than min heap size
  else if (minHeapSize() > maxHeapSize())
    return m_minHeap->locate(1);  //get min root
  //pick either of the two; i'm choosing max
  else
    return m_maxHeap->locate(1);
  
}

template <class T>
T MedianHeap<T>::getMin(){

  if (m_medSize < 1)
    throw out_of_range("Can't get minimum because Median Heap is empty.");
  
  return m_min;

}

template <class T>
T MedianHeap<T>::getMax(){
  
  if (m_medSize < 1)
    throw out_of_range("Can't get maximum because Median Heap is empty.");  
  
  return m_max;

}

template <class T>
bool MedianHeap<T>::deleteItem(T& givenItem, bool (*equalTo) (const T&, const T&)){
  
  //keep track of whether givenItem is found in min/max heap
  bool found = false;
  
  if (m_medSize < 1)
    throw out_of_range("Can't delete anything because Median Heap is empty.");
  
  //try to find it in max heap
  found = m_maxHeap->heapRemove(givenItem, equalTo);
  
  //if i didn't find it in the max heap, look through the min heap
  if (!found)
    found = m_minHeap->heapRemove(givenItem, equalTo);
  
  //if item deleted was min/max, we replace it with the previous one
  if (equalTo(givenItem, m_min)){
    m_min = m_prevMin;
  }
  if (equalTo(givenItem, m_max)){
    m_max = m_prevMax;
  }
  
  if ((m_minHeap->heapSize() > m_maxHeap->heapSize() + 1) || (m_maxHeap->heapSize() > m_minHeap->heapSize() + 1))
    balance();
  
  m_medSize--;
  
  return found;
  
}

template <class T>
void MedianHeap<T>::dump(){
  
  cout << "\nMax Heap:" << endl;
  cout << "Size: " << maxHeapSize() << " // Capacity: " << m_maxHeap->heapCapacity() << endl;
  m_maxHeap->dump();
  
  cout << "\nMin Heap:" << endl;
  cout << "Size: " << minHeapSize() << " // Capacity: " << m_minHeap->heapCapacity() << endl;
  m_minHeap->dump();
  
  cout << "\nMin: " << getMin() << endl;
  cout << "Median: " << getMedian() << endl;
  cout << "Max: " << getMax() << endl;

}

template <class T>
int MedianHeap<T>::maxHeapSize(){return m_maxHeap->heapSize();}

template <class T>
int MedianHeap<T>::minHeapSize(){return m_minHeap->heapSize();}



/********** Heap class implementations **********/

template <class T>
Heap<T>::Heap(int capacity, bool (*compare) (const T&, const T&)){
  
  m_heapCapacity = (capacity / 2) + 2;
  m_heap = new T[m_heapCapacity];
  m_heapSize = 0;
  m_end = 1;
  cmp = compare;
  
}

template <class T>
Heap<T>::~Heap(){delete[] m_heap;}

template <class T>
Heap<T>::Heap(const Heap<T>& other){
  
  m_end = other.m_end;
  m_heapSize = other.m_heapSize;
  m_heapCapacity = other.m_heapCapacity;
  
  for (int i = 1; i < m_heapSize; i++)
    m_heap[i] = other.m_heap[i];
  
}

template <class T>
const Heap<T>& Heap<T>::operator=(const Heap<T>& rhs){
  
  m_end = rhs.m_end;
  m_heapSize = rhs.m_heapSize;
  m_heapCapacity = rhs.m_heapCapacity;
  
  for (int i = 1; i < m_heapSize; i++)
    m_heap[i] = rhs.m_heap[i];
  
  return *this;
  
}

template <class T>
void Heap<T>::swapT(T& x, T& y){
  T temp = x;
  x = y;
  y = temp;
}

template <class T>
T Heap<T>::locate(int i){return m_heap[i];}

template <class T>
int Heap<T>::getParent(int i){return (i/ 2);}

template <class T>
int Heap<T>::getLeftKid(int i){return (i * 2);}

template <class T>
int Heap<T>::getRightKid(int i){return ((i * 2) + 1);}

template <class T>
int Heap<T>::heapSize(){return m_heapSize;}

template <class T>
int Heap<T>::heapCapacity(){return m_heapCapacity;}

template <class T>
void Heap<T>::trickleDown(int i, bool (*compare) (const T&, const T&)){
  
  int top;  //keep track of what the new parent is gonna be
  
  int left = getLeftKid(i);
  int right = getRightKid(i);
  int bottom = m_end - 1;
  
  //make sure last element in heap is at an index after the left child
  if (left <= bottom){
    if (left == bottom)
      top = left;
    else{
      //if right child is greater than (for max) or less than (for min) left child
      if (compare(m_heap[right], m_heap[left]))
        top = right;
      else
        top = left;
    }
    //if new parent is greater than (for max) or less than (for min) item at index i, swap
    if (compare(m_heap[top], m_heap[i])){
      swapT(m_heap[top], m_heap[i]);
      //recursively trickles down until we get to end of heap
      trickleDown(top, compare);  
    }
  }

}

template <class T>
void Heap<T>::bubbleUp(int root, int bottom, bool (*compare) (const T&, const T&)){
  
  //make sure end of heap's index is greater than root
  if (bottom > root){
    //swap last element if it's greater than (for max) or less than (for min) its parent
    if (compare(m_heap[bottom], m_heap[getParent(bottom)])){
      swapT(m_heap[bottom], m_heap[getParent(bottom)]);
      //recursively bubbles up until we get to root of heap
      bubbleUp(root, getParent(bottom), compare);
    }
  }
  
}

template <class T>
T Heap<T>::getRoot(){
  
  T root = m_heap[1]; //extract root to return later
  m_heap[1] = m_heap[m_end-1]; //make last item the new root
  
  //decrement size & end index to "remove" root
  m_heapSize--;
  m_end--;
  
  trickleDown(1, cmp);  //trickle down so heap is legal
  
  return root;
  
}

template <class T>
void Heap<T>::heapInsert(const T& item, bool (*compare) (const T&, const T&)){
  
  //cout << "Inserting " << item << endl;
  
  if (m_heapSize == m_heapCapacity)
    throw overflow_error("Heap is full.");
  
  //insert item into end of array
  m_heap[m_end] = item;
  m_heapSize++;
  m_end++;
  
  //sort heap so it's legal
  bubbleUp(1, (m_end - 1), compare);

}

template <class T>
bool Heap<T>::heapRemove(T& givenItem, bool (*equalTo) (const T&, const T&)){
  
  //to keep track of which index givenItem is found at
  int index = -1; 
  
  //search heap for given item
  for (int i = 1; i < m_end; i++){
    //found the item in heap
    if (equalTo(m_heap[i], givenItem)){
      givenItem = m_heap[i];  //so we can access its elements later
      index = i;
      break;
    }
  }
  
  if (index > 0){
    //replace item being removed with last element
    m_heap[index] = m_heap[m_end - 1];
    //sort heap so it's legal
    trickleDown(index, cmp);
    m_end--;
    m_heapSize--;
    return true;
  }
  else 
    return false;
  
}

template <class T>
void Heap<T>::dump(){
  
  if (m_heapSize < 1)
    cout << "This heap empty. YEET!" << endl;
  
  for (int i = 1; i <= heapSize(); i++)
    cout << "Index " << i << ": " << m_heap[i] << endl;

}

#endif