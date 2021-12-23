#include "cargo.h"

template<Temperature t, State s>
cargo<t, s>::cargo()
{
    temp = t;
    state = s;
}

template<Temperature t, State s>
cargo<t, s>::~cargo() 
{
    
}

template<Temperature t, State s>
String cargo<t, s>::getTemp() 
{
    switch (temp)
    {
    case solid : return "solid" ;   break;
    case liquid: return "liquid";   break;
    case gas   : return "gas"   ;   break;
    
    default: return "Error"
        break;
    }
}

template<Temperature t, State s>
String cargo<t, s>::getState() 
{
    return state;
}
