#include "dot_product.h"
#include <boost/config.hpp>
#include <boost/dll/alias.hpp>
#include <boost/dll/import.hpp>
#include <iostream>

namespace dot_product_namespace {

    dot_product::dot_product(op_ptr& arg) {
        sum_ptr = arg;
        std::cout << "[dot_product_constructor]" << std::endl;
    }

    std::string dot_product::name() const { return "dot_product"; }

    float dot_product::calculate(float a1, float a2) {
        // dot product given vector with itself
        // formula: a.b = a1*b1 + a2*b2
        return sum_ptr->calculate(a1 * a1, a2 * a2);
    }

    // Factory method
    /*static*/ op_ptr dot_product::create_dot_product(op_ptr sum_ptr) {
        return op_ptr(new dot_product(sum_ptr));
    }

    dot_product::~dot_product() {
        std::cout << "[~dot_product_destructor]" << std::endl;
    }
}; // namespace dot_product_namespace

BOOST_DLL_ALIAS(dot_product_namespace::dot_product::
                    create_dot_product, // <-- this function is exported with...
                create_dot_product      // <-- ...this alias name
)
