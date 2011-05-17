#ifndef THREAD_ENVOIS_H
#define THREAD_ENVOIS_H

#include <QThread>
#include <QTcpSocket>
#include <QTcpServer>

class thread_envois : public QThread
{
    Q_OBJECT
public:
    thread_envois(QTcpSocket*);

private:
    QTcpSocket* m_socket;

private slots:
    void EnvoieNote(char);
};

#endif // THREAD_ENVOIS_H
