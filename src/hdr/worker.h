#ifndef WORKER_H
#define WORKER_H

#include "hdr/ising_model.h"
#include <QMainWindow>
#include <QObject>
#include <QPainter>

namespace Ui {
class MainWindow;
}

class Worker : public QObject
{
    Q_OBJECT

public:
    explicit Worker(int* alg, bool *Status, Parameters p, Lattice *lptr = nullptr, QObject *parent = 0);
    ~Worker();

    int* alg;
    bool *Thread_status;
    bool Stop;
    bool Run;
    int step;
    Lattice *l;
    MonteCarlo *model;

signals:
    void finished();

    void sendStep(int);

public slots:
    void process();

    void recieveDeleteThread();
    void recieveChangeAlgo();
    void recievePause();
    void recieveRun();
    void recieveNewBeta(double new_beta);
};

#endif // WORKER_H
