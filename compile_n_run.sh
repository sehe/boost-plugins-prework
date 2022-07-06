#!/bin/bash

set -e -x -u
./cleanup.sh

echo "=> Compiling now..."
CPPFLAGS="-std=c++14 -fPIC -I /home/sehe/custom/boost-di/include/"
LDFLAGS=""

# Required to compile on sehe's machine:
#CPPFLAGS="$CPPFLAGS -I /home/sehe/custom/boost-di/include/"
#CPPFLAGS="$CPPFLAGS -isystem /home/sehe/custom/superboost/ ";
#LDFLAGS="$LDFLAGS -L /home/sehe/custom/superboost/stage/lib"

g++ $CPPFLAGS sum.cpp -shared -o libsum.so $LDFLAGS
g++ $CPPFLAGS dot_product.cpp -shared -o libdot_product.so $LDFLAGS

# add application libraries
LDFLAGS="$LDFLAGS -lboost_filesystem -lboost_system -ldl"
g++ $CPPFLAGS application_main.cpp -o application_main $LDFLAGS
g++ $CPPFLAGS application_di.cpp -o application_di $LDFLAGS

./application_main .

./application_di . use_sum
./application_di . # uses dot_product
