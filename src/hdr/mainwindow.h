#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "hdr/paintwidget.h"
#include "hdr/ising_model.h"
#include <QMainWindow>
#include <QLabel>

//#define DEBUG

//generated by Qt Designer from mainwindow.ui form (see build-drawing-Desktop_Qt_5_3_MinGW_32bit-Debug/ui_mainwindow.h)
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
    {
  Q_OBJECT

     public:
      explicit MainWindow(int lSize = 64, QWidget *parent = 0);
  ~MainWindow();

  int alg; //simulation algorithm: 1 for heat_bath, -1 for clasters
  bool threadStatus; //true when thread is working, false when terminated
  Parameters p; //parameters of the model
  int lSize; //square_lattice size - number of rows or columns
  Lattice *l; //lattice type of square_lattice, used in simulation

  public slots:
      void changeAlgoLabel();
  void canvasResized(QSize old_size, QSize new_size);
  void receiveStep(int number);

  signals:
      void sendDeleteThread();

      private slots:

     private:
      Ui::MainWindow *ui;
      PaintWidget *paintWidget; //new dynamically created widget
      QLabel *lb1;
      QLabel *lb2;
      QLabel *lb3;

      void drawPicture();
    };


#endif // MAINWINDOW_H
