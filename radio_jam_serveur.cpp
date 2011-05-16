#include "radio_jam_serveur.h"
#include "ui_radio_jam_serveur.h"
#include "QMessageBox"


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
    for(int i = 0; m_listeThread.size() > i; i++){
        m_listeThread[i]->quit();
    }
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
        ui->btnDemArr->setText("Serveur ferme");
        ui->btnDemArr->setEnabled(false);
    }
}

void Radio_Jam_Serveur::nouveauClient()
{
    threadclient * nouveauThread = new threadclient(m_serveur->nextPendingConnection());
    m_listeThread.append(nouveauThread);

    connect(nouveauThread, SIGNAL(ajoutClientVersPrinc(QByteArray, QByteArray)), this, SLOT(ajoutClient(QByteArray, QByteArray)));
    connect(this, SIGNAL(creationNouveauClient(QByteArray, QByteArray)), nouveauThread, SLOT(creationNouveauClient(QByteArray, QByteArray)));
    connect(nouveauThread, SIGNAL(PtArr(QString, QString)), this, SLOT(PtArrThread(QString, QString)));
    nouveauThread->start();
}

void Radio_Jam_Serveur::ajoutClient(QByteArray nom, QByteArray instru)
{
   //Envoie les infos à tous les threads réceptions en cours pour que chaque clients créent un nouveau thread de réception.
   emit(creationNouveauClient(nom, instru));

}

void Radio_Jam_Serveur::PtArrThread(QString titre, QString message)
{
    QMessageBox::information(this, titre, message);
}
