#include "calculator.h"
#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->add_btn->setCheckable(true);

    connect(
        ui->zero_btn, // sender
        SIGNAL(clicked()),
        this, // "receiver"
        SLOT(on_digits_clicked())
    );
    connect(
        ui->one_btn, // sender
        SIGNAL(clicked()),
        this, // "receiver"
        SLOT(on_digits_clicked())
        );
    connect(
        ui->two_btn, // sender
        SIGNAL(clicked()),
        this, // "receiver"
        SLOT(on_digits_clicked())
        );
    connect(
        ui->three_btn, // sender
        SIGNAL(clicked()),
        this, // "receiver"
        SLOT(on_digits_clicked())
        );
    connect(
        ui->four_btn, // sender
        SIGNAL(clicked()),
        this, // "receiver"
        SLOT(on_digits_clicked())
        );
    connect(
        ui->five_btn, // sender
        SIGNAL(clicked()),
        this, // "receiver"
        SLOT(on_digits_clicked())
        );
    connect(
        ui->six_btn, // sender
        SIGNAL(clicked()),
        this, // "receiver"
        SLOT(on_digits_clicked())
        );
    connect(
        ui->seven_btn, // sender
        SIGNAL(clicked()),
        this, // "receiver"
        SLOT(on_digits_clicked())
        );
    connect(
        ui->eight_btn, // sender
        SIGNAL(clicked()),
        this, // "receiver"
        SLOT(on_digits_clicked())
    );
    connect(
        ui->nine_btn, // sender
        SIGNAL(clicked()),
        this, // "receiver"
        SLOT(on_digits_clicked())
    );

    connect(
        ui->clear_btn, // sender
        SIGNAL(clicked()),
        this, // "receiver"
        SLOT(on_clear_btn_clicked())
    );

    connect(
        ui->dot_btn, // sender
        SIGNAL(clicked()),
        this, // "receiver"
        SLOT(on_dot_btn_clicked())
    );
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::on_digits_clicked()
{
    QPushButton* curr_btn = static_cast<QPushButton*>(sender());
    QString curr_digit = curr_btn->text();

    QString curr_number = ui->label->text();

    ui->label->setText(
        curr_number == "0"
        ? curr_digit
        : curr_number + curr_digit
    );
}


void Calculator::on_clear_btn_clicked()
{
    ui->label->setText("0");

    ui->add_btn->setChecked(false);
}


void Calculator::on_dot_btn_clicked()
{
    QString curr_number = ui->label->text();

    if (not curr_number.contains(".")) {
        ui->label->setText(curr_number + ".");
    }
}


void Calculator::on_add_btn_clicked()
{
    QString curr_number = ui->label->text();
    first_operand = curr_number.toDouble();

    ui->label->clear();

    ui->add_btn->setChecked(true);
}


void Calculator::on_eq_btn_clicked()
{
    double second_operand = ui->label->text().toDouble();
    double result = 0.0;

    if (ui->add_btn->isChecked()) {
        result = first_operand + second_operand;
        ui->add_btn->setChecked(false);
    }

    ui->label->setText(
        QString::number(result, 'g', 15)
    );
}

