#include <iostream>

class Complex
{
public:
    Complex(int32_t a_, int32_t b_)
        : a(a_), b(b_)
    {}

    Complex operator*(const Complex& other)
    {
        // Multiplying complex numbers
        // using only three multiplications.
        int32_t ac = a * other.a;
        int32_t bd = b * other.b;
        int32_t abcd = (a + b) * (other.a + other.b);
        return Complex(ac - bd, abcd - ac - bd);
    }
public:
    int32_t a;
    int32_t b;
};

int main()
{
    int32_t a, b, c, d;

    std::cout << "Input four numbers a, b, c, d separated by space: ";
    std::cin >> a >> b >> c >> d;

    Complex x(a, b);
    Complex y(c, d);
    Complex z = x * y;

    std::cout << "(" << x.a << (x.b < 0 ? "" : "+") << x.b << "i) * ";
    std::cout << "(" << y.a << (y.b < 0 ? "" : "+") << y.b << "i) = ";
    std::cout << z.a << (z.b < 0 ? "" : "+") << z.b << "i" << std::endl;
}
