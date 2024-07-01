#ifndef ABEL_INTEGER_HPP
#define ABEL_INTEGER_HPP

#include "numeric.hpp"

namespace abel {

class Integer : public numeric<int> {
private:
    std::string type_name_string = "Integer";

public:
    Integer();
    Integer(const Integer&);

    explicit Integer(const int&);
    explicit Integer(std::unique_ptr<Integer>&);
    explicit Integer(std::unique_ptr<object>&);
    explicit Integer(const std::shared_ptr<Integer>&);
    explicit Integer(const std::shared_ptr<object>&);

    ~Integer();
 
    Integer& operator=(const int&) override;
    Integer& operator=(std::unique_ptr<Integer>&);
    Integer& operator=(std::unique_ptr<object>&);
    Integer& operator=(const std::shared_ptr<Integer>&);
    Integer& operator=(const std::shared_ptr<object>&);

    operator int();
    operator double();
    operator float();

    std::string type_name() const override;
};

}
#endif