#include "mps.h"
#include <iostream>
#include <algorithm>

#include <sstream>

// constructors and destructor
//-------------------------------

/**
 * Constructor for a multiprecision simulator object using values.
 *
 * @param mantissa_length Mantisse of the floating point representation
 * @param exponent_length Exponent of the floating point representation
 * @param value Value of the floating point number
 */
mps::mps(unsigned long mantissa_length, unsigned long exponent_length, double value) {

    // check input values
    //-------------------------------
    if (mantissa_length <= 0) {
        throw std::invalid_argument("ERROR: in constructor : mantissa size too small");
    }
    if (exponent_length <= 1) {
        throw std::invalid_argument("ERROR: in constructor : exponent size too small");
    }
    //-------------------------------

    this->mantissa_length = mantissa_length;
    this->exponent_length = exponent_length;

    this->exponent.resize(this->exponent_length);
    this->mantissa.resize(this->mantissa_length);

    this->sign = false;

    this->setValue(value);
}

/**
 * Constructor for a multiprecision simulator object. The value is set to NAN.
 * Info: Having the value set to NAN is probably not necessary, but it may prevent errors because of false use.
 *
 * @param mantissa_length Mantisse of the floating point representation
 * @param exponent_length Exponent of the floating point representation
 */
mps::mps(unsigned long mantissa_length, unsigned long exponent_length) {

    // check input values
    //-------------------------------
    if (mantissa_length <= 0) {
        throw std::invalid_argument("ERROR: in constructor : mantissa size too small");
    }
    if (exponent_length <= 1) {
        throw std::invalid_argument("ERROR: in constructor : exponent size too small");
    }
    //-------------------------------

    this->mantissa_length = mantissa_length;
    this->exponent_length = exponent_length;

    this->exponent.resize(this->exponent_length);
    this->mantissa.resize(this->mantissa_length);

    this->sign = false;

    this->setNaN();     // Set it to be safe.
}

/**
 * Constructor for an empty multiprecision simulator object.
 */
mps::mps(){
    this->mantissa_length = 0;
    this->exponent_length = 0;

    this->sign = false;
}

/**
 * Destructor for a multiprecision simulator object.
 */
mps::~mps() = default;
//-------------------------------


// getter methods
//-------------------------------

/**
 * Returns the sign.
 *
 * @return the sign
 */
[[nodiscard]] bool mps::getSign() const{
    return this->sign;
}

/**
 * Returns the mantissa.
 *
 * @return the mantissa
 */
[[nodiscard]] vector<bool> mps::getMantissa() const{
    return this->mantissa;
}

/**
 * Returns the exponent.
 *
 * @return the mantissa
 */
[[nodiscard]] vector<bool> mps::getExponent() const{
    return this->exponent;
}

/**
 * Returns the length of the mantissa.
 *
 * @return length of the mantissa
 */
unsigned long mps::getMantisseLength() const {
    return this->mantissa_length;
}

/**
 * Returns the length of the exponent.
 *
 * @return length of the exponent
 */
unsigned long mps::getExponentLength() const {
    return this->exponent_length;
}

/**
 * Returns the length of the whole bit array.
 * Info: bit array = sign + matisse + exponent
 *
 * @return length of the total bit array
 */
unsigned long mps::getBitArrayLength() const {
    return this->exponent.size() + this->mantissa.size() + 1;
}

/**
 * Concatenates the sign bit with the exponent vector and the mantissa vector.
 * The resulting vector represents the floating point number in memory.
 * Info: bit array = sign + matisse + exponent
 *
 * @return vector representing the floating point number
 */
vector<bool> mps::getBitArray() const {

    vector<bool> ret;
    ret.reserve(1 + this->exponent_length + this->mantissa_length);

    ret.push_back(this->sign);
    ret.insert(ret.end(), this->exponent.begin(), this->exponent.end());
    ret.insert(ret.end(), this->mantissa.begin(), this->mantissa.end());

    return ret;
}

/**
 * Calculates the value of the floating point object as double.
 *
 * @return value as double
 */
double mps::getValue() const {

    // handle special cases
    if(isZero()){
        return 0;
    } else if (isInf() && isPositive()){
        return numeric_limits<double>::infinity();
    } else if (isInf()){
        return numeric_limits<double>::infinity() * -1;
    } else if (isNaN()){
        return numeric_limits<double>::quiet_NaN();
    }


    double ret;

    // positive or negative
    if(this->sign){
        ret = -1;
    } else {
        ret = 1;
    }

    // handle mantissa
    for(unsigned long i = 0; i < mantissa_length; i++){
        if(mantissa[i]){
            if(ret >= 0){
                ret += pow(0.5, i + 1);
            } else {
                ret -= pow(0.5, i + 1);
            }
        }
    }

    // get exponent
    long exp = 0;
    for(unsigned long i = 0; i < exponent_length; i++){
        if(this->exponent[i]){
            exp += (long) pow(2, exponent_length-i-1);
        }
    }

    // apply bias and apply exponent
    exp -= getBias();

    return ret * pow(2, exp);
}


/**
 * Returns true if the mps object is zero.
 * The sign bit is irrelevant.
 *
 * @return true if zero
 */
bool mps::isZero() const{

    for(unsigned long i = 0; i < this->exponent_length; i++){
        if(this->exponent[i]){
            return false;
        }
    }

    for(unsigned long i = 0; i < this->mantissa_length; i++){
        if(this->mantissa[i]){
            return false;
        }
    }

    return true;
}

/**
 * Returns true if the mps object is positive or negative infinity.
 *
 * @return true if pos. or neg. infinity
 */
bool mps::isInf() const{


    for(unsigned long i = 0; i < this->exponent_length; i++){
        if(!this->exponent[i]){
            return false;
        }
    }

    for(unsigned long i = 0; i < this->mantissa_length; i++){
        if(this->mantissa[i]){
            return false;
        }
    }

    return true;
}

/**
 * Returns true if the mps object is positive.
 *
 * @return true if positive
 */
bool mps::isPositive() const{

    if(this->sign){
        return false;
    } else {
        return true;
    }
}

/**
 * Returns true if the mps object represents a NaN value.
 * The sign bit is irrelevant since some implementations differ between -NaN and +NaN.
 *
 * @return true if NaN
 */
bool mps::isNaN() const{

    for(unsigned long i = 0; i < exponent_length; i++){

        if(!exponent[i]){
            return false;
        }
    }

    if(!mantissa[0]){
        return false;
    }

    for(unsigned long i = 1; i < mantissa_length; i++){

        if(mantissa[i]){
            return false;
        }
    }

    return true ;
}

/**
 * Returns a string that represents the floating point number as a bit array.
 * Info: bit array = sign + matisse + exponent
 *
 * @return the FPN as a string consisting of 1s and 0s
 */
