#include "Polynomial.h"
#include <cmath>
#include <stdexcept>

Polynomial::Polynomial() : coeffs(1, 0) {}

Polynomial::Polynomial(const vector<double>& coefficients) : coeffs(coefficients) {}

Polynomial::Polynomial(const Polynomial& other) : coeffs(other.coeffs) {}

Polynomial::~Polynomial() {}

Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        coeffs = other.coeffs;
    }
    return *this;
}

Polynomial Polynomial::operator+(const Polynomial& other) const {
    vector<double> result(max(coeffs.size(), other.coeffs.size()), 0);
    for (size_t i = 0; i < result.size(); ++i) {
        if (i < coeffs.size()) result[i] += coeffs[i];
        if (i < other.coeffs.size()) result[i] += other.coeffs[i];
    }
    return Polynomial(result);
}

Polynomial Polynomial::operator-(const Polynomial& other) const {
    vector<double> result(max(coeffs.size(), other.coeffs.size()), 0);
    for (size_t i = 0; i < result.size(); ++i) {
        if (i < coeffs.size()) result[i] += coeffs[i];
        if (i < other.coeffs.size()) result[i] -= other.coeffs[i];
    }
    return Polynomial(result);
}

Polynomial Polynomial::operator*(const Polynomial& other) const {
    vector<double> result(coeffs.size() + other.coeffs.size() - 1, 0);
    for (size_t i = 0; i < coeffs.size(); ++i) {
        for (size_t j = 0; j < other.coeffs.size(); ++j) {
            result[i + j] += coeffs[i] * other.coeffs[j];
        }
    }
    return Polynomial(result);
}

bool Polynomial::operator==(const Polynomial& other) const {
    return coeffs == other.coeffs;
}

ostream& operator<<(ostream& out, const Polynomial& poly) {
    bool firstTerm = true;
    for (int i = poly.degree(); i >= 0; --i) {
        if (poly.coeffs[i] != 0) {
            if (!firstTerm) {
                if (poly.coeffs[i] > 0) out << " + ";
                else out << " - ";
            } else {
                if (poly.coeffs[i] < 0) out << "-";
            }

            if (abs(poly.coeffs[i]) != 1 || i == 0) {
                out << abs(poly.coeffs[i]);
            }

            if (i > 0) out << "x";
            if (i > 1) out << "^" << i;

            firstTerm = false;
        }
    }
    return out;
}

int Polynomial::degree() const {
    return coeffs.size() - 1;
}

double Polynomial::evaluate(double x) const {
    double result = 0;
    for (int i = degree(); i >= 0; --i) {
        result = result * x + coeffs[i];
    }
    return result;
}

Polynomial Polynomial::derivative() const {
    if (coeffs.size() <= 1) return Polynomial({ 0 });
    vector<double> result(coeffs.size() - 1);
    for (size_t i = 1; i < coeffs.size(); ++i) {
        result[i - 1] = coeffs[i] * i;
    }
    return Polynomial(result);
}

Polynomial Polynomial::integral() const {
    vector<double> result(coeffs.size() + 1);
    result[0] = 0; // Constant term
    for (size_t i = 0; i < coeffs.size(); ++i) {
        result[i + 1] = coeffs[i] / (i + 1);
    }
    return Polynomial(result);
}

double Polynomial::integral(double x1, double x2) const {
    Polynomial integralPoly = integral();
    return integralPoly.evaluate(x2) - integralPoly.evaluate(x1);
}

double Polynomial::getRoot(double guess, double tolerance, int maxIter) const {
    double x = guess;
    for (int i = 0; i < maxIter; ++i) {
        double fx = evaluate(x);
        double fpx = derivative().evaluate(x);
        if (abs(fx) < tolerance) return x; // Root found
        if (fpx == 0) throw std::runtime_error("Derivative is zero. No root found.");
        x = x - fx / fpx; // Newton-Raphson step
    }
    return x; // Return the approximation of the root
}

Polynomial Polynomial::composition(const Polynomial& other) const {
    vector<double> result;
    for (size_t i = 0; i < coeffs.size(); ++i) {
        Polynomial temp = other;
        for (size_t j = 0; j < i; ++j) {
            temp = temp.integral(); // Get the integral for composition
        }
        result.push_back(coeffs[i] * temp.evaluate(1)); // Adjust for the composition
    }
    return Polynomial(result);
}
