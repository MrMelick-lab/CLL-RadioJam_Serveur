#ifndef RADIO_JAM_SERVEUR_H
#define RADIO_JAM_SERVEUR_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include "threadclient.h"
#include "thread_envois.h"

namespace Ui {
    class Radio_Jam_Serveur;
}

class Radio_Jam_Serveur : public QMainWindow
{
    Q_OBJECT

public:
    explicit Radio_Jam_Serveur(QWidget *parent = 0);
    ~Radio_Jam_Serveur();

private:
    Ui::Radio_Jam_Serveur *ui;
    QTcpServer* m_serveur;
     QTcpServer* m_serveurEnv;
    QList<threadclient *> m_listeThread;
    QList<thread_envois *> m_listeThreadEnv;

private slots:
    void on_btnDemArr_clicked();

    void nouveauClient();

    void PtArrThread(QString, QString);

    void nouveauRecepteur();

    void ajoutDUnClient(QByteArray, QByteArray);


signals:
    void creationNouveauClient(QByteArray, QByteArray);

    void informationsNouveauClient(QByteArray, QByteArray);

};

#endif // RADIO_JAM_SERVEUR_H
