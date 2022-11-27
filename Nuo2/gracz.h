#ifndef GRACZ_H
#define GRACZ_H


class Gracz
{
public:
    Gracz(const int id);
    int getIDGracza() const;

private:
    const int idGracza;
};

#endif // GRACZ_H
