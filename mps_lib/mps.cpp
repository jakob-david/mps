#include "mps.h"
#include <iostream>
#include <algorithm>


// constructors and destructor
//-------------------------------

/**
 * Constructor for the multiprecision simulator.
 *
 * @param mantisse Mantisse of the floating point representation.
 * @param exponent Exponent of the floating point representation.
 * @param value Value of the floating point number.
 */
mps::mps(int mantissa_length, int exponent_length, double value) {
    this->mantissa_length = mantissa_length;
    this->exponent_length = exponent_length;

    setBitArray(value);
}

mps::mps(){
    this->mantissa_length = 0;
    this->exponent_length = 0;
}

/**
 * Destructor for the multiprecision simulator.
 */
mps::~mps() = default;

//-------------------------------


// getter methods
//-------------------------------

/**
 * Returns the length of the matisse.
 *
 * @return length matisse
 */
int mps::getMantisseLength() const {
    return this->mantissa_length;
}

/**
 * Returns the length of the exponent.
 *
 * @return length exponent
 */
int mps::getExponentLength() const {
    return this->exponent_length;
}

/**
 * Returns the length of the whole bit array.
 * (sign + matisse + exponent)
 *
 * @return length matisse
 */
int mps::getBitArrayLength() const {
    return (int) this->bit_vector.size();
}

/**
 * Returns the bit vector.
 *
 * @return bit vector
 */
vector<bool> mps::getBitArray() {
    return this->bit_vector;
}

/**
 * Returns a pointer to the bit vector.
 *
 * @return pointer to bit vector
 */
vector<bool>* mps::getBitArrayReference() {
    return &this->bit_vector;
}

/**
 * Returns the value of the mps object as double.
 *
 * @return value as double.
 */
double mps::getValue() {

    // handle special cases
    if(isZero()){
        return 0;
    } else if (isInfinity() && isPositive()){
        return numeric_limits<double>::infinity();
    } else if (isInfinity()){
        return numeric_limits<double>::infinity() * -1;
    }

    double ret;

    // positive or negative
    if(bit_vector[0]){
        ret = -1;
    } else {
        ret = 1;
    }

    // handle mantissa
    for(int i = exponent_length + 1; i < (int) bit_vector.size(); i++){
        if(bit_vector[i]){
            if(ret >= 0){
                ret += pow(0.5, i - exponent_length);
            } else {
                ret -= pow(0.5, i - exponent_length);
            }
        }
    }

    // get exponent
    int exponent = 0;
    for(int i = 1; i <= exponent_length; i++){
        if(bit_vector[i]){
            exponent += (int) pow(2, exponent_length-i);
        }
    }

    // apply bias and apply exponent
    exponent -= getBias();
    ret *= pow(2, exponent);

    return ret;

}

/**
 * Returns true if the mps object is zero.
 *
 * @return true if zero.
 */
bool mps::isZero(){
    return all_of(bit_vector.begin(), bit_vector.end(), [](bool i){return !i;});
}

/**
 * Returns true if the mps object is positive or negative infinity.
 *
 * @return true if pos. or neg. infinity.
 */
bool mps::isInfinity() {

    for(int i = 1; i < exponent_length+1; i++){
        if(!bit_vector[i]){
            return false;
        }
    }

    for(int i = exponent_length+1; i < (int) bit_vector.size(); i++){
        if(bit_vector[i]){
            return false;
        }
    }

    return true;
}

/**
 * Returns true if the mps object is positive.
 *
 * @return true if positive.
 */
bool mps::isPositive(){
    if(bit_vector[0]){
        return false;
    } else {
        return true;
    }
}
//-------------------------------


// setter methods
//-------------------------------
/**
 * Sets the floating point number to infinity.
 *
 * @param negative set to true for negative infinity. (default false)
 */
void mps::setInf(bool negative) {

    bit_vector.erase(bit_vector.begin(),bit_vector.end());

    if(negative){
        bit_vector.push_back(true);
    } else {
        bit_vector.push_back(false);
    }

    for(int i = 0; i < exponent_length; i++){
        bit_vector.push_back(true);
    }

    for(int i = 0; i < mantissa_length; i++){
        bit_vector.push_back(false);
    }
}

