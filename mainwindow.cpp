#include "mainwindow.h"
#include "graphic.h"
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
      inputSpinBox(new QDoubleSpinBox),
      calculateBtn(new QPushButton("Посчитать")),
      drawBtn(new QPushButton("График"))
{
    connect(calculateBtn, SIGNAL(clicked(bool)), this, SLOT(calculate()));
    connect(drawBtn, SIGNAL(clicked(bool)), this, SLOT(draw()));
    QGridLayout *mainLay = new QGridLayout(this);
    QLabel *lbl = new QLabel("X:");
    enum {
        Lbl,
        Input,
        Btn,
        Total
    };
    mainLay->addWidget(lbl, 0, Lbl);
    mainLay->addWidget(inputSpinBox, 0, Input);
    mainLay->addWidget(calculateBtn, 0, Btn);
    mainLay->addWidget(drawBtn, 1, 0, Total, 0);
}

MainWindow::~MainWindow() {
}

void MainWindow::draw() {
    Graphic g(1, 4);
    g.plot(-10, 10, 0.1);
}

void MainWindow::calculate() {
    Graphic g(1, 4);
    float Y = g.getY(inputSpinBox->value());
    QMessageBox::information(nullptr, "Результат", QString("При Х = %1, Y = %2")
                             .arg(QString::number(inputSpinBox->value()))
                             .arg(QString::number(Y)), QMessageBox::Close);
}

