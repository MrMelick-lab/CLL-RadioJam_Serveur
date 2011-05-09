#include "threadclient.h"

threadclient::threadclient(QTcpSocket* socket)
{
    m_socket = socket;
    m_EnCours = false;
    m_recepteur = new QTcpServer();
}

void threadclient::run()
{
    QByteArray baReception;

    //Initialisation du nouveau client
    if(m_socket->waitForReadyRead(1000)){
        baReception.append(m_socket->readAll());//Réception du nom

        //Peut-être ajouter une validation plus tard ici, pour savoir si le nom est déjà utilisé

        m_socket->write("#");//Retourne un # pour confirmer une réception du nom sans problème
        m_socket->waitForBytesWritten();

        if(m_socket->waitForReadyRead(1000)){
            baReception.append(m_socket->readAll());//Réception du no d'instrument

            //Ajout du nouveau client à la liste
            emit(ajoutClientVersPrinc(baReception));
            m_EnCours = true;
        }
    }



    while(m_EnCours){
        //écoute les notes et les envoyes (avec un signal)
        //envoyer à partir de ce socket: m_socketRecepteur

    }
}

void threadclient::creationNouveauClient(QByteArray b)
{
    m_socket->write("N");
    m_socket->write(QString(b.at(0)).toAscii());
    m_socket->write(QString(b.at(1)).toAscii());

    m_recepteur->listen(QHostAddress::Any, 22224);
    if(m_recepteur->waitForNewConnection(30000))
        m_socketRecepteur = m_recepteur->nextPendingConnection();
}
