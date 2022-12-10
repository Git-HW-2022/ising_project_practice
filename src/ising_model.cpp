#include "ising_model.h"
#include "funcs.h"
#include <assert.h>
#include <math.h>
#include <fstream>

Parameters::Parameters(double beta, double H, double J, double mu) :
    beta(beta), H(H), J(J), mu(mu) {
}

void Parameters::setBeta(const double new_beta) {
    beta = new_beta;
}

Parameters::~Parameters() {
}

MonteCarlo::MonteCarlo(Parameters &p) : parameters(p) {
}

void MonteCarlo::heatBathSimulate(Lattice *l, int steps) const {
    int rand_spin, prob, nbrs = l->getNbrs(), *L = l->getL(), N = l->getN();
    int prob_arr[1 + 2 * nbrs]; // Array of all possible probabilities
    for (int i = -nbrs; i <= nbrs; ++i) // Filling the array
        prob_arr[i + nbrs] = RAND_MAX / (1 + exp(-2 * beta * i - mu * H));
    for (int i = 0; i < steps; ++i) {
        for (int j = 0; j < N; ++j) {
            rand_spin = randInRange(0, N); // Choose an arbitrary spin
            prob = prob_arr[l->sumNbr(rand_spin) + nbrs]; // Take the previously calculated probability from the array
            L[rand_spin] = def_spin(prob); // Assign +1 or -1
        }
    }
}

void MonteCarlo::clustersSimulate(Lattice *l, int steps) const {
    int spin, *L = l->getL(), N = l->getN();
    unsigned int nbrs = l->getNbrs(), nbr_arr[nbrs];
    int prob = RAND_MAX * (1 - exp(-2 * beta)); // The magic number
    for (int j = 0; j < steps; ++j) {
        spin = bigRand() % N; 						// Arbitrary choice of spin
        std::vector <int> Cluster {spin}, Pocket {spin}; // Put the spin in the cluster and in the pocket
        while (!Pocket.empty()) {
            spin = Pocket[big_rand() % Pocket.size()]; 	// An arbitrary choice from the pocket
            l->getNbrs(spin, nbr_arr); 				// Get neighbors spin
            for (unsigned int i = 0; i < nbrs; ++i) { 			// Check all the neighbors:
                if (L[spin] == L[nbr_arr[i]] && 			// If the neighbor's spin is the same
                    !vContains(Cluster, nbr_arr[i]) && 		// and it's not in the cluster yet,
                    rand() < prob) { 							// then with probability prob
                    Pocket.push_back(nbr_arr[i]); 				// Add to Pocket
                    Cluster.push_back(nbr_arr[i]);				// Add to Cluster
                }
            }
            vDel(Pocket, spin); 						// Remove from pocket
        }
        for (auto i = Cluster.begin(); i != Cluster.end(); ++i)
            L[*i] = - L[*i]; 						// Flip the whole cluster
        if (Cluster.size() > 5 * l->getN() / 6) // Cuts unnecessary calculations
            break;
    }
}

int MonteCarlo::defSpin(int plus_prob) const {
    int rand_prob = rand();
    if (rand_prob < plus_prob)
        return 1;
    return -1;
}

void MonteCarlo::plotMagnBeta(Lattice *l, const vector <double> &beta_points, vector <double> &magn_points, const int steps, const int averaging, const int algo) {
    try {
        if (averaging <= 0)
			throw Exception("averaging must be positive, you entered: ", averaging);

		magn_points.clear();
		std::cout << "Plot of the function average magnetization from temperature beta, avg_magn(beta)" << std::endl;
		if (algo == 0)
			std::cout << "Heat bath algorithm" << std::endl;
		if (algo == 1)
			std::cout << "Clasters algorithm" << std::endl;
		for (auto i = beta_points.begin(); i != beta_points.end(); ++i) {
			beta = *i;
			double avg_magn = 0;
			double mes;
			for(int j = 0; j < averaging; j++) {
				l->fillRandom();
				if (algo == 0)
					heatBathSimulate(l, steps);
				if (algo == 1)
					clustersSimulate(l, steps);
				mes = l->avgMagn();
				avg_magn += abs(mes);
			}
			avg_magn /= averaging;
			magn_points.push_back(avg_magn);
			std::cout << "beta = " << beta << "\tavg_magn = " << magn_points.back() << std::endl;
		}
	}
	catch (Exception &exc) {
        std::cout << exc.what() << exc.GetData() << std::endl;
    }
}

void MonteCarlo::test(Lattice *l) {//test here
    l->fillRandom();
    std::cout << "step 0:" << std::endl;
    l->show();
    std::cout << "avg. magn = " << l->avgMagn() << std::endl;

    int steps = 300;
	heatBathSimulate(l, steps);
	//clusters_simulate(l);
    std::cout << "step " << steps << ":" << std::endl;
    l->show();
    std::cout << "avg. magn = " << l->avg_magn() << std::endl;
}

int simulationExample() {
    srand((unsigned)time(NULL));
    parameters p(0.55); //beta
    square_lattice *l = new square_lattice(10);
    Monte_Carlo model(p);
    model.test(l);
    delete l;
    return 0;
}
