#include "Cliente.h"
#include <QDataStream>

Cliente::Cliente(QObject *parent)
    : QObject(parent), socket(new QTcpSocket(this)), server(new QTcpServer(this)) {
    connect(socket, &QTcpSocket::readyRead, this, &Cliente::onReadyRead);
    connect(server, &QTcpServer::newConnection, this, &Cliente::onNewConnection);
}

void Cliente::conectarConServidor(const QHostAddress &direccion, quint16 puerto) {
    socket->connectToHost(direccion, puerto);
}

void Cliente::iniciarServidor(quint16 puerto) {
    if (!server->listen(QHostAddress::Any, puerto)) {
        qDebug() << "Server failed to start. Error:" << server->errorString();
        return;
    }
}

void Cliente::enviarMensaje(const QString &mensaje) {
    /**
     * @args &mensaje
     * @return
     */
    if (socket->state() == QTcpSocket::ConnectedState) {
        QDataStream socketStream(socket);
        socketStream << mensaje;
    }
}

void Cliente::onReadyRead() {
    QTcpSocket* clientSocket = qobject_cast<QTcpSocket*>(sender());
    QDataStream socketStream(clientSocket);
    QString mensajeRecibido;
    socketStream >> mensajeRecibido;

    emit mensajeRecibidoSignal(mensajeRecibido);
}

void Cliente::onNewConnection() {
    QTcpSocket *newSocket = server->nextPendingConnection();
    connect(newSocket, &QTcpSocket::readyRead, this, &Cliente::onReadyRead);
    // Agregar newSocket a una lista de sockets
}