std::string mps::print() const {

    std::string str;
    for(bool bit : this->getBitArray()){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    return str;
}

/**
 * Returns the (double) value of the mps object as a string instead of a double.
 *
 * @return the value as a string
 */
std::string mps::toString(const int precision) const {

    if(precision < 0){
        return std::to_string(this->getValue());
    } else {
        std::ostringstream out;
        out.precision(precision);
        out << std::fixed << this->getValue();
        return std::move(out).str();
    }
}
//-------------------------------


// precision
//-------------------------------
/**
 * Compares the mantissa of two mps objects up to a specified precision.
 * So if the two mantissas are different of a magnitude smaller than the precision specified, the function returns true.
 *
 *
 * The two mps objects must have the same mantissa length and exponent length.
 *
 * @param compare the mps object to which "this" mps object should be compared to
 * @param precision up to which precision the mps objects should be compared
 * @return true if the mps objects are the same up to the given accuracy
 */
[[nodiscard]] bool mps::checkPrecision(const mps& compare, unsigned long precision) const {

    vector<bool> max_error_exponent;
    max_error_exponent.reserve(this->exponent_length);
    for(auto i = precision; i > 0; i /= 2){
        max_error_exponent.insert(max_error_exponent.begin(), i % 2);
    }
    for(auto i = max_error_exponent.size(); i < this->exponent_length; i++){
        max_error_exponent.insert(max_error_exponent.begin(), false);
    }

    addOneToBinary(&max_error_exponent);
    max_error_exponent = binarySubtraction(compare.exponent, max_error_exponent);


    mps max_error = mps(this->mantissa_length, this->exponent_length);
    max_error.setZero(false);

    if(not max_error_exponent[0]){ // if overflow happened
        max_error.setExponent(max_error_exponent);
    } else {
        cout << "WARNING: checkPrecision: value to small to check precision properly!\n";
        max_error_exponent.resize(this->exponent_length, false);
        max_error_exponent.back() = true;
    }

    auto diff = *this - compare;
    diff.setSign(false);

    if(diff <= max_error){
        return true;
    } else {
        return false;
    }
}

/**
 * Gets the precision of two mps objects.
 * A high level definition of the precision is the number of matching mantissa bits from left to right.
 * However, this is not a completely correct definition.
 *
 * Prints a WARNING when NaNs or Infinities are involved except if both mps objects are the same.
 *
 * Throws Exception:    When the mantissas do not match.
 *                      When the exponents do not match.
 *
 * @param compare the mps object which which this mps object should be compared
 * @return the matching mantissa bits
 */
[[nodiscard]] long long int mps::getPrecision(const mps& compare) const {

    if (this->exponent_length != compare.exponent_length) {
        throw std::invalid_argument("ERROR: in getPrecision : Exponents do not match");
    }
    if (this->mantissa_length != compare.mantissa_length) {
        throw std::invalid_argument("ERROR: in getPrecision : Mantissas do not match");
    }

    if(this->isNaN() && compare.isNaN()){
        return (long long) compare.mantissa_length;
    } else if(this->isNaN() || compare.isNaN()){
        cout << "WARNING: getPrecision: one value is NaN => returning max negative value\n";
        return numeric_limits<long long>::max() * -1;
    }

    if(this->isInf() && compare.isInf() && (this->isPositive() == compare.isPositive())){
        return (long long) compare.mantissa_length;
    } else if(this->isInf() || compare.isInf()){
        cout << "WARNING: getPrecision: one value is infinity => returning max negative value\n";
        return numeric_limits<long long>::max() * -1;
    }

    auto exponent_this = (long long) binaryToInt(this->exponent);
    auto exponent_compare = (long long) binaryToInt(compare.exponent);

    long long precision_error = 0;

    if(exponent_this == exponent_compare){

        auto mantissa_this = (long long) binaryToInt(this->mantissa);
        auto mantissa_compare = (long long) binaryToInt(compare.mantissa);

        if(mantissa_this == mantissa_compare){
            return (long long) compare.mantissa_length;
        }

        precision_error = (long long) floor(log2(abs(mantissa_this - mantissa_compare))) + 1;


    } else if (1 == exponent_this - exponent_compare){

        auto copy_this = this->mantissa;
        copy_this.insert(copy_this.begin(), true);

        auto copy_compare = compare.mantissa;
        copy_compare.insert(copy_compare.begin(), {false, true});
        copy_compare.pop_back();

        auto mantissa_compare = (long long) binaryToInt(copy_compare);
        auto mantissa_this = (long long) binaryToInt(copy_this);

        precision_error = (long long) floor(log2(abs(mantissa_this - mantissa_compare))) + 1;

    } else if(1 == exponent_compare - exponent_this) {

        auto copy_compare = compare.mantissa;
        copy_compare.insert(copy_compare.begin(), true);

        auto copy_this = this->mantissa;
        copy_this.insert(copy_this.begin(), {false, true});
        copy_this.pop_back();

        auto mantissa_compare = (long long) binaryToInt(copy_compare);
        auto mantissa_this = (long long) binaryToInt(copy_this);

        precision_error = (long long) floor(log2(abs(mantissa_this - mantissa_compare))) + 1;

    } else {

        if(exponent_compare > exponent_this){
            return 0;
        } else {

            auto difference = abs(exponent_compare - exponent_this);

            for(unsigned long i = 0; i < (unsigned long) difference; i++){
                if(this->mantissa[i]){
                    difference++;
                    break;
                }
            }

            return difference * -1;
        }
    }

    return ((long long) compare.mantissa_length) - precision_error;
}

/**
 * Calculates the absolute error between two mps objects using operators from the mps class.
 *
 * @param compare the mps object to which "this" mps object should be compared to
 * @return the absolute error
 */
[[nodiscard]] mps mps::getAbsoluteError(const mps& compare) const{

    auto ret = compare - *this;
    ret.setSign(false);

    return ret;
}

/**
 * Calculates the relative error between two mps objects using operators from the mps class.
 *
 * @param compare the mps object to which "this" mps object should be compared to
 * @return the relative error
 */
[[nodiscard]] mps mps::getRelativeError(const mps& compare) const {

    auto ret = this->getAbsoluteError(compare) / compare;
    ret.setSign(false);

    return ret;
}

/**
 * Calculates the absolute error between two mps objects using the built-in operators for double.
 *
 * @param compare the mps object to which "this" mps object should be compared to
 * @return the absolute error
 */
[[nodiscard]] double mps::getAbsoluteError_double(const mps& compare) const {

    auto is = this->getValue();
    auto should = compare.getValue();

    return abs(is-should);
}

/**
 * Calculates the relative error between two mps objects using the built-in operators for double.
 *
 * @param compare the mps object to which "this" mps object should be compared to
 * @return the relative error
 */
[[nodiscard]] double mps::getRelativeError_double(const mps& compare) const {

    auto is = this->getValue();
    auto should = compare.getValue();

    return abs(is-should) / abs(should);
}

/**
 * Calculates the absolute error between one mps object and a double value using the built-in operators for double.
 *
 * @param compare the mps object to which "this" mps object should be compared to
 * @return the absolute error
 */
[[nodiscard]] double mps::getAbsoluteError_double(const double& compare) const {

    auto is = this->getValue();
    return abs(is-compare);
}

/**
 * Calculates the relative error between one mps object and a double value using the built-in operators for double.
 *
 * @param compare the mps object to which "this" mps object should be compared to
 * @return the relative error
 */
[[nodiscard]] double mps::getRelativeError_double(const double& compare) const {

    auto is = this->getValue();
    return abs(is-compare) / abs(compare);
}
//-------------------------------


// setter methods
//-------------------------------

/**
 * Sets the floating point number to infinity.
 *
 * @param negative set to true for negative infinity (default false)
 */
void mps::setInf(bool negative) {

    if( exponent.empty() || mantissa.empty()){
        exponent.resize(exponent_length);
        mantissa.resize(exponent_length);
    }

    if(negative){
        sign = true;
    } else {
        sign = false;
    }

    for(unsigned long i = 0; i < exponent_length; i++){
        exponent[i] = true;
    }

    for(unsigned long i = 0; i < mantissa_length; i++){
        mantissa[i] = false;
    }
}

/**
 * Sets the floating point number to zero.
 *
 * @param negative set to true for negative zero (default false)
 */
void mps::setZero(bool negative){

    if( (exponent.size() != this->exponent_length) || (mantissa.size() != this->mantissa_length)){
        exponent.resize(exponent_length);
        mantissa.resize(mantissa_length);
    }

    sign = negative;

    for(unsigned long i = 0; i < exponent_length; i++){
        exponent[i] = false;
    }
    for(unsigned long i = 0; i < mantissa_length; i++){
        mantissa[i] = false;
    }
}

/**
 * Sets the floating point number to NaN (not a number)
 *
 * The sign bit can be set individually using the parameter.
 *
 * @param negative sets the sign bit of the NaN value
 */
void mps::setNaN(bool negative){

    if( exponent.empty() || mantissa.empty()){
        exponent.resize(exponent_length);
        mantissa.resize(exponent_length);
    }

    if(negative){
        sign = true;
    } else {
        sign = false;
    }

    for(unsigned long i = 0; i < exponent_length; i++){
        exponent[i] = true;
    }

    mantissa[0] = true;
    for(unsigned long i = 1; i < mantissa_length; i++){
        mantissa[i] = false;
    }
}

/**
 * Sets the sign bit of the mps object to a new value.
 *
 * @param negative the value to which the sign bit should be set (true for negative)
 */
void mps::setSign(bool negative){
    this->sign = negative;
}

/**
 * Sets the mantissa to a new mantissa.
 *
 * Throws Exception:    When mantissa sizes do not match.
 *
 * @param new_mantissa the vector to which the mantissa should be set
 */
void mps::setMantissa(vector<bool>& new_mantissa){

    if(new_mantissa.size() != this->mantissa.size()){
        throw std::invalid_argument("ERROR: in setMantissa: New mantissa has wrong size.");
    }

    for(unsigned long i = 0; i < new_mantissa.size(); i++){
        this->mantissa[i] = new_mantissa[i];
    }
}

/**
 * Sets the exponent to a new exponent.
 *
 * Throws Exception:    When exponent sizes do not match.
 *
 * @param new_mantissa the vector to which the mantissa should be set
 */
void mps::setExponent(vector<bool>& new_exponent){

    if(new_exponent.size() != this->exponent.size()){
        throw std::invalid_argument("ERROR: in setExponent: New exponent has wrong size.");
    }

    for(unsigned long i = 0; i < new_exponent.size(); i++){
        this->exponent[i] = new_exponent[i];
    }
}
//-------------------------------


// cast
//-------------------------------
/**
 * Casts the mps object to a new size.
 *
 * If the size is larger than before, the value is not changed, and the new elements are just filled with the
 * appropriate values. If the new size is smaller, the value is rounded to be accurate for this new size.
 * If needed, the object will be set to a special value.
 *
 * Info: Does check for correct input and special values.
 *
 * @param new_mantissa_size the new size of the mantissa
 * @param new_exponent_size the new size of the exponent
 * @return the resulting mps object.
 */
void mps::cast(const unsigned long new_mantissa_size, const unsigned long new_exponent_size){


    // check input values
    //-------------------------------
    if (new_mantissa_size <= 0) {
        throw std::invalid_argument("ERROR: in cast : new mantissa size too small");
    }
    if (new_exponent_size <= 1) {
        throw std::invalid_argument("ERROR: in cast : new exponent size too small");
    }
    //-------------------------------


    // handle special values
    //-------------------------------
    if(this->isNaN()){
        this->resize_mps_object(new_mantissa_size, new_exponent_size);
        this->setNaN();
        return;
    } else if(this->isInf()){
        this->resize_mps_object(new_mantissa_size, new_exponent_size);
        this->setInf(this->sign);
        return;
    }
    //-------------------------------


    // rounding of the exponent
    //-------------------------------
    if(new_exponent_size > this->exponent_length){

        if((this->exponent)[0] || this->isZero()){    // positive exponent case

            for(auto i = this->exponent_length; i < new_exponent_size; i++){
                this->exponent.insert(this->exponent.begin()+1, false);
            }

        } else {    // negative exponent case

            for(auto i = this->exponent_length; i < new_exponent_size; i++){
                this->exponent.insert(this->exponent.begin()+1, true);
            }

        }

        this->exponent_length = new_exponent_size;

    } else if(new_exponent_size < this->exponent_length) {


        // check if the exponent is too large or too small
        // ------------------------------------------------------
        if(!this->isZero()) {
            // "normal case"
            auto tmp = this->exponent_length - new_exponent_size + 1;
            for (unsigned long i = 1; i < tmp; i++) {
                if ((this->exponent)[i] == (this->exponent)[0]) {
                    this->resize_mps_object(new_mantissa_size, new_exponent_size);

                    if((this->exponent)[0]){
                        this->setInf();
                    } else {
                        this->setZero();
                    }

                    return;
                }
            }

            // case if new exponent would be all 1's.
            if((this->exponent)[0]) {
                auto tmp_case = true;
                for (auto i = this->exponent_length-1; i > (this->exponent_length - new_exponent_size + 1); i--) {
                    if (!(this->exponent)[i]) {
                        tmp_case = false;
                        continue;
                    }
                }
                if (tmp_case) {
                    this->resize_mps_object(new_mantissa_size, new_exponent_size);
                    this->setInf();
                    return;
                }
            }
        }
        // ------------------------------------------------------


        for(auto i = new_exponent_size; i < this->exponent_length; i++){
            this->exponent.erase(this->exponent.begin()+1);
        }

        this->exponent_length = new_exponent_size;
        //-------------------------------
    }


    // rounding of the mantissa
    //-------------------------------
    if(new_mantissa_size > this->mantissa_length){

        for(unsigned long i = this->mantissa_length; i < new_mantissa_size; i++){
            this->mantissa.push_back(false);
        }
        this->mantissa_length = new_mantissa_size;

    } else if(new_mantissa_size < this->mantissa_length) {

        round(&(this->mantissa), new_mantissa_size);
        this->mantissa_length = new_mantissa_size;
    }
    //-------------------------------
}

/**
 * Resizes the mps object to the a new size. It does not care for the value of the object
 * but sets the size of the vectors and the value of the variables containing the sizes.
 * Info: Does not check for correct input.
 *
 * @param new_mantissa_size the new size of the mantissa
 * @param new_exponent_size the new size of the exponent
 */
void mps::resize_mps_object(const unsigned long new_mantissa_size, const unsigned long new_exponent_size){

    if(new_mantissa_size > this->mantissa_length){
        for(auto i = this->mantissa_length; i < new_mantissa_size; i++){
            this->mantissa.push_back(false);
        }
    } else if(new_mantissa_size < this->mantissa_length){
        for(auto i = new_mantissa_size; i < this->mantissa_length; i++){
            this->mantissa.pop_back();
        }
    }

    if(new_exponent_size > this->exponent_length){
        for(auto i = this->exponent_length; i < new_exponent_size; i++){
            this->exponent.push_back(false);
        }
    } else if(new_exponent_size < this->exponent_length){
        for(auto i = new_exponent_size; i < this->exponent_length; i++){
            this->exponent.pop_back();
        }
    }

    this->mantissa_length = new_mantissa_size;
    this->exponent_length = new_exponent_size;
}
//-------------------------------


// operators
//-------------------------------

/**
 * Sets the value of the mps object.
 */
mps& mps::operator=(double value){

    this->setValue(value);
    return *this;
}

/**
 * Sets one mps object equal to another mps object.
 */
mps& mps::operator=(const mps& other) {

    if (this == &other){
        return *this;
    }

    if (this->exponent_length != other.exponent_length) {
        throw std::invalid_argument("ERROR: in = : Exponents do not match");
    }
    if (this->mantissa_length != other.mantissa_length) {
        throw std::invalid_argument("ERROR: in = : Mantissas do not match");
    }

    this->sign = other.sign;
    for(unsigned long i = 0; i < this->mantissa_length; i++){
        this->mantissa[i] = other.mantissa[i];
    }
    for(unsigned long i = 0; i < this->exponent_length; i++){
        this->exponent[i] = other.exponent[i];
    }

    return *this;
}

/**
 * Sets one mps object equal to another mps object.
 *
 * If the mantissas or the exponents do not match, this operator does not throw an exception
 * but reformats the object instead.
 *
 * This operator should be used with caution since, in this way, implicit casts are possible.
 */
mps& mps::operator|=(const mps& other) {

    if (this == &other){
        return *this;
    }

    if (this->exponent_length != other.exponent_length) {
        this->exponent_length = other.exponent_length;
        this->exponent.resize(this->exponent_length);
    }
    if (this->mantissa_length != other.mantissa_length) {
        this->mantissa_length = other.mantissa_length;
        this->mantissa.resize(this->mantissa_length);
    }

    this->sign = other.sign;
    for(unsigned long i = 0; i < this->mantissa_length; i++){
        this->mantissa[i] = other.mantissa[i];
    }
    for(unsigned long i = 0; i < this->exponent_length; i++){
        this->exponent[i] = other.exponent[i];
    }

    return *this;
}

/**
 * Performs an addition of two mps floating point values.
 *
 * It is responsible for special values and choosing which "calculation" to use.
 *
 * Throws Exception:    When the mantissas do not match.
 *                      When the exponents do not match.
 */
mps mps::operator+(const mps& other) const {

    if (this->exponent_length != other.exponent_length) {
        throw std::invalid_argument("ERROR: in + : Exponents do not match");
    }
    if (this->mantissa_length != other.mantissa_length) {
        throw std::invalid_argument("ERROR: in + : Mantissas do not match");
    }


    if(this->isNaN() || other.isNaN()){

        mps ret(this->mantissa_length, this->exponent_length);
        ret.setNaN();
        return ret;

    } else if(this->isInf() && other.isInf()){
        mps ret(this->mantissa_length, this->exponent_length);

        if(this->isPositive() == other.isPositive()){
            ret.setInf(!this->isPositive());
        } else {
            ret.setNaN();
        }

        return ret;
    } else if(this->isInf()){

        mps ret(this->mantissa_length, this->exponent_length);
        ret.setInf(!this->isPositive());
        return ret;

    } else if(other.isInf()){

        mps ret(other.mantissa_length, other.exponent_length);
        ret.setInf(!other.isPositive());
        return ret;

    } else if(this->isZero()){
        return other;
    } else if(other.isZero()){
        return *this;
    }


    if(this->isPositive() && other.isPositive()){
        return addition(*this, other, false);
    } else if(!this->isPositive() && !other.isPositive()){
        return addition(*this, other, true);
    } else if(!this->isPositive()){
        return subtraction(other, *this, false);
    } else{
        return subtraction(*this, other, false);
    }

}

/**
 * Performs a subtraction of two mps floating point values.
 *
 * It is responsible for special values and choosing which "calculation" to use.
 *
 * Throws Exception:    When the mantissas do not match.
 *                      When the exponents do not match.
 */
mps mps::operator-(const mps& other) const {

    if (this->exponent_length != other.exponent_length) {
        throw std::invalid_argument("ERROR: in - : Exponents do not match");
    }
    if (this->mantissa_length != other.mantissa_length) {
        throw std::invalid_argument("ERROR: in - : Mantissas do not match");
    }


    if(this->isNaN() || other.isNaN()){

        mps ret(this->mantissa_length, this->exponent_length);
        ret.setNaN();
        return ret;

    } else if(this->isInf() && other.isInf()){
        mps ret(this->mantissa_length, this->exponent_length);

        if(this->isPositive() == other.isPositive()){
            ret.setNaN();
        } else {
            ret.setInf(!this->isPositive());
        }

        return ret;
    } else if(this->isInf()){

        mps ret(this->mantissa_length, this->exponent_length);
        ret.setInf(!this->isPositive());
        return ret;

    } else if(other.isInf()){

        mps ret(other.mantissa_length, other.exponent_length);
        ret.setInf(other.isPositive());
        return ret;

    } else if(this->isZero()){
        auto ret = other;
        ret.sign = !ret.sign;
        return ret;
    } else if(other.isZero()){
        return *this;
    }


    if(this->isPositive() && other.isPositive()){
        return subtraction(*this, other, false);
    } else if(!this->isPositive() && !other.isPositive()){
        return subtraction(*this, other, true);
    } else if(this->isPositive()) {
        return addition(*this, other, false);
    } else {
        return addition(*this, other, true);
    }
}

/**
 * Performs a multiplication of two mps floating point values.
 *
 * It is responsible for special values and choosing which "calculation" to use.
 *
 * Throws Exception:    When the mantissas do not match.
 *                      When the exponents do not match.
 */
mps mps::operator*(const mps& other) const {

    if (this->exponent_length != other.exponent_length) {
        throw std::invalid_argument("ERROR: in * : Exponents do not match");
    }
    if (this->mantissa_length != other.mantissa_length) {
        throw std::invalid_argument("ERROR: in * : Mantissas do not match");
    }


    if(this->isNaN() || other.isNaN()){

        mps ret(this->mantissa_length, this->exponent_length);
        ret.setNaN();
        return ret;

    } else if(this->isInf() && other.isInf()){
        mps ret(this->mantissa_length, this->exponent_length);

        if(this->isPositive() == other.isPositive()){
            ret.setNaN();
        } else {
            ret.setInf(!this->isPositive());
        }

        return ret;
    } else if(this->isInf()){

        mps ret(this->mantissa_length, this->exponent_length);
        ret.setInf(!this->isPositive());
        return ret;

    } else if(other.isInf()){

        mps ret(other.mantissa_length, other.exponent_length);
        ret.setInf(!other.isPositive());
        return ret;

    } else if(this->isZero() || other.isZero()){
        mps ret(other.mantissa_length, other.exponent_length);
        ret.setZero();
        return ret;
    }


    return multiplication(*this, other, this->sign != other.sign);
}

/**
 * Performs a division of two mps floating point values.
 *
 * It is responsible for special values and choosing which "calculation" to use.
 *
 * Throws Exception:    When the mantissas do not match.
 *                      When the exponents do not match.
 */
mps mps::operator/(const mps& other) const {

    if (this->exponent_length != other.exponent_length) {
        throw std::invalid_argument("ERROR: in / : Exponents do not match");
    }
    if (this->mantissa_length != other.mantissa_length) {
        throw std::invalid_argument("ERROR: in / : Mantissas do not match");
    }


    if(this->isNaN() || other.isNaN()){

        mps ret(this->mantissa_length, this->exponent_length);
        ret.setNaN();
        return ret;

    } else if(this->isInf() && other.isInf()){
        mps ret(this->mantissa_length, this->exponent_length);

        if(this->isPositive() == other.isPositive()){
            ret.setNaN();
        } else {
            ret.setInf(!this->isPositive());
        }

        return ret;
    } else if(this->isInf()){

        mps ret(this->mantissa_length, this->exponent_length);
        ret.setInf(!this->isPositive());
        return ret;

    } else if(other.isInf()){

        mps ret(other.mantissa_length, other.exponent_length);
        if(this->isPositive() == other.isPositive()){
            ret.setZero();
        } else {
            ret.setZero(true);
        }
        return ret;

    } else if(this->isZero()){
        mps ret(other.mantissa_length, other.exponent_length);
        if(this->isPositive() == other.isPositive()){
            ret.setZero();
        } else {
            ret.setZero(true);
        }
        return ret;
    } else if(other.isZero()){
        mps ret(other.mantissa_length, other.exponent_length);
        ret.setInf(!this->isPositive());
        return ret;
    }


    return division(*this, other, this->sign != other.sign);
}


/**
 * Calculates the binary floating point representation of the given value and saves it inside the mps object.
 *
 * @param value the value to which the bit array should be set
 */
void mps::setValue(const double value) {

    // Handle special values.
    //-------------------------------
    if(0 == value){
        setZero(); return;
    } else if(numeric_limits<double>::infinity() == value) {
        setInf(); return;
    } else if (numeric_limits<double>::infinity() * -1 == value){
        setInf(true); return;
    } else if (isnan(value)){
        if(signbit(value)){
            setNaN(true);
        } else {
            setNaN();
        }
        return;
    }
    //-------------------------------

    // prepare vectors
    //-------------------------------
    exponent.clear();
    mantissa.clear();
    //-------------------------------


    // set sign
    //-------------------------------
    this->sign = value <= 0;
    //-------------------------------


    // exponent
    //-------------------------------
    // calculate the exponent
    long mantissa_shift;
    if(abs(value) > numeric_limits<float>::max()){
        // When the value is too large, rounding problems occur using log2.
        // (At least I think that is the problem)
        double tmp_value = abs(value);
        long tmp_count = 0;

        while(tmp_value >= 1){
            tmp_value /= 2;
            tmp_count++;
        }
        mantissa_shift = tmp_count-1;
    } else {
        mantissa_shift = (long) floor(log2(abs(value)));
    }

    // Getting the exponent in binary format.
    // The sign is not relevant. Always returns a "positive" value.
    for(auto i = mantissa_shift + getBias(); i > 0; i /= 2){
        exponent.insert(exponent.begin(), i % 2);
    }

    bool value_too_large = false;
    if(exponent.size() > exponent_length){
        value_too_large = true;
    } else if(exponent.size() == exponent_length){
        value_too_large = allTrue(this->exponent);
    }

    if  (value_too_large){

        exponent.resize(exponent_length);
        mantissa.resize(mantissa_length);

        if(value > 0){
            this->setInf();
        } else {
            this->setInf(true);
        }

        return;

    } else {
        exponent.insert(exponent.begin(), exponent_length-exponent.size(), false);
    }
    //-------------------------------


    // mantissa
    //-------------------------------
    auto tmp_value = value / pow(2, mantissa_shift); // adjust the value so that everything is behind the decimal point.

    // Convert the part after the decimal point to a bit string.
    // The sign is not relevant. Always returns a "positive" value.
    double reminder = abs(tmp_value) - floor(abs(tmp_value));
    for(unsigned long i = 0; i < mantissa_length; i++){

        reminder *= 2;
        if(reminder >= 1){
            mantissa.push_back(true); reminder -= 1;
        } else{
            mantissa.push_back(false);
        }
    }
    //-------------------------------

}

/**
 * Performs an addition on two mps objects that have the same sign.
 *
 * @param one reference to the first addend
 * @param two reference to the second addend
 * @param set_sign the sign to which the final result should be set
 * @return the resulting mps object
 */
[[nodiscard]] mps mps::addition(const mps &one, const mps &two, const bool set_sign) {

    // Set up the return object.
    //-------------------------------
    mps ret;
    ret.exponent_length = one.exponent_length;
    ret.mantissa_length = one.mantissa_length;
    ret.sign = set_sign;
    //-------------------------------


    // addition of mantissas.
    //-------------------------------
    auto add = []
            (const vector<bool> &first, const vector<bool> &second, unsigned long off_set, bool *carrier) -> vector<bool>{

        bool hd[2] = {true, true};
        bool p[2] = {false, false};

        return binaryOffsetAddition(first, second, off_set, true, p, hd, carrier);
    };
    //-------------------------------

    // set exponent and addition
    //-------------------------------
    bool carrier;
    unsigned long exponent_diff;
    char larger_tmp = larger(one.exponent, two.exponent);
    if(1 == larger_tmp){

        exponent_diff = binaryToInt(binarySubtraction(one.exponent, two.exponent));
        ret.exponent = one.exponent;

        if(exponent_diff <= one.mantissa.size()){
            ret.mantissa = add(two.mantissa, one.mantissa, exponent_diff, &carrier);
        } else if(one.mantissa.back() && (exponent_diff == one.mantissa.size()+1) && allFalse(two.mantissa)){
            // special case where the rounding distance is the same, and the rounded number, therefore, must be even.
            ret.mantissa = one.mantissa;
            if(addOneToBinary(&ret.mantissa)){
                addOneToBinary(&ret.exponent);
                // Checking the carrier bit can be omitted since it (conveniently) does this by default.
            }
            return ret;
        } else {
            ret.mantissa = one.mantissa;
            return ret;
        }

    } else if(-1 == larger_tmp){

        exponent_diff = binaryToInt(binarySubtraction(two.exponent, one.exponent));
        ret.exponent = two.exponent;

        if(exponent_diff <= one.mantissa.size()){
            ret.mantissa = add(one.mantissa, two.mantissa, exponent_diff, &carrier);
        } else if(two.mantissa.back() && (exponent_diff == two.mantissa.size()+1) && allFalse(one.mantissa)){
            // special case where the rounding distance is the same, and the rounded number, therefore, must be even.
            ret.mantissa = two.mantissa;
            if(addOneToBinary(&ret.mantissa)){
                addOneToBinary(&ret.exponent);
                // Checking the carrier bit can be omitted since it (conveniently) does this by default.
            }
            return ret;
        } else {
            ret.mantissa = two.mantissa;
            return ret;
        }

    } else {

        ret.exponent = two.exponent;
        ret.mantissa = add(one.mantissa, two.mantissa, 0, &carrier);
    }
    //-------------------------------


    // adjusting the mantissa
    //-------------------------------
    ret.mantissa.erase(ret.mantissa.begin(), ret.mantissa.begin()+1);
    if(round(&ret.mantissa, ret.mantissa_length)){
        addOneToBinary(&ret.exponent);
        // checking is not needed since it is (conveniently) correct by default
    }
    //-------------------------------

    // adjusting the mantissa
    //-------------------------------
    if(carrier){
        addOneToBinary(&ret.exponent);
        if(allTrue(ret.exponent)){
            ret.setInf(set_sign);
            return ret;
        }
    }
    //-------------------------------



    return ret;
}

/**
 * Performs a subtraction on two mps objects that have the same sign.
 *
 * @param minued reference to the minued number
 * @param subtrahend reference to the subtracted number
 * @param set_sign the sign to which the final result should be set
 * @return the resulting mps object
 */
[[nodiscard]] mps mps::subtraction(const mps &minued, const mps &subtrahend, bool set_sign) {

    // Set up the return object.
    //-------------------------------
    mps ret;
    ret.exponent_length = minued.exponent_length;
    ret.mantissa_length = minued.mantissa_length;
    ret.sign = set_sign;
    //-------------------------------


    // subtraction of mantissas.
    //-------------------------------
    auto subtract = []
            (const vector<bool> &first, const vector<bool> &sub, unsigned long off_set) -> vector<bool>{

            bool carrier;

            auto iSub = invertAndAddOne(sub, &carrier);
            bool hd[2] = {carrier, true};
            bool p[2] = {true, false};

            return binaryOffsetAddition(iSub, first, off_set, false, p, hd);
    };
    //-------------------------------


    // set exponent and does calculation.
    //-------------------------------
    char larger_tmp = larger(minued.exponent, subtrahend.exponent);
    if(1 == larger_tmp){
        unsigned long exponent_diff = binaryToInt(binarySubtraction(minued.exponent, subtrahend.exponent));
        ret.exponent = minued.exponent;

        if(exponent_diff <= minued.mantissa.size()){
            ret.mantissa = subtract(minued.mantissa, subtrahend.mantissa, exponent_diff);
        } else if (exponent_diff == minued.mantissa.size() + 1){
            ret.mantissa = minued.mantissa;

            if(allFalse(ret.mantissa)){
                subtractOneFromBinary(&ret.exponent);
            }
            subtractOneFromBinary(&ret.mantissa);

            return ret;
        } else {
            ret.mantissa = minued.mantissa;
            return ret;
        }

    } else if(-1 == larger_tmp){

        unsigned long exponent_diff = binaryToInt(binarySubtraction(subtrahend.exponent, minued.exponent));
        ret.exponent = subtrahend.exponent;
        ret.sign = !ret.sign; // flip sign

        if(exponent_diff <= minued.mantissa.size()){
            ret.mantissa = subtract(subtrahend.mantissa, minued.mantissa, exponent_diff);
        } else if(exponent_diff == minued.mantissa.size() + 1){
            ret.mantissa = subtrahend.mantissa;

            if(allFalse(ret.mantissa)){
                subtractOneFromBinary(&ret.exponent);
            }
            subtractOneFromBinary(&ret.mantissa);

            return ret;
        } else {
            ret.mantissa = subtrahend.mantissa;
            return ret;
        }

    } else {

        ret.exponent = minued.exponent;

        larger_tmp = larger(minued.mantissa, subtrahend.mantissa);
        if(1 == larger_tmp){

            ret.mantissa = subtract(minued.mantissa, subtrahend.mantissa, 0);

        } else if(-1 == larger_tmp){

            ret.mantissa = subtract(subtrahend.mantissa, minued.mantissa, 0);
            ret.sign = !ret.sign; // flip sign

        } else {
            ret.setZero();
            return ret;
        }

    }
    //-------------------------------


    // Adjust mantissa and exponent
    //-------------------------------
    unsigned long exponent_shift = 0;
    for(unsigned long i = 0; i < ret.mantissa.size(); i++){
        if(ret.mantissa[i]){
            exponent_shift = i;
            break;
        }

        // for every "right shift", pull one zero from the right.
        ret.mantissa.push_back(false);
    }

    ret.mantissa.erase(ret.mantissa.begin(), ret.mantissa.begin() + (long) exponent_shift + 1);

    vector<bool> exponent_shift_binary = intToBinary(exponent_shift);
    exponent_shift_binary.insert(exponent_shift_binary.begin(), ret.exponent_length - exponent_shift_binary.size(), false);
    ret.exponent = binarySubtraction(ret.exponent, exponent_shift_binary);
    //-------------------------------


    if(round(&ret.mantissa, ret.mantissa_length)){
        addOneToBinary(&ret.exponent);
        // cannot overflow since it is a subtraction.
    }

    return ret;
}

/**
 * Performs a multiplication on two mps objects that have the same sign.
 *
 * @param one reference to the first multiplicand
 * @param two reference to the second multiplicand
 * @param set_sign the sign to which the final result should be set
 * @return the resulting mps object
 */
[[nodiscard]] mps mps::multiplication(const mps& one, const mps& two, bool set_sign) {

    // Set up the return object.
    //-------------------------------
    mps ret(one.mantissa_length, one.exponent_length);
    ret.sign = set_sign;
    //-------------------------------


    // Calculate the exponent
    //-------------------------------
    if(one.exponent[0] && two.exponent[0]){ // Both exponents are positive.

        vector<bool> addend = two.exponent;

        addend[0] = !addend[0];
        addOneToBinary(&addend);    // Carrier bit must not be checked because of if-statement.

        bool tmp_carry;
        ret.exponent = binaryAddition(one.exponent, addend, &tmp_carry);

        // Check if the number will be more than the maximal allowed value.
        if(tmp_carry && one.exponent[0] && !addend[0]){
            ret.setInf(ret.sign);
            return ret;
        }

    } else {

        vector<bool> subtrahend;
        subtrahend.reserve(two.exponent.size());
        subtrahend.push_back(false);
        for(unsigned long i = 1; i < two.exponent.size(); i++){
            subtrahend.push_back(true);
        }

        if(one.exponent[0] && !two.exponent[0]){
            subtrahend = binarySubtraction(subtrahend, one.exponent);
            ret.exponent = binarySubtraction(two.exponent, subtrahend);
        } else {
            subtrahend = binarySubtraction(subtrahend, two.exponent);

            if(!one.exponent[0] && !two.exponent[0] && 1 == larger(subtrahend, one.exponent)){
                ret.setZero();
                return ret;
            }

            ret.exponent = binarySubtraction(one.exponent, subtrahend);
        }
    }
    //-------------------------------


    // Calculate the mantissa
    //-------------------------------
    //bool prefix[2] = {false, true};

    vector<bool> S;
    bool carrier;
    S = invertAndAddOne(one.mantissa, &carrier);
    S.insert(S.begin(), carrier);
    S.insert(S.begin(), true);


    // set up P vector (product)
    vector<bool> &P = ret.mantissa;     // Use reference P in order to keep the naming.
    P.clear();
    P.reserve(one.mantissa.size() + two.mantissa_length + 5);              // 3 => 2* (sign and "invisible 1") + 1
    for(unsigned long i = 0; i < one.mantissa_length + 2; i++){    // 2 => sign and "invisible 1"
        P.push_back(false);
    }
    P.push_back(false);
    P.push_back(true);
    for(unsigned long i = 0; i < two.mantissa_length; i++){
        P.push_back(two.mantissa[i]);
    }
    P.push_back(false);

    // main loop
    for(unsigned long i = 0; i < two.mantissa_length+2; i++){


        if(!P.end()[-2] && P.back()){
            binarySummation(&P, one.mantissa, true);
        } else if(P.end()[-2] && !P.back()) {
            binarySummation(&P, S);
        }

        P.pop_back();
        P.insert(P.begin(), P[0]);

    }

    P.pop_back();
    P.erase (P.begin());        // delete "invisible 1"

    // normalize
    int count = 0;
    for(unsigned long i = 0; i < P.size(); i++){
        if(P[0]){
            P.erase(P.begin());
            break;
        }
        P.erase(P.begin());
        count++;
    }
    //-------------------------------

    // rounding
    //-------------------------------
    if(round(&P, ret.mantissa_length)){
        addOneToBinary(&ret.exponent);
        // Cannot overflow. Same reasoning as for addition.
    }

    if(count <= 1){
        addOneToBinary(&ret.exponent);
    }
    //-------------------------------

    return ret;
}

/**
 * Performs a division on two mps objects that have the same sign.
 *
 * @param dividend reference to the dividend of the division
 * @param divisor reference to the divisor of the division
 * @param set_sign the sign to which the final result should be set
 * @return the resulting mps object
 */
[[nodiscard]] mps mps::division(const mps& dividend, const mps& divisor, bool set_sign) {

    // Set up the return object.
    //-------------------------------
    mps ret; //(dividend.mantissa_length, divisor.exponent_length);
    ret.mantissa_length = dividend.mantissa_length;
    ret.exponent_length = dividend.exponent_length;
    ret.sign = set_sign;
    //-------------------------------


    // Calculate the exponent
    //-------------------------------
    if(divisor.exponent[0]){ // Both exponents are positive.

        vector<bool> subtrahend = divisor.exponent;

        subtrahend[0] = !subtrahend[0];
        addOneToBinary(&subtrahend);    // Carrier bit must not be checked because of if-statement.

        ret.exponent = binarySubtraction(dividend.exponent, subtrahend);

        if(1 == larger(ret.exponent, dividend.exponent)){
            ret.mantissa.resize(ret.mantissa_length, false);
            ret.exponent.resize(ret.exponent_length, false);
            ret.setZero();
            return ret;
        }


    } else if(!divisor.exponent[0]){

        vector<bool> subtrahend;
        subtrahend.reserve(divisor.exponent.size());
        subtrahend.push_back(false);
        for(unsigned long i = 1; i < divisor.exponent.size(); i++){
            subtrahend.push_back(true);
        }

        subtrahend = binarySubtraction(subtrahend, divisor.exponent);

        bool carrier;
        ret.exponent = binaryAddition(dividend.exponent, subtrahend, &carrier);

        if(carrier || allTrue(ret.exponent)){
            ret.mantissa.resize(ret.mantissa_length, false);
            ret.exponent.resize(ret.exponent_length, false);
            ret.setInf(ret.sign);
            return ret;
        }

    }
    //-------------------------------


    // Division
    //-------------------------------

    // remainder
    vector<bool> R = dividend.mantissa;
    R.insert(R.begin(), true);
    R.insert(R.begin(), 2, false);

    // quotient
    vector<bool> &Q = ret.mantissa;         // reference for better naming.
    Q.resize(ret.mantissa_length, false);

    // subtrahend (used for binarySummation)
    auto S = invertAndAddOne(divisor.mantissa, nullptr, true);    // carry bit must not be checked because d must not be 0;


    // main loop
    for(auto && i : Q){
        shiftLeft(&R);

        char tmp = larger(R, divisor.mantissa, true);
        if(1 == tmp || 0 == tmp){
            binarySummation(&R, S);
            i = true;
        }
    }
    //-------------------------------


    // normalisation
    //-------------------------------
    unsigned long count = 0;
    vector<bool> count_vec(divisor.exponent.size(), false);

    for(unsigned long i = 0; i < Q.size(); i++){
        if(Q[0]){
            Q.erase(Q.begin());
            count++;
            //addOneToBinary(&count_vec);
            break;
        } else {
            Q.erase(Q.begin());
            count++;
            addOneToBinary(&count_vec);
        }
    }

    // rerun the algorithm for every leading bit removed.
    for(unsigned long i = 0; i < count; i++){
        shiftLeft(&R);

        char tmp = larger(R, divisor.mantissa, true);
        if(1 == tmp || 0 == tmp){
            // R = binarySubtraction(R, D);
            binarySummation(&R, S);
            Q.push_back(true);
        } else {
            Q.push_back(false);
        }
    }

    ret.exponent = binarySubtraction(ret.exponent, count_vec);
    //-------------------------------


    // rounding
    //-------------------------------
    shiftLeft(&R);

    char tmp = larger(R, divisor.mantissa, true);
    if(1 == tmp || 0 == tmp){
        addOneToBinary(&Q);
    }
    //-------------------------------

    return ret;
}
//-------------------------------


// comparators
//-------------------------------

/**
 * Checks whether two mps objects are the same.
 * Info: handles exceptions and special values.
 *
 * @return true if they are the same, false otherwise
 */
bool mps::operator==(const mps& other) const{

    if (this->exponent_length != other.exponent_length) {
        throw std::invalid_argument("ERROR: in == : Exponents do not match");
    }
    if (this->mantissa_length != other.mantissa_length) {
        throw std::invalid_argument("ERROR: in == : Mantissas do not match");
    }

    if(this->isNaN() || other.isNaN()){
        return false;
    }

    if(this->sign != other.sign) {             // positive positive case
        return false;
    } else {
        return equal(*this, other);
    }
}

/**
 * Checks whether two mps objects are not the same.
 * Info: handles exceptions and special values.
 *
 * @return true if they are not the same, false otherwise
 */
bool mps::operator!=(const mps& other) const{

    if (this->exponent_length != other.exponent_length) {
        throw std::invalid_argument("ERROR: in != : Exponents do not match" );
    }
    if (this->mantissa_length != other.mantissa_length) {
        throw std::invalid_argument("ERROR: in != : Mantissas do not match");
    }

    if(this->isNaN() || other.isNaN()){
        return true;
    }

    if(this->sign != other.sign) {  // positive positive case
        return true;
    } else {
        return notEqual(*this, other);
    }
}

/**
 * Checks whether the first mps object is larger than the other mps object.
 * Info: handles exceptions and special values.
 *
 * @return true if it is larger, false otherwise
 */
bool mps::operator>(const mps& other) const{

    if (this->exponent_length != other.exponent_length) {
        throw std::invalid_argument("ERROR: in > : Exponents do not match" );
    }
    if (this->mantissa_length != other.mantissa_length) {
        throw std::invalid_argument("ERROR: in > : Mantissas do not match" );
    }

    if(this->isNaN() || other.isNaN()){
        return false;
    }

    if(!this->sign &&!other.sign) { // positive positive case
        return larger(*this, other);
    } else if(!this->sign) {        // positive negative case
        return true;
    } else if(!other.sign){         // negative positive case
        return false;
    } else {                        // negative negative case
        return larger(other, *this);
    }
}

/**
 * Checks whether the first mps object is smaller than the other mps object.
 * Info: handles exceptions and special values.
 *
 * @return true if it is smaller, false otherwise
 */
bool mps::operator<(const mps& other) const{

    if (this->exponent_length != other.exponent_length) {
        throw std::invalid_argument("ERROR: in < : Exponents do not match" );
    }
    if (this->mantissa_length != other.mantissa_length) {
        throw std::invalid_argument("ERROR: in < : Mantissas do not match" );
    }

    if(this->isNaN() || other.isNaN()){
        return false;
    }

    if(!this->sign &&!other.sign) { // positive positive case
        return smaller(*this, other);
    } else if(!this->sign) {        // positive negative case
        return false;
    } else if(!other.sign){         // negative positive case
        return true;
    } else {                        // negative negative case
        return smaller(other, *this);
    }
}

/**
 * Checks whether the first mps object is larger than or equal to than the other mps object.
 * Info: handles exceptions and special values.
 *
 * @return true if it is larger or equal, false otherwise
 */
bool mps::operator>=(const mps& other) const {

    if (this->exponent_length != other.exponent_length) {
        throw std::invalid_argument("ERROR: in >= : Exponents do not match" );
    }
    if (this->mantissa_length != other.mantissa_length) {
        throw std::invalid_argument("ERROR: in >= : Mantissas do not match" );
    }

    if(this->isNaN() || other.isNaN()){
        return false;
    }

    if(!this->sign &&!other.sign) { // positive positive case
        return largerEqual(*this, other);
    } else if(!this->sign) {        // positive negative case
        return true;
    } else if(!other.sign){         // negative positive case
        return false;
    } else {                        // negative negative case
        return largerEqual(other, *this);
    }
}

/**
 * Checks whether the first mps object is smaller than or equal to the other mps object.
 * Info: handles exceptions and special values.
 *
 * @return true if it is larger, false otherwise
 */
bool mps::operator<=(const mps& other) const {

    if (this->exponent_length != other.exponent_length) {
        throw std::invalid_argument("ERROR: in <= : Exponents do not match" );
    }
    if (this->mantissa_length != other.mantissa_length) {
        throw std::invalid_argument("ERROR: in <= : Mantissas do not match" );
    }

    if(this->isNaN() || other.isNaN()){
        return false;
    }

    if(!this->sign &&!other.sign) { // positive positive case
        return smallerEqual(*this, other);
    } else if(!this->sign) {        // positive negative case
        return false;
    } else if(!other.sign){         // negative positive case
        return true;
    } else {                        // negative negative case
        return smallerEqual(other, *this);
    }
}


/**
 * Performs the actual check of whether two mps objects are the same.
 * Info: Does not check for correct input or special values.
 *
 * @param one first mps object
 * @param two second mps object
 * @return true if they are the same, false otherwise
 */
[[nodiscard]] bool mps::equal(const mps& one, const mps& two){

    auto res = compare(one, two);

    if(0 == res) {
        return true;
    } else {
        return false;
    }
}

/**
 * Performs the actual check whether two mps objects are not the same.
 * Info: Does not check for correct input or special values.
 *
 * @param one first mps object
 * @param two second mps object
 * @return true if they are not the same, false otherwise
 */
[[nodiscard]] bool mps::notEqual(const mps& one, const mps& two){

    auto res = compare(one, two);

    if(0 == res) {
        return false;
    } else {
        return true;
    }
}

/**
 * Performs the actual check whether the first mps object is larger than the second mps object.
 * Info: Does not check for correct input or special values.
 *
 * @param one first mps object
 * @param two second mps object
 * @return true if the first is larger, false otherwise
 */
[[nodiscard]] bool mps::larger(const mps& one, const mps& two){

    auto res = compare(one, two);

    if(-1 == res || 0 == res) {
        return false;
    } else {
        return true;
    }
}

/**
 * Performs the actual check whether the first mps object is smaller than the second mps object.
 * Info: Does not check for correct input or special values.
 *
 * @param one first mps object
 * @param two second mps object
 * @return true if the first is smaller, false otherwise
 */
[[nodiscard]] bool mps::smaller(const mps& one, const mps& two){

    auto res = compare(one, two);

    if(1 == res || 0 == res){
        return false;
    } else {
        return true;
    }
}

/**
 * Performs the actual check whether the first mps object is larger than or equal to the second mps object.
 * Info: Does not check for correct input or special values.
 *
 * @param one first mps object
 * @param two second mps object
 * @return true if the first is larger or equal, false otherwise
 */
[[nodiscard]] bool mps::largerEqual(const mps& one, const mps& two){

    auto res = compare(one, two);

    if(1 == res || 0 == res) {
        return true;
    } else {
        return false;
    }
}

/**
 * Performs the actual check whether the first mps object is smaller than or equal to the second mps object.
 * Info: Does not check for correct input or special values.
 *
 * @param one first mps object
 * @param two second mps object
 * @return true if the first is smaller or equal, false otherwise
 */
[[nodiscard]] bool mps::smallerEqual(const mps& one, const mps& two){

    auto res = compare(one, two);

    if(-1 == res || 0 == res){
        return true;
    } else {
        return false;
    }
}

/**
 * Compares two mps objects.
 * Info: Does not check for correct input or special values.
 *
 * @param one first mps object
 * @param two second mps object
 * @return 1: first is larger; 0: both are the same; -1: second is larger
 */
[[nodiscard]] char mps::compare(const mps& one, const mps& two){

    // compare exponent
    for(unsigned long i = 0; i < one.exponent_length; i++){

        if(one.exponent[i] && !two.exponent[i]){
            return 1;
        }
        if(two.exponent[i] && !one.exponent[i]){
            return -1;
        }
    }

    // compare mantissa
    for(unsigned long i = 0; i < one.mantissa_length; i++){

        if(one.mantissa[i] && !two.mantissa[i]){
            return 1;
        }
        if(two.mantissa[i] && !one.mantissa[i]){
            return -1;
        }
    }

    // equal case
    return 0;
}
//-------------------------------


// helper methods
//-------------------------------

/**
 * Performs a binary addition using a full adder.
 * The binary numbers are represented as vectors containing booleans.
 *
 * @param a reference to the first addend
 * @param b reference to the second addend
 * @param carry set to true if an adjustment is wanted when the carrier bit of the last iteration is 1
 * @param carrier_return pointer to a boolean where the last state of the carrier bit can be saved
 * @return the result as a binary number
 */
vector<bool> mps::binaryAddition(const vector<bool>& a, const vector<bool>& b, bool* carrier_return){

    vector<bool> ret;
    bool carrier = false;

    // full adder
    for(auto i = a.size(); i > 0;){
        i--;
        ret.insert(ret.begin(), (a[i] ^ b[i]) ^ carrier);
        carrier = ((a[i] && b[i]) || (a[i] && carrier)) || (b[i] && carrier);
    }

    /*
    // adjust if carrier bit is 1
    if(carry && carrier){
        ret.insert(ret.begin(), true);
        ret.pop_back();
    }
     */

    // save the state of the carrier bit in carrier_return.
    if(carrier_return != nullptr){
        *carrier_return = carrier;
    }

    return ret;
}

/**
 * Performs a binary subtraction.
 * The binary numbers are represented as vectors containing booleans.
 *
 * @param minuend reference to the vector, which should be reduced
 * @param subtrahend reference to the vector which should be subtracted
 * @return the result as a binary number
 */
vector<bool> mps::binarySubtraction(const vector<bool>& minuend, const vector<bool>& subtrahend){

    bool carrie;
    auto tmp = invertAndAddOne(subtrahend, &carrie);

    if(carrie){
        return minuend; // If there is a carrier bit present at the end, the subtrahend is zero.
    }

    return binaryAddition(minuend, tmp);
}

/**
 * Performs an addition but adds directly to the summand. The addend can be smaller.
 * If so, the addend will be "virtually" shifted to the left so the the first bits match.
 *
 * ATTENTION: The function does not check whether a carrier bit is present at the end,
 * since it is expected that the vectors either have an appropriate structure or that a subtraction is performed.
 *
 * @param summand pointer to the vector to which the addend is added.
 * @param addend reference to the addend which is going to be added to the summand.
 */
void mps::binarySummation(vector<bool> *summand, const vector<bool> &addend, const bool prefix) {

    bool carrier = false;
    bool tmp;
    auto j = addend.size(); // + start

    if(prefix) {
        j += 2;
    }

    // full adder
    for(auto i = addend.size(); i > 0;){
        i--;
        j--;
        tmp = ((*summand)[j] ^ addend[i]) ^ carrier;
        carrier = (((*summand)[j] && addend[i]) || ((*summand)[j] && carrier)) || (addend[i] && carrier);
        (*summand)[j] = tmp;
    }

    if(prefix) { // prefix: false, true

        j--;
        tmp = !(*summand)[j] ^ carrier;
        carrier = ((*summand)[j] || ((*summand)[j] && carrier)) || carrier;
        (*summand)[j] = tmp;

        j--;
        (*summand)[j] = (*summand)[j] ^ carrier;
    }

}

/**
 * Performs an addition of two floating point mantissas where an offset can also be set.
 *
 * If an offset is set, the first vector argument is shifted to the right (and padded on the left),
 * and the second vector argument is shifted to the left (and padded on the right).
 *
 * The padding can be set individually.
 *
 * It can be decided whether a carrier step should be made at the and. This is at the end of the addition of a carrier
 * bit is present, and an extra element (bool) will be added at the beginning of the resulting vector.
 *
 * Since this is an addition for floating point mantissas, it considers the hidden digit. This is the first bit left of
 * the decimal point, which is not saved since it is there by definition. To be able to use the code for inverted vectors
 * (which is needed for subtraction) the value of the hidden digit can be set individually.
 *
 * The last value of the carrier bit can be returned via cr.
 *
 * @param lp the vector which is padded on the left (and therefore shifted to the right)
 * @param rp the vector which is padded on the right (and therefore shifted to the left)
 * @param off_set the offset which can be set
 * @param c whether a carrier bit should be added at the beginning if present
 * @param p first: padding for lp, second: padding for rp
 * @param hd first: hidden digit for lp, second: hidden digit for rp
 * @param cr pointer to a bool where the last value of the carrier bit can be saved (default: nullptr)
 * @return the result as a vector consisting of booleans
 */
vector<bool> mps::binaryOffsetAddition(const vector<bool>& lp, const vector<bool>& rp, unsigned long off_set, bool c, const bool p[2], const bool hd[2],  bool* cr){

    // setting up basic variable.
    vector<bool> ret;
    bool carrier = false;

    // calculate the right padding part.
    //-------------------------------
    for(auto i = lp.size(); i > lp.size()-off_set;){
        i--;
        //ret.insert(ret.begin(), lp[i] ^ carrier);
        //carrier = ((lp[i] && false) || (lp[i] && carrier));
        ret.insert(ret.begin(), (lp[i] ^ p[1]) ^ carrier);
        carrier = ((lp[i] && p[1]) || (lp[i] && carrier)) || (p[1] && carrier);
    }
    //-------------------------------


    // calculate the part between the padding.
    //-------------------------------
    unsigned long j = rp.size();
    for(auto i = lp.size()-off_set; i > 0;){
        i--;
        j--;
        ret.insert(ret.begin(), (lp[i] ^ rp[j]) ^ carrier);
        carrier = ((lp[i] && rp[j]) || (lp[i] && carrier)) || (rp[j] && carrier);
    }
    //-------------------------------


    if(off_set > 0){

        // calculate the left parts hidden digit.
        j--;
        ret.insert(ret.begin(), (hd[0] ^ rp[j]) ^ carrier);
        carrier = ((hd[0] && rp[j]) || (hd[0] && carrier)) || (rp[j] && carrier);


        // calculate the left padding part.
        //-------------------------------
        for(; j > 0;){
            j--;
            //ret.insert(ret.begin(), rp[j] ^ carrier);
            //carrier = (rp[j] && carrier);
            ret.insert(ret.begin(), (p[0] ^ rp[j]) ^ carrier);
            carrier = ((p[0] && rp[j]) || (p[0] && carrier)) || (rp[j] && carrier);
        }
        //-------------------------------


        // calculate right parts hidden digit
        ret.insert(ret.begin(), (p[0] ^ hd[1]) ^ carrier);
        carrier = ((p[0]  && hd[1]) || (p[0]  && carrier)) || (hd[1] && carrier);

    } else {

        // calculate the hidden digit of both variables
        ret.insert(ret.begin(), (hd[0] ^ hd[1]) ^ carrier);
        carrier = ((hd[0] && hd[1]) || (hd[0] && carrier)) || (hd[1] && carrier);
    }

    // perform carrier step if wanted.
    if(c && carrier){
        ret.insert(ret.begin(), true);
    }

    // save carrier bit if wanted.
    if(cr != nullptr) {
        *cr = carrier;
    }


    return ret;
}

/**
 * Performs the rounding of the mantissa according to IEEE754.
 *
 * If an rounding upwards did take place and the following addition has a carry bit present at the end
 * the function returns true.
 *
 * @param mantissa pointer to the mantissa that should be rounded
 * @param mantissa_len The length to which the mantissa should be rounded
 * @return if an overflow happened.
 */
bool mps::round(vector<bool> *mantissa, unsigned long mantissa_len) {

    bool ret = false;

    if(mantissa->size() > mantissa_len){
        bool tmp = false;
        for(auto i = mantissa_len+1 ; i < mantissa->size(); i++){
            if ((*mantissa)[i]){
                tmp = true;
                break;
            }
        }
        if((*mantissa)[mantissa_len] && tmp){
            mantissa->erase(mantissa->begin() + (long) mantissa_len, mantissa->end());
            if(addOneToBinary(mantissa)){
                ret = true;
            }
        } else if((*mantissa)[mantissa_len]){
            mantissa->erase(mantissa->begin() + (long) mantissa_len, mantissa->end());
            if((*mantissa)[mantissa_len-1]){
                if(addOneToBinary(mantissa)){
                    ret = true;
                }
            }
        }else {
            mantissa->erase(mantissa->begin() + (long) mantissa_len, mantissa->end());
        }
    }

    return ret;
}

/**
 * Converts a binary number to an integer.
 * The binary number is stored in a vector of booleans.
 *
 * @param vector vector containing the binary number
 * @return the binary number as an integer
 */
unsigned long mps::binaryToInt(vector<bool> vector){

    unsigned long ret = 0;

    for(unsigned long i = 0; i < vector.size(); i++){
        if(vector[vector.size()-i-1]){
            ret += (unsigned long) pow(2,i);
        }
    }

    return ret;
}

/**
 * Converts an integer to a binary number.
 * The binary number is stored in a vector of booleans.
 *
 * @param value the value of the integer
 * @return the value as a binary number
 */
vector<bool> mps::intToBinary(unsigned long value) {

    vector<bool> ret;

    while (value >= 1){
        ret.insert(ret.begin(), value%2);
        value /= 2;
    }

    return ret;
}

/**
 * Returns the bias of the exponent.
 *
 * @return bias of the exponent
 */
long mps::getBias() const{
    return ((long) pow (2, exponent_length)) / 2 -1;
}

/**
 * Compares the size of a to the size of b.
 *
 * The return value is defined as values:
 * 1 if a > b
 * 0 if a == b
 * -1 if a < b
 *
 * ATTENTION: Does not check for same length!
 * Only works for vectors of the same size.
 *
 * Division Case: In the case of a division, the routine must account for "hidden" bits.
 *
 * @param a reference to the vector containing the first binary number
 * @param b reference to the vector containing the second binary number
 * @param division_case whether the division case is wanted or not
 * @return 1 if a > b, 0 if a == b, -1 if a < b
 */
char mps::larger(const vector<bool>& a, const vector<bool>& b, const bool division_case){

    if(!division_case){
        for(unsigned long i = 0; i < a.size(); i++){
            if(a[i] && !b[i]) { return 1;}
            else if(b[i] && !a[i]) {return -1;}
        }
    } else {

        if (a[0]){
            return 1;
        } else if(!a[1]) {
            return -1;
        }

        for(unsigned long i = 0; i < b.size(); i++){
            if(a[i+2] && !b[i]) { return 1;}
            else if(b[i] && !a[i+2]) {return -1;}
        }

        if(a[a.size()-1]){
            return 1;
        }
    }

    return 0;
}

/**
 * Adds one to a binary number saved inside a vector.
 * The vector consists of booleans, which represent a binary number.
 *
 * @param vector pointer to the vector containing the binary number where one should be added
 * @return true if a carrier bit was present in the last iteration, false otherwise
 */
bool mps::addOneToBinary(vector<bool>* vector){

    for(auto i = vector->size(); i > 0;){
        i--;
        (*vector)[i] = !(*vector)[i];
        if((*vector)[i]){
            return false;
        }
    }

    return true;
}

/**
 * Subtracts one to a binary number saved inside a vector.
 * The vector consists of booleans, which represent a binary number.
 *
 * @param vector pointer to the vector containing the binary number where one should be subtracted
 * @return true if a carrier bit was present in the last iteration, false otherwise
 */
bool mps::subtractOneFromBinary(vector<bool> *vector){

    for(auto i = vector->size(); i > 0;){
        i--;
        (*vector)[i] = !(*vector)[i];
        if(!(*vector)[i]){
            return false;
        }
    }

    return true;
}

/**
 * Creates a copy of the vector vec. Then, it inverts the copy, adds one to it, and returns it afterward.
 *
 * @param vec reference to the vector which copy should be inverted, and added one to it
 * @param carrie pointer to a boolean value, which will be set to true if a carrier bit is present at the end
 * @return the resulting copied and tempered vector
 */
vector<bool> mps::invertAndAddOne(const vector<bool> &vec, bool *carrie, const bool division_case){

    vector<bool> ret;

    if(!division_case){
        ret.reserve(vec.size());
    } else {
        ret.reserve(vec.size()+3);
        ret.push_back(true);
        ret.push_back(false);
    }

    for(auto && i : vec){
        ret.push_back(!i);
    }

    if(division_case){
        ret.push_back(true);
    }

    if(carrie != nullptr){
        *carrie = addOneToBinary(&ret);
    } else {
        addOneToBinary(&ret);
    }

    return ret;
}

/**
 * Checks if a vector only consists of true booleans.
 *
 * @param vector reference to the vector, which should be checked
 * @return true if all entries of the vector are true
 */
[[nodiscard]] bool mps::allTrue(const vector<bool>& vector) {
    return std::all_of(vector.begin(), vector.end(), [](bool i){return i;});
}

/**
 * Checks if a vector only consists of false booleans.
 *
 * @param vector reference to the vector, which should be checked
 * @return true if all entries of the vector are false
 */
[[nodiscard]] bool mps::allFalse(const vector<bool>& vector) {
    return std::all_of(vector.begin(), vector.end(), [](bool i){return !i;});
}

/**
 * Shifts a vector to the left.
 *
 * @param vector pointer to the vector, which should be shifted to the left
 */
void mps::shiftLeft(vector<bool>* vec){

    vec->erase(vec->begin());
    vec->push_back(false);
}
//-------------------------------