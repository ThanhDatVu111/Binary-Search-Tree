//================================================================
//Name: Thanh Dat Vu
//Complier:  g++
//File type: implementation file binstree.cpp
//================================================================

#include<iostream>
#include "binstreeEC.h"
using namespace std;

// constructor initializes Root
BST::BST()
{
  Root = NULL; //This is an empty tree
}

// destructor must completely destroy the tree
BST::~BST()
{
  dtraverse(Root); //traverse to delete all vertices in post order
  Root = NULL;    
}

// PURPOSE: Does Post Order traversal of the tree and deletes each vertex
// PARAM:  V is a pointer to the vertex to be deleted
void BST::dtraverse(Vertex *V)  // recursive post order traversal
{   
  if (V != NULL) 
  {
    dtraverse(V->Left);          // destroy left sub tree of V
    dtraverse(V->Right);        //  destroy right sub tree of V
    delete V;                  //  delete V
  }
} //return to where the function been called

// PURPOSE: Show vertices in IN order traversal from the Root
void BST::Display()
{
  cout << "\n--- Elements in the IN order: ---" << endl;
  cout << "Root is: " << Root->Elem << endl;
  INorderTraversal(Root); // start in-order traversal from the root
  cout << "---------------------------------" << endl;
}

// PURPOSE: Does IN order traversal from V recursively
// PARAM: V is te pointer to the vertex to visit right now
void BST::INorderTraversal(Vertex *V)
{
  if (V != NULL)
  {
    INorderTraversal(V->Left);//  traverse left sub-tree of V recursively
    cout << "Vertex: " << V->Elem << ", Height: " << V->Height << ", Balance: " << V->Balance << endl;  // display V's element, height and balance and do endl; 
    INorderTraversal(V->Right);// traverse right sub-tree of V recursively
  }
}

// PURPOSE: Searches for an element in PRE-order traversal
// This is the same as Depth First Traversal
bool BST::Search(el_t K)
{
  PREorderSearch(Root, K);  // start pre-order traversal from the root
}

// PURPOSE: Does PRE order search from V recursively
// PARAM: V is the pointer to the vertex to be visited now K is what we are looking for
bool BST::PREorderSearch(Vertex *V, el_t K)
{
  if (V != NULL)
  {
    if (K == V->Elem) 
      return true; // found the element in V
    else if (K < V->Elem) 
      PREorderSearch(V->Left, K); // traverse left sub-tree of V recursively
    else //K > V->Elem
      PREorderSearch(V->Right, K); // traverse right sub-tree of V recursively
  }
  else 
    return false;
}
// ------ The following are for adding and deleting vertices -----


