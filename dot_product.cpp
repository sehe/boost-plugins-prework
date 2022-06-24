#include <boost/config.hpp>
#include <boost/dll/alias.hpp>
#include <boost/dll/import.hpp>
#include <iostream>
#include "ioperation.hpp"

namespace dot_product_namespace {

class dot_product: public ioperation {

	boost::shared_ptr<ioperation> sum_ptr;
public:
	dot_product(boost::shared_ptr<ioperation> &arg) {
		sum_ptr = arg;
		std::cout << "[dot_product_constructor]" << std::endl;
	}

	std::string name() const {
		return "dot_product";
	}

	float calculate(float a1, float a2) {
		//dot product given vector with itself
		//formula: a.b = a1*b1 + a2*b2
		return sum_ptr->calculate(a1*a1, a2*a2);
	}

	// Factory method
	static boost::shared_ptr<ioperation> create_dot_product(boost::shared_ptr<ioperation> sum_ptr) {
        	return boost::shared_ptr<ioperation>(
            		new dot_product(sum_ptr)
        	);
    	}

	~dot_product() {
		std::cout << "[~dot_product_destructor]" << std::endl;
	}
    };
};

BOOST_DLL_ALIAS(
    dot_product_namespace::dot_product::create_dot_product, // <-- this function is exported with...
    create_dot_product                               // <-- ...this alias name
)
