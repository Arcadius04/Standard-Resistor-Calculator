#include "Combination.hpp"


Combination::Combination(string type,float firstResistor,float secondResistor,float deviation){
    this->type = type;
    this->firstResistor = firstResistor;
    this->secondResistor = secondResistor;
    this->deviation = deviation;
}
float Combination::getFirstResistor(){
    return this->firstResistor;
}
float Combination::getSecondResistor(){
    return this->secondResistor;
}
float Combination::getDeviation(){
    return this->deviation;
}
string Combination::getType(){
    return this->type;
}
