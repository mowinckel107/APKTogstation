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


#endif // __CARGO_H__