// PURPOSE: Adds a vertex to the binary search tree for a new element 
// PARAM: the new element E
// ALGORITHM: We will do this iteratively (not recursively)
// to demonstrate the algorithm that is in the notes
//    - smaller than the current -> go to the left
//    - bigger than the current  -> go to the right
//    - cannot go any further    -> add it there
void BST::InsertVertex(el_t E)
{
  // Set up a new vertex first
  Vertex *New_vertex;         // N will point to the new vertex to be inserted
  New_vertex = new Vertex;    // a new vertex is created
  New_vertex->Left  = NULL;   // make sure it does not
  New_vertex->Right = NULL;   // point to anything
  New_vertex->Elem  = E;      // put element E in it
  New_vertex->Height = 0;
  New_vertex->Balance = 0;
  New_vertex->Up = NULL;      // no parent for now

  cout << "\nTrying to insert " << E << endl;
  if (Root == NULL)  // Special case: we have a brand new empty tree
  {
    Root = New_vertex;      // the new vertex is added as the root
    cout << "...adding " << E << " as the root" << endl; 
  } // end of the special case
  else // the tree is not empty
  {
    Vertex *V;       // V will point to the current vertex
    Vertex *Parent;  // Parent will always point to V's parent

    V = Root;        // start with the root as V
    Parent = NULL;   // above V so it does not point to anything  

	//go down the tree until you cannot go any further     
    while (V != NULL)
    {
	    if (New_vertex->Elem == V->Elem) // the element already exists
      {	 
        cout << "...error: the element already exists" << endl;
		    return;  
      }
	    else if (New_vertex->Elem < V->Elem)  // what I have is smaller than V
		  {  
        cout << "...going to the left " << endl; 
        Parent = V;//  change Parent to be V to go down 
		    V = V->Left; // change V to be V's Left 
		  }
	      else // what I have is bigger than V
		  {  
        cout << "...going to the right " << endl; 
        Parent = V; // change Parent to be V to go down
		    V = V->Right; // change V to be V's Right 
		  }
	  }//end of while   
  //reached NULL -- Must add N as the Parent's child
    if (New_vertex->Elem < Parent->Elem)  
    {  
	    Parent->Left = New_vertex;// Parent's Left should point to the same place as N 
	    cout << "...adding " << E << " as the left child of " << Parent->Elem << endl;
      New_vertex->Up = Parent; // N must point UP to the Parent 
      cout << "..." << New_vertex->Elem  << " now points UP to " << New_vertex->Up->Elem << endl;   
      //EC call here to adjust height and BF	
      climbup(New_vertex);
    }
    else 
    {
	    Parent->Right = New_vertex; // Parent's Right should point to the same place as N 
      cout << "...adding " << E << " as the right child of " << Parent->Elem << endl;
      New_vertex->Up = Parent;// N must point UP to the Parent 
      cout << "..." << New_vertex->Elem << " now points UP to " << New_vertex->Up->Elem << endl;   
	    climbup(New_vertex);
  	}
  }// end of normal case
}// end of InsertVertex

  
// PURPOSE: Deletes a vertex that has E as its element.
// PARAM: element E to be removed
// ALGORITHM: First we must find the vertex then call Remove 
void BST::DeleteVertex(el_t E)
{
  cout << "\nTrying to delete " << E << endl;
  Vertex *V;       // the current vertex
  Vertex *Parent;  // Parent will always point to V's parent

  // case 1: Lonely Root (1 vertex)  --------------------
  if ((E == Root->Elem) && (Root->Left == NULL) && (Root->Right == NULL))
  { 
    cout << "...deleting the lonely root" << endl;
    delete Root; 
    Root = NULL;
    return; 
  }  // only the Root was there and deleted it
  
  // case 2:  One Substree Root ----------------
  else if (E == Root->Elem && Root->Left == NULL || E == Root->Elem && Root->Right == NULL) //if what you want to delete is the root
  { 
    if(Root->Right == NULL) // and it has only the left subtree
    {  
      // change the root to the left child and return
      cout << "...deleting the root and making left child the root" << endl; 
      Root = Root->Left;
      // making sure the old root has been deleted and the new root's UP is NULL 
      delete Root->Up;
      Root->Up = NULL;
      return;
    }
    else// and it has only the right subtree
    { 
      // change the root to the right child and return
      cout << "...deleting the root and making right child the root" << endl; 
      Root = Root->Right;
      // making sure the old root has been deleted and the new root's UP is NULL 
      delete Root->Up;
      Root->Up = NULL;
      return;
    }
  }// end of deleting the root with one subtree
  
  // ---- Otherwise deleting something else  --------------
  else
  {
    V = Root;  // start with the root to look for E
    Parent = NULL;  // above the V so does not point to anything yet

    // going down the tree looking for E
    while (V != NULL)
    { 
      if (E == V->Elem) // found it
      {  
        remove (V,Parent); // call remove here to remove V
        return; 
      }
      else if (E < V->Elem)
      {  
        cout << "...going to the left " << endl;
        Parent = V;
        V = V->Left;// update Parent and V here to go down
      }
      else //(E > V->Elem)
      {  
        cout << "...going to the right " << endl;
        Parent = V;
        V = V->Right; // update Parent and V here to go down
      }  
    }// end of while
    // reached NULL  -- did not find it
    cout << "Did not find the key in the tree." << endl;
  }
}// end of DeleteVertex


