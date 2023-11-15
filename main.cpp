#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow window1(12345, 12346); // Escucha en 12345, se conecta a 12346
    window1.show();

    MainWindow window2(12346, 12345); // Escucha en 12346, se conecta a 12345
    window2.show();

    return a.exec();
}
