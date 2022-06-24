#include "boost/shared_ptr.hpp"
#include <boost/dll/import.hpp>
#include "boost/function.hpp"
#include <iostream>
#include "ioperation.hpp"

namespace dll = boost::dll;

int main(int argc, char* argv[]) {

	//setting up paths to library(.so) files
	boost::filesystem::path shared_library_path(argv[1]);    // argv[1] contains path to directory with our plugin library
    	boost::filesystem::path child_library_path = shared_library_path/"dot_product";
	boost::filesystem::path parent_library_path = shared_library_path/"sum";

	//defining function types for lib constructors
	typedef boost::shared_ptr<ioperation> (sum_create_t)();
	typedef boost::shared_ptr<ioperation> (dot_product_create_t)(boost::shared_ptr<ioperation>);
	boost::function<sum_create_t> sum_creator;
	boost::function<dot_product_create_t> dot_product_creator;

	//importing SUM lib constructor(takes no arg)
	sum_creator = boost::dll::import_alias<sum_create_t>(   // type of imported symbol must be explicitly specified
        	parent_library_path,                            // path to library
        	"create_sum",                                   // symbol to import
        	dll::load_mode::append_decorations              // do append extensions and prefixes
    	);

	//importing DOT_PRODUCT lib constructor(takes 1 arg of ptr to IOPERATION)
	dot_product_creator = boost::dll::import_alias<dot_product_create_t>(   // type of imported symbol must be explicitly specified
        	child_library_path,                                             // path to library
        	"create_dot_product",                                           // symbol to import
        	dll::load_mode::append_decorations                              // do append extensions and prefixes
    	);

	//creating a ptr to PARENT_PLUGIN_SUM objecti
	boost::shared_ptr<ioperation> sum_ptr = sum_creator();

	//creating a ptr to CHILD_PLUGIN_MULT object(passing above created PARENT_PLUGIN_SUM object ptr)
	boost::shared_ptr<ioperation> dot_product_ptr = dot_product_creator(sum_ptr);

	//executing calculate methods for object ptrs
	std::cout << "Plugin Name: " << sum_ptr->name() << std::endl;
	std::cout << "sum_ptr->calculate(1, 2)[expected=3]: " << sum_ptr->calculate(1, 2) << std::endl;
	std::cout << "Plugin Name: " << dot_product_ptr->name() << std::endl;
    	std::cout << "dot_product_ptr->calculate(1, 2)[expected=5]: " << dot_product_ptr->calculate(1, 2) << std::endl;
}	
