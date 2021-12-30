#ifndef __CONTAINER_H__
#define __CONTAINER_H__

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

template <Temperature t, State s>
Container<t, s>::Container() : cargo_ptr(nullptr)
{
    
}

template <Temperature t, State s>
Container<t, s>::Container(std::string cargo) : cargo_ptr(new Cargo<t, s>(cargo))
{

}

template <Temperature t, State s>
Container<t, s>::~Container() 
{
    if (cargo_ptr != nullptr)
        delete cargo_ptr;
}

template <Temperature t, State s>
std::string Container<t, s>::seeCargo()
{
    if (cargo_ptr != nullptr)
        return cargo_ptr->getCargo();
    else
        return "Empty";
}

template <Temperature t, State s>
void Container<t, s>::addCargo(std::string cargo)
{
    if (cargo_ptr == nullptr)
        cargo_ptr = new Cargo<t, s>(cargo);
}

template <Temperature t, State s>
void Container<t, s>::removeCargo()
{
    if (cargo_ptr != nullptr)
        cargo_ptr = nullptr;
}

#endif // __CONTAINER_H__