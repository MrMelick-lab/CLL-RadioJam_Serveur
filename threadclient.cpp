#include "threadclient.h"

threadclient::threadclient(QTcpSocket* socket)
{
    m_socket = socket;
    m_EnCours = false;
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
            emit(ajoutClient(baReception));
            m_EnCours = true;
        }
    }



    while(m_EnCours){
        //écoute les notes envoyées par le client et les transmet à tous les autres
    }
}
