#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <vector>

using namespace std;

class Polynomial {
private:
    vector<double> coeffs;

public:
    Polynomial(); // Constructor for default polynomial (0)
    Polynomial(const vector<double>& coefficients); // Constructor with coefficients
    Polynomial(const Polynomial& other); // Copy constructor
    ~Polynomial(); // Destructor

    Polynomial& operator=(const Polynomial& other); // Assignment operator
    Polynomial operator+(const Polynomial& other) const; // Addition
    Polynomial operator-(const Polynomial& other) const; // Subtraction
    Polynomial operator*(const Polynomial& other) const; // Multiplication
    bool operator==(const Polynomial& other) const; // Equality check

    friend ostream& operator<<(ostream& out, const Polynomial& poly); // Output stream

    int degree() const; // Degree of the polynomial
    double evaluate(double x) const; // Evaluate the polynomial at x
    Polynomial derivative() const; // Derivative of the polynomial
    Polynomial integral() const; // Indefinite integral of the polynomial
    double integral(double x1, double x2) const; // Definite integral
    double getRoot(double guess, double tolerance = 1e-7, int maxIter = 100) const; // Find root
    Polynomial composition(const Polynomial& other) const; // Composition of polynomials
};

#endif
