#pragma one

#include "systemc"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

using namespace sc_core;

class BasicIO : sc_module
{
public:
    sc_in<bool> input_pin;
    sc_out<bool> output_pin;

    BasicIO(sc_core::sc_module_name name);
    ~BasicIO();

    SC_HAS_PROCESS(BasicIO);
private:

    void ioHandling(void);
};