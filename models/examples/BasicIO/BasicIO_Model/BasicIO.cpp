#include "BasicIO.hpp"

BasicIO::BasicIO(sc_core::sc_module_name name) : input_pin("INPUT_PIN"), output_pin("OUTPUT_PIN")
{
    SC_METHOD(ioHandling);
    sensitive << input_pin.value_changed();
}

BasicIO::~BasicIO()
{
}

void BasicIO::ioHandling(void)
{
    output_pin = ~(input_pin.read());
    std::cout << "IO Status\n";
    std::cout << "Input Pin:  " << input_pin.read() << std::endl;
    std::cout << "Output Pin: " << output_pin.read() << std::endl;
}