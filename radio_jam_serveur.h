#ifndef RADIO_JAM_SERVEUR_H
#define RADIO_JAM_SERVEUR_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include "threadclient.h"

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
    QList<threadclient *> m_listeThread;

private slots:
    void on_btnDemArr_clicked();

    void nouveauClient();

    void ajoutClient(QByteArray);


signals:
    void creationNouveauClient(QByteArray);

};

#endif // RADIO_JAM_SERVEUR_H
