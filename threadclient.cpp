#include "threadclient.h"

threadclient::threadclient(QTcpSocket* socket)
{
    m_socket = socket;
    m_EnCours = false;
    m_recepteur = new QTcpServer();
    //m_attenteCreation = true;
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

        variable.setValue(baNom);
        emit(PtArr("nom", variable.toString()));

        //Peut-être ajouter une validation plus tard ici, pour savoir si le nom est déjà utilisé

        m_socket->write("#");//Retourne un # pour confirmer une réception du nom sans problème
        m_socket->waitForBytesWritten();

        if(m_socket->waitForReadyRead(1000)){
            baInstru.append(m_socket->readAll());//Réception du no d'instrument

            variable.setValue(baInstru);
            emit(PtArr("instru", variable.toString()));

            //Ajout du nouveau client à la liste
            //emit(ajoutClientVersPrinc(baNom, baInstru));
            m_EnCours = true;
        }
    }

    /*while(m_attenteCreation)
    {
        //boucle qui attent que la création du thread de réception soit terminé.
    }*/


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

void threadclient::creationNouveauClient(QByteArray nom, QByteArray instru)
{
    /*m_socket->write("N");
    m_socket->waitForBytesWritten();
    m_socket->write(QString(nom.at(0)).toAscii());
    m_socket->waitForBytesWritten();
    m_socket->write(QString(instru.at(1)).toAscii());
    m_socket->waitForBytesWritten();

    emit PtArr("Creation en cours", "attente de connexion");

    m_recepteur->listen(QHostAddress::Any, 22224);
    if(m_recepteur->waitForNewConnection(30000))
    {
        m_socketRecepteur = m_recepteur->nextPendingConnection();
        emit PtArr("Creation en cours", "connexion etabli");
    }
    m_attenteCreation = false;*/
}
