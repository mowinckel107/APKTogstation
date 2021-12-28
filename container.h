#ifndef __CONTAINER_H__
#define __CONTAINER_H__

#include "cargo.h"

template <Temperature t, State s>
class Container
{
private:
    void* cargo_ptr;    // Void pointer to later point to cargo when cargo is created
public:
    Container();                    // Creates container and empty cargo
    Container(std::string cargo);   // Creates container with cargo
    ~Container();
    std::string seeCargo();
    void addCargo(std::string cargo);
    void removeCargo();
};

#endif // __CONTAINER_H__