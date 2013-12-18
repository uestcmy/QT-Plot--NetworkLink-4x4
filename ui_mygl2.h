/********************************************************************************
** Form generated from reading UI file 'mygl2.ui'
**
** Created: Tue Dec 3 21:09:09 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYGL2_H
#define UI_MYGL2_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mygl2
{
public:

    void setupUi(QWidget *mygl2)
    {
        if (mygl2->objectName().isEmpty())
            mygl2->setObjectName(QString::fromUtf8("mygl2"));
        mygl2->resize(400, 300);

        retranslateUi(mygl2);

        QMetaObject::connectSlotsByName(mygl2);
    } // setupUi

    void retranslateUi(QWidget *mygl2)
    {
        mygl2->setWindowTitle(QApplication::translate("mygl2", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class mygl2: public Ui_mygl2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYGL2_H
