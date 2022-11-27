#include "logowanie.h"
#include "./ui_logowanie.h"
#include <QPushButton>
#include <QTextEdit>
#include <windows.h>
#include <QTcpSocket>
#include "wyborgry.h"
#include "gracz.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
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

    polaczZServerem();

    connect(ui->PolaczZServerem, &QPushButton::pressed, this, &Logowanie::polaczZServerem);

    connect(ui->TextDoServeraTest, &QPushButton::pressed, this, &Logowanie::wyslijWiadomosc);

    connect(ui->zarejestruj, &QPushButton::pressed, this, &Logowanie::zakladkaRejestracji);
    connect(ui->zaloguj, &QPushButton::pressed, this, &Logowanie::zakladkaLogowania);
}

Logowanie::~Logowanie()
{
    socket->close();
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
    if(nazwa.length() > 3 && haslo.length() > 3)
    {
        //Tworzenie wysyłanego obiektu JSON
        QJsonObject *daneUzytkownika = new QJsonObject;
        QJsonDocument *jsonDocument = new QJsonDocument;

        daneUzytkownika->insert("Typ", "R");
        daneUzytkownika->insert("Nazwa", nazwa);
        daneUzytkownika->insert("Haslo", haslo);

        jsonDocument->setObject(*daneUzytkownika);


        QByteArray *jsonByte = new QByteArray(jsonDocument->toJson(QJsonDocument::Compact));

        socket->write(*jsonByte);
        socket->flush();

        socket->waitForReadyRead(100);
        if(socket->readAll() == "t")
        {
            disconnect(ui->B_Rejestracja, &QPushButton::pressed, this, &Logowanie::rejestracja);
            ui->Blad->hide();

            //Tworzene menu po pomyślnej rejestracji
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

            //Dane wysyłane do servera
            QString daneLogowania = "Rejestracja: ";
            daneLogowania = ui->Nazwa->text();
            daneLogowania += " ";
            daneLogowania +=  ui->Haslo->text();
            socket->write(daneLogowania.toStdString().c_str());

            //W tym connectie użyte zostało wyrażenie lambda
            connect(b_pomyslnie, &QPushButton::clicked, this, [w_pomyslnie, this]()
            {
                delete w_pomyslnie;
                ui->Nazwa->clear();
                ui->Haslo->clear();
                guzikiLogowania();
            });
        }
    }
    else if(nazwa.length() < 3 && haslo.length() > 3)
    {
        ui->Blad->setText("Nazwa jest za krótka");
        ui->Blad->show();
    }
    else if(nazwa.length() > 3 && haslo.length() < 3)
    {
        ui->Blad->setText("Hasło jest za krótkie");
        ui->Blad->show();
    }
    else
    {
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

    QJsonObject *daneLogowania = new QJsonObject;
    QJsonDocument *jsonDocument = new QJsonDocument;

    daneLogowania->insert("Typ", "L");
    daneLogowania->insert("Nazwa", nazwa);
    daneLogowania->insert("Haslo", haslo);

    jsonDocument->setObject(*daneLogowania);

    QByteArray *jsonFile = new QByteArray(jsonDocument->toJson(QJsonDocument::Compact));

    socket->write(*jsonFile);
    socket->flush();

    socket->waitForReadyRead(100);
    QByteArray *wiadomosc = new QByteArray(socket->readAll());
    QJsonDocument *json = new QJsonDocument(QJsonDocument::fromJson(*wiadomosc));

    if(!json->isEmpty())
    {
        QJsonObject *jsonObject = new QJsonObject(json->object());
        if(jsonObject->value("Bool").toString() == "t")
        {
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
            connect(b_pomyslnie, &QPushButton::clicked, this, [w_pomyslnie, this, jsonObject]()
            {
                delete w_pomyslnie;
                ui->Nazwa->clear();
                ui->Haslo->clear();
                Gracz *gracz = new Gracz(jsonObject->value("ID").toInt());
                WyborGry *wyborGry = new WyborGry(gracz);
                wyborGry->show();
                this->close();
            });

        }
        else
        {
            qDebug() << "Coś poszło nie tak" << *jsonObject;
        }
    }
    else
    {
        qDebug() << "Nie poprawny login lub haslo";
    }
}

void Logowanie::polaczZServerem()
{
    socket->close();
    socket->connectToHost("89.72.109.193", 6969);

    if(socket->waitForConnected(10000))
    {
        socket->waitForReadyRead(300);
        ui->CzyJestPolaczenie->setText(socket->readAll());

    }
    else
    {
        QMessageBox::critical(this, "Error", socket->errorString());
        ui->CzyJestPolaczenie->setText("Brak złączenia z serverem");
    }
}


void Logowanie::wyslijWiadomosc()
{
    socket->write(ui->TextDoWyslaniaTest->text().toStdString().c_str());
}
