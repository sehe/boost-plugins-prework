#pragma once
#include <boost/shared_ptr.hpp>
#include <string>

struct ioperation {
  virtual std::string name() const                = 0;
  virtual float       calculate(float x, float y) = 0;

  virtual ~ioperation() = default;
};

using op_ptr = boost::shared_ptr<ioperation>;
