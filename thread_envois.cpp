#include "thread_envois.h"

thread_envois::thread_envois(QTcpSocket* socket)
{
    m_socket = socket;
}

void thread_envois::EnvoieNote(char note)
{
    m_socket->write(&note);
    m_socket->waitForBytesWritten();
}
