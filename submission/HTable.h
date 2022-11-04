// -------------------------------------------------
// HTable.h
// -------------------------------------------------
// This .h file is a template file for a hash table.
// This is used in conjunction with LinkedList.h
// to form a hash table
// -------------------------------------------------
// Written by Patrick Holt (c3400636)
// Last update: 08/09/2022
// -------------------------------------------------
#ifndef PATRICK_HTABLE
#define PATRICK_HTABLE
#include <cstddef>//For nullptr & NULL
#include <ostream>//For ostream
#include "MechPart.h"
using namespace std;//For a lil bit of everything

template <typename T>
class HTable
{
    //Public Members
    public:

        //Constructors
        //Pre: None
        //Post: Constructs a hash table and sets private members to NULL/nullptr/etc.
        HTable();

        //Deconstructor
        //Pre: None
        //Post: Deconstructs a hash table object by setting any pointers to nullptr and deleting them
        ~HTable();

        //Setters
        //Pre: Requires a mechpart object
        //Post: Adds a new mechpart object to the table
        void add(T& newMechPart);

        //Getters
        //Pre: Requires a mechpart object reference
        //Post: Returns a mechpart object reference
        T& get(T& mechPart);

        //Pre: Requires a position in the array
        //Post: Returns a template reference object
        T& getFromPosition(int position);

        //Pre: None
        //Post: Returns true if the hash table object is empty
        bool isEmpty() const;

        //Pre: None
        //Post: Returns an int value of the size of the hash table object
        int getSize() const;

        //Pre: None
        //Post: Returns an int value of the largest value in the hash table
        int getMaxSize() const;

        //Calculate Functions
        //Pre: None
        //Post: Calculates how many unique parts there are in the table
        int calculateParts() const;

        //Pre: None
        //Post: Calculates the total number of parts in the table
        int calculateInventory() const;

        //Removers
        //Pre: Requires a templated object
        //Post: Removes said object from the table
        void remove(T x);

        //Pre: None
        //Post: Clears the entire table
        void clear();

        //Pre: Requires a templated object
        //Post: Gives said object its location in the table
        int hashFunction(const T& value ); 


    //Private Members   
    private:
    int HTMaxSize = 5000;//Max size of the table
    T data[5000]; //Where the information is stored
    int currentSize; //Counter for size
};
//<< Overloader Function
//Pre: Requires the output stream and the table being printed
//Post: Returns output of the table
template <typename T>
ostream& operator <<(ostream& output, HTable<T>& outputTable)
{
    for(int counter = 0;counter < 5000;counter++)
    {
        if(outputTable.getFromPosition(counter).get_code() != "" || outputTable.getFromPosition(counter).get_quantity() != 0)
        {
            output << outputTable.getFromPosition(counter);
        }//End if statement
    }//End for loop
    return(output);//Returns output stream
}//End overloading function

//Constructors
template <typename T>  
HTable<T>::HTable()
{
    for(int counter = 0;counter < HTMaxSize;counter++)
    {
        data[counter] = MechPart("", 0);
    }//End for loop
    currentSize = 0;
};//End constructor

//Deconstructor
template <typename T>  
HTable<T>::~HTable()
{
    clear();
};//End deconstructor

//Setters
template <typename T>  
void HTable<T>::add(T& newMechPart)
{
    int location = hashFunction(newMechPart);
    data[location] = newMechPart;
};//End add function

//Getters
template <typename T>  
T& HTable<T>::get(T& mechPart)
{
    int location = hashFunction(mechPart);
    return(data[location]);
};//End get function

template <typename T>  
T& HTable<T>::getFromPosition(int position)
{
    return(data[position]);
};//End get position function

template <typename T>  
bool HTable<T>::isEmpty() const
{
    return(currentSize == 0);
};//End is empty function 

template <typename T>  
int HTable<T>::getSize() const
{
    return(currentSize);
};//End get size function

template <typename T>  
int HTable<T>::getMaxSize() const
{
    return(HTMaxSize);
};//End get max size function

//Calculate Functions
template <typename T> 
int HTable<T>::calculateParts() const
{
    int totalParts = 0;
    for(int counter = 0;counter < HTMaxSize;counter++)
        {
            if(data[counter].get_code() != "" || data[counter].get_quantity() != 0)
            {
                totalParts++;
            }//End if statement
        }//End for loop
    return(totalParts);
};//End calculate parts function

template <typename T> 
int HTable<T>::calculateInventory() const
{
    int totalInventory = 0;
    for(int counter = 0;counter < HTMaxSize;counter++)
        {
            if(data[counter].get_code() != "" || data[counter].get_quantity() != 0);
            {
                totalInventory += data[counter].get_quantity();
            }//End if statement
        }//End for loop
    return(totalInventory);
};//End calculate inventory function

//Removers
template <typename T>  
void HTable<T>::remove(T removedMechPart)
{
    for(int counter = 0;counter < HTMaxSize;counter++)
        {
            if(data[counter].get_code() == removedMechPart.get_code())
            {
                data[counter].set_quantity(0);
                data[counter].set_code("");
            }//End if statement
        }//End for loop
};//End remove function

template <typename T>  
void HTable<T>::clear()
{
    for(int counter = 0;counter < HTMaxSize;counter++)
    {
        if(data[counter].get_code() != "" || data[counter].get_quantity() != 0)
        {
            data[counter].set_code("");
            data[counter].set_quantity(0);
        }//End if statement
    }//End for loop
    currentSize = 0;
    HTMaxSize = 0;
};//End clear function

//Hash Function
template <typename T>
int HTable<T>::hashFunction(const T& value) 
{
    int position = 0;
    string temp = value.get_code ( );
    for ( int i=0; i<(int)temp.length( ); i++ ) 
    {
        position += ( i+1 ) * ( i+1 ) * temp.at( i );
    }//End for loop
    return position % HTMaxSize;
}//End hash function

#endif
