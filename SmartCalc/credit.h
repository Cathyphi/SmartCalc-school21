#ifndef CREDIT_H
#define CREDIT_H
//#include "Calc.h"

#include <QDialog>

// extern "C" {
//#include <Calc.h>
// }

namespace Ui {
class Credit;
}

class Credit : public QDialog {
  Q_OBJECT

 public:
  explicit Credit(QWidget *parent = nullptr);
  ~Credit();

 private slots:
  // void credit_result();
  //    void AnnuityCreditcalc (double summa, int period, double percent, double
  //    *payment, double *totalpayment, double *overpayment); void
  //    DiffCreditcalc (double summa, int period, double percent, double
  //    *payment, double *totalpayment, double *overpayment);
  // void on_pushButton_credit_clicked();
  void on_pushButton_clicked();

 private:
  Ui::Credit *ui;
};

#endif  // CREDIT_H
