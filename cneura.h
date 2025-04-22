/* Project: NEURA 
NEURA is an artificial neuron and network development research project 
focused on artificial intelligence for data analysis. The goal is to find 
the optimal neural network structure and improve artificial neurons for 
efficiency and speed.

Project Development and Innovations:
- Project Neura: Neuron investigation project
- Project Mei: Neural Net Architecture investigation project
- Project Raiden: Network development 
- Hardware integration(Raiden Mei Project): After successfully developing the artificial 
  neuron network, the project will transition into hardware implementation.

Developer: QCAT FERMI

*/

#ifndef CNEURA_H
#define CNEURA_H

#include <iostream>
#include <vector>
#include <memory> // For std::unique_ptr
#include <algorithm>
#include <cmath>
#include <numeric>
#include "clayer.h"

using namespace std;

class Neural{
    private:
        vector<unique_ptr<Layer>> layers; // Use unique_ptr for better memory management
        vector<vector<vector<double>>> weight; // Stores weights for all layers

    public:
    Neural(const vector<size_t>& num_neurons, const vector<double>& inputs,
        const double& learning_rate, const double& decay_rate, const vector<double>& beta,
        normtype ntype_norm, actfunc actFunc, lrs lr_schedule, optimizer opt, lossfunc lossFunc) {
            
            if (inputs.empty()) {
                throw invalid_argument("Input vector cannot be empty.");
            }
            
            vector<double> current_input = inputs; // Start with the input data
            
            for (size_t i = 0; i < num_neurons.size(); ++i) {
                neurontype layer_type = (i == num_neurons.size() - 1) ? OUTPUT : HIDDEN;
                
                layers.emplace_back(make_unique<Layer>(
                    num_neurons[i], current_input,
                    learning_rate, decay_rate, beta,
                    layer_type, actFunc, lr_schedule, opt, lossFunc
                ));
                
                if (i == 0) {
                    layers[i]->normalization(ntype_norm);
                }
                current_input = layers.back()->get_activated_output(); // Update the input for the next layer
                }
            }

            // Set step size for all layers
            void set_step_size(int stepsize) noexcept {
                for (auto& layer : layers) {
                    layer->set_step_size(stepsize);
                }
            }
            
            // Perform feedforward computation
            void feedforward() {
                vector<double> current_input = layers.front()->get_input(); // Start with the input of the first layer
            
                for (auto& layer : layers) {
                    layer->set_input(current_input); // Set the input for the current layer
                    layer->feedforward();           // Perform feedforward computation
                    current_input = layer->get_activated_output(); // Update the input for the next layer
                }
            }

            void probability_calculation() {
                if (layers.empty()) return;
            
                // Perform probability calculation for the output layer
                layers.back()->probability_calculation();
            
                // Propagate errors backward to hidden layers
                for (int i = static_cast<int>(layers.size()) - 2; i >= 0; --i) {
                    layers[i]->set_error(layers[i + 1]->get_error()); // Set error from the next layer
                    layers[i]->probability_calculation();             // Perform probability calculation
                }
            }
            
            // Perform backpropagation
            void backpropagation() {
                if (layers.empty()) return;
                
                // Output layer first
                layers.back()->backpropagation();
                
                // Hidden layers
                for (int i = static_cast<int>(layers.size()) - 2; i >= 0; --i) {
                    layers[i]->set_error(layers[i + 1]->get_error());
                    layers[i]->backpropagation();
                }
            }

            void debug_feedforward() const {
                for (size_t i = 0; i < layers.size(); ++i) {
                    cout << "Layer " << i + 1 << " Outputs: ";
                    for (const auto& val : layers[i]->get_output()) {
                        cout << val << " ";
                    }
                    cout << endl;
                }
            }

            void train(int epochs, double error_margin, bool verbose = false) {
                for (int epoch = 0; epoch < epochs; ++epoch) {
                    feedforward();
                    
                    if (verbose) {
                        //cout << "Epoch " << epoch + 1 << endl;
                        print();
                    }
                    
                    double total_error = 0.0;
                    for (const auto& layer : layers) {
                        for (double e : layer->get_error()) {
                            total_error += abs(e);
                        }
                    }
                    
                    if (total_error < error_margin) {
                        if (verbose) cout << "Error margin reached. Stopping.\n";
                        break;
                    }
                    backpropagation();
                }
            }
            
            void print() const {
                for (const auto& layer : layers) {
                    layer->debug_state();
                }
            }
            
            vector<double> get_final_output() const {
                return layers.back()->get_output();
            }
            
            const vector<unique_ptr<Layer>>& get_layers() const noexcept {
                return layers;
            }

            void set_target(const vector<double>& targets, const double& inquired_number) {
                if (!layers.empty()) {
                    layers.back()->set_target(targets);
                }
            }

            void set_labeling(const vector<double>& labeling, const double& resolution) {
                if (!layers.empty()) {
                    layers.back()->set_labeling(labeling, resolution);
                }
            }
};

#endif
