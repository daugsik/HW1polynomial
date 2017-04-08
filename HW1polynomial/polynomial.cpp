#include "polynomial.h"


// Overloaded <<: prints Cn * x^n + Cn-1 * X^n-1 + ... C1 * X + C0
ostream& operator<<(ostream &output, const Polynomial& p)
{
	output << p.print();
	return output;
}

/*
	Produces the string representation of the polynomial to be passed to
	output.

	Performs most of the print logic. Delegates the printing of individual
	terms to printHelper. Handles the printing of spaces between the terms
	and the printing of individual term signs.
*/
string Polynomial::print() const
{
	string toReturn = "";
	Term *index = NULL;
	index = head->next;

	// if the polynomial is empty, return 0.
	if (index == head)
	{
		return "0";
	}

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
	If the coefficient is negative, drops the negative, as print()
	handles expressing negativity.
*/
string Polynomial::printHelper(const Term& toPrint) const
{
	string toReturn = "";
	// If the coefficient is = 1, do not concatenate unless the power of
	// x is equal to 0.
	if (toPrint.coeff != 1 || toPrint.power == 0)
	{
		string temp = "";
		stringstream stream;
		stream << fixed << setprecision(1) << abs(toPrint.coeff);
		temp = stream.str();
		toReturn += temp;
	};
	
	// If the power of x is anything other than 0, concatenate x
	if (toPrint.power != 0)
	{
		toReturn += "x";

		// if the power anything other than 1, concatenate carat notation.
		if (toPrint.power != 1)
		{
			toReturn += "^";
			toReturn += to_string(toPrint.power);
		};
	};

	return toReturn;
};

// Constructor: the default is a 0-degree polynomial with 0.0 coefficient
// Member functions
Polynomial::Polynomial()
{
	Term *temp = new Term;
	temp->coeff = 0;
	temp->power = 0;
	temp->next = temp;
	temp->prev = temp;
	head = temp;
	temp = NULL;
	size = 0;
};

Polynomial::Polynomial(const Polynomial& p)
{
	Term *temp = new Term;
	temp->coeff = 0;
	temp->power = 0;
	temp->next = temp;
	temp->prev = temp;
	head = temp;
	temp = NULL;
	size = 0;
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

/*
	Finds the largest power of the polynomial.
*/
int Polynomial::degree() const
{
	return(head->next->power);
}

/*
	Searches for a specific power in the list. If it cannot
	find the power, it returns 0.
*/
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

/*
	Replaces or inserts a new term for a given power. If the power does not exist,
	creates a new term and inserts appropriately. If power DOES exist, creates new
	term, deletes existing term, and inserts new in its place.
*/
bool Polynomial::changeCoefficient(const double newCoefficient, const int power)
{
	Term *index = head->next;

	// if the list is empty, just add new term, unless term is 0.
	if (index == head && newCoefficient != 0)
	{
		return insert(index, newCoefficient, power);
	}

	for (index; index != head; index = index->next)
	{
		// if found, update coefficient to newCoefficient and return true.
		if (index->power == power)
		{
			// if coefficient is 0, remove term
			if (newCoefficient == 0)
			{
				return remove(index);
			}

			// otherwise, increment forward and delete previous node
			index = index->next;
			remove(index->prev);
			return insert(index, newCoefficient, power);;
		}

		// if the current term has a power < the one being sought
		// then the term does not currently exist. Perform an insertion
		// IF the coefficient is not 0 (i.e. a removal)
		if (index->power < power && newCoefficient != 0)
		{
			return insert(index, newCoefficient, power);
		}

	}

	// if the program reaches the end of the list, use the dummy header as
	// 'next' and perform the insertion.
	if (index == head && newCoefficient != 0)
	{
		return insert(index, newCoefficient, power);
	}

	// if program falls out of loop for some reason, return false
	return false;
}

// Arithmetic operators

/*
	Adds two polynomials together. Treats the calling Polynomial as the data struct
	and the argument polynomial as a queue. Assumes that there exists negative powers.
	A new polynomial is allocated and its functions are run to perform the arithmetic.

	If powers are equal, calls the newly allocated polynomial's changeCoefficient, where 
	the newCoefficient argument is the SUM of the two terms' coefficients.

	If the "data" polynomial's term power is less than the "queue's" term power, the data 
	index is iterated to a term with lower power.

	If the data polynomial's term power is greater than the queue's term power, the queue
	term is added to the newly allocated polynomial, and the queue index is incremented.
*/
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
			//moves forward to avoid a deletion
			index = index->next;
			toReturn->changeCoefficient((pIndex->coeff + index->prev->coeff), pIndex->power);

			// increment both indices
			pIndex = pIndex->next;

		}

		/*
			if to be added term has greater power than current index, insert before.
			Alternatively, if index has reached the end of its list of terms, append
			terms to the end of the list by using the dummy header as "next"
		*/
		else if (pIndex->power > index->power || index == toReturn->head)
		{
			toReturn->insert(index, pIndex->coeff, pIndex->power);

			//only increment pIndex in case of more > powers
			pIndex = pIndex->next;
		}

		/*
			if to be added term has power < index power, perform no additions or changes.
			If the index is pointing to the dummy header, do not increment index.
		*/
		else if (pIndex->power < index->power && index != toReturn->head)
		{
			// increment only the index
			index = index->next;
		}
	}

	return *toReturn;
}

