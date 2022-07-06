#pragma once
#include "ioperation.hpp"
#include "ioperation.hpp"

namespace sum_namespace {
    struct sum : ioperation {
        sum();
        ~sum() override;
        std::string name() const override;
        float       calculate(float, float) override;

        static op_ptr create_sum();
    };
} // namespace sum_namespace
