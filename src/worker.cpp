#include "worker.h"
#include <QThread>
#include <QDebug>
#include <QPainter>

Worker::Worker(int* alg, bool *Status, Parameters p, Lattice *lptr, QObject *parent) :
    QObject(parent), alg(alg), threadStatus(Status), l(lptr), model(new MonteCarlo(p))

{
    stop = false;
    run = false;
    step = 0;
}

Worker::~Worker()
{
    //qDebug() << "destruction Thread";
	delete model;
    *threadStatus = false;
}

void Worker::process()
{
    stop = false;
    run = false;
    while (!stop)
    {
        if(run && !stop)
        {
			if (*alg == 0)
				model->heat_bath_simulate(l);
			if (*alg == 1)
				model->clusters_simulate(l);
            step++;
			emit(SendStep(step));
            QThread::msleep(50);
        }
        else
            QThread::msleep(100);
    }
    emit finished();
}

void Worker::recieveDeleteThread()
{
    stop = true;
	//qDebug() << "RecieveDeleteThread = " << Stop;
    emit finished();
}

void Worker::recieveChangeAlgo()
{
	*alg = (*alg + 1) % 2;
	//qDebug() << "Algo changed to " << *alg;
}

void Worker::recieveRun()
{
    run = true;
    //qDebug() << "Recieve Run";
}

void Worker::recievePause()
{
    run = false;
    //qDebug() << "Recieve Pause";
}

void Worker::recieveNewBeta(double new_beta)
{
    //qDebug() << "Recieved " << new_beta << " beta";
    model->setBeta(new_beta);
}