/**
 * Sets the floating point number to zero.
 */
void mps::setZero(){

    bit_vector.erase(bit_vector.begin(),bit_vector.end());

    for(int i = 0; i < exponent_length + mantissa_length + 1; i++){
        bit_vector.push_back(false);
    }
}

/**
 * Sets the floating point number to NaN (not a number)
 */
void mps::setNaN(){

    bit_vector.erase(bit_vector.begin(),bit_vector.end());

    bit_vector.push_back(false);

    for(int i = 0; i < exponent_length; i++){
        bit_vector.push_back(true);
    }

    bit_vector.push_back(true);

    for(int i = 1; i < mantissa_length; i++){
        bit_vector.push_back(false);
    }
}
//-------------------------------

// operators
//-------------------------------

/**
 * Sets one mps object equal to an other mps object.
 */
mps& mps::operator=(const mps& other) {

    if (this == &other){
        return *this;
    }

    this->bit_vector.erase(bit_vector.begin(), bit_vector.end());

    for(auto i : other.bit_vector){
        this->bit_vector.push_back(i);
    }

    this->mantissa_length = other.mantissa_length;
    this->exponent_length = other.exponent_length;

    return *this;
}

/**
 * Performs am addition to two mps floating point values.
 */
mps mps::operator+(mps& other) {

    //TODO: Remove when finished.
    if(this->mantissa_length != other.mantissa_length || this->exponent_length != other.exponent_length){
        cout << "ERROR: addition, sizes do not match"  << endl;
    }


    // If signs are different perform Subtraction.
    //-------------------------------
    if(this->bit_vector[0] && !other.bit_vector[0]){
        this->bit_vector[0] = false;
        return other - *this;
    } else if (other.bit_vector[0] && !this->bit_vector[0]) {
        other.bit_vector[0] = false;
        return *this - other;
    }
    //-------------------------------


    // Set up the return object.
    //-------------------------------
    mps ret;
    vector<bool>& ret_vector = ret.bit_vector;
    ret.exponent_length = this->exponent_length;
    ret.mantissa_length = this->mantissa_length;
    //-------------------------------


    // set sign
    //-------------------------------
    // TODO: Maybe simplify because of preceding if.
    if(this->isPositive() && other.isPositive()){
        ret.bit_vector.push_back(false);
    } else if(!this->isPositive() && !other.isPositive()){
        ret.bit_vector.push_back(true);
    }
    //-------------------------------


    // Handle special values.
    //-------------------------------
    if(this->isZero()){
        return other;
    } else if(other.isZero()){
        return *this;
    }
    //-------------------------------


    // Extract exponents and mantissas
    //-------------------------------
    vector<bool> a_mantissa(this->bit_vector.begin()+exponent_length+1, this->bit_vector.end());
    a_mantissa.insert(a_mantissa.begin(), true);

    vector<bool> b_mantissa(other.bit_vector.begin()+exponent_length+1, other.bit_vector.end());
    b_mantissa.insert(b_mantissa.begin(), true);

    vector<bool> a_exponent(this->bit_vector.begin()+1, this->bit_vector.begin()+1+this->exponent_length);
    vector<bool> b_exponent(other.bit_vector.begin()+1, other.bit_vector.begin()+1+other.exponent_length);
    vector<bool> exponent;
    //-------------------------------


    // Match mantissas and set exponent
    //-------------------------------
    int exponent_diff = 0;
    char larger_tmp = larger(a_exponent, b_exponent);
    if(1 == larger_tmp){
        exponent_diff = binaryToInt(binarySubtraction(a_exponent, b_exponent));
        exponent.insert(exponent.end(), a_exponent.begin(), a_exponent.end());
        matchMantissas(&b_mantissa, &a_mantissa, exponent_diff);
    } else if(-1 == larger_tmp){
        exponent_diff = binaryToInt(binarySubtraction(b_exponent, a_exponent));
        exponent.insert(exponent.end(), b_exponent.begin(), b_exponent.end());
        matchMantissas(&a_mantissa, &b_mantissa, exponent_diff);
    } else {
        exponent.insert(exponent.end(), a_exponent.begin(), a_exponent.end());
    }
    //-------------------------------


    // Actual addition and adjusting mantissa
    //-------------------------------
    bool carrier;
    vector<bool> mantissa = binaryAddition(a_mantissa, b_mantissa,true, &carrier);
    mantissa.erase(mantissa.begin(), mantissa.begin()+1);
    if(carrier){
        addOneToBinary(&exponent);
    }
    //-------------------------------


    round(&mantissa, ret.mantissa_length);
/*
    // Rounding and further adjustment of the mantissa
    //-------------------------------
    bool tmp = false;
    for(int i = ((int) mantissa.size())-exponent_diff+1 ; i < (int) mantissa.size(); i++){
        if (mantissa[i]){
            tmp = true;
            break;
        }
    }
    if(exponent_diff>0 && mantissa[mantissa.size()-exponent_diff] && tmp){
        mantissa.erase(mantissa.end()-exponent_diff, mantissa.end());
        if(addOneToBinary(&mantissa)){
            addOneToBinary(&exponent);
        }
    } else if(exponent_diff>0 && mantissa[mantissa.size()-exponent_diff]){
        if(mantissa[mantissa.size()-exponent_diff-1]){
            mantissa.erase(mantissa.end()-exponent_diff, mantissa.end());
            if(addOneToBinary(&mantissa)){
                addOneToBinary(&exponent);
            }
        } else {
            mantissa.erase(mantissa.end()-exponent_diff, mantissa.end());
        }
    }else {
        mantissa.erase(mantissa.end()-exponent_diff, mantissa.end());
    }
    //-------------------------------
*/

    // set everything together.
    //-------------------------------
    ret_vector.insert(ret_vector.end(), exponent.begin(), exponent.end());
    ret_vector.insert(ret_vector.end(), mantissa.begin(), mantissa.end());
    //-------------------------------

    return ret;
}

