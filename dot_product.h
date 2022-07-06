#pragma once
#include "ioperation.hpp"

namespace dot_product_namespace {

    struct dot_product : ioperation {
        dot_product(op_ptr&);
        ~dot_product() override;
        std::string name() const override;
        float       calculate(float, float) override;

        static op_ptr create_dot_product(op_ptr sum_ptr);

      private:
        op_ptr sum_ptr;
    };
}; // namespace dot_product_namespace
