#ifndef FUNCS_H
#define FUNCS_H

#include <stdlib.h>
#include <vector>

int calcPlot(const char* f_input, const char* f_output, int lsize, int algo, int steps, int averaging = 1);

bool vContains(const std::vector <int> &v, int el);
bool vDel(std::vector <int> &v, int el);
void vLinfill(std::vector <double> &v, const double start, const double end, const int points);
int bigRand();
int randInRange(int x, int y);
int big30Bit();

#endif // FUNCS_H
