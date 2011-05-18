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
    m_serveurEnv = new QTcpServer();
    connect(m_serveurEnv, SIGNAL(newConnection()), this, SLOT(nouveauRecepteur()));
}

Radio_Jam_Serveur::~Radio_Jam_Serveur()
{
    for(int i = 0; m_listeThread.size() > i; i++){
        m_listeThread[i]->quit();
    }
    for(int i = 0; m_listeThreadEnv.size() > i; i++){
        m_listeThreadEnv[i]->quit();
    }
    delete ui;
}

void Radio_Jam_Serveur::on_btnDemArr_clicked()
{
    if(ui->btnDemArr->text() == "Demarrer le serveur"){
        m_serveur->listen(QHostAddress::Any, 22222);
        m_serveurEnv->listen(QHostAddress::Any, 22224);
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

    //MessageBox pour les testes
    connect(nouveauThread, SIGNAL(PtArr(QString, QString)), this, SLOT(PtArrThread(QString, QString)));

    //Recois les informations du nouveau client
    connect(nouveauThread, SIGNAL(ajoutClientVersPrinc(QByteArray,QByteArray)), this, SLOT(ajoutDUnClient(QByteArray,QByteArray)));
    //Transmet les informations des nouveaux clients a tous les threads
    connect(this, SIGNAL(informationsNouveauClient(QByteArray,QByteArray)), nouveauThread, SLOT(unNouveauClientCestConnecte(QByteArray,QByteArray)));

    nouveauThread->start();
}

void Radio_Jam_Serveur::nouveauRecepteur()
{
    thread_envois* nouveauThreadEnv = new thread_envois(m_serveurEnv->nextPendingConnection());
    m_listeThreadEnv.append(nouveauThreadEnv);
    int id = m_listeThreadEnv.size() - 1;
    connect(m_listeThread[id], SIGNAL(EnvoieNote(int)), m_listeThreadEnv[id], SLOT(EnvoieNote(int)));
    m_listeThread[id]->m_attenteConnexion = false;
    connect(nouveauThreadEnv, SIGNAL(PtArr(QString, QString)), this, SLOT(PtArrThread(QString, QString)));
}

void Radio_Jam_Serveur::PtArrThread(QString titre, QString message)
{
    QMessageBox::information(this, titre, message);
}

void Radio_Jam_Serveur::ajoutDUnClient(QByteArray nom, QByteArray instru)
{
    //transmet les informations des nouveaux clients à tous les threads client
    emit informationsNouveauClient(nom, instru);
}
