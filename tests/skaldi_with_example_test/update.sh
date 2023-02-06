#!/bin/bash

# Update library with the latest tested version of Skaldi

## Update CPP files
cp src/Skaldi.cpp ../../src/Skaldi.cpp
cp -r src/client ../../src/
cp -r src/server ../../src/

## Update Header files
cp include/Skaldi.hpp ../../include/Skaldi.hpp
cp -r include/client ../../include/
cp -r include/server ../../include/

# Update example with the latest tested version of Skaldi

## Update CPP files
cp src/main.cpp ../../example/src/main.cpp
cp src/ParserArgs.cpp ../../example/src/ParserArgs.cpp
cp -r src/utilities ../../example/src/

## Update Header files
cp include/ParserArgs.hpp ../../example/include/ParserArgs.hpp
cp -r include/utilities ../../example/include/
