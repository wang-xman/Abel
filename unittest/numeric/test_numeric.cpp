/* Unittest: numeric */
#include "numeric.hpp"
#include "dora.hpp"

using namespace abel;

// Test if types derived from numeric are still covariant.
void print(std::shared_ptr<object> ptr)
{
    std::cout << ptr->type_name() << "\n";
}

void test_specialisation()
{
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = [](){
        numeric<int> test1 (50);
        dora::assert_equal(__LINE__, test1.type_name(), "numeric");
    };

    // Default constructor
    test_case.pool = [](){
        numeric<int> test1 (50);
        dora::assert_equal(__LINE__, test1.type_name(), "numeric");
        dora::assert_equal(__LINE__, test1.value(), 50);
    };

    // Shared pointer of a specialised type_name is still covariant
    // with share pointer of Object type_name.
    test_case.pool = [](){
        std::shared_ptr<numeric<int> > ptr (new numeric<int> (10));
        print(ptr);
    };

    test_case.all();
}


class IntegerTest : public numeric<int> {
private:
    std::string type_ = "IntegerTest";
    int internal_;
public:
    IntegerTest() {}
    IntegerTest(int num) : internal_(num) {}
    IntegerTest(const std::shared_ptr<IntegerTest> sptr) {
        internal_ = sptr->value();
    }
    ~IntegerTest() {}
    std::string type_name() const override { return type_; };
    int value() const override { return internal_; }
    operator int() { return (int)internal_; }
};


void test_integer()
{
    dora::TestCase test_case(__FILE__, __func__);
    
    // Default constructor
    test_case.pool = [](){
        IntegerTest test1;
        dora::assert_equal(__LINE__, test1.type_name(), "IntegerTest");
    };

    // Default constructor
    test_case.pool = [](){
        IntegerTest test1 (10);
        dora::assert_equal(__LINE__, test1.type_name(), "IntegerTest");
        dora::assert_equal(__LINE__, test1.value(), 10);
    };

    // Copy constructor
    // NOTE: Invokes the default copy constructor of IntegerTest,
    //       NOT the one from base class numeric.
    test_case.pool = [](){
        IntegerTest test1 (10);
        IntegerTest test2 (test1);
        dora::assert_equal(__LINE__, test2.type_name(), "IntegerTest");
        dora::assert_equal(__LINE__, test2.value(), 10);
    };

    // Copy constructor
    // NOTE: Must implement this for IntegerTest itself.
    test_case.pool = [](){
        std::shared_ptr<IntegerTest> test1 (new IntegerTest(10));
        IntegerTest test2 (test1);
        dora::assert_equal(__LINE__, test2.type_name(), "IntegerTest");
        dora::assert_equal(__LINE__, test2.value(), 10);
        std::cout << test1 << std::endl;
        // Test is a shared pointer of IntegerTest is still
        // covariant with shared pointer of Object.
        print(test1); // Yes.
    };

    // Copy assigment constructor
    test_case.pool = [](){
        IntegerTest test1;
        // integer assignment
        test1 = 100;
        dora::assert_equal(__LINE__, test1.type_name(), "IntegerTest");
        dora::assert_equal(__LINE__, test1.value(), 100);
    };

    // Comparison with same type_name
    test_case.pool = [](){
        IntegerTest test1 (10);
        IntegerTest test2 (test1);
        IntegerTest test3 (30);
        dora::assert_equal(__LINE__, test2.type_name(), "IntegerTest");
        dora::assert_equal(__LINE__, test2.value(), 10);
        dora::assert_true(__LINE__, test2==test1);
        dora::assert_true(__LINE__, test3>test1);
        dora::assert_true(__LINE__, test1<test3);
        dora::assert_true(__LINE__, test1!=test3);
        dora::assert_false(__LINE__, test2!=test1);
    };

    // Comparison with rvalue
    test_case.pool = [](){
        IntegerTest test1 (10);
        dora::assert_true(__LINE__, test1==10);
        dora::assert_true(__LINE__, test1<30);
        dora::assert_true(__LINE__, test1!= 30);
        dora::assert_equal(__LINE__, test1, 10.0);

    };

    // Comparison with primitive lvalue
    test_case.pool = [](){
        IntegerTest test1 (10);
        int i1 = 10;
        int i3 = 30;
        dora::assert_true(__LINE__, test1 == i1);
        dora::assert_false(__LINE__, test1 < i1);
        dora::assert_true(__LINE__, test1 < i3);
        dora::assert_true(__LINE__, i3 > test1);
    };

    // Conversion operator
    test_case.pool = [](){
        IntegerTest test1 (10);
        dora::assert_true(__LINE__, int(test1)==10);
    };

    test_case.all();
}