mps mps::operator-(mps& other){

    //TODO: Remove when finished.
    if(this->mantissa_length != other.mantissa_length || this->exponent_length != other.exponent_length){
        cout << "ERROR: addition, sizes do not match"  << endl;
    }


    // If signs are different perform Subtraction.
    //-------------------------------
    if(this->bit_vector[0] && !other.bit_vector[0]){
        other.bit_vector[0] = true;
        return other + *this;
    } else if (other.bit_vector[0] && !this->bit_vector[0]) {
        other.bit_vector[0] = false;
        return *this + other;
    }
    //-------------------------------


    // Set up the return object.
    //-------------------------------
    mps ret;
    vector<bool>& ret_vector = ret.bit_vector;
    ret.exponent_length = this->exponent_length;
    ret.mantissa_length = this->mantissa_length;
    //-------------------------------


    // set sign
    //-------------------------------
    // TODO: Maybe simplify because of preceding if.
    if(this->isPositive() && other.isPositive()){
        ret.bit_vector.push_back(false);
    } else if(!this->isPositive() && !other.isPositive()){
        ret.bit_vector.push_back(true);
    }
    //-------------------------------


    // Handle special values.
    //-------------------------------
    if(this->isZero()){
        return other;
    } else if(other.isZero()){
        return *this;
    }
    //-------------------------------

    // Extract exponents and mantissas
    //-------------------------------
    vector<bool> a_mantissa(this->bit_vector.begin()+exponent_length+1, this->bit_vector.end());
    a_mantissa.insert(a_mantissa.begin(), true);

    vector<bool> b_mantissa(other.bit_vector.begin()+exponent_length+1, other.bit_vector.end());
    b_mantissa.insert(b_mantissa.begin(), true);

    vector<bool> a_exponent(this->bit_vector.begin()+1, this->bit_vector.begin()+1+this->exponent_length);
    vector<bool> b_exponent(other.bit_vector.begin()+1, other.bit_vector.begin()+1+other.exponent_length);
    vector<bool> exponent;
    //-------------------------------


    // Match mantissas and set exponent
    //-------------------------------
    int exponent_diff;
    char larger_tmp = larger(a_exponent, b_exponent);
    if(1 == larger_tmp){
        exponent_diff = binaryToInt(binarySubtraction(a_exponent, b_exponent));
        exponent.insert(exponent.end(), a_exponent.begin(), a_exponent.end());
        matchMantissas(&b_mantissa, &a_mantissa, exponent_diff);
    } else if(-1 == larger_tmp){
        exponent_diff = binaryToInt(binarySubtraction(b_exponent, a_exponent));
        exponent.insert(exponent.end(), b_exponent.begin(), b_exponent.end());
        matchMantissas(&a_mantissa, &b_mantissa, exponent_diff);
    } else {
        exponent.insert(exponent.end(), a_exponent.begin(), a_exponent.end());
    }
    //-------------------------------


    // Actual Subtraction
    //-------------------------------
    vector<bool> mantissa;
    larger_tmp = larger(a_mantissa, b_mantissa);
    if(1 == larger_tmp){
        mantissa = binarySubtraction(a_mantissa, b_mantissa);
    } else if(-1 == larger_tmp){
        mantissa = binarySubtraction(b_mantissa, a_mantissa);
        ret_vector[0] = !ret_vector[0]; // flip sign
    } else {
        ret.setZero();
        return ret;
    }
    //-------------------------------


    // Adjust mantissa and exponent
    //-------------------------------
    int exponent_shift = 0;
    for(int i = 0; i < (int) mantissa.size(); i++){
        if(mantissa[i]){
            exponent_shift = i;
            break;
        }
    }

    mantissa.erase(mantissa.begin(), mantissa.begin()+exponent_shift+1);
    vector<bool> exponent_shift_binary = intToBinary(exponent_shift);
    for(int i = (int) exponent_shift_binary.size(); i < ret.exponent_length; i++){
        exponent_shift_binary.insert(exponent_shift_binary.begin(), false);
    }
    exponent = binarySubtraction(exponent, exponent_shift_binary);
    //-------------------------------


    round(&mantissa, ret.mantissa_length);
    /*
    // rounding
    //-------------------------------
    if((int) mantissa.size() > ret.mantissa_length){
        bool tmp = false;
        for(int i = ret.mantissa_length+1 ; i < (int) mantissa.size(); i++){
            if (mantissa[i]){
                tmp = true;
                break;
            }
        }
        if(mantissa[ret.mantissa_length] && tmp){
            mantissa.erase(mantissa.end()-((int) mantissa.size()-ret.mantissa_length), mantissa.end());
            if(addOneToBinary(&mantissa)){
                addOneToBinary(&exponent);
            }
        } else if(mantissa[ret.mantissa_length]){
            if(mantissa[ret.mantissa_length-1]){
                mantissa.erase(mantissa.end()-((int) mantissa.size()-ret.mantissa_length), mantissa.end());
                if(addOneToBinary(&mantissa)){
                    addOneToBinary(&exponent);
                }
            } else {
                mantissa.erase(mantissa.end()-((int) mantissa.size()-ret.mantissa_length), mantissa.end());
            }
        }else {
            mantissa.erase(mantissa.end()-((int) mantissa.size()-ret.mantissa_length), mantissa.end());
        }
    }

    //-------------------------------
*/

    // set everything together.
    //-------------------------------
    ret_vector.insert(ret_vector.end(), exponent.begin(), exponent.end());
    ret_vector.insert(ret_vector.end(), mantissa.begin(), mantissa.end());
    //-------------------------------

    return ret;
}

