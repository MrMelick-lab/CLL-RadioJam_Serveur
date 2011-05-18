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
    bool m_attenteConnexion;

protected:
    void run();

private:
    QTcpSocket* m_socket, *m_socketRecepteur;
    QTcpServer* m_recepteur;

signals:
    void EnvoieNote(int);
    void PtArr(QString, QString);
    void ajoutClientVersPrinc(QByteArray, QByteArray);

private slots:
        void unNouveauClientCestConnecte(QByteArray, QByteArray);

};

#endif // THREADCLIENT_H
