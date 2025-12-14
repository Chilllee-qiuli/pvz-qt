#include "showfather.h"
#include "ui_showfather.h"

ShowFather::ShowFather(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ShowFather)
{
    ui->setupUi(this);
}

ShowFather::~ShowFather()
{
    delete ui;
}

void ShowFather::on_pushButton_clicked()
{

}

