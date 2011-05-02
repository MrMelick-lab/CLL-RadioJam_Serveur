#include <QtGui/QApplication>
#include "radio_jam_serveur.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Radio_Jam_Serveur w;
    w.show();

    return a.exec();
}
