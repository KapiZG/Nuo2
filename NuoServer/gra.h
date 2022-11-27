#ifndef GRA_H
#define GRA_H

#include <QObject>



class Gra
{
public:
    Gra(const QString *id, class Gracz *gracz);

private:
    const QString IDGry;
    class Gracz *gracze[8];
    class Karta *kartaNaStosie;
    class Karta *kartaDoWziecia;

    friend class NuoServer;
};

#endif // GRA_H
