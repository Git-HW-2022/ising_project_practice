#include "hdr/worker.h"
#include <QThread>
#include <QDebug>
#include <QPainter>

worker::worker(int* alg, bool *Status, parameters p, lattice *lptr, QObject *parent) :
    QObject(parent), alg(alg), Thread_status(Status), l(lptr), model(new MonteCarlo(p))

{
    Stop = false;
    Run = false;
    step = 0;
}

worker::~worker()
{
    //qDebug() << "destruction Thread";
	delete model;
    *threadStatus = false;
}

void worker::process()
{
    Stop = false;
    Run = false;
    while (!Stop)
    {
        if(Run && !Stop)
        {
			if (*alg == 0)
				model->heat_bath_simulate(l);
			if (*alg == 1)
				model->clusters_simulate(l);
            step++;
			emit(sendStep(step));
            QThread::msleep(50);
        }
        else
            QThread::msleep(100);
    }
    emit finished();
}

void worker::recieveDeleteThread()
{
    Stop = true;
	//qDebug() << "RecieveDeleteThread = " << Stop;
    emit finished();
}

void worker::recieveChangeAlgo()
{
	*alg = (*alg + 1) % 2;
	//qDebug() << "Algo changed to " << *alg;
}

void worker::recieveRun()
{
    Run = true;
    //qDebug() << "Recieve Run";
}

void worker::recievePause()
{
    Run = false;
    //qDebug() << "Recieve Pause";
}

void worker::recieveNewBeta(double new_beta)
{
    //qDebug() << "Recieved " << new_beta << " beta";
    model->set_beta(new_beta);
}
