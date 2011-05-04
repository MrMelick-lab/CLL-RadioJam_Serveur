#include "radio_jam_serveur.h"
#include "ui_radio_jam_serveur.h"
#include "threadclient.h"

Radio_Jam_Serveur::Radio_Jam_Serveur(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Radio_Jam_Serveur)
{
    ui->setupUi(this);
    m_serveur = new QTcpServer();
    connect(m_serveur, SIGNAL(newConnection()), this, SLOT(nouveauClient()));
}

Radio_Jam_Serveur::~Radio_Jam_Serveur()
{
    delete ui;
}

void Radio_Jam_Serveur::on_btnDemArr_clicked()
{
    if(ui->btnDemArr->text() == "Demarrer le serveur"){
        m_serveur->listen(QHostAddress::Any, 22222);
        ui->btnDemArr->setText("Arreter le serveur");
    }
    else{
        m_serveur->close();
        ui->btnDemArr->setText("Demarrer le serveur");
    }
}

void Radio_Jam_Serveur::nouveauClient()
{
    QTcpSocket* socketClient = m_serveur->nextPendingConnection();
    threadclient* nouveauThread = new threadclient(socketClient);
    nouveauThread->start();
    connect(nouveauThread, SIGNAL(ajoutClient(QByteArray)), this, SLOT(ajoutClient(QByteArray)));
    //m_listeThread.append(nouveauThread);
}

void Radio_Jam_Serveur::ajoutClient(QByteArray b)
{

}