mps mps::operator*(mps& other){

    // Set up the return object.
    //-------------------------------
    mps ret;
    vector<bool>& ret_vector = ret.bit_vector;
    ret.exponent_length = this->exponent_length;
    ret.mantissa_length = this->mantissa_length;
    //-------------------------------


    // Set up sign.
    //-------------------------------
    if(this->bit_vector[0] == other.bit_vector[0]){
        ret_vector.push_back(false);
    } else {
        ret_vector.push_back(true);
    }
    //-------------------------------




    vector<bool> A(this->bit_vector.begin()+exponent_length+1, this->bit_vector.end());
    vector<bool> S;

    A.reserve((int) A.size() + other.bit_vector.size() + 1 +2 +2);
    A.insert(A.begin(), true);
    A.insert(A.begin(), false);
    S.reserve((int) A.size() + other.bit_vector.size() + 1 +2 +2);

    for(int i = 0; i < (int) A.size(); i++){
        S.push_back(!A[i]);
    }
    addOneToBinary(&S);

    for(int i = 0; i < other.mantissa_length + 1 +1 +1; i++){
        A.push_back(false);
        S.push_back(false);
    }

    vector<bool> P;
    P.reserve((int) A.size() + other.bit_vector.size() + 1 +2 +2);
    for(int i = 0; i < this->mantissa_length+1+1; i++){
        P.push_back(false);
    }
    P.push_back(false);
    P.push_back(true);
    for(int i = 0; i < other.mantissa_length; i++){
       P.push_back(other.bit_vector[i+1+other.exponent_length]);
    }
    P.push_back(false);


    for(int i = 0; i < other.mantissa_length+2; i++){


        if(!P.end()[-2] && P.back()){
            P = binaryAddition(P, A, false);
        } else if(P.end()[-2] && !P.back()) {
            P = binaryAddition(P, S, false);
        }

        P.pop_back();
        P.insert(P.begin(), P[0]);

    }

    P.pop_back();
    P.erase (P.begin());
    int count = 0;
    for(int i = 0; i < (int) P.size(); i++){
        if(P[0]){
            P.erase(P.begin());
            break;
        }
        P.erase(P.begin());
        count++;
    }


    round(&P, ret.mantissa_length);

    /*
    // rounding
    //-------------------------------
    if((int) P.size() > ret.mantissa_length){
        bool tmp = false;
        for(int i = ret.mantissa_length+1 ; i < (int) P.size(); i++){
            if (P[i]){
                tmp = true;
                break;
            }
        }
        if(P[ret.mantissa_length] && tmp){
            P.erase(P.end()-((int) P.size()-ret.mantissa_length), P.end());
            if(addOneToBinary(&P)){
                addOneToBinary(&P);
            }
        } else if(P[ret.mantissa_length]){
            if(P[ret.mantissa_length-1]){
                P.erase(P.end()-((int) P.size()-ret.mantissa_length), P.end());
                if(addOneToBinary(&P)){
                    addOneToBinary(&P);
                }
            } else {
                P.erase(P.end()-((int) P.size()-ret.mantissa_length), P.end());
            }
        }else {
            P.erase(P.end()-((int) P.size()-ret.mantissa_length), P.end());
        }
    }
    //-------------------------------
*/



    vector<bool> a_exponent(this->bit_vector.begin()+1, this->bit_vector.begin()+1+this->exponent_length);
    vector<bool> b_exponent(other.bit_vector.begin()+1, other.bit_vector.begin()+1+other.exponent_length);

    // TODO: Check for carry
    b_exponent[0] = !b_exponent[0];
    addOneToBinary(&b_exponent);
    if(count <= 1){
        addOneToBinary(&b_exponent);
    }
    vector<bool> exponent = binaryAddition(a_exponent, b_exponent, false);



    // set everything together.
    //-------------------------------
    ret_vector.insert(ret_vector.end(), exponent.begin(), exponent.end());
    ret_vector.insert(ret_vector.end(), P.begin(), P.end());
    //-------------------------------


    return ret;
}
//-------------------------------


