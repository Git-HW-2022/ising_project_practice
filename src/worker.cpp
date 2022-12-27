#include "hdr/worker.h"
#include <QThread>
#include <QDebug>
#include <QPainter>

Worker::Worker(int* alg, bool *Status, Parameters p, Lattice *lptr, QObject *parent) :
    QObject(parent), alg(alg), Thread_status(Status), l(lptr), model(new MonteCarlo(p))

{
    Stop = false;
    Run = false;
    step = 0;
}

Worker::~Worker()
{
    //qDebug() << "destruction Thread";
	delete model;
    *Thread_status = false;
}

void Worker::process()
{
    Stop = false;
    Run = false;
    while (!Stop)
    {
        if(Run && !Stop)
        {
			if (*alg == 0)
                model->heatBathSimulate(l);
			if (*alg == 1)
                model->clustersSimulate(l);
            step++;
            emit(sendStep(step));
            QThread::msleep(50);
        }
        else
            QThread::msleep(100);
    }
    emit finished();
}

void Worker::recieveDeleteThread()
{
    Stop = true;
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
    Run = true;
    //qDebug() << "Recieve Run";
}

void Worker::recievePause()
{
    Run = false;
    //qDebug() << "Recieve Pause";
}

void Worker::recieveNewBeta(double new_beta)
{
    //qDebug() << "Recieved " << new_beta << " beta";
    model->setBeta(new_beta);
}
