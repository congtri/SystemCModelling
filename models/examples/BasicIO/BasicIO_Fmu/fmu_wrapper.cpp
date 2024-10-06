#include "include/fmi2Functions.h"
#include "../BasicIO_Model/BasicIO.hpp"
#include <systemc>

#include <memory>
#include <string>

static std::unique_ptr<BasicIO> model;
static sc_core::sc_signal<bool> input_signal;

extern "C" {

FMI2_Export const char* fmi2GetTypesPlatform() {
    return fmi2TypesPlatform;
}

FMI2_Export const char* fmi2GetVersion() {
    return fmi2Version;
}

FMI2_Export fmi2Component fmi2Instantiate(fmi2String instanceName, fmi2Type fmuType,
    fmi2String fmuGUID, fmi2String fmuResourceLocation, const fmi2CallbackFunctions* functions,
    fmi2Boolean visible, fmi2Boolean loggingOn) {
    
    // Initialize SystemC if it hasn't been already
    if (!sc_core::sc_is_running()) {
        sc_core::sc_start(sc_core::SC_ZERO_TIME);
    }
    
    // Create the BasicIO instance with the provided instance name
    model = std::make_unique<BasicIO>(instanceName);
    model->input_pin(input_signal);
    return static_cast<void*>(model.get());
}

FMI2_Export void fmi2FreeInstance(fmi2Component c) {
    model.reset();
}

FMI2_Export fmi2Status fmi2SetupExperiment(fmi2Component c, fmi2Boolean toleranceDefined,
    fmi2Real tolerance, fmi2Real startTime, fmi2Boolean stopTimeDefined, fmi2Real stopTime) {
    return fmi2OK;
}

FMI2_Export fmi2Status fmi2EnterInitializationMode(fmi2Component c) {
    return fmi2OK;
}

FMI2_Export fmi2Status fmi2ExitInitializationMode(fmi2Component c) {
    return fmi2OK;
}

FMI2_Export fmi2Status fmi2DoStep(fmi2Component c, fmi2Real currentCommunicationPoint,
    fmi2Real communicationStepSize, fmi2Boolean noSetFMUStatePriorToCurrentPoint) {
    sc_core::sc_start(sc_core::SC_ZERO_TIME);
    return fmi2OK;
}

FMI2_Export fmi2Status fmi2Terminate(fmi2Component c) {
    return fmi2OK;
}

FMI2_Export fmi2Status fmi2Reset(fmi2Component c) {
    return fmi2OK;
}

FMI2_Export fmi2Status fmi2GetBoolean(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, fmi2Boolean value[]) {
    if (nvr == 1 && vr[0] == 0) {
        value[0] = model->output_pin.read();
        return fmi2OK;
    }
    return fmi2Error;
}

FMI2_Export fmi2Status fmi2SetBoolean(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, const fmi2Boolean value[]) {
    if (nvr == 1 && vr[0] == 0) {
        input_signal.write(value[0]);
        return fmi2OK;
    }
    return fmi2Error;
}

// Implement other required FMI functions...

}