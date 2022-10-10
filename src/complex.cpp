#include "complex.hpp"

namespace abel {

Complex::Complex () {}

Complex::Complex(const double& real, const double& imag)
        : complex<double>::complex(real, imag) {}
    
// via abel::Double
Complex::Complex(const Double& real, const Double& imag)
        : complex<double>::complex( real.value(), imag.value() ) {}

// via abel::Integer
Complex::Complex(const Integer& real, const Integer& imag)
        : complex<double>::complex( real.value(), imag.value() ) {}

Complex::Complex(const std::complex<double>& ref)
        : complex<double>::complex(ref) {}

// note the conversion from int to double
Complex::Complex(const std::complex<int>& ref)
        : complex<double>::complex( (double)ref.real(), (double)ref.imag() ) {}

Complex::Complex(const std::shared_ptr<Complex>& sptr)
{ 
    internal = sptr->value();
}

Complex::Complex(const std::shared_ptr<object>& sptr)
{
    try {
        if (sptr->type_name() != "Complex") {
            std::string msg = "Cannot copy-contruct a non-Complex type shared"
                              "pointer of abel::object to an Complex object.";
            throw error::IncompatibleType(msg);
        } else {
            internal = std::dynamic_pointer_cast<Complex>(sptr)->value();
        }
    } catch (error::IncompatibleType& err) {
        err.make_show();
    }
}

Complex& Complex::operator=(const std::shared_ptr<object> sptr)
{
    complex<double>::operator=(sptr);
    return *this;
}

Complex& Complex::operator=(const std::shared_ptr<Complex> sptr)
/*
    FIXME! Shall I accept Double, Integer, etc, as type-widening casting?
*/
{
    try {
        if (sptr->type_name() != "Complex") {
            std::string msg = "Cannot assign a non-Complex type shared"
                              "pointer of abe::object to a Complex object.";
            throw error::IncompatibleType(msg);
        }
        internal = std::dynamic_pointer_cast<Complex>(sptr)->value();
    } catch (error::IncompatibleType& err) {
        err.make_show();
    }
    return *this;   
}

std::string Complex::type_name() const { return type_name_string; };

}