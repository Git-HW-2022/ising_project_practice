#ifndef LATTICE_H
#define LATTICE_H

#include <iostream>
#include <assert.h>

class Exception : public std::exception {
private:
    std::string mError;
    int data;
public:
    Exception(const std::string& m_error, int data) : mError(m_error), data(data) {}

    const char* what() const noexcept {
        return mError.c_str();
    }

    int getData() {
        return data;
    }
};

class Lattice { //abstract
	Lattice& operator = (const Lattice &obj); //private assignment

protected:
    const unsigned int N; //number of spins
    int *L; //spins in array
    const unsigned int nbrS; //number of spin neighbors

public:
    Lattice(unsigned int N, unsigned int nbrs);
    Lattice(const Lattice &old);
    virtual ~Lattice();

    unsigned int getN() const;
    int* getL();
    unsigned int getNbrs() const;
    void fillRandom();
    int sumNbr(unsigned int index) const;
    double avgMagn() const;

    virtual void getNbrs(unsigned int index, unsigned int *arr) const = 0; //returns array of nbr indexes
    virtual void show() const = 0; //the pure virtual function, prints Lattice
};

class RectLattice : public Lattice {
	const unsigned int A, B; //Lattice sizes: A strings, B columns

public:
    RectLattice(unsigned int A, unsigned int B);
    virtual ~RectLattice();

	void getNbrs(unsigned int index, unsigned int *arr) const;
    void show() const;
};

class SquareLattice : public RectLattice {
public:
    squareLattice(unsigned int A);
};

class LinearLattice : public Lattice {
public:
    LinearLattice(unsigned int N);

    void getNbrs(unsigned int index, unsigned int *arr) const;
	void show() const;
};

class TridimensionalLattice : public Lattice {
	const unsigned int A, B, C; //Lattice sizes

public:
	TridimensionalLattice(unsigned int A, unsigned int B, unsigned int C);
	virtual ~TridimensionalLattice();

	void getNbrs(unsigned int index, unsigned int *arr) const;
	void show() const;
};

class cubic_Lattice : public TridimensionalLattice {
public:
	cubicLattice(unsigned int A);
};

#endif // LATTICE_H
