#include <iostream>
#include <vector> //essential
#include <stdlib.h>
#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <ctime>
#include <assert.h>

using namespace std;

inline bool vcontains(const vector <int> &v, int el);
bool vdel(vector <int> &v, int el);
int big_rand();

//FOR DEBUG:
void vshow (const char *s, const vector <int> &v) {
	cout << s << ": {";
	for (int i = 0; i < v.size(); i++)
		cout << v[i] << " ";
	cout << "}" << endl;
}

void vshow (const char *s, int *arr, int size) {
	cout << s << ": {";
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << "}" << endl;
}

class lattice { //abstract
protected:
	int N; //number of spins
	int *L; //spins in array
	int nbrs; //number of nbrs

public:
	lattice(int N, int nbrs) : N(N), L(new int[N]), nbrs(nbrs) {
		cout << "lattice(" << N << ")" << endl;
	}

	lattice(const lattice &old) : N(old.N), L(new int[N]), nbrs(nbrs) {
		cout << "lattice(" << N << ") copy constructor" << endl;
		for (int i = 0; i < N; i++)
			L[i] = old.L[i];
	}

	lattice& operator = (const lattice &obj) {
		cout << "opertator = (const lattice &obj) assignment" << endl;
		N = obj.N;
		L = new int[N];
		nbrs = obj.nbrs;
		for (int i = 0; i < N; i++)
			L[i] = obj.L[i];
		return *this;
	}

	void fill_random() {
		//srand(time(0));
		for (int i = 0; i < N; i++)
			L[i] = 2 * (rand() % 2) - 1;
	}

	int sum_nbr(int index) const { //returns sum of neighbour spins
		int *nbr_arr = new int[nbrs];
		get_nbrs(index, nbr_arr);
		int sum = L[nbr_arr[0]];
		for (int i = 1; i < nbrs; sum += L[nbr_arr[i]], i++);
		return sum;
	}

	virtual void get_nbrs(int index, int *arr) const = 0; //returns array of nbr indexes

	virtual void show() const = 0; //the pure virtual function, prints lattice

	double avg_magn() const {//returns average magnetization
		int sum = 0;
		for (int i = 0; i < N; i++)
			sum += L[i];
		return (double) sum / N;
	}

	virtual ~lattice() {
		delete [] L;
		cout << "~lattice()" << endl;
	}

	friend class Monte_Carlo;
};

class square_lattice : public lattice {
	int A, B; //lattice sizes: A strings, B columns

public:
	square_lattice(int A, int B) : lattice(A * B, 4), A(A), B(B) {
		cout << "sq_lattice(" << A << "*" << B << ")" << endl;
	}

	void get_nbrs(int index, int *arr) const { //returns array of nbr indexes [U, D, L, R]
		int a = index / B, b = index % B;
		arr[0] = B * ((a + A - 1) % A) + b;
		arr[1] = B * ((a + 1) % A) + b;
		arr[2] = B * a + (b + B - 1) % B;
		arr[3] = B * a + (b + 1) % B;
	}

	void show() const {
		for (int i = 0; i < A; i++) {
			for (int j = 0; j < B; j++)	{
				if (L[B * i + j] > 0)
					cout << "+"; //+1
				else
					cout << "."; //-1
			}
			cout << endl;
		}
	}

	~square_lattice() {
		cout << "~sq_lattice()" << endl;
	}
};

class parameters {
protected:
	//double T; //temperature in Kelvins - needs later
	double beta; //beta = 1/kT
	double H; //outer magnetic field
	double J; //exchange energy
	double mu; //magnetic moment

public:
	parameters(double beta, double H = 0, double J = 1, double mu = 1) : beta(beta), H(H), J(J), mu(mu) {
		cout << "parameters()" << endl;
	}

	parameters(const parameters &old) : beta(old.beta), H(old.H), J(old.J), mu(old.mu) {
		cout << "parameters() copy constructor" << endl;
	}

	virtual ~parameters() {
		cout << "~parameters()" << endl;
	}
};

class Monte_Carlo : public parameters {
	lattice *l;

public:
	Monte_Carlo (parameters &p, lattice *l) : parameters(p), l(l) {
		cout << "Monte_Carlo()" << endl;
	}

	void simulate(int steps) const {
		int *prob_arr = new int [1 + l->nbrs]; //array of all possible probabilities
		for (int i = 0; i <= l->nbrs; i++)
			prob_arr[i] =  round(RAND_MAX / (1 + exp(-2 * beta *((2 * i - l->nbrs) + mu * H))));
		for (int i = 0; i < steps; i++) {
			for (int j = 0; j < l->N; j++) {
				int rand_spin = big_rand() % l->N;
				int prob = prob_arr[(l->nbrs + l->sum_nbr(rand_spin)) / 2];
				l->L[rand_spin] = def_spin(prob);
			}
		}
		delete [] prob_arr;
	}

	void clasters_simulate() const {
		int steps = 20 * sqrt(l->N) * exp(-3 * beta);
		double prob = RAND_MAX * (1 - exp(-2 * beta)); //magical number
		int *nbr_arr = new int[l->nbrs];
		for (int j = 0; j < steps; j++) {
			int spin = big_rand() % l->N;
			vector <int> Claster {spin}, Pocket {spin};
			while (Pocket.size()) {
				spin = Pocket[big_rand() % Pocket.size()]; //randomly choose from pocket
				l->get_nbrs(spin, nbr_arr);
				for (int i = 0; i < l->nbrs; i++) {
					if (rand() < prob && //take spin with probability
						l->L[spin] == l->L[nbr_arr[i]] && !vcontains(Claster, nbr_arr[i])) {
						Pocket.push_back(nbr_arr[i]); //add it to pocket
						Claster.push_back(nbr_arr[i]); //and to claster
					}
				}
				assert(vdel(Pocket, spin)); //delete from pocket
				//vshow("Pocket", Pocket);
				//vshow("Claster", Claster);
			}
			for (auto i = Claster.begin(), end = Claster.end(); i != end; i++)
				l->L[*i] = -l->L[*i]; //flipping claster
		}
		delete nbr_arr;
	}

	int def_spin(int plus_prob) const {
		int rand_prob = rand();
		if (rand_prob < plus_prob)
			return +1;
		return -1;
	}

	void test();

	~Monte_Carlo() {
		delete l;
		cout << "~Monte_Carlo()" << endl;
	}
};

void Monte_Carlo::test() {//test here
	l->fill_random();
	cout << "step 0:" << endl;
	l->show();
	cout << "avg. magn = " << l->avg_magn() << endl;

	int steps = 300;
	//simulate(steps);
	clasters_simulate();
	cout << "step " << steps << ":" << endl;
	l->show();
	cout << "avg. magn = " << l->avg_magn() << endl;
	//lattice l1 = *l;
	//l1.show();
}

int main() {
	parameters p(0.9); //beta, H
	square_lattice *l = new square_lattice(64, 64);
	Monte_Carlo model(p, l);
	model.test();
	return 0;
}

inline bool vcontains(const vector <int> &v, int el) { //checks if vector contains element
    return find(v.begin(), v.end(), el) != v.end();
}

bool vdel(vector <int> &v, int el) { //deletes element from vector. returns false if not found
	auto del = find(v.begin(), v.end(), el);
	if (del != v.end()) {
		v.erase(del);
		return true;
	}
	return false;
}

int big_rand() { //30-bit random number
	int r = rand() & 0x7FFF;
	r = (r << 15) | (rand() & 0x7FFF);
	return r;
}
