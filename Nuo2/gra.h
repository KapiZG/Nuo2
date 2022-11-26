#ifndef GRA_H
#define GRA_H

#include <QWidget>

class Gra : public QWidget
{
    Q_OBJECT
public:
    explicit Gra(QString *id, const class Gracz *gracz, QWidget *parent = nullptr);

private:
    const QString *idGry;
};

#endif // GRA_H
