#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

using namespace std;

class lattice {
protected:
	int N;	//number of spins
	int *L;	//lattice stores as array

public:
	lattice () : N (0), L (nullptr)	{cout << "lattice ()\n";}
	lattice (int N)	: N (N), L (new int [N])	{cout << "lattice (" << N << ")\n";}
<<<<<<< HEAD

=======
	
>>>>>>> 429d8ca218a82ea989d7430cfd917e09707ec872
	void fill_random ()	{
		srand(time(0));
		for (int i = 0; i < N; i++)	{
			L[i] = 2 * (rand() % 2) - 1;
		}
	}

<<<<<<< HEAD
	virtual void show ()	{}
=======
	virtual void show () {}
>>>>>>> 429d8ca218a82ea989d7430cfd917e09707ec872

	virtual ~lattice ()	{
		delete L;
		cout << "~lattice ()\n";
	}
};

class square_lattice : public lattice	{
public:
	square_lattice ()	{cout << "sq_lattice ()\n";}
	~square_lattice ()	{cout << "~sq_lattice ()\n";}
};

int main ()  {
	lattice l1;
	lattice *l = new square_lattice ();
	delete l;
	return 0;
}
