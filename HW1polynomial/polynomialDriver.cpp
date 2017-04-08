/* -------------------polynomialDriver.cpp-------------------------
Dongkyu Daniel Kim, CSS343A, ##
Creation: April 5th, 2017
Last Accessed: April 7th, 2017

----------------------------------------------------------
Purpose:
	This driver tests the functionality of the polynomial class.
	No special features have been used. However, I have assumed
	that the use of double means that displaying at least one
	decimal place would be a good idea.

---------------------------------------------------------------*/
#include "polynomial.h"
#define TEST_SIZE 5

void driverPrint(const string& name, const Polynomial& toPrint);

int main()
{
	// Create two polynomials
	Polynomial a, b;

	cout << "Intialization" << endl;
	driverPrint("a", a);
	driverPrint("b", b);
	cout << "--" << endl;


	// Manual insertions
	for (int i = 0; i < TEST_SIZE; i++)
	{
		double j = double(i) / 2;
		a.changeCoefficient(i, TEST_SIZE - i);
		b.changeCoefficient(j, i);
	}

	cout << "Term Insertion" << endl;
	driverPrint("a", a);
	driverPrint("b", b);
	cout << "--" << endl;


	// Change Coefficients
	// Switches polynomials a and b term by term
	for (int i = 0; i < TEST_SIZE; i++)
	{
		double j = double(i) / 2;
		a.changeCoefficient(j, i);
		b.changeCoefficient(i, TEST_SIZE - i);
	}

	a.changeCoefficient(5, 0);
	b.changeCoefficient(100, 0);

	cout << "Term Change" << endl;
	driverPrint("a", a);
	driverPrint("b", b);
	cout << "--" << endl;

	// Manual Deletions
	a.changeCoefficient(0, 1);
	b.changeCoefficient(0, 2);

	a.changeCoefficient(0, 1);
	b.changeCoefficient(0, 2);

	cout << "Term Deletion" << endl;
	driverPrint("a", a);
	driverPrint("b", b);
	cout << "--" << endl;


	// Copy test
	cout << "Copy Test" << endl;
	Polynomial c = a;
	Polynomial d = a;

	driverPrint("c", c);
	driverPrint("d", d);

	d = b;

	driverPrint("d", d);
	cout << "--" << endl;
	
	
	// Polynomial Logic
	cout << "Polynomial Logic" << endl;
	cout << boolalpha;

	bool tempValue = a == b;	// false
	cout << tempValue << endl;

	tempValue = a == c;			// true
	cout << tempValue << endl;

	tempValue = a != d;			// true
	cout << tempValue << endl;

	tempValue = a != a;			// false
	cout << tempValue << endl;

	cout << "--" << endl;


	// Polynomial Arithmetic
	cout << "Polynomial Arithmetic" << endl;

	c = a + b;
	cout << "c = a + b" << endl;
	driverPrint("a", a);
	driverPrint("b", b);
	driverPrint("c", c);

	d = b - a;
	cout << "d = b - a" << endl;
	driverPrint("d", d);

	c += c;
	cout << "c += c" << endl;
	driverPrint("c", c);

	c -= d;
	cout << "c -= d" << endl;
	driverPrint("d", d);

	c -= c;
	cout << "c -= c" << endl;
	driverPrint("c", c);

	c += d;
	cout << "c += d" << endl;
	driverPrint("c", c);

	cout << "Polynomial a stats:" << endl;
	cout << "\tDegree: " << a.degree() << endl;
	cout << "\tCoeff of power 3: " << a.coefficient(3) << endl;

	cout << "Polynomial b stats:" << endl;
	cout << "\tDegree: " << b.degree() << endl;
	cout << "\tCoeff of power 3: " << b.coefficient(3) << endl;

	return 0;
}


/*-------------------- driverPrint --------------------------
driverPrint: prints out the name(size) of the polynomial
along with its string formatted output. For neatness.

preconditions:
	is given the name that corresponds to the polynomial
	to be printed.
postconditions:
	outputs a labeled polynomial string.
--------------------------------------------------------------*/
void driverPrint(const string& name, const Polynomial& toPrint)
{
	cout << "\t" << name << "(" << toPrint.getSize() << "): " << toPrint << endl;
}