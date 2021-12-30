#ifndef __CARGO_H__
#define __CARGO_H__

#include <string>
// The "temperature" of the cargo
// Frozen implies solid
enum Temperature
{
    temperate,
    cold,
    frozen
};

// The physical state the cargo is in
// Solid metal, or liquid mercury
enum State
{
    solid,
    liquid,
    gas
};

template <Temperature t, State s>
class Cargo
{
private:
    Temperature temp_;
    State state_;
    std::string cargo_;
public:
    Cargo();                    // Cargo is empty
    Cargo(std::string theCargo);// Cargo
    ~Cargo();
    std::string getTemp();       // Returns Temperature enum as a string
    std::string getState();      // Returns State enum as a string
    void setCargo(std::string cargo);
    std::string getCargo();
};

// All implementation code is in header because template has been used

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


#endif // __CARGO_H__