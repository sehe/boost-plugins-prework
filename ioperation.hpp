#include <string>

class ioperation {

public:
    virtual std::string name() const = 0;
    virtual float calculate(float x, float y) = 0;

    virtual ~ioperation() {}
};


