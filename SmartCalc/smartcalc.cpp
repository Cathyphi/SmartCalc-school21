#include "smartcalc.h"
#include "ui_smartcalc.h"
#include "Calc.h"
#include <math.h>
#include <credit.h>


SmartCalc::SmartCalc(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SmartCalc)
{
    ui->setupUi(this);
    connect(ui->pushButton_0,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_9,SIGNAL(clicked()),this,SLOT(digit_numbers()));

    connect(ui->pushButton_acos,SIGNAL(clicked()),this,SLOT(function()));
    connect(ui->pushButton_asin,SIGNAL(clicked()),this,SLOT(function()));
    connect(ui->pushButton_atan,SIGNAL(clicked()),this,SLOT(function()));
    connect(ui->pushButton_cos,SIGNAL(clicked()),this,SLOT(function()));
    connect(ui->pushButton_div,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_dot,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_ln,SIGNAL(clicked()),this,SLOT(function()));
    connect(ui->pushButton_log,SIGNAL(clicked()),this,SLOT(function()));
    connect(ui->pushButton_minus,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_mod,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_mult,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_plus,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_pow,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_sin,SIGNAL(clicked()),this,SLOT(function()));
    connect(ui->pushButton_sqrt,SIGNAL(clicked()),this,SLOT(function()));
    connect(ui->pushButton_tan,SIGNAL(clicked()),this,SLOT(function()));
    connect(ui->pushButton_x,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_lbr,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_rbr,SIGNAL(clicked()),this,SLOT(digit_numbers()));

    connect(ui->pushButton_clear,SIGNAL(clicked()),this,SLOT(clearAC()));
    connect(ui->pushButton_equal,SIGNAL(clicked()),this,SLOT(result()));


}

SmartCalc::~SmartCalc()
{
    delete ui;
}

void SmartCalc::digit_numbers()
{
    QPushButton *button = (QPushButton *)sender();

    QString newstr = button->text();
    ui->label_result->setText(ui->label_result->text() += newstr);

}

void SmartCalc::function()
{
    QPushButton *button = (QPushButton *)sender();

    QString newstr = button->text();
    ui->label_result->setText(ui->label_result->text() += newstr + '(');

}

void SmartCalc::clearAC()
{
    ui->label_result->setText("");
    ui->widget->clearGraphs();
}

void SmartCalc::result()
{
    QByteArray newstr = ui->label_result->text().toLocal8Bit();
    char str[1024] = {0};
    char pol_nat[1024] = {0};
    memcpy(str, newstr, ui->label_result->text().length() + 1);
    stackN *output_str;
    stackN *stack_str;
    if(parsing(str, &output_str, pol_nat) == 1) {
        ui->label_result->setText("ERROR");
    } else {
    double res = 0;
    Smartcalc(pol_nat, &stack_str, &res, 0);
    ui->label_result->setText(QString::number(res, 'f', 7));
    }
}

void SmartCalc::on_pushButton_credit_clicked()
{
    Credit window;
    window.setModal(true);
    window.exec();

}


void SmartCalc::on_pushButton_graphic_clicked()
{
    x.clear();
    y.clear();
    h = 0.1;
    QString xBegin_str = ui->Xmin->text();
    QString xEnd_str = ui->Xmax->text();
    QString yBegin_str = ui->Ymin->text();
    QString yEnd_str = ui->Ymax->text();
    xBegin = xBegin_str.toDouble();
    xEnd = xEnd_str.toDouble();
    yBegin = yBegin_str.toDouble();
    yEnd = yEnd_str.toDouble();

    N = (xEnd - xBegin)/h + 2;

    for (X = xBegin; X<= xEnd; X+=h) {

        QByteArray newstr = ui->label_result->text().toLocal8Bit();
        char str[1024] = {0};
        char pol_nat[1024] = {0};
        memcpy(str, newstr, ui->label_result->text().length() + 1);
        stackN *output_str;
        stackN *stack_str;
        if(parsing(str, &output_str, pol_nat) == 1) {
            ui->label_result->setText("ERROR");
        } else {
        double res = 0;
        Smartcalc(pol_nat, &stack_str, &res, X);
        x.push_back(X);
        y.push_back(res);
    }
}
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->xAxis->setRange(xBegin, xEnd);
    ui->widget->yAxis->setRange(yBegin, yEnd);
    ui->widget->replot();
    ui->widget->setInteraction(QCP::iRangeZoom, true);
    ui->widget->setInteraction(QCP::iRangeDrag, true);
}

