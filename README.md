# boost-plugins-prework

# To execute code run for just plugin loading:

./compile_n_run.sh

# To compile the application for Dependency Injection (DI) and Dynamic library loading (BOOST.DLL)

g++ application_di.cpp -lboost_filesystem -lboost_system -ldl -o application_di;