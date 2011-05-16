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
    bool m_EnCours;

protected:
    void run();

private:
    QTcpSocket* m_socket, *m_socketRecepteur;
    QTcpServer* m_recepteur;
    //bool m_attenteCreation;

signals:
    void ajoutClientVersPrinc(QByteArray, QByteArray);
    void PtArr(QString, QString);

private slots:
    void creationNouveauClient(QByteArray, QByteArray);
};

#endif // THREADCLIENT_H
