#include <iostream>
using namespace std;
#include "binstreeEC.h"

// This client tests all kinds of cases.
int main()
{
  //***** test 1 **********************************************
  cout << "===  Starting a new tree with many nodes ===="<< endl;
  BST MyTree;  // my first binary search tree

  for(int i = 1; i <=9; i=i+2) // inserting 1,3,5,7,9 into the tree
  {
    MyTree.InsertVertex(i);
  }

  for(int i = 10; i >=2 ; i=i-2)  // inserting 10,8,6,4,2 into the tree
  {
    MyTree.InsertVertex(i);
  }

  MyTree.Display();  // should show in the sorted order

  cout << "\nSearching .... " << endl;

  cout << "--- Start searching for " << 5 << " ---" << endl;
  if (MyTree.Search(5) == true) 
    cout << "found 5" << endl; 
  else 
    cout << "5 not found" << endl;

  cout << "--- Start searching for " << 11 << " ---" << endl;
  if (MyTree.Search(11) == true) 
    cout << "found 11" << endl; 
  else 
    cout << "11 not found" << endl;

  cout << "--- Start searching for " << 0 << " ---" << endl;
  if ( MyTree.Search(0) == true) 
    cout << "found 0" << endl; 
  else 
    cout << "0 not found" << endl;

  char ans;
  cout << "Continue? Press any key: ";
  cin >> ans;

  //***** test 2 **********************************************
  cout << "\n====  Starting a new tree with 3 nodes ===="<< endl;
  BST Nums1;  // Nums1 is the second binary search tree

   Nums1.InsertVertex(1);
   Nums1.InsertVertex(2);
   Nums1.InsertVertex(3);
   Nums1.DeleteVertex(7); // cannot delete
   Nums1.DeleteVertex(1); // delete the root
   Nums1.Display();

  cout << "Continue? Press any key: ";
  cin >> ans;

  //******* test 3 ********************************************
  cout << "\n====  Starting another tree with 3 nodes ===="<< endl;
  BST Nums2;  // Nums2 is another binary search tree

  Nums2.InsertVertex(10);
  Nums2.InsertVertex(9);
  Nums2.InsertVertex(8);
  Nums2.DeleteVertex(7);   // cannot delete
  Nums2.DeleteVertex(10);  // delete the root
  Nums2.Display();
  cout << "Continue? Press any key: ";
  cin >> ans;

 //****** test 4 **************************************
  cout << "\n====  Starting a new tree with 7 nodes ===="<< endl;
  BST Nums;  // Nums is the last binary search tree

  // creates a shallowest 7 node tree (draw this)
  Nums.InsertVertex(3);  // root
  Nums.InsertVertex(1);  // level 1 L
  Nums.InsertVertex(2);  // level 2 R
  Nums.InsertVertex(0);  // level 2 L
  Nums.InsertVertex(5);  // level 1 R
  Nums.InsertVertex(6);  // level 2 R
  Nums.InsertVertex(4);  // level 2 L
  Nums.InsertVertex(4);  // should be an error

  //and show the nodes in sorted order
  Nums.Display();
  cout << "Continue? Press any key: ";
  cin >> ans;
  cout << "then delete 5 nodes .." << endl;
  
  //  - level 2 right most leaf
  Nums.DeleteVertex(6);
  Nums.Display();
  //  - level 2 left most leaf
  Nums.DeleteVertex(0);
  Nums.Display();
  // - level 1 right most node with one left child
  Nums.DeleteVertex(5);
  // - level 1 left most node with one right child
  Nums.DeleteVertex(1);
  // - level 0 root with two children
  Nums.DeleteVertex(3);
  // - deleting a non-existing one
  Nums.DeleteVertex(7);
  //and then show the remaining nodes in sorted order
  Nums.Display();
  return 0;
}// end of program
