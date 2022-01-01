#ifndef FUNCTORWRAPPER_H
#define FUNCTORWRAPPER_H

template <typename DATA, typename INPUT, typename OUTPUT, typename FUNCTORTYPE>
struct FunctorWrapper
{
    FUNCTORTYPE * func_;
    DATA data_;

    FunctorWrapper(FUNCTORTYPE * func, DATA data) : func_(func), data_(data) { } 

    OUTPUT operator()(INPUT input)
    {
        return (*func_)(data_, input);
    }
};


#endif /* FUNCTORWRAPPER_H */