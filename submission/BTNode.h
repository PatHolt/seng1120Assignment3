// -------------------------------------------------
// BTNodeNode.h
// -------------------------------------------------
// This .h file is a template file for a binary search
// tree node. This is used in conjunction with 
// LinkedList.h to form a binary search tree
// -------------------------------------------------
// Written by Patrick Holt (c3400636)
// Last update: 08/09/2022
// -------------
#ifndef PATRICK_BTNode
#define PATRICK_BTNode
#include <cstddef>//For nullptr & NULL
using namespace std;//For a lil bit of everything

template <typename T>
class BTNode
{
    //Public Members
    public:

        //Constructors
        
        //Pre: None
        //Post: Constructs node object
        BTNode();

        //Pre: Requires templated reference object
        //Post: Constructs node object and sets said data to data variable
        BTNode(T& newData);

        //Deconstructor
        
        //Pre: None
        //Post: Deconstructs node object
        ~BTNode();

        //Setters
        
        //Pre: Requires a templated reference object
        //Post: Sets said object as data
        void setData(const T& newData);

        //Pre: Requires a templated node object
        //Post: Sets said object to the left
        void setLeft(BTNode<T>* newLeft);

        //Pre: Requires a templated node object
        //Post: Sets said object to the right
        void setRight(BTNode<T>* newRight);

        //Getters
        
        //Pre: None
        //Post: Returns reference to templated data object
        T& getData();

        //Pre: None
        //Post: Returns pointer to leaf to the left
        BTNode<T>* getLeft();

        //Pre: None
        //Post: Returns pointer to leaf to the right
        BTNode<T>* getRight();

    //Private Members   
    private:
    T data;//Stores templated object
    BTNode<T>* left;//Stored pointer to a node
    BTNode<T>* right;//Stored pointer to a node

};

//Constructors
template <typename T>
BTNode<T>::BTNode()
{
    left = nullptr;
    right = nullptr;
};//End constructor

template <typename T>
BTNode<T>::BTNode(T& newData)
{
    data = newData;
    left = nullptr;
    right = nullptr;
};//End constructor

//Deconstructor
template <typename T>
BTNode<T>::~BTNode()
{
    left = nullptr;
    right = nullptr;
};//End deconstructor

//Setters
template <typename T>
void BTNode<T>::setData(const T& newData)
{
    data = newData;
};//End set data function

template <typename T>
void BTNode<T>::setLeft(BTNode<T>* newLeft)
{
    left = newLeft;
};//End set left function

template <typename T>
void BTNode<T>::setRight(BTNode<T>* newRight)
{
    right = newRight;
};//End set right function

//Getters
template <typename T>
T& BTNode<T>::getData()
{
    return(data);
};//End get data function

template <typename T>
BTNode<T>* BTNode<T>::getLeft()
{
    return(left);
};//End get left function

template <typename T>
BTNode<T>* BTNode<T>::getRight()
{
    return(right);
};//End get right function

#endif