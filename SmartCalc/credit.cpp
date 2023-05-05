#include "credit.h"
#include "ui_credit.h"

extern "C" {
#include "Calc.h"
}

Credit::Credit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Credit)
{
    ui->setupUi(this);
}


Credit::~Credit()
{
    delete ui;
}

void Credit::on_pushButton_clicked()
{
    double payment = 0;
    double overpayment = 0;
    double totalpayment = 0;
    double summapercentMax = 0;
    double summapercentMin = 0;

    double summa = ui->summa->text().toDouble();
    double period = ui->period->text().toInt();
    double percent = ui->percent->text().toDouble();

  if(ui->annuity->isChecked()){
      AnnuityCreditcalc (summa, period, percent,  &payment, &totalpayment,  &overpayment);
      ui->payment->setText(QString::number(payment, 'f', 2));
      ui->overpayment->setText(QString::number(overpayment, 'f', 2));
      ui->totalpayment->setText(QString::number(totalpayment, 'f', 2));
  } else if(ui->differentiated->isChecked()){
      DiffCreditcalc (summa, period, percent, &payment, &totalpayment, &overpayment, &summapercentMax, &summapercentMin);
      ui->payment->setText(QString::number(summapercentMax, 'f', 2));
      ui->payment->setText(ui->payment->text() += " ... ");
      ui->payment->setText(ui->payment->text() += QString::number(summapercentMin, 'f', 2));
      ui->overpayment->setText(QString::number(overpayment, 'f', 2));
      ui->totalpayment->setText(QString::number(totalpayment, 'f', 2));
  }
}

