# S101toGML

The S101toGML project is a tool for converting IHO S-101 format files to IHO S-100 GML format. S-101 is an IHO (International Hydrographic Organization) standard for Electronic Navigational Charts (ENC) used in marine navigation.

## Purpose

The project is designed to convert Electronic Navigational Chart files to GML format, which is widely used in Geographic Information Systems (GIS) for storing and exchanging geographic data.

## Project Structure

The project consists of the following main components:

- `libS101`: Library for reading and processing S-101 files
- `S101GML`: Module for exporting S-101 data to GML format
- `S101toGML`: Main application that combines the above components

## Dependencies

- CMake (version 3.16 or higher)
- C++17
- pugixml - XML processing library (extlibs/pugixml)

## Building the Project

Build the project using CMake:
   ```
   mkdir build
   cd build
   cmake ..
   make
   ```

## Usage

After building the project, you can use the executable to convert files:

```
./S101toGML <input_S101_file_path> <output_GML_file_path>
```

For example:
```
./S101toGML S101toGML/File/101KR005X01SW.000 ./101KR005X01SW.gml
```

## Credits

Original repository - https://github.com/gorogara/S101toGML.

Differences: 
- structure (gml converter splitted from libS101)
- crossplatform with cmake (origin is windows native)