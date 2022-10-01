#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QDoubleSpinBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void draw();
    void calculate();

private:
    QDoubleSpinBox *inputSpinBox;
    QPushButton *calculateBtn;
    QPushButton *drawBtn;
};
#endif // MAINWINDOW_H
