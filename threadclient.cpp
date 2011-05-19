#include "threadclient.h"

threadclient::threadclient(QTcpSocket* socket)
{
    m_socket = socket;
    m_EnCours = false;
    m_recepteur = new QTcpServer();
    m_attenteConnexion = true;
}

void threadclient::run()
{
    QByteArray baReception;
    QVariant variable;
    bool quitter = true;

    //Initialisation du nouveau client
    m_socket->write("d");//envoie un 'd' pour dire au client qu'il est pret a écouter.
    m_socket->waitForBytesWritten();
    if(m_socket->waitForReadyRead(3000))
    {
        QByteArray baNom, baInstru;
        baNom.append(m_socket->readAll());//Réception du nom

        /*variable.setValue(baNom);
        emit(PtArr("nom", variable.toString()));*/

        //Peut-être ajouter une validation plus tard ici, pour savoir si le nom est déjà utilisé

        m_socket->write("#");//Retourne un # pour confirmer une réception du nom sans problème
        m_socket->waitForBytesWritten();

        if(m_socket->waitForReadyRead(1000)){
            baInstru.append(m_socket->readAll());//Réception du no d'instrument

            /*variable.setValue(baInstru);
            emit(PtArr("instru", variable.toString()));*/

            //Ajout du nouveau client à la liste
            emit ajoutClientVersPrinc(baNom, baInstru);
            m_EnCours = true;
        }
    }

    while(m_attenteConnexion)
    {
        //attend que la connexion avec le thread_envois soit établi
    }
    while(m_EnCours){
        //écoute les notes et les envoyes (avec un signal)
        //envoyer à partir de ce socket: m_socketRecepteur

        if(m_socket->waitForReadyRead(1000))
        {
            baReception.append(m_socket->read(1));
            if(baReception.at(0) == 'L')//Si il réceptionne la lettre 'L', ça signifie que le client quitte
            {
                m_EnCours = false;
                quitter = false;

                //signal au thread d'envoie de se fermer
            }
            else if(baReception.at(0) == 'M')//Changement d'instrument
            {
                //Seulement dans la version payante du serveur RadioJam (5000$ CAN)
            }
            else//Sinon c'est une note qu'il envoie
            {
                emit EnvoieNote(baReception.at(0));
                /*variable.setValue(baReception.at(0));
                emit PtArr("Recoie une note", variable.toString());
                variable.clear();*/
            }
            baReception.clear();
        }
    }
    //Le serveur ferme par lui même et avertie le client
    if(quitter)
    {
        m_socket->write("L");
        m_socket->waitForBytesWritten();
        //réception du caractère de fin
        if(m_socket->waitForReadyRead())
            m_socket->readAll();
    }
    m_socket->close();

}

void threadclient::unNouveauClientCestConnecte(QByteArray nom, QByteArray instru)
{
    m_socket->write("N");
    m_socket->waitForBytesWritten();
    m_socket->write(nom + instru);
    m_socket->waitForBytesWritten();
}
