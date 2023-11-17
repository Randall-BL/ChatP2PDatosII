#ifndef ENCRIPTADOR_H
#define ENCRIPTADOR_H
#include <QtCore/QCryptographicHash>

class Encriptador
{
public:
    Encriptador(){};
    QByteArray encriptar(const QByteArray& datos){
        QCryptographicHash hash(QCryptographicHash::Sha256);
        hash.addData(datos);
        return hash.result();
    }

};

#endif // ENCRIPTADOR_H
