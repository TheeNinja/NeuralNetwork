#ifndef NEURALNETWORK_MODEL_H
#define NEURALNETWORK_MODEL_H

#include <stdbool.h>
#include "data.h"
#include "functions.h"

typedef int ActivationFunctionType;

#define SIGMOID 0
#define TANH 1
#define RELU 2

#define INPUT_LAYER_INDEX 0

typedef double (*CostFunction)(double, double);
typedef double (*ActivationFunction)(double);
typedef double (*WeightInitializationFunction)(double, double);
typedef double (*BiasInitializingFunction)(double, double);


/**
 * Represents a model to be used in regards to training the vehicle to move efficiently.
 * Implemented as a neural network.
 */
struct Model {
    /* Weight of link between two neurons is received with indices
     * [layer index of end neuron][index of end neuron within its layer][index of start neuron within its layer] */
    double*** weights;
    double** biases;
    double** values;

    int numberOfLayers;
    int* neuronsPerLayer;

    double learningRate;

    /**
     * the function used to activate the neuron. The value returned by this function is put into the neuron.
     */
    ActivationFunction getActivation;

    /**
     * the derivative of the function used to activate the neuron.
     */
    ActivationFunction getActivationPrime;

    /**
     * the function uses to calculate the cost, given an output neuron's value and its target value
     */
    CostFunction getCost;

    /**
     * the function used to calculate the derivative of the cost with respect to the output neuron's value, given the
     * output neuron's value and its target value
     */
    CostFunction getCostPrime;

    WeightInitializationFunction getInitialWeightValue;
    BiasInitializingFunction getInitialBiasValue;
};

void train(struct Model* model, struct Data* data, int inputColumnIndices[], int targetOutputColumnIndices[], int epochCount);
void test(struct Model* model, struct Data* data, int inputColumnIndices[], int outputColumnIndices[], double* predictedOutputs[], double costs[]);

void initParameters(struct Model* model);
void initValues(struct Model* model);

void freeParameters(struct Model* model);
void freeValues(struct Model* model);

void initializeInput(double *input, const double *entry, const int *inputColumnIndices, int inputColumnIndicesCount);
void initializeTargetOutput(double *targetOutput, const double *entry, const int *targetOutputIndices,
                            int targetOutputIndicesCount);

void initializeModel(struct Model* model, int neuronsPerLayer[], int numberOfLayers, double learningRate, ActivationFunctionType activationFunctionType);

#endif