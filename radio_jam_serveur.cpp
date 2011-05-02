#include "radio_jam_serveur.h"
#include "ui_radio_jam_serveur.h"

Radio_Jam_Serveur::Radio_Jam_Serveur(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Radio_Jam_Serveur)
{
    ui->setupUi(this);
}

Radio_Jam_Serveur::~Radio_Jam_Serveur()
{
    delete ui;
}
