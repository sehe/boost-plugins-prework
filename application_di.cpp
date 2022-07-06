#include "boost/function.hpp"
#include "ioperation.hpp"
#include <boost/di.hpp>
#include <boost/dll/import.hpp>
#include <iostream>

namespace di = boost::di;
namespace dll = boost::dll;

class app {
 private:
   op_ptr ptr_;

 public:
     app(boost::shared_ptr<ioperation> ptr)
         : ptr_(ptr)
     {
         std::cout << "name: " << ptr_->name() << std::endl;
     }
};

using boost::filesystem::path;

int main(int argc, char** argv) {
    // setting up paths to library(.so) files
    path lib_path(argc > 1 ? argv[1] : "."),
        child_library_path = lib_path / "dot_product",
        parent_library_path = lib_path / "sum";

    // defining function types for lib constructors
    using sum_create_t = op_ptr();
    using dot_product_create_t = op_ptr(op_ptr);

    // importing SUM lib factory
    auto sum_creator = boost::dll::import_alias<sum_create_t>(
        parent_library_path,
        "create_sum",
        dll::load_mode::append_decorations);

    // importing DOT_PRODUCT lib factory
    auto dot_product_creator =
        boost::dll::import_alias<dot_product_create_t>(
            child_library_path,
            "create_dot_product",
            dll::load_mode::append_decorations);

    auto use_sum = true;

    const auto injector =
        di::make_injector(di::bind<ioperation>().to(
            [=, &use_sum](const auto& injector) -> op_ptr
            {
                return use_sum
                    ? sum_creator()
                    : dot_product_creator(sum_creator());
            }) //
        );

    use_sum = argc > 2;
    injector.create<app>();
}
