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
	for (int i = 1; i < TEST_SIZE; i++)
	{
		a.changeCoefficient(i, TEST_SIZE - i);
		b.changeCoefficient(i*2, i);
	}

	cout << "Term Insertion" << endl;
	driverPrint("a", a);
	driverPrint("b", b);
	cout << "--" << endl;


	// Change Coefficients
	for (int i = 1; i < TEST_SIZE; i++)
	{
		a.changeCoefficient(i*2, i);
		driverPrint("a", a);
		b.changeCoefficient(i, TEST_SIZE - i);
		driverPrint("b", b);
	}

	cout << "Term Change" << endl;
	driverPrint("a", a);
	driverPrint("b", b);


	// Manual Deletions
	a.changeCoefficient(0, 1);
	b.changeCoefficient(0, 2);

	cout << "Term Deletion" << endl;
	driverPrint("a", a);
	driverPrint("b", b);
	cout << "--" << endl;


	// Copy test
	Polynomial c = a;
	Polynomial d = a;

	driverPrint("c", c);
	driverPrint("d", d);

	d = b;

	driverPrint("d", d);
	cout << "--" << endl;
	
	
	// Polynomial Logic
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
	d -= d;
	cout << "d -= d" << endl;
	driverPrint("d", d);

	return 0;
}

void driverPrint(const string& name, const Polynomial& toPrint)
{
	cout << name << "(" << toPrint.getSize() << "): " << toPrint << endl;
}