#include "container.h"
#include "cargo.h"

template <Temperature t, State s>
Container<t, s>::Container() : cargo_ptr(&Cargo<t,s>("Empty"))
{
    
}

template <Temperature t, State s>
Container<t, s>::Container(std::string cargo) : cargo_ptr(&Cargo<t, s>(cargo))
{
    
}

template <Temperature t, State s>
Container<t, s>::~Container() 
{
    cargo_ptr->~Cargo();
}

template <Temperature t, State s>
std::string Container<t, s>::seeCargo()
{
    return cargo_ptr->getCargo();
}

template <Temperature t, State s>
void Container<t, s>::addCargo(std::string cargo)
{

}

template <Temperature t, State s>
void Container<t, s>::removeCargo()
{
    
}