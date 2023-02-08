#!/bin/bash

# Update library with the latest tested version of Skaldi

## Update CPP files
cp -r src/core ../../src/

## Update Header files
cp include/Skaldi.hpp ../../include/Skaldi.hpp
cp -r include/core ../../include/

# Update example with the latest tested version of Skaldi

## Update CPP files
cp src/main.cpp ../../example/src/main.cpp
cp src/ParserArgs.cpp ../../example/src/ParserArgs.cpp
cp -r src/utilities ../../example/src/

## Update Header files
cp include/ParserArgs.hpp ../../example/include/ParserArgs.hpp
cp -r include/utilities ../../example/include/
