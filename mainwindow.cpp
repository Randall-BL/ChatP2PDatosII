#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHostAddress>

MainWindow::MainWindow(quint16 serverPort, quint16 clientPort, QWidget *parent)
    : QMainWindow(parent) {
    // Configuración de la interfaz de usuario
    auto *centralWidget = new QWidget(this);
    auto *layout = new QVBoxLayout(centralWidget);

    messageDisplay = new QTextEdit(centralWidget);
    messageInput = new QLineEdit(centralWidget);
    sendButton = new QPushButton("Send", centralWidget);

    messageDisplay->setReadOnly(true);

    layout->addWidget(messageDisplay);
    layout->addWidget(messageInput);
    layout->addWidget(sendButton);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Conectar señales y slots
    connect(sendButton, &QPushButton::clicked, this, &MainWindow::enviarMensaje);
    connect(&cliente, &Cliente::mensajeRecibidoSignal, this, &MainWindow::mostrarMensajeRecibido);

    // Configurar conexiones de red
    cliente.iniciarServidor(serverPort); // Iniciar el servidor en el puerto especificado
    cliente.conectarConServidor(QHostAddress::LocalHost, clientPort); // Conectar al servidor en otro puerto
}

void MainWindow::enviarMensaje() {
    QString mensaje = messageInput->text();
    cliente.enviarMensaje(mensaje);
    messageDisplay->append("Yo: " + mensaje);
    messageInput->clear();
}

void MainWindow::mostrarMensajeRecibido(const QString &mensaje) {
    messageDisplay->append("Otro: " + mensaje);
}
