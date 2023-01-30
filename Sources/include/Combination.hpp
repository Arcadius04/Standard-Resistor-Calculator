#ifndef _Combination_HPP_
#include <string>
using namespace std;

class Combination{

private:
    float firstResistor;
    float secondResistor;
    string type;
    float deviation;

public:
    Combination(string,float,float,float);
    float getFirstResistor();
    float getSecondResistor();
    float getDeviation();
    string getType();

};


#endif // _Combination_HPP_
