#include "cargo.h"

// Standard template instantiation

template<Temperature t, State s>
Cargo<t, s>::Cargo()
{
    temp_ = t;
    state_ = s;
    cargo_ = "Empty";
}

template<Temperature t, State s>
Cargo<t, s>::Cargo(std::string theCargo)
{
    temp_ = t;
    state_ = s;
    cargo_ = theCargo;
}

template<Temperature t, State s>
Cargo<t, s>::~Cargo() 
{
    
}

template<Temperature t, State s>
std::string Cargo<t, s>::getTemp() 
{
    switch (temp_)
    {
    case solid : return "solid" ; 
    case liquid: return "liquid";
    case gas   : return "gas"   ;
    
    default: return "Error";
    }
}

template<Temperature t, State s>
std::string Cargo<t, s>::getState() 
{
    switch (state_)
    {
    case temperate  : return "temperate"; 
    case cold       : return "cold";
    case frozen     : return "gas";
    
    default: return "Error";
    }
}

template<Temperature t, State s>
void Cargo<t, s>::setCargo(std::string cargo)
{
    cargo_ = cargo;
}

template<Temperature t, State s>
std::string Cargo<t, s>::getCargo()
{
    return cargo_;
}

// Template arguments that are invalid should result in error

template<>
Cargo<frozen, liquid>::Cargo()
{
}