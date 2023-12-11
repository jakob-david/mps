//
// Created by Jakob on 11.12.23.
//

#ifndef MPS_LIB_MPS_H
#define MPS_LIB_MPS_H


class mps {

private:
    int mantisse_length;
    int exponent_length;

    long double double_value;

public:

    mps(int mantisse, int exponent, long double value);

    int getMantisseLength() const;
    int getExponentLength() const;

    long double getDoubleValue() const;


};


#endif //MPS_LIB_MPS_H