// helper methods
//-------------------------------

/**
 * Sets the bit vector of the mps object.
 *
 * @param value the value to which the bit array should be set.
 */
void mps::setBitArray(double value) {


    // Handle special values.
    //-------------------------------
    if(0 == value){
        setZero(); return;
    } else if(numeric_limits<double>::infinity() == value) {
        setInf(); return;
    } else if (numeric_limits<double>::infinity() * -1 == value){
        setInf(true); return;
    } else if (isnan(value)){
        setNaN(); return;
    }
    //-------------------------------


    // prepare bit_vector
    //-------------------------------
    bit_vector.erase(bit_vector.begin(),bit_vector.end());
    //-------------------------------


    // exponent
    //-------------------------------
    // calculate the exponent
    int mantissa_shift;
    if(abs(value) > numeric_limits<float>::max()){
        // When the value is too large rounding problems occur using log2.
        // (At least I think that is the problem)
        double tmp_value = abs(value);
        int tmp_count = 0;

        while(tmp_value > 1){
            tmp_value /= 2;
            tmp_count++;
        }

        mantissa_shift = tmp_count-1;
    } else {
        mantissa_shift = floor(log2(abs(value)));
    }
    int exponent_int =  mantissa_shift + getBias();

    // Getting the exponent in binary format.
    // The sign is not relevant. Always returns a "positive" value.
    vector<bool> exponent;
    for(int i = abs(exponent_int); i > 0; i /= 2){
        exponent.insert(exponent.begin(), i%2);
    }

    // Fill not used but available bits with zero.
    if((int) exponent.size() > exponent_length) {
        cout << "ERROR: exponent too large" << endl;
        // TODO: add proper error handling.
    } else {
        for(int i = (int) exponent.size(); i < exponent_length; i++){
            exponent.insert(exponent.begin(), false);
        }
    }
    //-------------------------------


    // mantissa
    //-------------------------------
    value = value / pow(2, mantissa_shift); // adjust the value so that everything is behind the decimal point.

    // Convert the part after the decimal point to a bit string.
    // The sign is not relevant. Always returns a "positive" value.
    vector<bool> mantissa;
    double reminder = abs(value) - floor(abs(value));
    for(int i = 0; i < mantissa_length; i++){

        reminder *= 2;
        if(reminder >= 1){
            mantissa.push_back(true); reminder -= 1;
        } else{
            mantissa.push_back(false);
        }
    }
    //-------------------------------


    // set everything together
    //-------------------------------
    if(value > 0){
        bit_vector.push_back(false);
    } else {
        bit_vector.push_back(true);
    }

    bit_vector.insert(bit_vector.end(), exponent.begin(), exponent.end());
    bit_vector.insert(bit_vector.end(), mantissa.begin(), mantissa.end());
    //-------------------------------

}

