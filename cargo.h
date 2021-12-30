#ifndef __CARGO_H__
#define __CARGO_H__

#include <string>
#include <type_traits>

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

// No cargo given, cargo is empty
template<Temperature t, State s>
Cargo<t, s>::Cargo()
{
    // Throw compile time error if frozen and liquid
    static_assert(!(t == frozen && s == liquid), "Can't be frozen and a liquid");

    //Throw compile time error if frozen and gas
    static_assert(!(t == frozen && s == gas), "Can't be frozen and a gas");
    temp_ = t;
    state_ = s;
    cargo_ = "Empty";
}

// cargo is given, cargo is theCargo
template<Temperature t, State s>
Cargo<t, s>::Cargo(std::string theCargo)
{
    // Throw compile time error if frozen and liquid
    static_assert(!(t == frozen && s == liquid), "Can't be frozen and a liquid");

    //Throw compile time error if frozen and gas
    static_assert(!(t == frozen && s == gas), "Can't be frozen and a gas");

    temp_ = t;
    state_ = s;
    cargo_ = theCargo;
}

// Destructor
template<Temperature t, State s>
Cargo<t, s>::~Cargo() 
{
    
}

// Get a string corresponding to value of temp_
template<Temperature t, State s>
std::string Cargo<t, s>::getTemp() 
{
    switch (temp_)
    {
    case temperate  : return "temperate"; 
    case cold       : return "cold";
    case frozen     : return "frozen";
    
    
    default: return "Error";
    }
}

// Get a string corresponding to value of state_
template<Temperature t, State s>
std::string Cargo<t, s>::getState() 
{
    switch (state_)
    {
    case solid : return "solid" ; 
    case liquid: return "liquid";
    case gas   : return "gas"   ;
    
    default: return "Error";
    }
}

// Set cargo_
template<Temperature t, State s>
void Cargo<t, s>::setCargo(std::string cargo)
{
    cargo_ = cargo;
}

// Return cargo_
template<Temperature t, State s>
std::string Cargo<t, s>::getCargo()
{
    return cargo_;
}

// Retired code since I couldn't figure out how to implement a way to compile error on specialization

// // Template arguments that are illogical should result in error
// // In order to do this, making custom false type
// template<typename T>
// struct assert_false : std::false_type
// { };

// template<>
// Cargo<frozen, liquid>::Cargo()
// {
//     static_assert(assert_false<int>::value);
// }

// template<>
// Cargo<frozen, gas>::Cargo()
// {

// }


#endif // __CARGO_H__