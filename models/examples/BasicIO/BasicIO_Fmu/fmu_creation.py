from fmpy import write_fmu
import os

# Define paths
fmu_path = 'MyModel.fmu'
model_description_path = 'modelDescription.xml'
binary_path = 'binaries/'  # Adjust based on your structure
resources_path = 'resources/'  # If any

# Collect all necessary files
files = [
    model_description_path,
    # Add paths to compiled binaries
    os.path.join(binary_path, 'win64', 'MyModel.dll'),
    os.path.join(binary_path, 'linux64', 'libMyModel.so'),
    os.path.join(binary_path, 'mac64', 'libMyModel.dylib'),
    # Add resource files if any
]

# Write FMU
write_fmu(
    unzip=False,
    fmi_version='2.0',
    fmu_type='me',  # 'me' for Model Exchange, 'cs' for Co-Simulation
    model_identifier='MyModel',
    files=files,
    fmu_path=fmu_path
)

print("FMU created using FMPy.")
