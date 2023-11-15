#ifndef CLIENTE_H
#define CLIENTE_H

#include <QTcpSocket>
#include <QTcpServer>
#include <QObject>

class Cliente : public QObject {
    Q_OBJECT

public:
    explicit Cliente(QObject *parent = nullptr);
    void conectarConServidor(const QHostAddress &direccion, quint16 puerto);
    void iniciarServidor(quint16 puerto);
    void enviarMensaje(const QString &mensaje);

signals:
    void mensajeRecibidoSignal(const QString &mensaje);



private slots:
    void onReadyRead();
    void onNewConnection();

private:
    QTcpSocket *socket;
    QTcpServer *server;
};

#endif // CLIENTE_H
