// -------------------------------------------------
// BSTree.h
// -------------------------------------------------
// This .h file is a template file for a binary search tree.
// This is used in conjunction with LinkedList.h
// to form a binary search tree
// -------------------------------------------------
// Written by Patrick Holt (c3400636)
// Last update: 08/09/2022
// -------------------For Markers-------------------//
// My calculateInventory function kept printing 48705007 parts 
// despite using two different methods as shown below. 
// My first recursive calculate function is commented out and
// replaced with a simple size counter version
// any feedback on why I was getting an insanely large number
// for both version would be helpful thanks
// -------------------------------------------------
#ifndef PATRICK_BSTree
#define PATRICK_BSTree
#include <cstddef>//For nullptr & NULL
#include <iostream>//For output
#include "BTnode.h"//Includes the BTNode h file
#include "MechPart.h"//Includes the mechpart.h file
using namespace std;//For a lil bit of everything

template <typename T>
class BSTree
{
    //Public Members
    public:

        //Constructors

        //Pre: None
        //Post: Constructs a tree
        BSTree();

        //Deconstructor

        //Pre: None
        //Post: Deconstructs a tree
        ~BSTree();

        //Setters

        //Pre: A template reference as an argument
        //Post: Decides where to put the new templated data
        void add(T& newLeaf);

        //Getters

        //Pre: None
        //Post: Returns true if empty, and false if it contains a node
        bool isEmpty() const;

        //Pre: None
        //Post: Returns the total size of the BSTree
        int getSize() const;

        //Pre: None
        //Post: Returns the size of the unique items in the BSTree
        int getUniqueSize() const;

        //Calculate Functions

        //Pre: None
        //Post: Calculates how many unique parts there are in the tree
        int calculateParts();

        //Pre: None
        //Post: Calculates the total number of parts in the tree
        int calculateInventory();

        //Removers
        //Pre: Requires a templated node to remove from the tree
        //Post: Deletes said node from the tree
        void deleteFromTree(BTNode<T>* removingLeaf);

        //Pre: Requires a mechpart
        //Post: Removes said mechpart from tree
        void remove(T& removingLeaf);

        //Output Functions

        //Pre: Requires output stream
        //Post: Sends output stream to inorder traversal
        void outputHelper(ostream& output);

    //Private Members   
    private:
        BTNode<T>* root;//The node at the top of the tree that all other nodes are connected through
        BTNode<T>* current;//Pointer to move through the tree
        int size;//Quantity of nodes in the tree
        int uniqueSize;//Quantity of all items in the tree
    
        //Setters(private)
        
        //Pre: Requires a template node object and a leaf object
        //Post: Inserts the new object into the tree where required
        void insert(BTNode<T>* node, T& newLeaf);
    
        //Output Functions(private)
    
        //Pre: Requires a templated node and the output stream
        //Post: Outputs the BSTree
        void inorderTraversal(BTNode<T>* leaf, ostream& output);
    
        //Calculator Functions(private)
        
        //Pre: Requires a templated node object
        //Post: Returns a value of the number of parts
        //int calculateInventoryRecursive(BTNode<T>* leaf);
        //Above is attempted recursive counter
};

//<< Overloader Function
//Pre: Requires the output stream and the tree being printed
//Post: Returns output of the tree
template <typename T>
ostream& operator <<(ostream& output, BSTree<T>& outputTree)
{
    outputTree.outputHelper(output);//Passes output stream to the output function
    return(output);//Returns output stream
}

//Constructors
template <typename T>
BSTree<T>::BSTree()
{
    root = nullptr;
    current = nullptr;
    size = 0;
    uniqueSize = 0;
};//End BSTree constructor

//Deconstructor
template <typename T>
BSTree<T>::~BSTree()
{
    root = nullptr;
    current = nullptr;
    size = 0;
    uniqueSize = 0;
};//End ~BSTree deconstructor

//Setters
template <typename T>
void BSTree<T>::add(T& newLeaf)
{
    if(root == nullptr)
    {
        root = new BTNode<T>(newLeaf);
        uniqueSize++;
    }//End if statement
    else
    {
        insert(root, newLeaf);
    }//End else statement
    getSize() += newLeaf.get_quantity();
}//End add function

//Public
//Getters

template <typename T>
bool BSTree<T>::isEmpty() const
{
    return(root == nullptr);//If root is nullptr, the tree is empty
};//End isEmpty function

template <typename T>
int BSTree<T>::getSize() const
{
    return(size);
};//End  getSize function

template <typename T>
int BSTree<T>::getUniqueSize() const
{
    return(uniqueSize);
};//End getUniqueSize function

//Calculate Functions

template <typename T> 
int BSTree<T>::calculateParts()
{
    int parts = getUniqueSize();
    return(parts);
};//End calculateParts function

template <typename T> 
int BSTree<T>::calculateInventory()
{
    //Old recursive calculator that doesn't seem to count properly
    /*if (root != NULL) 
    {
        size = calculateInventoryRecursive(root);//passes to the recursive inventory
    }
    return(size);
    */
   return(getSize()); //Replaced with simple getSize() that increments inside the add and decrements in remove 
};//End calculate inventory function

//Removers