/**
 * Returns the bias of the exponent.
 *
 * @return bias of the exponent
 */
int mps::getBias() const{
    return ((int) pow (2, exponent_length)) / 2 -1;
}


/**
 * Performs a binary addition using a full adder.
 * The binary numbers are represented as vector containing booleans.
 *
 * @param a reference to the first addend
 * @param b reference to the second addend
 * @param carry set to true if an adjustment is wanted when the carrier bit of the last iteration is 1
 * @param carrier_return pointer to a boolean where the last state of the carrier bit can be save
 * @return the result as binary number.
 */
vector<bool> mps::binaryAddition(vector<bool>& a, vector<bool>& b, bool carry, bool* carrier_return){

    vector<bool> ret;
    bool carrier = false;

    //TODO: Remove when finished.
    if(a.size() != b.size()){
        cout << "ERROR: binary addition vectors must have same length" << endl;
        return ret;
    }

    // full adder
    for(int i = (int) a.size()-1; i >= 0; i--){
        ret.insert(ret.begin(), (a[i] ^ b[i]) ^ carrier);
        carrier = ((a[i] && b[i]) || (a[i] && carrier)) || (b[i] && carrier);
    }

    // adjust if carrier bit is 1
    if(carry && carrier){
        ret.insert(ret.begin(), true);
        ret.pop_back();
    }

    // save the state of the carrier bit in carrier_return.
    if(carrier_return != nullptr){
        *carrier_return = carrier;
    }

    return ret;
}

/**
 * Performs a binary subtraction.
 * The binary numbers are represented as vector containing booleans.
 *
 * @param minuend reference to the vector which should be reduced
 * @param subtrahend reference to the vector which should be subtracted.
 * @return the result as a binary number.
 */
vector<bool> mps::binarySubtraction(vector<bool>& minuend, vector<bool> subtrahend){

    // invert
    for(auto && i : subtrahend){
        i = !i;
    }

    // add one
    if(addOneToBinary(&subtrahend)){
        return minuend; // if there is a carrier bit present at the end the subtrahend is zero.
    }

    return binaryAddition(minuend, subtrahend, false);
}

/**
 * Performs the rounding of the mantissa according to IEEE754.
 *
 * @param mantissa Pointer to the mantissa which should be rounded.
 * @param mantissa_len The length to which the mantissa should be rounded.
 */