class DoubleTest : public numeric<double> {
private:
    std::string type_ = "DoubleTest";
    int internal_;
public:
    DoubleTest() {}
    DoubleTest(double num) : internal_(num) {}
    ~DoubleTest() {}
    std::string type_name() const override { return type_; };
    double value() const override { return internal_; }
};

void test_double()
{
    dora::TestCase test_case(__FILE__, __func__);
    
    // Default constructor
    test_case.pool = [](){
        DoubleTest test1;
        dora::assert_equal(__LINE__, test1.type_name(), "DoubleTest");
    };

    // Default constructor
    test_case.pool = [](){
        DoubleTest test1 (10);
        dora::assert_equal(__LINE__, test1.type_name(), "DoubleTest");
        dora::assert_equal(__LINE__, test1.value(), 10);
    };
    
    // Assignment from a primitive type_name
    test_case.pool = [](){
        DoubleTest test1;
        test1 = 10; // invokes numeric::opertor(& ref)
        dora::assert_equal(__LINE__, test1.type_name(), "DoubleTest");
        dora::assert_equal(__LINE__, test1.value(), 10);
    };
    
    // Assignment from same type_name
    // NOIE If DoubleTest has not its own method, this triggers the same
    //     method of numeric class.
    test_case.pool = [](){
        DoubleTest test1 (100);
        DoubleTest test2;
        test2 = test1; // invokes numeric.operator=(& ref)
        dora::assert_equal(__LINE__, test1.type_name(), "DoubleTest");
        dora::assert_equal(__LINE__, test1.value(), 100.0);
    };
    
    // Compare same type_name -> invoking numeric::operator>,<, ==, !=
    test_case.pool = [](){
        DoubleTest test1 (100);
        DoubleTest test2 (90);
        dora::assert_false(__LINE__, (test2 > test1));
        dora::assert_true(__LINE__, (test2 < test1));
    };

    // Compare differnt types
    test_case.pool = [](){
        IntegerTest test1 (100);
        DoubleTest test2 (90);
        dora::assert_false(__LINE__, (test2 == test1));
        dora::assert_false(__LINE__, (test1 == test2));
        dora::assert_true(__LINE__, test1 > test2);
    };

    // compare with lvalue
    test_case.pool = [](){
        DoubleTest test1 (100);
        double d = 200.0;
        dora::assert_true(__LINE__, (test1 < d));
        dora::assert_false(__LINE__, test1 > d);
        dora::assert_true(__LINE__, d > test1);
        dora::assert_true(__LINE__, test1 != d);
        dora::assert_false(__LINE__, test1 == d);

        int i = 200;
        dora::assert_true(__LINE__, (test1 < i));
        dora::assert_false(__LINE__, test1 > i);
        dora::assert_true(__LINE__, i > test1);
        dora::assert_true(__LINE__, test1 != i);
        dora::assert_false(__LINE__, test1 == i);
    };

    // compare with rvalue
    test_case.pool = [](){
        IntegerTest test1 (100);
        DoubleTest test2 (90);
        dora::assert_false(__LINE__, (test2 == 100));
        dora::assert_false(__LINE__, (100 == test2));
        dora::assert_true(__LINE__, test2 > 80);
        dora::assert_equal(__LINE__, test2, 90.0);
    };

    // Test stream operator
    test_case.pool = [](){
        DoubleTest test2 (90);
        std::shared_ptr<DoubleTest> test_ptr (new DoubleTest (1000.0));
        std::cout << "streaming a DoubleTest instance " << test2 << "\n";
        std::cout << "streaming a DoubleTest shared pointer " << test_ptr << "\n";
    };

    test_case.all();
}

int main()
{
    test_specialisation();
    test_integer();
    test_double();
}