// PURPOSE: Removes vertex pointed to by V
// PARAM: V and its parent pointer P
// Case 1: it is a leaf, delete it
// Case 2: it has just one child, bypass it
// Case 3: it has two children, replace it with the max of the left subtree
void BST::remove(Vertex *V, Vertex *P)
{
  cout << "...removing " << V->Elem << endl;
  if(V->Left == NULL && V->Right == NULL) // if V is a leaf (case 1)
  {
	  cout << "...removing a leaf" << endl;
	  if(V == P->Left) // if V is a left child of P
	  {
      delete V;
      P->Left = NULL; // delete V and also make Parent's left NULL 
      //EC call here from P to adjust height and BF  
      climbup(P);
	  }
	  else // V is a right child of the Parent
	  { 
      delete V;
      P->Right = NULL; // delete V and also make Parent's right NULL 
      //EC call from P to adjust height and BF
      climbup(P);
	  }
  }//end of leaf case
  else if (V->Left != NULL && V->Right == NULL) // if V has just the left child so bypass V (case 2)
  {    
    Vertex* C = V->Left; // C is the left child
	  cout << "...removing a vertex with just a left child" << endl;
    // You need if then else to determine Parent's left or right should point to C; 
    if (C->Elem < P->Elem)
      P->Left = C;
    else
      P->Right = C;
	  // Make C point UP to the parent;   
    C->Up = P;
    cout << C->Elem << " points up to " << C->Up->Elem << endl;
    delete V;// Be sure to delete V
    //EC call from P to adjust height and BF
    climbup(P);
	}// end of V with left child       
  else if (V->Left == NULL && V->Right != NULL) // if V has just the right child so bypass V (case 2)
  {    
    Vertex* C = V->Right;  // C is the right child
	  cout << "...removing a vertex with just a right child" << endl;
	  // You need if then else to determine Parent's left or right should point to C;
    if (C->Elem < P->Elem)
      P->Left = C;
    else
      P->Right = C;
	  // Make C point UP to the parent;   
    C->Up = P;
    cout << C->Elem << " points up to " << C->Up->Elem << endl;
    delete V;// Be sure to delete V
    // EC call from P to adjust height and BF 
    climbup(P);
  }//end of V with right child
  else // V has two children (case 3)
	{ 
    cout << "...removing an internal vertex with children" << endl;
	  cout << "...find the MAX of its left sub-tree" << endl;
	  el_t Melem;
	  // find MAX element in the left sub-tree of V
    Melem = findMax(V); 
    cout << "...replacing " << V->Elem << " with " << Melem << endl;
    V->Elem = Melem; // Replace V's element with Melem here
  }//end of V with two children    
}// end of remove

// PURPOSE: Finds the Maximum element in the left sub-tree of and also deletes that vertex
el_t BST::findMax(Vertex *V)
{
  Vertex *Parent = V;
  V = V->Left; // start with the left child of V
  while (V->Right != NULL) // while the right child of V is still available
  {
    Parent = V;
    V = V->Right; // update Parent and V to go to the right
  }
  // reached NULL Right -- V now has the MAX element
  el_t X = V->Elem;
  cout << "...Max is " << X << " and we need to remove it" << endl;
  remove(V, Parent);    // remove the MAX vertex 
  return X;             // return the MAX element
}// end of FindMax

void BST::climbup(Vertex* V)
{
  cout << ">>>Start climbing up to adjust heights<<<" << endl;
  int leftHeight;
  int rightHeight;
  while (V != NULL)
  {
    if (V->Left != NULL) 
      leftHeight = V->Left->Height;
    else //leaf
      leftHeight = -1;

    if (V->Right != NULL) 
      rightHeight = V->Right->Height;
    else //leaf
      rightHeight = -1;

    //compute V->Height based on the left/right children's heights
    V->Height = max(leftHeight, rightHeight) + 1;
    //compute V->Balance based on the left/right children's heights 
    V->Balance = (leftHeight - rightHeight) * -1;
    cout << "...Vertex " << V->Elem << "'s height: " << V->Height << " with balance: " << V->Balance << endl;
    if(V->Balance == 2 || V->Balance == -2)
    {
      fixIt(V);
    }
    V = V->Up;  
  }
}  

//Note that rotated.out shows what happens if you rotate the tree
//everytime Balance -2 or 2 is found, and the tree is displayed
//as soon as the rotation is completed.
void BST::calculateHeightAndBalance(Vertex* V) 
{
  // Height
  if(V->Left == NULL && V->Right == NULL) // Leaf node
    V->Height = 0; 
  else if(V->Left == NULL) // Only right child
    V->Height = V->Right->Height + 1;
  else if(V->Right == NULL) // Only left child
    V->Height = V->Left->Height + 1;
  else // Both children
    V->Height = max(V->Left->Height, V->Right->Height) + 1;

  // Balance
  if(V->Left == NULL)
    V->Balance = 0;
  else if(V->Right == NULL) 
    V->Balance = V->Left->Height;
  else 
    V->Balance = V->Left->Height - V->Right->Height;
}

Vertex* BST::rotateLeft(Vertex*Red)
{
  Vertex* Pivot;
  Pivot = Red->Right;	// Right child of the red node is the Pivot
  cout << "---Rotate left with pivot: " << Pivot->Elem << endl;
  // Rotate pointers
  Red->Right = Pivot->Left;  
  Pivot->Left = Red;
  //update link
  if(Red->Right != NULL)
    Red->Right->Up = Red;
  Pivot->Up = Red->Up;
  Red->Up = Pivot;
  if(Pivot->Up != NULL)
  {
    if(Pivot->Up->Right == Red) //if the parent of red is still point to red
      Pivot->Up->Right = Pivot;
  }
  //update height and balance;
  calculateHeightAndBalance(Pivot);
  calculateHeightAndBalance(Red);
  return Pivot;
}

