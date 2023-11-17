#include "Mainwindow.h"
#include <QVBoxLayout>
#include <QHostAddress>
#include <QtCore/QCryptographicHash>
#include "encriptador.h"
#include <string>
#include <iostream>
#include <sstream>
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
    //se obtiene el mensaje del cuadro de texto.
    QString mensaje = messageInput->text();

    //Se utiliza una funcion de hash de Sha256 para encriptar el mensaje
    QCryptographicHash hash(QCryptographicHash::Sha256);
    hash.addData(mensaje.toUtf8());

    //Se obtiene el resultado de la encriptacion
    QByteArray mensajeEncriptado = hash.result();

    //Se envía el mensaje encriptado
    cliente.enviarMensaje(mensajeEncriptado);

    // Imprimir el mensaje encriptado en consola.
    std::stringstream ss;
    ss << mensajeEncriptado.toStdString().c_str();
    std::cout << ss.str() << std::endl;

    hashEnviado = hash.result();
    messageDisplay->append("Yo: " + mensaje);
    messageInput->clear();
}

void MainWindow::mostrarMensajeRecibido(const QString &mensaje) {
    // Obtiene el mensaje recibido
    QByteArray mensajeEncriptado = mensaje.toUtf8();

    // Verifica la integridad del mensaje
    QByteArray hashValue;

    // Calcula el hash del mensaje
    hashValue = QCryptographicHash::hash(mensajeEncriptado, QCryptographicHash::Sha256);

    // Compara el hash del mensaje con el hash que se envió con el mensaje
    bool mensajeVerificado = hashValue == hashEnviado;


    // Si el mensaje es válido, lo agrega al cuadro de texto de mensajes

    //if (mensajeVerificado) {
        // Descifra el mensaje
        //QByteArray mensajeDescifrado = QCryptographicHash::decrypt(mensajeEncriptado, hashEnviado);

    messageDisplay->append("Otro: " + mensaje);
    //} else {
      //  messageDisplay->append("El mensaje recibido es inválido");
    //}



}
