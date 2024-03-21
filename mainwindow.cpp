#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinBox->setMinimum(5);
    ui->spinBox_2->setMinimum(5);

    field = nullptr;
    QPoint pos;
    QSize size;

    state->RestoreState(pos, size);

    this->move(pos);
    this->resize(size);
}

MainWindow::~MainWindow()
{
    state->SaveState(this->pos(), this->size());
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(field != nullptr){
        delete field;
    }
    int w = ui->spinBox->value() * cellSize;
    int h = ui->spinBox_2->value() * cellSize;
    field = new Field(w, h, this);
    ui->verticalLayout->addWidget(field);
    field->generate();
}

