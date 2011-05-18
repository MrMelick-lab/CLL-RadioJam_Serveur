#include "thread_envois.h"

thread_envois::thread_envois(QTcpSocket* socket)
{
    m_socket = socket;
}

void thread_envois::EnvoieNote(int note)
{
    /*QVariant v;
    v.setValue(note);*/
    //emit PtArr("note envoye", v);
    QByteArray envoie;
    envoie.append(note);
    m_socket->write(envoie);
    m_socket->waitForBytesWritten();
}
