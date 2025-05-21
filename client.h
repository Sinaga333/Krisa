#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT

public:
    Client(QString host, int port);
private:
    QTcpSocket* psocket;
    quint16 next_block_size;
    void slot_send_to_server(QString str);
private slots:
    void slot_ready_read();
    void slot_connected();
};

#endif // CLIENT_H
