#ifndef __CARGO_H__
#define __CARGO_H__

#include <string.h>
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
class cargo
{
private:
    Temperature temp;
    State state;
public:
    cargo();
    ~cargo();
    String getTemp();       // Returns Temperature enum as a string
    String getState();      // Returns State enum as a string
};


#endif // __CARGO_H__