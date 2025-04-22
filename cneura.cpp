/* Project: NEURA 
NEURA is an artificial neuron and network development research project 
focused on artificial intelligence for data analysis. The goal is to find 
the optimal neural network structure and improve artificial neurons for 
efficiency and speed.

Future projects:
- Project Mei: Neuron investigation project
- Project Raiden: Network development 
- Hardware integration: After successfully developing the artificial 
  neuron network, the project will transition into hardware implementation.

Developer: QCAT FERMI
*/

#include <iostream>
#include <vector>
#include "cneura.h"

using namespace std;

int main(){
    //Define the number of neuron on each layer
    vector <size_t> num_neurons(9, 9); //= {3, 3, 3, 3};
    // Define input and target output
    vector<double> targets = {1, 2, 3, 4, 5, 6, 7, 8, 9};//{0.5, 0.1, 0.4}; // Example single input
    vector<double> inputs = {7, 2, 5, 4, 6, 6, 4, 2, 6}; // Example target output
    double learning_rate = 1e-2;
    double decay_rate = 0.001;
    vector<double> beta = {0.9, 0.9999}; // Momentum factor for Adam
    int step_size = 10; // For step decay learning rate

    // Initialize Neural Network with Adam optimizer and Step Decay learning rate
    Neural neural(
        num_neurons, inputs,
        learning_rate, decay_rate, beta,
        MEANCENTER, LEAKY_RELU, ITDECAY, ADAM, MSE
    );

    neural.set_step_size(step_size);
    neural.set_target(targets, 1e-6);

    neural.feedforward();
    neural.print();
    neural.backpropagation();

    return 0;
}
