#ifndef SMARTCALC_H
#define SMARTCALC_H

#include <QMainWindow>
#include <QVector>

#ifdef __cplusplus
extern "C" {
#endif
#include "../SmartCalc1.h"
#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class SmartCalc; }
QT_END_NAMESPACE

class SmartCalc : public QMainWindow
{
    Q_OBJECT

public:
    SmartCalc(QWidget *parent = nullptr);
    ~SmartCalc();

private:
    Ui::SmartCalc *ui;
    double xBegin, xEnd, h, X, Y;
    int N;
    QVector <double> x, y;
    double valux;

    t_credit d;
    t_credit *data = &d;

    t_deposit v;
    t_deposit *value = &v;

private slots:
    void digit();
    void on_pushButton_X_clicked();
    void on_pushButton_pow_clicked();
    void on_pushButton_div_clicked();
    void on_pushButton_mult_clicked();
    void on_pushButton_AC_clicked();
    void on_pushButton_eq_clicked();
    void on_pushButton_makeGraph_clicked();
    void on_pushButton_cr_count_clicked();
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_radioButton_3_clicked();
    void on_radioButton_4_clicked();
    void on_pushButton_cr_count_2_clicked();
    void on_pushButton_del_clicked();
};
#endif // SMARTCALC_H
