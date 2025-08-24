//
// Created by Jakob on 15.01.24.
//

#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <bitset>

inline std::string is_mps(const std::vector<bool>& vec){

    std::string str;
    for(bool bit : vec){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    return str;
}

template <typename T>
inline std::string should_value(T fp_number){

    std::string compare_str;
    char* bits = reinterpret_cast<char*>(&fp_number);
    for(unsigned long n = 0; n < sizeof fp_number; ++n) {
        std::string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    return  compare_str;
}


#endif // HELPER_FUNCTIONS_H
