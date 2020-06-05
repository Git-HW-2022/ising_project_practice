#include "ising_model.h"
#include <assert.h>
#include <math.h>
#include <fstream>

parameters::parameters(double beta, double H, double J, double mu) :
    beta(beta), H(H), J(J), mu(mu) {
#ifdef DEBUG
        cout << "parameters()" << endl;
#endif
}

void parameters::set_beta(const double new_beta) {
        beta = new_beta;
}

parameters::~parameters() {
#ifdef DEBUG
    cout << "~parameters()" << endl;
#endif
}

Monte_Carlo::Monte_Carlo(parameters &p) : parameters(p) {
#ifdef DEBUG
    cout << "Monte_Carlo()" << endl;
#endif
}

void Monte_Carlo::heat_bath_simulate(lattice *l, int steps) const {
    int rand_spin, prob, nbrs = l->getnbrs(), *L = l->getL(), N = l->getN();
	int prob_arr[1 + 2 * nbrs]; // ������ ���� ��������� ������������
	for (int i = -nbrs; i <= nbrs; ++i) // ���������� �������
		prob_arr[i + nbrs] = RAND_MAX / (1 + exp(-2 * beta * i - mu * H));
	for (int i = 0; i < steps; ++i) {
		for (int j = 0; j < N; ++j) {
			rand_spin = big_rand() % N; // ������� ������������ ����
			prob = prob_arr[l->sum_nbr(rand_spin) + nbrs]; // ����� ����������� ����� �����������
			L[rand_spin] = def_spin(prob); // ��������� +1 ��� -1
		}
	}
}

void Monte_Carlo::clasters_simulate(lattice *l, int steps) const {
    int spin, *L = l->getL(), N = l->getN();
    unsigned int nbrs = l->getnbrs(), nbr_arr[nbrs];
	int prob = RAND_MAX * (1 - exp(-2 * beta)); // ���������� �����
	for (int j = 0; j < steps; ++j) {
		spin = big_rand() % N; 						// ������������ ����� �����
		vector <int> Claster {spin}, Pocket {spin}; // ������ ��� � ������� � � ������
		while (!Pocket.empty()) {
			spin = Pocket[big_rand() % Pocket.size()]; 	// ������������ ����� �� �������
			l->get_nbrs(spin, nbr_arr); 				// �������� ������� �����
			for (unsigned int i = 0; i < nbrs; ++i) { 			// ��������� ���� �������:
				if (L[spin] == L[nbr_arr[i]] && 			// ���� ���� ������ ���������
					!vcontains(Claster, nbr_arr[i]) && 		// � ��� ��� ��� � ��������,
					rand() < prob) { 							// �� � ������������ prob
					Pocket.push_back(nbr_arr[i]); 				// ���������� � ������
					Claster.push_back(nbr_arr[i]);				// ���������� � �������
				}
			}
			vdel(Pocket, spin); 						// ������� �� �������
		}
		for (auto i = Claster.begin(); i != Claster.end(); ++i)
			L[*i] = - L[*i]; 						// ��������� ��������
		if (Claster.size() > 5 * l->getN() / 6) //cuts unnecessary calculations
			break;
    }
}

int Monte_Carlo::def_spin(int plus_prob) const {
    int rand_prob = rand();
    if (rand_prob < plus_prob)
        return 1;
    return -1;
}

void Monte_Carlo::plot_magn_beta(lattice *l, const vector <double> &beta_points, vector <double> &magn_points, const int steps, const int averaging, const int algo) {
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
				l->fill_random();
				if (algo == 0)
					heat_bath_simulate(l, steps);
				if (algo == 1)
					clasters_simulate(l, steps);
				mes = l->avg_magn();
				avg_magn += abs(mes);
			}
			avg_magn /= averaging;
			magn_points.push_back(avg_magn);
			std::cout << "beta = " << beta << "\tavg_magn = " << magn_points.back() << std::endl;
		}
	}
	catch (Exception &exc) {
        cout << exc.what() << exc.Get_data() << endl;
    }
}

void Monte_Carlo::test(lattice *l) {//test here
    l->fill_random();
    cout << "step 0:" << endl;
    l->show();
    cout << "avg. magn = " << l->avg_magn() << endl;

    int steps = 300;
	heat_bath_simulate(l, steps);
    //clasters_simulate(l);
    cout << "step " << steps << ":" << endl;
    l->show();
    cout << "avg. magn = " << l->avg_magn() << endl;
}

#if 0
int main() {
    srand((unsigned)time(NULL));
    parameters p(0.55); //beta
    square_lattice *l = new square_lattice(0);
    Monte_Carlo model(p);
    model.test(l);
    delete l;
    return 0;
}
#endif
