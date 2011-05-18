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
    void EnvoieNote(int);

signals:
    void PtArr(QString, QString);//Pour des testes
};

#endif // THREAD_ENVOIS_H
