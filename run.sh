#!/bin/bash

# Compile the main.cpp file
g++ -c main.cpp

# Link the object file and create the executable
g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

# Run the executable
./sfml-app
