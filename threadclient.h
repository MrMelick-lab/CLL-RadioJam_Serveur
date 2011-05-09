#ifndef THREADCLIENT_H
#define THREADCLIENT_H

#include <QThread>
#include <QTcpSocket>
#include <QTcpServer>

class threadclient : public QThread
{
    Q_OBJECT
public:
    threadclient(QTcpSocket*);

protected:
    void run();

private:
    QTcpSocket* m_socket, *m_socketRecepteur;
    QTcpServer* m_recepteur;
    bool m_EnCours;

signals:
    void ajoutClientVersPrinc(QByteArray);

private slots:
    void creationNouveauClient(QByteArray);
};

#endif // THREADCLIENT_H
