import fmpy
from fmpy import read_model_description, instantiate_fmu, simulate_fmu
from fmpy.util import download_test_file
import numpy as np

# Path to the FMU
fmu_path = './build/BasicIO_Fmu.fmu'

# Read the model description
model_description = read_model_description(fmu_path)

# Instantiate the FMU
fmu = instantiate_fmu(fmu_path, model_description)

# Define simulation parameters
start_time = 0.0
stop_time = 1.0
step_size = 0.1

# Define input sequence for input_pin
input_times = [0.1, 0.3, 0.5, 0.7, 0.9]
input_values = [True, False, True, False, True]

# Prepare input for FMPy
input_sequence = {
    'input_pin': (input_times, input_values)
}

# Simulate the FMU
result = simulate_fmu(fmu_path, start_time=start_time, stop_time=stop_time, input=input_sequence, step_size=step_size)

# Print the output_pin values
print("Simulation Results:")
for time, output in zip(result['time'], result['output_pin']):
    print(f"Time: {time:.2f}s, output_pin: {bool(output)}")
