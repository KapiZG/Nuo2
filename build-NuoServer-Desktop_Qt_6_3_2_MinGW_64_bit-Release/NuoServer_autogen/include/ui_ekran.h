/********************************************************************************
** Form generated from reading UI file 'ekran.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EKRAN_H
#define UI_EKRAN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Ekran
{
public:

    void setupUi(QWidget *Ekran)
    {
        if (Ekran->objectName().isEmpty())
            Ekran->setObjectName(QString::fromUtf8("Ekran"));
        Ekran->resize(800, 600);

        retranslateUi(Ekran);

        QMetaObject::connectSlotsByName(Ekran);
    } // setupUi

    void retranslateUi(QWidget *Ekran)
    {
        Ekran->setWindowTitle(QCoreApplication::translate("Ekran", "Ekran", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Ekran: public Ui_Ekran {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EKRAN_H