Vertex* BST::rotateRight(Vertex*Red)
{
  Vertex* Pivot;
  Pivot = Red->Left;	// Left child of the red node is the Pivot
  cout << "---Rotate right with pivot: " << Pivot->Elem << endl;
  // Rotate pointers
  Red->Left = Pivot->Right;  
  Pivot->Right = Red;
  //update link
  if(Red->Left != NULL)
    Red->Left->Up = Red;
  Pivot->Up = Red->Up;
  Red->Up = Pivot;
  if(Pivot->Up != NULL)
  {
    if(Pivot->Up->Left == Red) //if the parent of red is still point to red
      Pivot->Up->Left = Pivot;
  }
  //update height and balance;
  calculateHeightAndBalance(Pivot);
  calculateHeightAndBalance(Red);
  return Pivot;
}

Vertex* BST::doubleRightRotation(Vertex*Red, Vertex*Green) //case 4
{
  Vertex* Pivot;
  Pivot = Green->Right;
  cout << "---Rotate left with pivot: " << Pivot->Elem << endl;
  Green->Right = Pivot->Left;
  Pivot->Left = Green;
  //update link
  Red->Left = Pivot;
  Pivot->Up = Red;
  Green->Up = Pivot;
  //update height and balance;
  calculateHeightAndBalance(Green);
  calculateHeightAndBalance(Pivot);

  cout << "---Rotate right with pivot: " << Pivot->Elem << endl;
  Pivot = Red->Left;
  Red->Left = Pivot->Right;
  Pivot->Right = Red;
  //update link
  Pivot->Up = Red->Up;
  Red->Up = Pivot;
  if(Pivot->Up != NULL)
  {
    if(Pivot->Up->Right == Red) //if the parent of red is still point to red
      Pivot->Up->Right = Pivot;
  }
  //update height and balance;
  calculateHeightAndBalance(Red);
  calculateHeightAndBalance(Pivot);
  return Pivot;
}

Vertex* BST::doubleLeftRotation(Vertex*Red, Vertex*Green) //case 3
{
  Vertex* Pivot;
  Pivot = Green->Left;
  cout << "---Rotate right with pivot: " << Pivot->Elem << endl;
  Green->Left = Pivot->Right;
  Pivot->Right = Green;
  //update link
  Red->Right = Pivot;
  Pivot->Up = Red;
  Green->Up = Pivot;
  //update height and balance;
  calculateHeightAndBalance(Green);
  calculateHeightAndBalance(Pivot);

  cout << "---Rotate left with pivot: " << Pivot->Elem << endl;
  Pivot = Red->Right;
  Red->Right = Pivot->Left;
  Pivot->Left = Red;
  //update link
  Pivot->Up = Red->Up;
  Red->Up = Pivot;
  if(Pivot->Up != NULL)
  {
    if(Pivot->Up->Left == Red) //if the parent of red is still point to red
      Pivot->Up->Left = Pivot;
  }
  //update height and balance;
  calculateHeightAndBalance(Red);
  calculateHeightAndBalance(Pivot);
  return Pivot;
}

//Red is where +2 or -2 was found
void BST::fixIt(Vertex* Red)
{ 
  cout << ">>>Fixing an unbalanced vertex at " << Red->Elem << "<<<" << endl;
  Vertex* Pivot;
  if (Red->Balance == 2 && Red->Right->Balance == 1) 
  {
    cout << "---Case 1: right heavy so rotate to left---" << endl;
    Pivot = rotateLeft(Red);
  }
  else if (Red->Balance == -2 && Red->Left->Balance == -1)
  {
    cout << "---Case 2: left heavy so rotate to right---" << endl;
    Pivot = rotateRight(Red);
  }
  else if (Red->Balance == -2 && Red->Left->Balance == 1)
  {
    cout << "---Case 4: left heavy with right heavy substree---" << endl;
    Vertex* Green = Red->Left;
    Pivot = doubleRightRotation(Red,Green);
  }
  else //Red->Balance == 2 && Red->Right->Balance == -1)
  {
    cout << "---Case 3: right heavy with left heavy substree---" << endl;
    Vertex* Green = Red->Right;
    Pivot = doubleLeftRotation(Red,Green);
  }

  if (Root == Red)
  { 
    Root = Pivot; // new Root
    cout << "---New root is: " << Root->Elem << endl;
  }
  cout << ">>>Fixed<<<" << endl;
}
