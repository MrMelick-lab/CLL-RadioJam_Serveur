#include "radio_jam_serveur.h"
#include "ui_radio_jam_serveur.h"


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
        for(int i = 0; m_listeThread.size() > i; i++){
            if(m_listeThread[i]->isRunning())
                m_listeThread[i]->m_EnCours = false;
        }
        m_serveur->close();
        ui->btnDemArr->setText("Demarrer le serveur");
    }
}

void Radio_Jam_Serveur::nouveauClient()
{
    threadclient * nouveauThread = new threadclient(m_serveur->nextPendingConnection());
    m_listeThread.append(nouveauThread);

    //nouveauThread->isRunning()
    //connect(nouveauThread, SIGNAL(ajoutClientVersPrinc(QByteArray)), this, SLOT(ajoutClient(QByteArray)));
    //connect(this, SIGNAL(creationNouveauClient(QByteArray)), nouveauThread, SLOT(creationNouveauClient(QByteArray)));
    nouveauThread->start();
}

void Radio_Jam_Serveur::ajoutClient(QByteArray b)
{
   //Envoie les infos à tous les threads réceptions en cours pour que chaque clients créent un nouveau thread de réception.
    //emit(creationNouveauClient(b));

}
