#include "cargo.h"

// Standard template instantiation

template<Temperature t, State s>
cargo<t, s>::cargo()
{
    temp_ = t;
    state_ = s;
}

template<Temperature t, State s>
cargo<t, s>::~cargo() 
{
    
}

template<Temperature t, State s>
std::string cargo<t, s>::getTemp() 
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
std::string cargo<t, s>::getState() 
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
void cargo<t, s>::setCargo(std::string cargo)
{
    cargo_ = cargo;
}

template<Temperature t, State s>
std::string cargo<t, s>::getCargo()
{
    return cargo_;
}

// Template arguments that are invalid should result in error

template<>
cargo<frozen, liquid>::cargo()
{
}