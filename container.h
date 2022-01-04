#ifndef __CONTAINER_H__
#define __CONTAINER_H__

// This Header file holds template for Container class
// Container class holds cargo. Can only hold 1 Cargo at a time
// Able to add and remove Cargo.

#include "cargo.h"

template <Temperature t, State s>
class Container
{
private:
    Cargo<t,s>* cargo_ptr;    // Void pointer to later point to cargo when cargo is created
public:
    Container();                    // Creates container and empty cargo
    Container(std::string cargo);   // Creates container with cargo
    ~Container();
    std::string seeCargo();
    void addCargo(std::string cargo);
    void removeCargo();
};

// Remember to put implementation in header file to solve template issues
// If not, compiler has no idea how to implement functions

// No cargo was given, create null ptr
template <Temperature t, State s>
Container<t, s>::Container() : cargo_ptr(nullptr)
{
    
}

// Cargo given, create new Cargo and give to pointer
template <Temperature t, State s>
Container<t, s>::Container(std::string cargo) : cargo_ptr(new Cargo<t, s>(cargo))
{

}

// On destruction, clean up cargo_ptr
template <Temperature t, State s>
Container<t, s>::~Container() 
{
    if (cargo_ptr != nullptr)
        delete cargo_ptr;
}

// Shows Cargo name. If nullptr (No Cargo) show "Empty"
template <Temperature t, State s>
std::string Container<t, s>::seeCargo()
{
    if (cargo_ptr != nullptr)
        return cargo_ptr->getCargo();
    else
        return "Empty";
}

// Add Cargo if nullptr (No Cargo)
template <Temperature t, State s>
void Container<t, s>::addCargo(std::string cargo)
{
    if (cargo_ptr == nullptr)
        cargo_ptr = new Cargo<t, s>(cargo);
}

// Remove Cargo if not nullptr (Has Cargo)
template <Temperature t, State s>
void Container<t, s>::removeCargo()
{
    if (cargo_ptr != nullptr)
    {
        delete cargo_ptr;
        cargo_ptr = nullptr;
    }
    
}

#endif // __CONTAINER_H__