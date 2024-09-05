/********************************************************************************
** Form generated from reading UI file 'install_common.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSTALL_COMMON_H
#define UI_INSTALL_COMMON_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_install_common
{
public:
    QLabel *label_2;
    QComboBox *comboBox;
    QLabel *label_3;
    QComboBox *comboBox_2;
    QPushButton *pushButton;
    QTextEdit *textEdit;
    QPushButton *pushButton_2;
    QLabel *label_4;
    QComboBox *comboBox_3;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;

    void setupUi(QWidget *install_common)
    {
        if (install_common->objectName().isEmpty())
            install_common->setObjectName(QString::fromUtf8("install_common"));
        install_common->resize(980, 700);
        label_2 = new QLabel(install_common);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 10, 67, 17));
        comboBox = new QComboBox(install_common);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(150, 10, 501, 25));
        label_3 = new QLabel(install_common);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 50, 131, 17));
        comboBox_2 = new QComboBox(install_common);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(150, 50, 501, 25));
        pushButton = new QPushButton(install_common);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(660, 90, 89, 25));
        textEdit = new QTextEdit(install_common);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(50, 140, 631, 501));
        pushButton_2 = new QPushButton(install_common);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(300, 650, 89, 25));
        label_4 = new QLabel(install_common);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 100, 67, 17));
        comboBox_3 = new QComboBox(install_common);
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setGeometry(QRect(150, 90, 501, 25));
        pushButton_3 = new QPushButton(install_common);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(670, 50, 89, 25));
        pushButton_4 = new QPushButton(install_common);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(770, 50, 89, 25));

        retranslateUi(install_common);

        QMetaObject::connectSlotsByName(install_common);
    } // setupUi

    void retranslateUi(QWidget *install_common)
    {
        install_common->setWindowTitle(QCoreApplication::translate("install_common", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("install_common", "Device:", nullptr));
        label_3->setText(QCoreApplication::translate("install_common", "Node Config List:", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("install_common", "/V0/gps_0", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("install_common", "/V0/sense_0", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("install_common", "/V0/sense_1", nullptr));
        comboBox_2->setItemText(3, QCoreApplication::translate("install_common", "/V0/ultrasound_1", nullptr));
        comboBox_2->setItemText(4, QCoreApplication::translate("install_common", "/V0/ultrasound_2", nullptr));
        comboBox_2->setItemText(5, QCoreApplication::translate("install_common", "/V0/zed_0", nullptr));
        comboBox_2->setItemText(6, QCoreApplication::translate("install_common", "/V0/zed_1", nullptr));
        comboBox_2->setItemText(7, QCoreApplication::translate("install_common", "/V0/zed_2", nullptr));
        comboBox_2->setItemText(8, QCoreApplication::translate("install_common", "/V0/webcam_0", nullptr));
        comboBox_2->setItemText(9, QCoreApplication::translate("install_common", "/V0/webcam_1", nullptr));
        comboBox_2->setItemText(10, QCoreApplication::translate("install_common", "/V0/chassis_steering_0", nullptr));
        comboBox_2->setItemText(11, QCoreApplication::translate("install_common", "/V0/chassis_steering_1", nullptr));
        comboBox_2->setItemText(12, QCoreApplication::translate("install_common", "/V0/chassis_steering_2", nullptr));
        comboBox_2->setItemText(13, QCoreApplication::translate("install_common", "/V0/chassis_steering_3", nullptr));
        comboBox_2->setItemText(14, QCoreApplication::translate("install_common", "/V0/chassis_motor_0", nullptr));
        comboBox_2->setItemText(15, QCoreApplication::translate("install_common", "/V0/chassis_motor_1", nullptr));
        comboBox_2->setItemText(16, QCoreApplication::translate("install_common", "/V0/chassis_motor_2", nullptr));
        comboBox_2->setItemText(17, QCoreApplication::translate("install_common", "/V0/chassis_motor_3", nullptr));
        comboBox_2->setItemText(18, QCoreApplication::translate("install_common", "/V0/controlserver_0", nullptr));
        comboBox_2->setItemText(19, QCoreApplication::translate("install_common", "/V0/grounddetect_0", nullptr));
        comboBox_2->setItemText(20, QCoreApplication::translate("install_common", "/V0/qosserver_0", nullptr));
        comboBox_2->setItemText(21, QCoreApplication::translate("install_common", "/V0/safetyserver_0", nullptr));
        comboBox_2->setItemText(22, QCoreApplication::translate("install_common", "/V0/timesyncserver_0", nullptr));
        comboBox_2->setItemText(23, QCoreApplication::translate("install_common", "/V0/dataserver_0", nullptr));

        pushButton->setText(QCoreApplication::translate("install_common", "select", nullptr));
        pushButton_2->setText(QCoreApplication::translate("install_common", "upload", nullptr));
        label_4->setText(QCoreApplication::translate("install_common", "File:", nullptr));
        comboBox_3->setItemText(0, QCoreApplication::translate("install_common", "common.yaml", nullptr));
        comboBox_3->setItemText(1, QCoreApplication::translate("install_common", "service.json", nullptr));

        pushButton_3->setText(QCoreApplication::translate("install_common", "load", nullptr));
        pushButton_4->setText(QCoreApplication::translate("install_common", "save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class install_common: public Ui_install_common {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSTALL_COMMON_H
