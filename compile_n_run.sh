#!/bin/bash

set -e 
./cleanup.sh

echo "=> Compiling now..."
g++ -std=c++14 -fPIC -c -o libsum.o  sum.cpp
g++ -shared -o libsum.so libsum.o

g++ -std=c++14 -fPIC -c -o libdot_product.o  dot_product.cpp
g++ -shared -o libdot_product.so libdot_product.o

g++ -std=c++14 -lboost_filesystem -lboost_system -ldl application_main.cpp -o application_main

echo "=> Compilation completed. "

	

echo "=> Executing ./application_main ."
./application_main .