/*
	Adds two polynomials together. Treats the calling Polynomial as the data struct
	and the argument polynomial as a queue. Assumes that there exists negative powers.
	A new polynomial is allocated and its functions are run to perform the arithmetic.

	If powers are equal, calls the newly allocated polynomial's changeCoefficient, where
	the newCoefficient argument is the DIFFERENCE of the two terms' coefficients.

	If the "data" polynomial's term power is less than the "queue's" term power, the data
	index is iterated to a term with lower power.

	If the data polynomial's term power is greater than the queue's term power, the queue
	term is added WITH A NEGATED INDEX to the newly allocated polynomial, and the queue 
	index is incremented.
*/
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

		//if equivalent powers are found, change coefficient to reflect addition
		if (pIndex->power == index->power)
		{
			//moves forward to avoid a deletion
			index = index->next;
			toReturn->changeCoefficient((index->prev->coeff - pIndex->coeff), pIndex->power);

			// increment both indices
			pIndex = pIndex->next;

		}

		/*
		if to be added term has greater power than current index, insert before.
		Alternatively, if index has reached the end of its list of terms, append
		terms to the end of the list by using the dummy header as "next"
		*/
		else if (pIndex->power > index->power || index == toReturn->head)
		{
			toReturn->insert(index, -(pIndex->coeff), pIndex->power);

			//only increment pIndex in case of more > powers
			pIndex = pIndex->next;
		}

		/*
		if to be added term has power < index power, perform no additions or changes.
		If the index is pointing to the dummy header, do not increment index.
		*/
		else if (pIndex->power < index->power && index != toReturn->head)
		{
			// increment only the index
			index = index->next;
		}
	}

	return *toReturn;
}

// Boolean comparison operators

/*
	Moves stepwise through both this and p polynomials. Checks only
	equality of coefficients and powers in each term with termEquality.
	At the first sign of difference, returns false. Once both pointers
	return to the head, returns true.
*/
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

/*
	Inverts == result.
*/
bool Polynomial::operator!=(const Polynomial& p) const
{
	// performs equality check and inverts result
	return !(*this == p);
}

// Assignment operators

/*
	Clears out currently held terms and updates list with terms in p
*/
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

	// if to-copy polynomial is empty, return.
	if (pIndex == p.head)
	{
		return;
	}


	// while pindex is not pointing to the to-copy list's head
	// continue copying terms into new Polynomial
	// Because of how insertion works, index stays constant
	while (pIndex != p.head)
	{
		insert(index, pIndex->coeff, pIndex->power);
		pIndex = pIndex->next;
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
	Term *index = head->next;

	if (index == head)
	{
		return;
	}

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
	Polynomial *temp = new Polynomial;
	*temp = *this + p;
	*this = *temp;
	return (*this);
}

Polynomial& Polynomial::operator-=(const Polynomial& p)
{
	Polynomial *temp = new Polynomial;
	*temp = *this - p;
	*this = *temp;
	return (*this);
}

/*
	Inserts one newly allocated term with the coefficient newCoefficient and power power.
	Uses "next" as a reference for where to insert. Once insertion is complete, increments
	size and exits.

	Returns false if a term with that power already exists (does not change existing term).
*/
bool Polynomial::insert(Term* next, const double newCoefficient, const int power)
{
	// if there is already a term, do not insert.
	if (coefficient(power) != 0)
	{
		return false;
	}

	Term *toInsert = new Term; // create new node to insert
	toInsert->coeff = newCoefficient;
	toInsert->power = power;

	toInsert->prev = next->prev; // assign pointer to next term
	toInsert->next = next; // assign prev to prev
	next->prev = toInsert; // prev to new term
	toInsert->prev->next = toInsert; // next to new term

	size++; // increment size

	return true;
}

/*
	Removes a term given by the pointer pos. Stores a temporary pointer
	to the next node, then updates prev and next nodes to point to each other.
	The memory pos points to is then deallocated, and pos is updated to
	next term.

	Returns false if Term points to a null value. Otherwise, assumes pointer
	is valid.
*/
bool Polynomial::remove(Term* pos)
{
	if (pos == NULL)
	{
		return false;
	}

	pos->next->prev = pos->prev; // next term's prev = pos.prev
	pos->prev->next = pos->next; // prev term's next = pos.next

	pos->next = NULL; // safety NULL assignments
	pos->prev = NULL;

	delete pos; // deallocate memory

	size--;	// decrement size

	return true;
}

int Polynomial::getSize() const
{
	return size;
}