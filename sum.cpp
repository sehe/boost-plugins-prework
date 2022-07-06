#include <boost/config.hpp>
#include <boost/dll/alias.hpp>
#include <boost/dll/import.hpp>
#include "ioperation.hpp"
#include <iostream>

namespace sum_namespace {
    class sum : public ioperation {
      public:
        sum() { std::cout << "[sum_constructor]" << std::endl; }
        std::string name() const { return "sum"; }
        float calculate(float x, float y) { return x + y; }
        ~sum() { std::cout << "[~sum_destructor]" << std::endl; }

        // Factory method
        static op_ptr create_sum() { return op_ptr(new sum()); }
    };
} // namespace sum_namespace

BOOST_DLL_ALIAS(
    sum_namespace::sum::create_sum, // <-- this function is exported with...
    create_sum                      // <-- ...this alias name
)
