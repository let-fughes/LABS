#include "podrobnee.h"
#include "ui_podrobnee.h"

Podrobnee::Podrobnee(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Podrobnee)
{
    ui->setupUi(this);
}

Podrobnee::~Podrobnee()
{
    delete ui;
}
