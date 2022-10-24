#include "logowanie.h"
#include "./ui_logowanie.h"
#include <QPushButton>
#include <QTextEdit>
#include <windows.h>
#include <QTcpSocket>
#include "wyborgry.h"
#include <QMessageBox>

//#include <QtSql>

Logowanie::Logowanie(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Logowanie)
{
    ui->setupUi(this);
    ui->W_Rejestracja->hide();
    ui->Blad->hide();
    qDebug()<<"TAKKKK";
    socket = new QTcpSocket(this);

    socket->connectToHost("127.0.0.1", 6969);

    if(socket->waitForConnected(10)){

        socket->write("Odpowiedz od socketa");
        socket->flush();
        socket->waitForBytesWritten(100);

        socket->waitForReadyRead(300);
        qDebug()<<"Test:" <<socket->readAll();

        socket->close();
    } else {
        QMessageBox::critical(this, "Error", "Nie można połączyć z serverem");
    }
    connect(ui->zarejestruj, &QPushButton::pressed, this, &Logowanie::zakladkaRejestracji);
    connect(ui->zaloguj, &QPushButton::pressed, this, &Logowanie::zakladkaLogowania);
}

Logowanie::~Logowanie()
{
    delete ui;
}

//metoda służąca do przywrócenia menu głównego
void Logowanie::guzikiLogowania()
{
    ui->zaloguj->show();
    ui->zarejestruj->show();
}

//Metoda służąca do otwarcia widgetu rejestracji
void Logowanie::zakladkaRejestracji()
{
    ui->zaloguj->hide();
    ui->zarejestruj->hide();
    ui->W_Rejestracja->show();
    connect(ui->B_Rejestracja, &QPushButton::pressed, this, &Logowanie::rejestracja);
}

//Metoda słuząca do stworzenia widgetu po pomyślniej rejestracji, gdy nazwa użytkownika jest dłuższa od 3 liter
void Logowanie::rejestracja()
{
    QString nazwa = ui->Nazwa->text();
    QString haslo = ui->Haslo->text();
    if(nazwa.length() > 3 && haslo.length() > 3){
        disconnect(ui->B_Rejestracja, &QPushButton::pressed, this, &Logowanie::rejestracja);
        ui->Blad->hide();
        QWidget *w_pomyslnie = new QWidget();
        QVBoxLayout *l_pomyslnie = new QVBoxLayout();
        QPushButton *b_pomyslnie = new QPushButton("Zatwierdz");
        l_pomyslnie->addWidget(b_pomyslnie);
        QTextEdit *t_pomyslnie = new QTextEdit("Pomyslnie Zarejestrowano");
        t_pomyslnie->setReadOnly(true);
        l_pomyslnie->addWidget(t_pomyslnie);
        w_pomyslnie->setLayout(l_pomyslnie);
        ui->W_Rejestracja->hide();
        this->layout()->addWidget(w_pomyslnie);
        //W tym connectie użyte zostało wyrażenie lambda
        connect(b_pomyslnie, &QPushButton::clicked, this, [w_pomyslnie, this]()
        {
            delete w_pomyslnie;
            ui->Nazwa->clear();
            ui->Haslo->clear();
            guzikiLogowania();
        });
    } else if(nazwa.length() < 3 && haslo.length() > 3){
        ui->Blad->setText("Nazwa jest za krótka");
        ui->Blad->show();
    } else if(nazwa.length() > 3 && haslo.length() < 3){
        ui->Blad->setText("Hasło jest za krótkie");
        ui->Blad->show();
    } else {
        ui->Blad->setText("Hasło i nazwa są za krótkie");
        ui->Blad->show();
    }

}

void Logowanie::zakladkaLogowania()
{
    ui->W_Rejestracja->show();
    ui->zaloguj->hide();
    ui->zarejestruj->hide();
    connect(ui->B_Rejestracja, &QPushButton::pressed, this, &Logowanie::logowanie);
}

void Logowanie::logowanie()
{
    QString nazwa = ui->Nazwa->text();
    QString haslo = ui->Haslo->text();
    if(nazwa.length() > 3 && haslo.length() > 3){
        disconnect(ui->B_Rejestracja, &QPushButton::pressed, this, &Logowanie::logowanie);
        ui->Blad->hide();
        QWidget *w_pomyslnie = new QWidget();
        QVBoxLayout *l_pomyslnie = new QVBoxLayout();
        QPushButton *b_pomyslnie = new QPushButton("Zatwierdz");
        l_pomyslnie->addWidget(b_pomyslnie);
        QTextEdit *t_pomyslnie = new QTextEdit("Pomyslnie Zalogowano");
        t_pomyslnie->setReadOnly(true);
        l_pomyslnie->addWidget(t_pomyslnie);
        w_pomyslnie->setLayout(l_pomyslnie);
        ui->W_Rejestracja->hide();
        this->layout()->addWidget(w_pomyslnie);
        //W tym connectie użyte zostało wyrażenie lambda
        connect(b_pomyslnie, &QPushButton::clicked, this, [w_pomyslnie, this]()
        {
            delete w_pomyslnie;
            ui->Nazwa->clear();
            ui->Haslo->clear();
            WyborGry *wyborGry = new WyborGry();
            wyborGry->show();
            this->close();
        });
    }
}
