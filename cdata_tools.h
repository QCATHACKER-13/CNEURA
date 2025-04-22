/*

This cdata++.h is a header file for statistics, mathematical methods 
formula for computational data science. It is tool for data processing, 
filtering and categorize selection, and other formula tools for data science
and data analytics. And also used on the Project NEURA for data training.


Project NEURA is an artificial neuron and network development research project 
focused on artificial intelligence for data analysis. The goal is to find 
the optimal neural network structure and improve artificial neurons for 
efficiency and speed.

Future projects:
- Project Mei: Neuron investigation project
- Project Raiden: Network development 
- Hardware integration: After successfully developing the artificial 
  neuron network, the project will transition into hardware implementation.

Developer: Christopher Emmanuelle J. Visperas, Applied Physics Researcher
*/

#ifndef CDATA_TOOLS_H
#define CDATA_TOOLS_H

#include <iostream>
#include <cmath>     // for exp()
#include <vector>
#include <algorithm> // for max_element, accumulate
#include <numeric>   // for accumulate

using namespace std;

class Data{
    private:
        vector<double> input;

    public:
        Data(const vector<double> inputs) : input(inputs){
            //Intialize the constructor
            this -> input = inputs;
        }

        vector <double> min_max_normalization(){
            double min = *min_element(input.begin(), input.end());
            double max = *max_element(input.begin(), input.end());
            vector <double> output;

            for(size_t i = 0; i < input.size(); i++){
                output[i] = (input[i] - min) / (max - min);
            }
            return output; 
        }

        vector <double> mean_normalization(){
            double min = *min_element(input.begin(), input.end());
            double max = *max_element(input.begin(), input.end());
            double mean = accumulate(input.begin(), input.end(), 0.0) / input.size();
            vector <double> output;

            for(size_t i = 0; i < input.size(); i++){
                output[i] = (input[i] - mean) / (max - min);
            }
            return output; 
        }
};

#endif