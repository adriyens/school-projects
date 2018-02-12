#include "SqList.h"
#include <iostream>
using namespace std;

int main(){
  SqList A;
  
  for (int i = 0; i < 35; i++)
    A.addFirst(i);
  for (int i = 50; i < 70; i++)
    A.addLast(i);
  
  cout << "Before removing" << endl;
  A.dump();
  cout << endl;
  
  for (int i = 0; i < A.numItems(); i++)
    cout << "Index " << i << ": " << A[i].m_data << endl;
  
  for (int i = 0; i < 5; i++)
    cout << "Removing from first: " << A.removeFirst().m_data << endl;
  for (int i = 0; i < 3; i++)
    cout << "Removing from last: " << A.removeLast().m_data << endl;
  
  A.add(16, 700);
  cout << "\nRemoving at index 5: " << A.remove(5).m_data << endl;
  
  cout << "\nIndex of element 25? " << A.indexOf(25) << endl;

  cout << "\nBefore calling copy constructor" << endl;
  A.dump();

  SqList B(A);
  cout << "\nAfter calling copy constructor" << endl;
  B.dump();

  
  cout << "\nBouta call the overloaded assignment operator" << endl;
  SqList C;
  C = B;
  C.dump();

  return 0;
}
