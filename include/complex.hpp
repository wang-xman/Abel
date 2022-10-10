#ifndef _ABEL_COMPLEX_HPP_
#define _ABEL_COMPLEX_HPP_

#include "numeric.hpp"
#include "double.hpp"

namespace abel {

template <typename T> class complex : public numeric<std::complex<T> > {
private:
    std::string type_name_string = "complex_T";

public:
    complex() {}

    complex(const T& real, const T& imag)
            : numeric<std::complex<T> >::numeric(std::complex<T>{real, imag}) {}

    complex(const complex& ref) : numeric<std::complex<T> >::numeric(ref) {}

    complex(const std::complex<T>& ref)
            : numeric<std::complex<T> >::numeric(ref) {}

    explicit complex(const std::shared_ptr<complex<T> > sptr)
            : numeric<std::complex<T> >::numeric( sptr->value() ) {}

    ~complex() {}
 
    complex& operator=(const std::shared_ptr<complex> sptr)
    {
        this->internal = sptr->value();
        return *this;
    }

    complex& operator=(const std::shared_ptr<object> sptr)
    {
        try {
            if (sptr->type_name() != "Complex") {
                std::string msg = "Cannot assign a non-Complex type shared "
                                  "pointer of object to a Complex object.";
                throw error::IncompatibleType(msg);
            }
            this->internal
                    = std::dynamic_pointer_cast<complex<T> >(sptr)->value();
        } catch (error::IncompatibleType& err) { err.make_show(); }
        return *this;
    }

    operator std::complex<T>() { return value(); }

    std::complex<T> value() const override
    {
        return numeric<std::complex<T> >::value();
    }

    T real() { return value().real(); }
    T imag() { return value().imag(); }

    std::string type_name() const override { return type_name_string; };
};

// Comparison is delegated to std::complex type.
// Types in the template must be the same.
// Object == / != Object
template <typename Tl, typename Tr>
bool operator==(const complex<Tl>& l_com_ref, const complex<Tr>& r_com_ref)
{
    return l_com_ref.value() == r_com_ref.value();
};

template <typename Tl, typename Tr>
bool operator!=(const complex<Tl>& l_com_ref, const complex<Tr>& r_com_ref)
{
    return !(l_com_ref == r_com_ref);
};

// Object == / != std:complex
template <typename Tl, typename Tr>
bool operator==(const complex<Tl>& l_com_ref, const std::complex<Tr>& r_std)
{
    return l_com_ref.value() == r_std;
};

template <typename Tl, typename Tr>
bool operator!=(const complex<Tl>& l_com_ref, const std::complex<Tr>& r_std)
{
    return !(l_com_ref == r_std);
};

// Compare std::complex == Object
template <typename Tl, typename Tr>
bool operator==(const std::complex<Tl>& l_std, const complex<Tr>& r_com_ref)
{
    return l_std == r_com_ref.value();
};

template <typename Tl, typename Tr>
bool operator!=(const std::complex<Tl>& l_std, const complex<Tr>& r_com_ref)
{
    return !(l_std == r_com_ref);
};

class Complex : public complex<double> {
private:
    std::string type_name_string = "Complex";

public:
    Complex ();
    Complex(const double&, const double&);
    Complex(const Double&, const Double&);
    Complex(const Integer&, const Integer&);
    Complex(const std::complex<double>&);
    Complex(const std::complex<int>&);
    Complex(const std::shared_ptr<Complex>&);
    Complex(const std::shared_ptr<object>&);

    Complex& operator=(const std::shared_ptr<object>);
    Complex& operator=(const std::shared_ptr<Complex>);

    std::string type_name() const override;
};

}
#endif