//sapirblumshtein@gmail.com
//324246651

#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>

// Class to represent complex numbers
class Complex {
public:
    // Constructor to initialize the complex number
    Complex(double real, double imag) : real(real), imag(imag) {}

    // Get the real part of the complex number
    double get_real() const { return real; }
    // Get the imaginary part of the complex number
    double get_imag() const { return imag; }

    // Overload the > operator to compare complex numbers
    bool operator>(const Complex& other) const {
        return (real > other.real) || (real == other.real && imag > other.imag);
    }

    // Overload the == operator to compare complex numbers
    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }

    // Overload the << operator to print complex numbers
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real << " + " << c.imag << "i";
        return os;
    }

private:
    double real; // Real part
    double imag; // Imaginary part
};

#endif // COMPLEX_HPP
