#include <QApplication>
#include "mainwindow.h"
#include "graphic.h"
#include <iostream>

bool parameterCheck(const char *arg, const char *checked) {
    int length = ((strlen(arg) < strlen(checked)) ? strlen(arg) : strlen(checked)) + 1;
    int i;
    for (i = 0; i < length; i++)
        if (tolower(arg[i]) != tolower(checked[i]))
            break;
    return (i == length);
}

bool isGUI(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (parameterCheck(argv[i], "--gui")) {
            return true;
        }
        if (parameterCheck(argv[i], "--help") || parameterCheck(argv[i], "-h")) {
            printf("Парамерты запуска: \n"
            "\t--gui        включить GUI\n"
            "\t--help | -h  справка\n");
            fflush(stdout);
            exit(0);
        }
    }
    return false;
}

int main(int argc, char *argv[])
{
//    if (isGUI(argc, argv)) {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
//    } else {
//        float X = 0;
//        printf("Введи X:");fflush(stdout);
//        std::cin >> X;
//        Graphic g(1, 4);
//        float Y = g.getY(X);
//        printf("Y: %f\n", Y);fflush(stdout);
//        return 0;
//    }
}