template <typename T>
void BSTree<T>::deleteFromTree(BTNode<T>* removingLeaf)
{
    BTNode<T>* trail;//Stays behind current when necessary
    BTNode<T>* sacrificialLeaf; //pointer to delete the node
    if(removingLeaf->getLeft() == nullptr && removingLeaf->getRight() == nullptr)
    {
        sacrificialLeaf = removingLeaf;
        removingLeaf = nullptr;
        delete(sacrificialLeaf);
    }//End else if statement
    else if (removingLeaf->getLeft() == nullptr)
    {
        sacrificialLeaf = removingLeaf;
        removingLeaf = sacrificialLeaf->getRight();
        delete(sacrificialLeaf);
    }//End else if statement
    else if (removingLeaf->getRight() == nullptr)
    {
        sacrificialLeaf = removingLeaf;
        removingLeaf = sacrificialLeaf->getLeft();
        delete(sacrificialLeaf);
    }//End else if statement
    else
    {
        current = removingLeaf->getLeft();
        trail = nullptr;

        while (current->getRight() != nullptr)
        {
            trail = current;
            current = current->getRight();
        }//End while loop

        removingLeaf->setData(current->getData());

        if (trail == nullptr)
        {
            //current == removingLeaf->getLeft(); adjust p
            removingLeaf->setLeft(current->getLeft());
        }//End if statement
        else
        {
            trail->setRight(current->getLeft());
        }//End else statement
        current = nullptr;
    }//End else statement
} //end deleteFromTree

template <typename T>
void BSTree<T>::remove(T& removingLeaf)
{
    getSize() -= removingLeaf.get_quantity();
    BTNode<T>* trail;//Stays behind current when necessary
    bool found = false;
    if(root == nullptr)
    {
        cout << "The tree is without leaf";
    }//End if statement
    else
    {
        current = root;
        trail = root;
        while(current != nullptr && found == true)
        {
            if(current->getData().get_code() == removingLeaf.get_code())
            {
                found == true;
            }//End if statement
            else
            {
                trail = current;
                if(current->getData().get_code() > removingLeaf.get_code())
                {
                    current = current->getLeft();
                }//End if statement
                else
                {
                    current = current->getRight();
                }//End else statement
            }//End else statement
        }//End while loop
        if(current == nullptr)
        {
            cout << "Item doesn't exist" << endl;
        }//End if statement
        else if(found)
        {
            if(current == root)
            {
                deleteFromTree(root);
            }//End if statement
            else if(trail->getData().get_code() > removingLeaf.get_code())
            {
                deleteFromTree(trail->getLeft());
            }
            else
            {
                deleteFromTree(trail->getRight());
            }
        }//End else if statement
    }//End else statement
};

//Output Functions

template <typename T>
void BSTree<T>::outputHelper(ostream& output) 
{
    inorderTraversal(root, output);//Sends root pointer and output to inorderTraversak
}

//Private
//Setters(private)

template <typename T>
void BSTree<T>::insert(BTNode<T>* node, T& newLeaf)
{
    if(node->getData().get_code() == newLeaf.get_code())
    {
        int newQuantity = node->getData().get_quantity();
        node->getData().set_quantity(newQuantity += newLeaf.get_quantity());
    }//End if statement
    else if(node->getData().get_code() < newLeaf.get_code())
    {
        if(node->getRight() == nullptr)
        {
            node->setRight(new BTNode<T>(newLeaf));
            uniqueSize++;
        }//End if statement
        else
        {
            insert(node->getRight(), newLeaf);//Recursion to find new position
        }//End else statement
    }//End else if statement
    else if(node->getData().get_code() > newLeaf.get_code())
    {
        if(node->getLeft() == nullptr)
        {
            node->setLeft(new BTNode<T>(newLeaf));
            uniqueSize++;
        }//End if statement
        else
        {
            insert(node->getLeft(), newLeaf);//Recursion to find new position
        }//End else statement
    }
    else
    {
        cout << "Error: add"; 
    }//End else statement
};

//Output Functions(private)

template <typename T>
void BSTree<T>::inorderTraversal(BTNode<T>* leaf, ostream& output)
{
    if (leaf != NULL) 
    {
        inorderTraversal(leaf->getLeft(), output);//Passes output stream to the node left of the current node and continues down the tree (using recursion)
        output << leaf->getData() << " ";//Adds data content and a space to the output stream
        inorderTraversal(leaf->getRight(), output);//Passes output stream to the node right of the current node and continues down the tree (using recursion)
    }//End if statement
}//End inorder traversal function 


//Calculator Functions(private) - Attempted calculating recursion as mentioned above

/*template <typename T>
int BSTree<T>::calculateInventoryRecursive(BTNode<T>* leaf)
{
    int counter = 0;
    if (leaf != NULL) 
    {
        counter += calculateInventoryRecursive(leaf->getLeft());//Passes output stream to the node left of the current node and continues down the tree (using recursion)
        counter += calculateInventoryRecursive(leaf->getRight());//Passes output stream to the node right of the current node and continues down the tree (using recursion)
        counter += leaf->getData().get_quantity();

    }//End if statement
    return(counter);
};//End recursive inventory statement */

#endif