// fmi_wrapper.cpp

#include "./include/fmi2Functions.h"  // FMI functions
#include "systemc.h"
#include "BasicIO.hpp"
#include <iostream>

int sc_main(int argc, char *argv[])
{
    // Create an instance of your BasicIO module

    while (true)
    {
        printf("TEST\n");
    };

    // Start the SystemC simulation
    sc_start();

    return 0;
}

// Forward declarations of FMI functions
extern "C" {
    fmi2Component fmi2Instantiate(fmi2String instanceName,
                                  fmi2Type fmuType,
                                  fmi2String fmuGUID,
                                  fmi2String fmuResourceLocation,
                                  const fmi2CallbackFunctions* functions,
                                  fmi2Boolean visible,
                                  fmi2Boolean loggingOn);

    fmi2Status fmi2DoStep(fmi2Component c,
                          fmi2Real currentCommunicationPoint,
                          fmi2Real communicationStepSize,
                          fmi2Boolean noSetFMUStatePriorToCurrentPoint);

    fmi2Status fmi2Terminate(fmi2Component c);
    fmi2Status fmi2Reset(fmi2Component c);
    // Add other FMI functions as needed.
}

// Structure to hold simulation state
typedef struct {
    BasicIO* basic_io;               // SystemC model
    sc_signal<bool> input_signal;    // SystemC input signal
    sc_signal<bool> output_signal;   // SystemC output signal
    sc_time current_time;            // Current simulation time
} FMIComponent;

static FMIComponent* fmiComponent = nullptr;

// FMI instantiation function: Initialize the SystemC model
fmi2Component fmi2Instantiate(fmi2String instanceName,
                              fmi2Type fmuType,
                              fmi2String fmuGUID,
                              fmi2String fmuResourceLocation,
                              const fmi2CallbackFunctions* functions,
                              fmi2Boolean visible,
                              fmi2Boolean loggingOn) {
    // Allocate memory for FMI component
    fmiComponent = new FMIComponent;

    // Instantiate SystemC model
    fmiComponent->basic_io = new BasicIO("basic_io");

    // Binding input and output signals
    fmiComponent->basic_io->input_pin(fmiComponent->input_signal);
    fmiComponent->basic_io->output_pin(fmiComponent->output_signal);

    // Initialize simulation time
    fmiComponent->current_time = SC_ZERO_TIME;

    std::cout << "FMU instantiated." << std::endl;
    return fmiComponent;
}

// Step the simulation
fmi2Status fmi2DoStep(fmi2Component c,
                      fmi2Real currentCommunicationPoint,
                      fmi2Real communicationStepSize,
                      fmi2Boolean noSetFMUStatePriorToCurrentPoint) {
    if (fmiComponent == nullptr) {
        return fmi2Error;
    }

    // Convert step size from FMI to SystemC time units (assumed to be in seconds)
    sc_time step_time(communicationStepSize, SC_SEC);

    // Advance the simulation by the step size
    sc_main(NULL, nullptr);
    sc_start(step_time);

    // Update the simulation time
    fmiComponent->current_time += step_time;

    // Optionally log the output signal value
    std::cout << "Time: " << fmiComponent->current_time << ", Output: " 
              << fmiComponent->output_signal.read() << std::endl;

    return fmi2OK;
}

// Terminate the simulation
fmi2Status fmi2Terminate(fmi2Component c) {
    if (fmiComponent == nullptr) {
        return fmi2Error;
    }

    // Terminate SystemC simulation
    sc_stop();

    std::cout << "FMU simulation terminated." << std::endl;
    return fmi2OK;
}

// Reset the simulation (optional)
fmi2Status fmi2Reset(fmi2Component c) {
    if (fmiComponent == nullptr) {
        return fmi2Error;
    }

    // Reset the SystemC simulation
    sc_stop();
    delete fmiComponent->basic_io;

    fmiComponent->basic_io = new BasicIO("basic_io");
    fmiComponent->basic_io->input_pin(fmiComponent->input_signal);
    fmiComponent->basic_io->output_pin(fmiComponent->output_signal);
    fmiComponent->current_time = SC_ZERO_TIME;

    std::cout << "FMU simulation reset." << std::endl;
    return fmi2OK;
}

// Additional FMI functions can be implemented as needed.
