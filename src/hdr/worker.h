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
      explicit Worker(int* alg, bool *status, Parameters p, Lattice *lptr = nullptr, QObject *parent = 0);
  ~Worker();

  int* alg;
  bool *threadStatus;
  bool stop;
  bool run;
  int step;
  Lattice *l;
  MonteCarlo *model;

  signals:
      void finished();

      void sendStep(int);

      public slots:
      void process();

      void receiveDeleteThread();
      void receiveChangeAlgo();
      void receivePause();
      void receiveRun();
      void receiveNewBeta(double new_beta);
    };

#endif // WORKER_H