void mps::round(vector<bool> *mantissa, int mantissa_len) {

    if((int) mantissa->size() > mantissa_len){
        bool tmp = false;
        for(int i = mantissa_len+1 ; i < (int) mantissa->size(); i++){
            if ((*mantissa)[i]){
                tmp = true;
                break;
            }
        }
        if((*mantissa)[mantissa_len] && tmp){
            mantissa->erase(mantissa->end()-((int) mantissa->size()-mantissa_len), mantissa->end());
            if(addOneToBinary(mantissa)){
                addOneToBinary(mantissa);
            }
        } else if((*mantissa)[mantissa_len]){
            if((*mantissa)[mantissa_len-1]){
                mantissa->erase(mantissa->end()-((int) mantissa->size()-mantissa_len), mantissa->end());
                if(addOneToBinary(mantissa)){
                    addOneToBinary( mantissa);
                }
            } else {
                mantissa->erase(mantissa->end()-((int) mantissa->size()-mantissa_len), mantissa->end());
            }
        }else {
            mantissa->erase(mantissa->end()-((int) mantissa->size()-mantissa_len), mantissa->end());
        }
    }
}


/**
 * Converts a binary number to an integer.
 * The binary number is stored in a vector of booleans.
 *
 * @param vector vector containing the binary number
 * @return the binary number as integer
 */
int mps::binaryToInt(vector<bool> vector){

    int ret = 0;

    for(int i = 0; i < (int) vector.size(); i++){
        if(vector[vector.size()-i-1]){
            ret += (int) pow(2,i);
        }
    }

    return ret;
}

/**
 * Converts an integer to a binary number.
 * The binary number is stored in a vector of booleans.
 *
 * @param value the value of the integer.
 * @return the value as binary number.
 */
vector<bool> mps::intToBinary(unsigned int value) {

    vector<bool> ret;

    while (value >= 1){
        ret.insert(ret.begin(), value%2);
        value /= 2;
    }

    return ret;
}

/**
 * To be read: Is the bit value a represents larger than the one of b.
 * 1 if a > b
 * 0 if a == b
 * -1 if a < b
 *
 * Only works for vectors of same size.
 *
 * @param a reference to the vector containing the first binary number
 * @param b reference to the vector containing the second binary number
 * @return 1 if a > b, 0 if a == b, -1 if a < b
 */
char mps::larger(vector<bool>& a, vector<bool>& b){

    // TODO: Remove at the end.
    if(a.size() != b.size()){
        cout << "ERROR: larger: not same size" << endl;
    }

    for(int i = 0; i < (int) a.size(); i++){
        if(a[i] && !b[i]) { return 1;}
        else if(b[i] && !a[i]) {return -1;}
    }
    return 0;
}

/**
 * Aligns two bit vectors about an amount.
 * The amount is the number so that after the operation the two bit vectors align and have the same exponent.
 *
 * The vectors are not really shifted but zeros are added either to the left or the right.
 * Therefore the size of both vectors is increased by the amount both are "shifted".
 *
 * @param vector_right_shift pointer to the vector which should be "shifted" to the right
 * @param vector_left_shift pointer to the vector which should be "shifted" to the left
 * @param amount amount the two vectors should be "shifted"
 */
void mps::matchMantissas(vector<bool>* vector_right_shift, vector<bool>* vector_left_shift, int amount){

    for(int i = 0; i < amount; i++){
        vector_right_shift->insert(vector_right_shift->begin(), false);
        vector_left_shift->insert(vector_left_shift->end(), false);
    }
}

/**
 * Adds one to a binary number saved inside a vector.
 * The vector consists of booleans which represents a binary number.
 *
 * If a carrier bit is present in the last iteration a "one" is added at the beginning
 * and the last element is erased.
 *
 * @param vector pointer to the vector containing the binary number where one should be added
 * @return true if a carrier bit was present in the last iteration, false otherwise
 */
bool mps::addOneToBinary(vector<bool>* vector){

    for(int i = (int) vector->size() - 1; i >= 0; i--){
        (*vector)[i] = !(*vector)[i];
        if((*vector)[i]){
            return false;
        }
    }

    vector->insert(vector->begin(), true);
    vector->pop_back();
    return true;
}
//-------------------------------