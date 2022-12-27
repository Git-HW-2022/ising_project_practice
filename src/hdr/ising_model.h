#ifndef ISING_MODEL_H
#define ISING_MODEL_H

#include "hdr/lattice.h"
#include <iostream>
#include <vector>

#ifdef DEBUG
#include "debug.h" //debug functions
#endif

class Parameters {
protected:
    double beta; //beta = 1/kT
    double H; //outer magnetic field
    double J; //exchange energy
    double mu; //magnetic moment

public:
    Parameters(double beta = 0.4, double H = 0, double J = 1, double mu = 1);
    virtual ~Parameters();

    void setBeta(const double new_beta);
};

class MonteCarlo : public Parameters {
public:
    MonteCarlo(Parameters &p);
    void heatBathSimulate(Lattice *l, int steps = 1) const;
    void clustersSimulate(Lattice *l, int steps = 1) const;
    int defSpin(int plus_prob) const;
    void plotMagnBeta(Lattice *l, const std::vector <double> &beta_points, std::vector <double> &magn_points, const int steps, const int averaging, const int algo);
    void test(Lattice *l);
};

#endif // ISING_MODEL_H
