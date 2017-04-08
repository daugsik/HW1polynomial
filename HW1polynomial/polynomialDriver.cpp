/*
	CSS 343 Spring 2017
	4/7/2017
	Dongkyu Daniel Kim

	Driver for polynomial.cpp

*/
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

	return 0;
}

void driverPrint(const string& name, const Polynomial& toPrint)
{
	cout << "\t" << name << "(" << toPrint.getSize() << "): " << toPrint << endl;
}