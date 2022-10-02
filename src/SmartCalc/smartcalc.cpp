#include "smartcalc.h"
#include "ui_smartcalc.h"

SmartCalc::SmartCalc(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SmartCalc)
{
    ui->setupUi(this);

    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digit()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digit()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digit()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digit()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digit()));
    connect(ui->pushButton_05, SIGNAL(clicked()), this, SLOT(digit()));
    connect(ui->pushButton_06, SIGNAL(clicked()), this, SLOT(digit()));
    connect(ui->pushButton_07, SIGNAL(clicked()), this, SLOT(digit()));
    connect(ui->pushButton_08, SIGNAL(clicked()), this, SLOT(digit()));
    connect(ui->pushButton_09, SIGNAL(clicked()), this, SLOT(digit()));
    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(digit()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(digit()));
    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(digit()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(digit()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(digit()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(digit()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(digit()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(digit()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(digit()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(digit()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(digit()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(digit()));
    connect(ui->pushButton_bro, SIGNAL(clicked()), this, SLOT(digit()));
    connect(ui->pushButton_brc, SIGNAL(clicked()), this, SLOT(digit()));
    connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(digit()));

//    xBegin = ui->SpinBox_minX->value();
//    xEnd = ui->SpinBox_maxX->value();

//    ui->graf->xAxis->setRange(ui->SpinBox_minX->value(), ui->SpinBox_maxX->value());
//    ui->graf->yAxis->setRange(ui->SpinBox_minY->value(), ui->SpinBox_maxY->value());

//    N = (xEnd-xBegin)/h+2;

//    for (X = xBegin; X <= xEnd; X += h) {
//        x.push_back(X);
//        y.push_back(smart_calc((char*)ui->lineEdit_oi->text().toStdString().c_str(), valux, &Y));
//    }

//    ui->graf->addGraph();
//    ui->graf->graph(0)->addData(x, y);
//    ui->graf->replot();
//    x.clear();
//    y.clear();
}

SmartCalc::~SmartCalc()
{
    delete ui;
}

void SmartCalc::digit()
{
    QPushButton *button = (QPushButton *)sender();
//    double value;
//    QString input;
//    value = (ui->lineEdit_oi->text() + button->text()).toDouble();
//    input = QString::number(value, 'g', 8);
    ui->lineEdit_oi->setText(ui->lineEdit_oi->text() + button->text());
}

void SmartCalc::on_pushButton_X_clicked()
{
    ui->lineEdit_oi->setText(ui->lineEdit_oi->text() + "x");
}

void SmartCalc::on_pushButton_pow_clicked()
{
    ui->lineEdit_oi->setText(ui->lineEdit_oi->text() + "^");
}

void SmartCalc::on_pushButton_div_clicked()
{
    ui->lineEdit_oi->setText(ui->lineEdit_oi->text() + "/");
}

void SmartCalc::on_pushButton_mult_clicked()
{
    ui->lineEdit_oi->setText(ui->lineEdit_oi->text() + "*");
}

void SmartCalc::on_pushButton_AC_clicked()
{
    ui->lineEdit_oi->setText("");
}

void SmartCalc::on_pushButton_eq_clicked()
{
    QString output;
    double result;
    valux = ui->lineEdit_X_value->text().toDouble();
    int check = smart_calc((char*)ui->lineEdit_oi->text().toStdString().c_str(), valux, &result);
    if (!check) {
        output = QString::number(result, 'g', 8);
        ui->lineEdit_oi->setText(output);
    } else {
        ui->lineEdit_oi->setText("incorrect data");
    }
}


void SmartCalc::on_pushButton_makeGraph_clicked()
{
    ui->graf->clearGraphs();

    h = 0.1;
    xBegin = ui->SpinBox_minX->value();
    xEnd = ui->SpinBox_maxX->value();

    ui->graf->xAxis->setRange(ui->SpinBox_minX->value(), ui->SpinBox_maxX->value());
    ui->graf->yAxis->setRange(ui->SpinBox_minY->value(), ui->SpinBox_maxY->value());

    N = (xEnd-xBegin)/h+2;

    for (X = xBegin; X <= xEnd; X += h) {
        smart_calc((char*)ui->lineEdit_oi->text().toStdString().c_str(), X, &Y);
        x.push_back(X);
        y.push_back(Y);
    }

    ui->graf->addGraph();
    ui->graf->graph(0)->addData(x, y);
    ui->graf->replot();
    x.clear();
    y.clear();
}


void SmartCalc::on_radioButton_clicked()
{
    data->type = 0;
}

void SmartCalc::on_radioButton_2_clicked()
{
    data->type = 1;
}

void SmartCalc::on_pushButton_cr_count_clicked()
{
    data->sum = ui->SpinBox_cr_sum->value();
    data->time = ui->SpinBox_cr_time->value();
    data->perc = ui-> SpinBox_cr_tax->value();
    credit_calc(data);
    ui->textEdit_6->setFontPointSize(18);
    ui->textEdit_6->setText("Ежемесячный платеж");
    if (data->type)
        ui->textEdit_payment->setText(QString::number(data->payment[0], 'f', 2) + " → \n" + QString::number(data->payment[(int)data->time-1], 'f', 2));
    else
        ui->textEdit_payment->setText(QString::number(data->payment[0], 'f', 2));
    ui->textEdit_7->setFontPointSize(18);
    ui->textEdit_7->setText("Переплата по кредиту");
    ui->textEdit_overpay->setText(QString::number(data->overpayment, 'f', 2));
    ui->textEdit_8->setFontPointSize(18);
    ui->textEdit_8->setText("Общая выплата");
    ui->textEdit_total->setText(QString::number(data->total, 'f', 2));
}


void SmartCalc::on_radioButton_3_clicked()
{
    ui->textEdit_pay_or_cap->setText("Периодичность выплат");
    value->capitalization = 0;
}

void SmartCalc::on_radioButton_4_clicked()
{
    ui->textEdit_pay_or_cap->setText("Капитализация процентов");
    value->capitalization = 1;
    value->frequency = ui->comboBox_freq-> currentIndex();
}


void SmartCalc::on_pushButton_cr_count_2_clicked()
{
    value->input = ui->SpinBox_d_input->value();
    value->period = ui->SpinBox_d_period->value();
    value->perc = ui->SpinBox_d_perc->value();
    value->tax = ui->SpinBox_d_tax->value();
    value->add_list[0] = ui->SpinBox_add_0->value();
    value->add_list[1] = ui->SpinBox_add_1->value();
    value->add_list[2] = ui->SpinBox_add_2->value();
    value->subtract_list[0] = ui->SpinBox_sub_0->value();
    value->subtract_list[1] = ui->SpinBox_sub_1->value();
    value->subtract_list[2] = ui->SpinBox_sub_2->value();
    deposit_calc(value);
    ui->textEdit_15->setFontPointSize(18);
    ui->textEdit_15->setText("Начисленные прoценты");
    ui->textEdit_d_interest->setText(QString::number(value->interest, 'f', 0));
    ui->textEdit_16->setFontPointSize(18);
    ui->textEdit_16->setText("Сумма налога");
    ui->textEdit_total_tax->setText(QString::number(value->total_tax, 'f', 0));
    ui->textEdit_17->setFontPointSize(18);
    ui->textEdit_17->setText("Сумма на вкладе к концу срока");
    ui->textEdit_d_output->setText(QString::number(value->output, 'f', 0));
}


void SmartCalc::on_pushButton_del_clicked()
{
     ui->lineEdit_oi->setText(ui->lineEdit_oi->text().left(ui->lineEdit_oi->text().size()-1));
}

