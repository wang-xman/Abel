#ifndef _ABEL_NUMERIC_HPP_
#define _ABEL_NUMERIC_HPP_

#include "object.hpp"

namespace abel {

template<typename PrimitiveType> class numeric : public object {
private:
    std::string type_name_string = "numeric";

protected:
    PrimitiveType internal;

public:
    typedef numeric numeric_type;

    numeric() {}
    explicit numeric(const numeric& num_ref) : internal( num_ref.value() ) {}
    explicit numeric(const PrimitiveType& number) : internal(number) {}
    explicit numeric(const std::shared_ptr<numeric>& sptr) : internal( sptr->value() ) {}

    virtual ~numeric() {};

    virtual numeric<PrimitiveType>& operator=(const numeric<PrimitiveType>& ref)
    {
        internal = ref.value();
        return *this;
    };

    virtual numeric<PrimitiveType>& operator=(const PrimitiveType& num)
    {
        internal = num;
        return *this;
    }

    explicit operator PrimitiveType() { return internal;}

    std::string type_name() const override { return type_name_string; };

    virtual PrimitiveType value() const { return internal; }
};

/* Compare numeric object (left) with numeric object (right) */

template <typename Tl, typename Tr>
bool operator<(const numeric<Tl>& l_num_ref, const numeric<Tr>& r_num_ref)
/*
    l_num_ref < r_num_ref
*/
{
    return l_num_ref.value() < r_num_ref.value();
}

template <typename Tl, typename Tr>
bool operator>(const numeric<Tl>& l_num_ref, const numeric<Tr>& r_num_ref)
/*
    l_num_ref > r_num_ref
*/
{
    return l_num_ref.value() > r_num_ref.value();     
}

template <typename Tl, typename Tr>
bool operator==(const numeric<Tl>& l_num_ref, const numeric<Tr>& r_num_ref)
/*
    l_num_ref == r_num_ref
*/
{
    return !(l_num_ref < r_num_ref) && !(r_num_ref < l_num_ref);
};

template <typename Tl, typename Tr>
bool operator!=(const numeric<Tl>& l_num_ref, const numeric<Tr>& r_num_ref)
/*
    l_num_ref != r_num_ref
*/
{
    return !(l_num_ref == r_num_ref);
};

// TODO Following functions not fully documented.

/* Compare numeric object (left) and C++ primitive arithmetic (right) */

template <typename Tl, typename Tr,
    typename std::enable_if<std::is_arithmetic<Tr>::value, bool>::type=true
>
bool operator<(const numeric<Tl>& l_num_ref, const Tr& r_prim_ref)
/*
    l_num_ref < r_prim_ref
*/
{
    return l_num_ref.value() < r_prim_ref;
}

template <typename Tl, typename Tr,
    typename std::enable_if<std::is_arithmetic<Tr>::value, bool>::type=true
>
bool operator>(const numeric<Tl>& l_num_ref, const Tr& r_prim_ref)
/*
    l_num_ref > r_prim_ref
*/
{
    return l_num_ref.value() > r_prim_ref;     
}

template <typename Tl, typename Tr,
    typename std::enable_if<std::is_arithmetic<Tr>::value, bool>::type=true
>
bool operator==(const numeric<Tl>& l_num_ref, const Tr& r_prim_ref)
/*
    l_num_ref == r_prim_ref
*/
{
    return l_num_ref.value() == r_prim_ref; 
}

template <typename Tl, typename Tr,
    typename std::enable_if<std::is_arithmetic<Tr>::value, bool>::type=true
>
bool operator!=(const numeric<Tl>& l_num_ref, const Tr& r_prim_ref)
/*
    l_num_ref != r_prim_ref
*/
{
    return !(l_num_ref.value() == r_prim_ref);
}

/* Compare C++ primitive (left) with numeric object (right) */

template <typename Tl, typename Tr,
    typename std::enable_if<std::is_arithmetic<Tl>::value, bool>::type=true
>
bool operator<(const Tl& l_prim_ref, const numeric<Tr>& r_num_ref)
/*
    l_num_ref < r_prim_ref
*/
{
    return l_prim_ref < r_num_ref.value();
}

template <typename Tl, typename Tr,
    typename std::enable_if<std::is_arithmetic<Tl>::value, bool>::type=true
>
bool operator>(const Tl& l_prim_ref, const numeric<Tr>& r_num_ref)
/*
    l_num_ref > r_prim_ref
*/
{
    return l_prim_ref > r_num_ref.value();
}

template <typename Tl, typename Tr,
    typename std::enable_if<std::is_arithmetic<Tl>::value, bool>::type=true
>
bool operator==(const Tl& l_prim_ref, const numeric<Tr>& r_num_ref)
/*
    l_num_ref == r_prim_ref
*/
{
    return l_prim_ref == r_num_ref.value(); 
}

template <typename Tl, typename Tr,
    typename std::enable_if<std::is_arithmetic<Tl>::value, bool>::type=true
>
bool operator!=(const Tl& l_prim_ref, const numeric<Tr>& r_num_ref)
/*
    l_num_ref != r_prim_ref
*/
{
    return !( l_prim_ref == r_num_ref.value() );
}

/* Stream operators */

template <typename T>
std::ostream& operator<<(std::ostream& output, const numeric<T>& ref)
{
    output << ref.value();
    return output;
}

template <typename T>
std::ostream& operator<<(std::ostream& output, const std::shared_ptr<T> sptr)
{
    output << sptr->value();
    return output;
}

}
#endif