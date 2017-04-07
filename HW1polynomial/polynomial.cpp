#include "polynomial.h"


// Overloaded <<: prints Cn * x^n + Cn-1 * X^n-1 + ... C1 * X + C0
ostream& operator<<(ostream &output, const Polynomial& p)
{
	output << p.print();
	return output;
}

// iterates through list until it returns to header.
string Polynomial::print() const
{
	string toReturn = "";
	Term *index = NULL;
	index = head->next;

	// if the first term is negative, tack on the minus
	// at the front of the string
	if (index->coeff < 0)
	{
		toReturn += "-";
	};

	// while there are still values in the list, print them out
	while (index != head)
	{
		toReturn += printHelper(*index);
		index = index->next;

		// if there exists another term, identify what sign it is
		// and add + or - accordingly.
		if (index != head)
		{
			// negative case
			if (index->coeff < 0)
			{
				toReturn += " - ";
			}
			// positive case, 0 values should not exist
			else
			{
				toReturn += " + ";
			};
		};
	};

	// returns completed polynomial string
	return toReturn;
}

/*
	returns a single string in the form "Cx^k" with no spaces.
*/
string Polynomial::printHelper(const Term& toPrint) const
{
	string toReturn = "";
	// If the coefficient is = 1, do not concatenate unless the power of
	// x is equal to 0.
	if (toPrint.coeff != 1 || toPrint.power == 0)
	{
		toReturn += toPrint.coeff;
	};
	
	// If the power of x is anything other than 0, concatenate x
	if (toPrint.power != 0)
	{
		toReturn += "x";

		// if the power anything other than 1, concatenate carat notation.
		if (toPrint.power != 1)
		{
			toReturn += "^";
			toReturn += toPrint.power;
		};
	};

};

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
	copyTerms(p);
	size = p.size; // copy size
};

Polynomial::~Polynomial()
{
	// clear all nonhead terms.
	clearTerms();
	
	delete head; // deallocate dummy head
	head = NULL;
};

// assumes that 0 is an acceptable value for an empty Polynomial
// also assumes polynomial is ordered in descending numeric
int Polynomial::degree() const
{
	return(head->next->power);
}

// returns the coefficient of the x^power term.
double Polynomial::coefficient(const int power) const
{
	Term *index = head->next;

	for (index; index != head; index = index->next)
	{
		// if found, return coeff.
		if (index->power == power)
		{
			return index->coeff;
		}

		// if the current term has a power < the one being sought
		// the coefficient is 0.
		if (index->power < power)
		{
			return 0;
		}
	}

	// if the program goes through the entire list and falls out of the for loop,
	// return 0 as it was not found.
	return 0;
}


// replaces the coefficient of the x^power term
// assumes that the term must already exist in the list or else the function
// returns false.
bool Polynomial::changeCoefficient(const double newCoefficient, const int power)
{
	Term *index = head->next;

	for (index; index != head; index = index->next)
	{
		// if found, update coefficient to newCoefficient and return true.
		if (index->power == power)
		{
			index->coeff = newCoefficient;
			index = NULL;
			return true;
		}

		// if the current term has a power < the one being sought
		// the coefficient is 0. Do not update anything and 
		if (index->power < power)
		{
			return false;
		}
	}

	// if program fall sout of loop, return false
	return false;
}

// Arithmetic operators
Polynomial Polynomial::operator+(const Polynomial& p) const
{
	// creates a copy of "this" polynomial to perform operations on
	Polynomial *toReturn = new Polynomial(*this);

	// intialize both indices to first term (if any)
	Term *index = toReturn->head->next;
	Term *pIndex = p.head->next;

	// while p still contains unvisited terms
	while (pIndex != p.head)
	{
		//if equivalent powers are found, change coefficient to reflect addition
		if (pIndex->power == index->power)
		{
			toReturn->changeCoefficient((pIndex->coeff + index->coeff), pIndex->power);

			// increment both indices
			pIndex = pIndex->next;
			index = index->next;
		}

		/*
			if to be added term has greater power than current index, insert before.
			Alternatively, if index has reached the end of its list of terms, append
			terms to the end of the list by using the dummy header as "next"
		*/
		if (pIndex->power > index->power || index == toReturn->head)
		{
			toReturn->insert(index, pIndex->coeff, pIndex->power);

			//only increment pIndex in case of more > powers
			pIndex = pIndex->next;
		}

		/*
			if to be added term has power < index power, perform no additions or changes.
			If the index is pointing to the dummy header, do not increment index.
		*/
		if (pIndex->power < index->power && index != toReturn->head)
		{
			// increment only the index
			index = index->next;
		}
	}

	toReturn->normalize();
	return *toReturn;
}

