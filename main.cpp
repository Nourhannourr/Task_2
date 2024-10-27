#include <iostream>
#include <vector>
#include <algorithm>
#include "Polynomial.h"

using namespace std;

// Function to reverse coefficients for proper input order
vector<double> reverseCoefficients(const vector<double>& coeffs) {
    vector<double> reversedCoeffs = coeffs;
    reverse(reversedCoeffs.begin(), reversedCoeffs.end());
    return reversedCoeffs;
}

void printMenu() {
    cout << "\nChoose an operation:\n";
    cout << "1. Add polynomials\n";
    cout << "2. Subtract polynomials\n";
    cout << "3. Multiply polynomials\n";
    cout << "4. Derivative of a polynomial\n";
    cout << "5. Integral of a polynomial\n";
    cout << "6. Evaluate polynomial\n";
    cout << "7. Get degree of a polynomial\n";
    cout << "8. Find root of a polynomial\n";
    cout << "9. Definite integral of a polynomial\n";
    cout << "10. Check equality of polynomials\n";
    cout << "11. Composition of polynomials\n";
    cout << "12. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    int degree1, degree2;
    cout << "Enter the degree of the first polynomial: ";
    cin >> degree1;
    vector<double> coeffs1(degree1 + 1);
    cout << "Enter the coefficients (real parts) from highest to lowest degree for the first polynomial: ";
    for (int i = degree1; i >= 0; --i) {
        double realPart;
        cout << "Coefficient for x^" << i << " (real): ";
        cin >> realPart;
        coeffs1[degree1 - i] = realPart;
    }
    coeffs1 = reverseCoefficients(coeffs1);

    cout << "Enter the degree of the second polynomial: ";
    cin >> degree2;
    vector<double> coeffs2(degree2 + 1);
    cout << "Enter the coefficients (real parts) from highest to lowest degree for the second polynomial: ";
    for (int i = degree2; i >= 0; --i) {
        double realPart;
        cout << "Coefficient for x^" << i << " (real): ";
        cin >> realPart;
        coeffs2[degree2 - i] = realPart;
    }
    coeffs2 = reverseCoefficients(coeffs2);

    Polynomial p1(coeffs1);
    Polynomial p2(coeffs2);
    Polynomial result;

    cout << "\nPolynomial 1: " << p1 << endl;
    cout << "Polynomial 2: " << p2 << endl;

    int choice;
    do {
        printMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                result = p1 + p2;
                cout << "Result of addition: " << result << endl;
                break;
            case 2:
                result = p1 - p2;
                cout << "Result of subtraction: " << result << endl;
                break;
            case 3:
                result = p1 * p2;
                cout << "Result of multiplication: " << result << endl;
                break;
            case 4: {
                int polyChoice;
                cout << "Choose polynomial (1 or 2): ";
                cin >> polyChoice;
                if (polyChoice == 1) {
                    result = p1.derivative();
                    cout << "Derivative of polynomial 1: " << result << endl;
                } else if (polyChoice == 2) {
                    result = p2.derivative();
                    cout << "Derivative of polynomial 2: " << result << endl;
                }
                break;
            }
            case 5: {
                int polyChoice;
                cout << "Choose polynomial (1 or 2): ";
                cin >> polyChoice;
                if (polyChoice == 1) {
                    result = p1.integral();
                    cout << "Integral of polynomial 1: " << result << endl; // Removed + C
                } else if (polyChoice == 2) {
                    result = p2.integral();
                    cout << "Integral of polynomial 2: " << result << endl; // Removed + C
                }
                break;
            }
            case 6: {
                int polyChoice;
                double x;
                cout << "Choose polynomial (1 or 2): ";
                cin >> polyChoice;
                cout << "Enter the value of x: ";
                cin >> x;
                if (polyChoice == 1) {
                    cout << "Evaluation of polynomial 1 at x = " << x << ": " << p1.evaluate(x) << endl;
                } else if (polyChoice == 2) {
                    cout << "Evaluation of polynomial 2 at x = " << x << ": " << p2.evaluate(x) << endl;
                }
                break;
            }
            case 7: {
                int polyChoice;
                cout << "Choose polynomial (1 or 2): ";
                cin >> polyChoice;
                if (polyChoice == 1) {
                    cout << "Degree of polynomial 1: " << p1.degree() << endl;
                } else if (polyChoice == 2) {
                    cout << "Degree of polynomial 2: " << p2.degree() << endl;
                }
                break;
            }
            case 8: {
                double guess;
                cout << "Enter an initial guess for the root of the first polynomial: ";
                cin >> guess;
                try {
                    double root = p1.getRoot(guess);
                    cout << "Root found: " << root << endl;
                } catch (const runtime_error& e) {
                    cout << e.what() << endl;
                }
                break;
            }
            case 9: {
                double x1, x2;
                cout << "Choose polynomial (1 or 2): ";
                int polyChoice;
                cin >> polyChoice;
                cout << "Enter the lower limit of integration: ";
                cin >> x1;
                cout << "Enter the upper limit of integration: ";
                cin >> x2;
                if (polyChoice == 1) {
                    cout << "Definite integral of polynomial 1 from " << x1 << " to " << x2 << ": " << p1.integral(x1, x2) << endl;
                } else if (polyChoice == 2) {
                    cout << "Definite integral of polynomial 2 from " << x1 << " to " << x2 << ": " << p2.integral(x1, x2) << endl;
                }
                break;
            }
            case 10:
                if (p1 == p2)
                    cout << "The polynomials are equal." << endl;
                else
                    cout << "The polynomials are not equal." << endl;
                break;
            case 11: {
                Polynomial compositionResult = p1.composition(p2);
                cout << "Composition of the first polynomial with the second: " << compositionResult << endl;
                break;
            }
            case 12:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 12);

    return 0;
}

