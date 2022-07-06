#include "boost/shared_ptr.hpp"
#include <boost/dll/import.hpp>
#include "boost/function.hpp"
#include <iostream>
#include "ioperation.hpp"

namespace dll = boost::dll;
using boost::filesystem::path;

int main(int argc, char** argv)
{
    // setting up paths to library(.so) files
    path lib_path(argc > 1 ? argv[1] : "."),
        child_library_path = lib_path / "dot_product",
        parent_library_path = lib_path / "sum";

    // defining function types for lib constructors
    using sum_create_t = op_ptr();
    using dot_product_create_t = op_ptr(op_ptr);

    // importing SUM lib factory
    auto sum_creator = dll::import_alias<sum_create_t>(
        parent_library_path,
        "create_sum",
        dll::load_mode::append_decorations);

    // importing DOT_PRODUCT lib factory
    auto dot_product_creator =
        dll::import_alias<dot_product_create_t>(
            child_library_path,
            "create_dot_product",
            dll::load_mode::append_decorations);

	auto sum_ptr = sum_creator();
	auto dot_product_ptr = dot_product_creator(sum_ptr);

	//executing calculate methods for object ptrs
    for (op_ptr op : {sum_creator(), dot_product_creator(sum_creator()) }) {
        std::cout << "\nPlugin Name: " << op->name() << "\n";
        std::cout << "calculate(1, 2): " << op->calculate(1, 2) << "\n";
    }
}
