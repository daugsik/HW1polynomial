#include "polynomial.h"


// Overloaded <<: prints Cn * x^n + Cn-1 * X^n-1 + ... C1 * X + C0
ostream& operator<<(ostream &output, const Polynomial& p)
{

}

void Polynomial::ostreamHelper() const
{

}

// Constructor: the default is a 0-degree polynomial with 0.0 coefficient
// Member functions
Polynomial::Polynomial()
{
	Term *temp = new Term;
	temp->coeff = 0;
	temp->power = 0;
	head = temp;
	temp = NULL;
	size = 0;
};

Polynomial::Polynomial(const Polynomial& p)
{
	Term *index = NULL;

	// keep track of place in to-copy polynomial
	index = p.head->next;

	// while to-copy polynomial is not fully iterated through, copy terms
	while (index != p.head)
	{
		// add every new term to the new polynomial,
		// keep in mind every copy should be deep
	}

	size = p.size; // copy size
};

Polynomial::~Polynomial()
{
	Term *index = NULL;
	index = head->next; // moves to next node.

	// if the polynomial is empty, just jump to deleting dummy header
	// else, iterate through list, removing one at a time.
	while (index != head)
	{
		index = index->next; // moves forward 1
		remove(index->prev); // remove() handles updating "next" and "prev" pointers
	}
	
	delete index; // deallocate dummy head
	index = NULL;
};


// Arithmetic operators
Polynomial Polynomial::operator+(const Polynomial& p) const
{

}

Polynomial Polynomial::operator-(const Polynomial& p) const
{

}

// Boolean comparison operators
bool Polynomial::operator==(const Polynomial& p) const
{

}

// Performs a check on two terms from different Polynomials
bool Polynomial::termEquality(const Term& a, const Term& b) const
{
	return (a.coeff == b.coeff && a.power == b.power);
}

bool Polynomial::operator!=(const Polynomial& p) const
{
	// performs equality check and inverts result
	return !(*this == p);
}

// Assignment operators
Polynomial& Polynomial::operator=(const Polynomial& p)
{

}

Polynomial& Polynomial::operator+=(const Polynomial& p)
{

}

Polynomial& Polynomial::operator-=(const Polynomial& p)
{

}

bool Polynomial::insert(Term* prev, const double newCoefficient, const int power)
{
	Term *toInsert = new Term; // create new node to insert
	toInsert->coeff = newCoefficient;
	toInsert->power = power;

	toInsert->next = prev->next; // assign pointer to next term
	toInsert->prev = prev; // assign prev to prev
	prev->next = toInsert; // prev to new term
	toInsert->next->prev = toInsert; // next to new term

	size++; // increment size
}

bool Polynomial::remove(Term* pos)
{
	pos->next->prev = pos->prev; // next term's prev = pos.prev
	pos->prev->next = pos->next; // prev term's next = pos.next

	pos->next = NULL; // safety NULL assignments
	pos->prev = NULL;

	delete pos; // deallocate memory
	pos = NULL;
	size--;	// decrement size
}