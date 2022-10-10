#ifndef _ABEL_DOUBLE_HPP_
#define _ABEL_DOUBLE_HPP_

#include "integer.hpp"

namespace abel {

class Double : public numeric<double> {
private:
    std::string type_name_string = "Double";

public:
    Double();
    Double(const Double&);

    explicit Double(const double&);
    explicit Double(std::unique_ptr<Double>&);
    explicit Double(std::unique_ptr<object>&);
    explicit Double(const std::shared_ptr<Double>&);
    explicit Double(const std::shared_ptr<object>&);

    ~Double();

    Double& operator=(const double&) override;
    Double& operator=(std::unique_ptr<Double>&);
    Double& operator=(std::unique_ptr<object>&);
    Double& operator=(const std::shared_ptr<Double>&);
    Double& operator=(const std::shared_ptr<object>&);

    operator double();

    std::string type_name() const override;
};

}
#endif