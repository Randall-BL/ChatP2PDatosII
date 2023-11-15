#ifndef SERVIDORP2P_H
#define SERVIDORP2P_H

#include <QTcpServer>
#include <QTcpSocket>

class ServidorP2P : public QTcpServer {
    Q_OBJECT

public:
    explicit ServidorP2P(QObject *parent = nullptr);
    void iniciarServidor(quint16 puerto);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void onReadyRead();

private:
    QTcpSocket *clienteSocket;
};

#endif // SERVIDORP2P_H
