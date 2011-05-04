#ifndef THREADCLIENT_H
#define THREADCLIENT_H

#include <QThread>
#include <QTcpSocket>

class threadclient : public QThread
{
    Q_OBJECT
public:
    threadclient(QTcpSocket*);

protected:
    void run();

private:
    QTcpSocket* m_socket;
    bool m_EnCours;

signals:
    void ajoutClient(QByteArray);
};

#endif // THREADCLIENT_H
