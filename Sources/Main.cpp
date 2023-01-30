#include <iostream>
#include <limits.h>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iomanip>
#include "Combination.hpp"

using namespace std;

const vector<float> E12 = {0,1.0,1.2,1.5,1.8,2.2,2.7,3.3,3.9,4.7,5.6,6.8,8.2};
const vector<float> E24 = {0,1.0,1.1,1.2,1.3,1.5,1.6,1.8,2.0,2.2,2.4,2.7,3.0,3.3,3.6,3.9,4.3,4.7,5.1,5.6,6.2,6.8,7.5,8.2,9.1};
vector<float> ResistorsBase;

void start();

int main()
{
    start();
    return 0;
}

void start()
{
    cout << std::fixed;
    cout << "************************* Resistor Standard Calculator *************************" << endl;
    int input=-1;
    while(input == -1)
    {
        cout << "Please choose the standard resistor series." << endl;
        cout << "1. E12" << endl;
        cout << "2. E24" << endl;
        cout << "Input: ";
        cin >> input;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            input = -1;
            cout << "[Error] Bad Input. You have to input a number!" << endl;
        }
        switch(input)
        {
        case 1:
        {
            ResistorsBase=E12;
            break;
        }
        case 2:
        {
            ResistorsBase=E24;
            break;
        }
        default:
        {
            input = -1;
            cout << "[Error] Invalid option please select a number from the menu!" << endl;
            break;
        }
        }
    }
    float value = -1;
    while(value == -1)
    {
        cout << "Please insert the value of the resistor you want to find it's standard equivalent." << endl;
        cout << "Input: ";
        cin >> value;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            value = -1;
            cout << "[Error] Bad Input. You have to input a number!" << endl;
        }
    }

    cout << "Please wait... Calculating...." << endl;
    vector<Combination> combinations;
    for(float &firstbase : ResistorsBase)
    {
        for(int i = 1; i <= 6; i++)
        {
            float firstResistor = firstbase*pow(10,i);
            for(float &secondbase : ResistorsBase)
            {
                for(int j = 1; j <= 6; j++)
                {
                    float secondResistor = secondbase*pow(10,j);
                    // Check series deviation
                    float seriesCombination = firstResistor+secondResistor;
                    float seriesDeviation = ((seriesCombination-value)/(value))*100;
                    // Check parallel deviation
                    float parallelCombination = pow(((1/firstResistor)+(1/secondResistor)),-1);
                    float parallelDeviation = ((parallelCombination-value)/(value))*100;
                    // Add both combinations to the combination vector
                    Combination series("Series",firstResistor,secondResistor,seriesDeviation);
                    Combination parallel("Parallel",firstResistor,secondResistor,parallelDeviation);
                    combinations.push_back(series);
                    combinations.push_back(parallel);
                    //cout << combinations.size() << ", " << firstResistorBase.size() << ", " << secondResistorBase.size() << endl;
                }
            }
        }
    }
    cout << "--------------------------------------" << endl;
    vector<Combination> sortedCombinations;
    for(Combination c : combinations)
    {
        if(c.getDeviation() <= 2.0 && c.getDeviation() >= -2.0)
        {
            if(sortedCombinations.empty())
            {
                sortedCombinations.push_back(c);
                continue;
            }
            vector<Combination>::iterator position = sortedCombinations.begin();
            for(vector<Combination>::iterator it = sortedCombinations.begin(); it != sortedCombinations.end(); it++)
            {
                if((*it).getDeviation() >= c.getDeviation())
                {
                    position = it+1;
                }
                else
                {
                    break;
                }
            }
            if(position >= sortedCombinations.end())
            {
                position = sortedCombinations.end();
            }
            else if(position <= sortedCombinations.begin())
            {
                position = sortedCombinations.begin();
            }
            sortedCombinations.insert(position,1,c);
        }
    }
    int i = 1;
    for(Combination s : sortedCombinations)
    {
        if(i++ % 2 == 0)
            if(s.getType() == "Series")
            {
                cout << (int)s.getFirstResistor() << " + " << (int)s.getSecondResistor() << ", " << "Deviation: " << s.getDeviation() << "%" << endl;
            }
            else if (s.getType() == "Parallel")
            {
                cout << (int)s.getFirstResistor() << " || " << (int)s.getSecondResistor() << ", " << "Deviation: " << s.getDeviation() << "%" << endl;
            }
    }
    cout << "--------------------------------------" << endl;
    string permission = "";
    while(permission == "")
    {
        cout << "Would you like to perform another operation? (Y/N)" << endl;
        cout << "Input: ";
        cin >> permission;
        if(permission=="Y" || permission == "y")
        {
            start();
        }
        else if(permission == "N" || permission == "n")
        {
            cout << "Thank you and good bye!" << endl;
            return;
        }
        else
        {
            permission = "";
            cout << "[Error] Invalid option!" << endl;
        }
    }
}
