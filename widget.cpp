#include <stdio.h>
#include <stdlib.h>
#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // all buttons's status will be disable.
    changeJuiceBtnStatus();
}

Widget::~Widget()
{
    delete ui;
}

/*
 * change money(class member) variable's value.
 * if money value will be less than 0, no act.
 * change juice buttons status after money value changed.
 */
void Widget::changeMoney(int diff)
{
    // ex) 100 + (-150) => not work.
    if(money + diff >= 0) {
        money += diff;

        ui->lcdNumber->display(money);
        changeJuiceBtnStatus();
    }
}

/*
 * chagne juice buttons status.
 * for example,
 * if money value is greater than or equal 100, coffee button will be enable.
 *
 * you should call this method, if money value was changed.
 */
void Widget::changeJuiceBtnStatus()
{
    ui->pbCoffee->setEnabled(false);
    ui->pbTea->setEnabled(false);
    ui->pbMilk->setEnabled(false);

    if(money >= 100) {
        ui->pbCoffee->setEnabled(true);
    }
    if(money >= 150) {
        ui->pbTea->setEnabled(true);
    }
    if(money >= 200) {
        ui->pbMilk->setEnabled(true);
    }
}

/*
 * add 10 to money
 */
void Widget::on_pb10_clicked()
{
    changeMoney(10);
}

/*
 * add 50 to money
 */
void Widget::on_pb50_clicked()
{
    changeMoney(50);
}

/*
 * add 100 to money
 */
void Widget::on_pb100_clicked()
{
    changeMoney(100);
}

/*
 * add 500 to money
 */
void Widget::on_pb500_clicked()
{
    changeMoney(500);
}

/*
 * buy a coffee.
 * subtract 100 from money.
 */
void Widget::on_pbCoffee_clicked()
{
    changeMoney(-100);
}

/*
 * buy a tea.
 * subtract 150 from money.
 */
void Widget::on_pbTea_clicked()
{
    changeMoney(-150);
}

/*
 * buy a milk.
 * subtract 200 from money.
 */
void Widget::on_pbMilk_clicked()
{
    changeMoney(-200);
}

/*
 * return remained money and terminate process.
 */
void Widget::on_pbReset_clicked()
{
    int cnt10, cnt50, cnt100, cnt500;
    int tmpMoney = money;

    cnt500 = tmpMoney / 500;
    tmpMoney = tmpMoney % 500;

    cnt100 = tmpMoney / 100;
    tmpMoney %= 100;

    cnt50 = tmpMoney / 50;
    tmpMoney %= 50;

    cnt10 = tmpMoney / 10;

    char msg[128];
    snprintf(msg, sizeof(msg) / sizeof(char), "500원 %d개\n100원 %d개\n50원 %d개\n10원 %d개\n가 반환됩니다.", cnt500, cnt100, cnt50, cnt10);

    QMessageBox m;
    m.information(nullptr, "result", msg);

    exit(0);
}
