#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include "Cliente.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(quint16 serverPort, quint16 clientPort, QWidget *parent = nullptr);

private:
    QTextEdit *messageDisplay;
    QLineEdit *messageInput;
    QPushButton *sendButton;

    Cliente cliente;

private slots:
    void enviarMensaje();
    void mostrarMensajeRecibido(const QString &mensaje);
};

#endif // MAINWINDOW_H
