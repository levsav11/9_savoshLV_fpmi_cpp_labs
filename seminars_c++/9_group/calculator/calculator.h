#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Calculator;
}
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void on_digits_clicked();

    void on_clear_btn_clicked();

    void on_dot_btn_clicked();

    void on_add_btn_clicked();

    void on_eq_btn_clicked();

private:
    Ui::Calculator *ui;

    double first_operand;
};
#endif // CALCULATOR_H
