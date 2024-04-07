//
// Created by Jakob on 07.04.24.
//

#ifndef MPS_MPE_H
#define MPS_MPE_H


class mpe {

private:
    int A;

public:

    // constructors and destructor
    //-------------------------------
    mpe();
    ~mpe();
    //-------------------------------

    // getter
    //-------------------------------
    [[nodiscard]] int getA();
    //-------------------------------
};


#endif //MPS_MPE_H
