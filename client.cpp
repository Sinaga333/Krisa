#include "client.h"

Client::Client(QString host, int port)
{
    psocket = new QTcpSocket(this);
    next_block_size = 0;
    psocket->connectToHost(host, port);
    connect(psocket, SIGNAL(connected()), SLOT(slot_connected()));
    connect(psocket, SIGNAL(readyRead()), SLOT(slot_ready_read()));
}

void Client::slot_send_to_server(QString str)
{
    QByteArray arr;
    QDataStream out(&arr, QIODevice::WriteOnly);

    out.setVersion(QDataStream::Qt_6_0);
    out << quint16(0) << str;
    out.device()->seek(0);
    out << quint16(arr.size() - sizeof(quint16));
    psocket->write(arr);

}

void Client::slot_ready_read()
{
    QDataStream in(psocket);
    in.setVersion(QDataStream::Qt_6_0);
    for(;;)
    {
        if(!next_block_size)
        {
            if(psocket->bytesAvailable() < sizeof(quint16))
            {
                break;
            }
            next_block_size = psocket->bytesAvailable();
        }

        if(psocket->bytesAvailable() < next_block_size)
        {
            break;
        }
        QString str;
        in >> str;
        qDebug() << str;
    }
}

void Client::slot_connected()
{
    qDebug() << "connected to server";
}