Polynomial Polynomial::operator-(const Polynomial& p) const
{
	// creates a copy of "this" polynomial to perform operations on
	Polynomial *toReturn = new Polynomial(*this);

	// intialize both indices to first term (if any)
	Term *index = toReturn->head->next;
	Term *pIndex = p.head->next;

	// while p still contains unvisited terms
	while (pIndex != p.head)
	{
		//if equivalent powers are found, change coefficient to reflect subtraction
		// note that p is the value that is negated.
		if (pIndex->power == index->power)
		{
			toReturn->changeCoefficient((index->coeff - pIndex->coeff), pIndex->power);

			// increment both indices
			pIndex = pIndex->next;
			index = index->next;
		}

		/*
			if to be added term has greater power than current index, insert before.
			Alternatively, if index has reached the end of its list of terms, append
			terms to the end of the list by using the dummy header as "next"

			coefficient is negated prior to passing into insert.
		*/
		if (pIndex->power > index->power || index == toReturn->head)
		{
			toReturn->insert(index, -(pIndex->coeff), pIndex->power);

			//only increment pIndex in case of more > powers
			pIndex = pIndex->next;
		}

		/*
		if to be added term has power < index power, perform no additions or changes.
		If the index is pointing to the dummy header, do not increment index.
		*/
		if (pIndex->power < index->power && index != toReturn->head)
		{
			// increment only the index
			index = index->next;
		}
	}

	toReturn->normalize();
	return *toReturn;
}

void Polynomial::normalize()
{
	Term *index = head->next;

	while (index != head)
	{
		if (index->coeff == 0 && index->power == 0)
		{
			remove(index);	// index is incremented in remove function
		}
		
		else
		{
			index = index->next;
		}
	}
}

// Boolean comparison operators
bool Polynomial::operator==(const Polynomial& p) const
{
	//
	Term *a = NULL;
	Term *b = NULL;
	bool isEqual = true;

	a = head->next;
	b = p.head->next;

	// special case: if terms are similar but one has
	// more terms, run comparison of term as it will
	// compare against the head and isEqual will become false.

	while ((a != head || b != p.head) && isEqual)
	{
		// calls helper to see if terms are equal
		isEqual = termEquality(*a, *b);
		a = a->next;
		b = b->next;
	}

	a = NULL; // safety null assignments
	b = NULL;
	return isEqual; 
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
	this->copyTerms(p);
	return *this;
}

/*
	Creates newly allocated terms from reference Polynomial p.
	Used in copy constructor and assignment operator. First
	clears any existing terms and copies in new terms.
*/
void Polynomial::copyTerms(const Polynomial& p)
{
	clearTerms();

	// two indices to interate through polynomials
	Term *pIndex = p.head->next;
	Term *index = head;

	// while pindex is not pointing to the to-copy list's head
	// continue copying terms into new Polynomial
	while (pIndex != p.head)
	{
		insert(index, pIndex->coeff, pIndex->power);
		index = index->next;
	}

	index = NULL; // safety null assignment
	pIndex = NULL;
}

/* 
	Helper for Assignment Operator: cleans out all Terms
	and copies polynomial passed in. Also used in destructor.
 */
void Polynomial::clearTerms()
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
	index = NULL;
}

Polynomial& Polynomial::operator+=(const Polynomial& p)
{
	return (*this + p);
}

Polynomial& Polynomial::operator-=(const Polynomial& p)
{
	return (*this - p);
}

// Assumes that there are no terms with identical powers.
bool Polynomial::insert(Term* next, const double newCoefficient, const int power)
{
	Term *toInsert = new Term; // create new node to insert
	toInsert->coeff = newCoefficient;
	toInsert->power = power;

	toInsert->prev = next->prev; // assign pointer to next term
	toInsert->next = next; // assign prev to prev
	next->prev = toInsert; // prev to new term
	toInsert->prev->next = toInsert; // next to new term

	size++; // increment size
}

// Assumes this is not the dummy header term.
bool Polynomial::remove(Term* pos)
{
	Term *temp = pos->next;

	pos->next->prev = pos->prev; // next term's prev = pos.prev
	pos->prev->next = pos->next; // prev term's next = pos.next

	pos->next = NULL; // safety NULL assignments
	pos->prev = NULL;

	delete pos; // deallocate memory

	pos = temp; // moves pos to next node.
	temp = NULL;

	size--;	// decrement size
}