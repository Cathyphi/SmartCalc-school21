#ifndef SMARTCALC_H
#define SMARTCALC_H

#include <QMainWindow>
#include <QVector>

extern "C" {
#include <Calc.h>
}

QT_BEGIN_NAMESPACE
namespace Ui {
class SmartCalc;
}
QT_END_NAMESPACE

class SmartCalc : public QMainWindow {
  Q_OBJECT

 public:
  SmartCalc(QWidget *parent = nullptr);
  ~SmartCalc();

 private:
  Ui::SmartCalc *ui;
  double xBegin, xEnd, yBegin, yEnd, h,
      X;  // h это шаг  // Х временная переменная для заполнения вектора
  int N;  // количество точек

  QVector<double> x, y;  //координаты точки

 private slots:
  void digit_numbers();
  void function();
  void clearAC();
  void result();
  void on_pushButton_credit_clicked();
  void on_pushButton_graphic_clicked();
};
#endif  // SMARTCALC_H
