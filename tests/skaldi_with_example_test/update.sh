#!/bin/bash

# Update library with the latest tested version of Skaldi

if [[ "$1" == "test_to_release" ]]; then
  ## Update CPP files
  cp -r src/core ../../src/
  cp -r src/protocol ../../src/

  ## Update Header files
  cp include/Skaldi.hpp ../../include/Skaldi.hpp
  cp -r include/core ../../include/
  cp -r include/protocol ../../include/

  # Update example with the latest tested version of Skaldi

  ## Update CPP files
  cp src/main.cpp ../../example/src/main.cpp
  cp src/ParserArgs.cpp ../../example/src/ParserArgs.cpp
  cp -r src/utilities ../../example/src/

  ## Update Header files
  cp include/ParserArgs.hpp ../../example/include/ParserArgs.hpp
  cp -r include/utilities ../../example/include/
elif [[ "$1" == "release_to_test" ]]; then
  ## Update CPP files
  cp -r ../../src/core src/
    cp -r ../../src/protocol include/

  ## Update Header files
  cp ../../include/Skaldi.hpp include/Skaldi.hpp
  cp -r ../../include/core include/
  cp -r ../../include/protocol include/

  # Update example with the latest tested version of Skaldi

  ## Update CPP files
  cp ../../example/src/main.cpp src/main.cpp
  cp ../../example/src/ParserArgs.cpp src/ParserArgs.cpp
  cp -r ../../example/src/utilities src/

  ## Update Header files
  cp ../../example/include/ParserArgs.hpp include/ParserArgs.hpp
  cp -r ../../example/include/utilities include/
fi

