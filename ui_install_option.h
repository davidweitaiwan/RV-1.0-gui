/********************************************************************************
** Form generated from reading UI file 'install_option.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSTALL_OPTION_H
#define UI_INSTALL_OPTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_install_option
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *comboBox;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_5;

    void setupUi(QWidget *install_option)
    {
        if (install_option->objectName().isEmpty())
            install_option->setObjectName(QString::fromUtf8("install_option"));
        install_option->resize(550, 355);
        label = new QLabel(install_option);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 40, 121, 17));
        label_2 = new QLabel(install_option);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(50, 80, 101, 17));
        label_3 = new QLabel(install_option);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 120, 41, 17));
        comboBox = new QComboBox(install_option);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(160, 40, 271, 25));
        lineEdit = new QLineEdit(install_option);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(160, 80, 271, 25));
        lineEdit_2 = new QLineEdit(install_option);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(160, 120, 271, 25));
        pushButton = new QPushButton(install_option);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(160, 260, 89, 25));
        label_4 = new QLabel(install_option);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(50, 10, 91, 17));
        label_5 = new QLabel(install_option);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(160, 10, 171, 17));
        pushButton_2 = new QPushButton(install_option);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(300, 260, 111, 25));
        pushButton_3 = new QPushButton(install_option);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(30, 260, 89, 25));
        checkBox = new QCheckBox(install_option);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(230, 170, 92, 23));
        checkBox_2 = new QCheckBox(install_option);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setGeometry(QRect(130, 170, 92, 23));
        checkBox_3 = new QCheckBox(install_option);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setGeometry(QRect(40, 170, 92, 23));
        checkBox_4 = new QCheckBox(install_option);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setGeometry(QRect(340, 170, 92, 23));
        checkBox_5 = new QCheckBox(install_option);
        checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));
        checkBox_5->setGeometry(QRect(40, 220, 181, 23));

        retranslateUi(install_option);

        QMetaObject::connectSlotsByName(install_option);
    } // setupUi

    void retranslateUi(QWidget *install_option)
    {
        install_option->setWindowTitle(QApplication::translate("install_option", "Form", nullptr));
        label->setText(QApplication::translate("install_option", "Package Name:", nullptr));
        label_2->setText(QApplication::translate("install_option", "Interface:", nullptr));
        label_3->setText(QApplication::translate("install_option", "IP:", nullptr));
        lineEdit->setText(QApplication::translate("install_option", "eth0", nullptr));
        lineEdit_2->setText(QApplication::translate("install_option", "dhcp", nullptr));
        pushButton->setText(QApplication::translate("install_option", "close", nullptr));
        label_4->setText(QApplication::translate("install_option", "Host Name:", nullptr));
        label_5->setText(QApplication::translate("install_option", "Undefined Text", nullptr));
        pushButton_2->setText(QApplication::translate("install_option", "Save and close", nullptr));
        pushButton_3->setText(QApplication::translate("install_option", "Reset", nullptr));
        checkBox->setText(QApplication::translate("install_option", "install", nullptr));
        checkBox_2->setText(QApplication::translate("install_option", "update", nullptr));
        checkBox_3->setText(QApplication::translate("install_option", "remove", nullptr));
        checkBox_4->setText(QApplication::translate("install_option", "preserve", nullptr));
        checkBox_5->setText(QApplication::translate("install_option", "update depolyment", nullptr));
    } // retranslateUi

};

namespace Ui {
    class install_option: public Ui_install_option {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSTALL_OPTION_H
