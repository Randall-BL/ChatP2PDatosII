#include "ServidorP2P.h"
#include <QDataStream>

ServidorP2P::ServidorP2P(QObject *parent)
    : QTcpServer(parent), clienteSocket(nullptr) {}

void ServidorP2P::iniciarServidor(quint16 puerto) {
    if (!this->listen(QHostAddress::Any, puerto)) {
        qDebug() << "No se pudo iniciar el servidor. Error:" << this->errorString();
        return;
    }
}

void ServidorP2P::incomingConnection(qintptr socketDescriptor) {
    clienteSocket = new QTcpSocket(this);
    clienteSocket->setSocketDescriptor(socketDescriptor);
    connect(clienteSocket, &QTcpSocket::readyRead, this, &ServidorP2P::onReadyRead);
}

void ServidorP2P::onReadyRead() {
    QDataStream socketStream(clienteSocket);
    QString mensajeRecibido;
    socketStream >> mensajeRecibido;

    qDebug() << "Mensaje recibido:" << mensajeRecibido;

    // Enviar un mensaje de vuelta (usar directamente socketStream)
    socketStream << "Eco: " + mensajeRecibido;
}
