#include "install_common.h"
#include "./../ui_install_common.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QMessageBox>
#include <libssh/sftp.h>
#include <libssh/libssh.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <ctype.h>
#include <QFileDialog>
#include <QTextStream>
#include <QByteArray>

// Good chunk size
#define MAX_XFER_BUF_SIZE 16384

install_common::install_common(QWidget *parent,QString device) :
    QWidget(parent),
    ui(new Ui::install_common)
{
    ui->setupUi(this);
    // ui->comboBox->addItem("v0-sensor-ultrasound-0／e4:5f:01:72:fe:6f／192.168.0.45／");
    // ui->comboBox->addItem("Unkown／dc:a6:32:28:15:86／192.168.4.104／");
    ui->comboBox->addItem(device);
    connect(ui->pushButton,&QPushButton::clicked, this, &install_common::on_device_select_pushbutton_clicked);
    connect(ui->pushButton_2,&QPushButton::clicked, this, &install_common::on_save_pushbutton_clicked);
    connect(ui->pushButton_3,&QPushButton::clicked, this, &install_common::on_load_file_pushbutton_clicked);
    connect(ui->pushButton_4,&QPushButton::clicked, this, &install_common::on_save_file_pushbutton_clicked);
}

install_common::~install_common()
{
    delete ui;
}

void install_common::on_device_select_pushbutton_clicked(){
    QString device=ui->comboBox->currentText();
    QString mac_address=device.split("／")[1];
    QString host_name=device.split("／")[0];
    std::string ip_address = device.split("／")[2].toStdString();
    std::string device_type = "";

    QFile install_file("install_setting.json");
    if(!install_file.open(QIODevice::ReadWrite)) {
    qDebug() << "File open error,the premission may denied.";
    } else {
    qDebug() <<"install_setting File open!";
    }
    QByteArray install_setting_file = install_file.readAll();
    QJsonDocument install_setting_json_document = QJsonDocument::fromJson(install_setting_file);
    QJsonObject install_root = install_setting_json_document.object();
    QJsonObject install_config = install_root["install_config"].toObject();
    QJsonObject host;
    // if (DNS_replace !="")
    // {
    //     host = install_config[DNS_replace].toObject();

    // }else{
        host = install_config[mac_address].toObject();
        qDebug()<<mac_address;

    // }
    
    std::string user = host["user"].toString().toStdString();
    std::string password = host["password"].toString().toStdString();

    if(user =="" ||password ==""){
        user =install_root["default_user_name"].toString().toStdString();
        password = install_root["default_password"].toString().toStdString();
        qDebug()<<QString::fromStdString(user);
    }
    device_type = host["device"].toString().toStdString();
    install_file.close();
    int rc;
    int port = 22;
    int verbosity = SSH_LOG_PROTOCOL;

    // lisbssh new session
    ssh_session my_ssh_session;
    my_ssh_session = ssh_new();
    if (my_ssh_session == NULL)
        return;
    ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST,ip_address.c_str());
    ssh_options_set(my_ssh_session, SSH_OPTIONS_PORT, &port);
    ssh_options_set(my_ssh_session,SSH_OPTIONS_PASSWORD_AUTH,password.c_str());
    ssh_options_set(my_ssh_session, SSH_OPTIONS_USER,user.c_str());
    ssh_options_set(my_ssh_session, SSH_OPTIONS_LOG_VERBOSITY, &verbosity);
    ssh_options_set(my_ssh_session, SSH_OPTIONS_CIPHERS_C_S,"aes128-ctr");
    ssh_options_set(my_ssh_session,SSH_OPTIONS_TIMEOUT_USEC,"10");
    rc = ssh_connect(my_ssh_session);
    if (rc != SSH_OK)  
    {
        ssh_free(my_ssh_session);
        return ;
    }
    rc = ssh_userauth_password(my_ssh_session, user.c_str(), password.c_str());
    if (rc != SSH_AUTH_SUCCESS)  
    {
        ssh_free(my_ssh_session);
        QMessageBox exception_ssh;
        exception_ssh.setText("Auth Error");
        exception_ssh.exec();
        return;
    }
    qDebug()<<"ssh connect success";
    // libssh sftp
    sftp_session sftp;
    
    sftp = sftp_new(my_ssh_session);
    if (sftp == NULL)
    {
        fprintf(stderr, "Error allocating SFTP session: %s\n",
                ssh_get_error(my_ssh_session));
        return ;
    }
    
    rc = sftp_init(sftp);
    if (rc != SSH_OK)
    {
        fprintf(stderr, "Error initializing SFTP session: code %d.\n",
                sftp_get_error(sftp));
        sftp_free(sftp);
        return ;
    }
    int access_type;
    sftp_file file;

    char buffer[MAX_XFER_BUF_SIZE];
    int nbytes, nwritten;
    int fd;
    // O_RDONLY 00
    access_type = 00;
    qDebug()<<QString::fromStdString(user);
    qDebug()<<QString::fromStdString(password);
    qDebug()<<QString::fromStdString(ip_address);
    qDebug()<<QString::fromStdString(device_type);
    std::string file_name;
    file_name = "./ros2_docker/"+ui->comboBox_3->currentText().toStdString();
    file = sftp_open(sftp, file_name.c_str(),
                    access_type, 0);
    if (file == NULL) {
        fprintf(stderr, "Can't open file for reading: %s\n",
                ssh_get_error(my_ssh_session));
        return ;
    }
 
//   fd = open("/path/to/profile", O_CREAT);
//   if (fd < 0) {
//       fprintf(stderr, "Can't open file for writing: %s\n",
//               strerror(errno));
//       return SSH_ERROR;
//   }
    QByteArray ssh_Qbyte;
    QByteArray ssh_merge_qbyte;
    QString ssh_infor_string;
    for (;;) {
        nbytes = sftp_read(file, buffer, sizeof(buffer));
        if (nbytes == 0) {
            break; // EOF
        } else if (nbytes < 0) {
            fprintf(stderr, "Error while reading file: %s\n",
                    ssh_get_error(my_ssh_session));
            sftp_close(file);
            return ;
        }
        ssh_Qbyte = QByteArray::fromRawData(buffer,nbytes);
        ssh_merge_qbyte.append(ssh_Qbyte);
        ssh_infor_string=ssh_merge_qbyte;
    //   nwritten = write(fd, buffer, nbytes);
    //   if (nwritten != nbytes) {
    //       fprintf(stderr, "Error writing: %s\n",
    //               strerror(errno));
    //       sftp_close(file);
    //       return SSH_ERROR;
    //   }

    }
    ssh_infor_string=ssh_merge_qbyte;
    qDebug().noquote()<<ssh_infor_string;

    rc = sftp_close(file);
    if (rc != SSH_OK) {
        fprintf(stderr, "Can't close the read file: %s\n",
                ssh_get_error(my_ssh_session));
        return ;
    }

    ui->textEdit->setText(ssh_infor_string);
}
void install_common::on_save_pushbutton_clicked(){
QString device=ui->comboBox->currentText();
    QString mac_address=device.split("／")[1];
    QString host_name=device.split("／")[0];
    std::string ip_address = device.split("／")[2].toStdString();
    std::string device_type = "";

    QFile install_file("install_setting.json");
    if(!install_file.open(QIODevice::ReadWrite)) {
    qDebug() << "File open error,the premission may denied.";
    } else {
    qDebug() <<"install_setting File open!";
    }
    QByteArray install_setting_file = install_file.readAll();
    QJsonDocument install_setting_json_document = QJsonDocument::fromJson(install_setting_file);
    QJsonObject install_root = install_setting_json_document.object();
    QJsonObject install_config = install_root["install_config"].toObject();
    QJsonObject host;
    // if (DNS_replace !="")
    // {
    //     host = install_config[DNS_replace].toObject();

    // }else{
        host = install_config[mac_address].toObject();
        qDebug()<<mac_address;

    // }
    
    std::string user = host["user"].toString().toStdString();
    std::string password = host["password"].toString().toStdString();

    if(user =="" ||password ==""){
        user =install_root["default_user_name"].toString().toStdString();
        password = install_root["default_password"].toString().toStdString();
        qDebug()<<QString::fromStdString(user);
    }
    device_type = host["device"].toString().toStdString();
    install_file.close();
    int rc;
    int port = 22;
    int verbosity = SSH_LOG_PROTOCOL;

    // lisbssh new session
    ssh_session my_ssh_session;
    my_ssh_session = ssh_new();
    if (my_ssh_session == NULL)
        return;
    ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST,ip_address.c_str());
    ssh_options_set(my_ssh_session, SSH_OPTIONS_PORT, &port);
    ssh_options_set(my_ssh_session,SSH_OPTIONS_PASSWORD_AUTH,password.c_str());
    ssh_options_set(my_ssh_session, SSH_OPTIONS_USER,user.c_str());
    ssh_options_set(my_ssh_session, SSH_OPTIONS_LOG_VERBOSITY, &verbosity);
    ssh_options_set(my_ssh_session, SSH_OPTIONS_CIPHERS_C_S,"aes128-ctr");
    ssh_options_set(my_ssh_session,SSH_OPTIONS_TIMEOUT_USEC,"100");
    rc = ssh_connect(my_ssh_session);
    if (rc != SSH_OK)  
    {
        ssh_free(my_ssh_session);
        return ;
    }
    rc = ssh_userauth_password(my_ssh_session, user.c_str(), password.c_str());
    if (rc != SSH_AUTH_SUCCESS)  
    {
        ssh_free(my_ssh_session);
        QMessageBox exception_ssh;
        exception_ssh.setText("Auth Error");
        exception_ssh.exec();
        return;
    }
    qDebug()<<"ssh connect success";
    // libssh sftp
    sftp_session sftp;
    
    sftp = sftp_new(my_ssh_session);
    if (sftp == NULL)
    {
        fprintf(stderr, "Error allocating SFTP session: %s\n",
                ssh_get_error(my_ssh_session));
        return ;
    }
        rc = sftp_init(sftp);
    if (rc != SSH_OK)
    {
        fprintf(stderr, "Error initializing SFTP session: code %d.\n",
                sftp_get_error(sftp));
        sftp_free(sftp);
        return ;
    }
  int access_type = O_WRONLY | O_CREAT | O_TRUNC;
  sftp_file file;
    std::string wirte_text = ui->textEdit->toPlainText().toStdString();
    const char *helloworld = "Hello, World!\n";
    int length = wirte_text.length();
    char buffer[MAX_XFER_BUF_SIZE];
    int nbytes, nwritten;
    int fd;

    qDebug()<<QString::fromStdString(user);
    qDebug()<<QString::fromStdString(password);
    qDebug()<<QString::fromStdString(ip_address);
    qDebug()<<QString::fromStdString(device_type);
    
    std::string file_name;
    file_name = "./ros2_docker/"+ui->comboBox_3->currentText().toStdString();
    file = sftp_open(sftp, file_name.c_str(),
                    access_type, S_IRWXU);
    if (file == NULL)
    {
        fprintf(stderr, "Can't open file for writing: %s\n",
                ssh_get_error(my_ssh_session));
        return ;
    }
 
    nwritten = sftp_write(file, wirte_text.c_str(), length);
    if (nwritten != length)
    {
        fprintf(stderr, "Can't write data to file: %s\n",
                ssh_get_error(my_ssh_session));
        sftp_close(file);
        return ;
    }
 
    rc = sftp_close(file);
    if (rc != SSH_OK)
    {
        fprintf(stderr, "Can't close the written file: %s\n",
                ssh_get_error(my_ssh_session));
        return ;
    }
}
void install_common::on_load_file_pushbutton_clicked(){
    QString file_name = ui->comboBox_2->currentText()+"_"+ui->comboBox_3->currentText()+".txt";
    file_name = file_name.replace("/","");
    QFile file(file_name);
    if(!file.open(QIODevice::ReadOnly)) {
    qDebug() << "File open error,the premission may denied.";
    } else {
    qDebug() <<"File open!";
    }
    QByteArray file_byte = file.readAll();
    QString file_string = file_byte;
    ui->textEdit->setText(file_string);
    file.close();
}
void install_common::on_save_file_pushbutton_clicked(){
    QString file_name = ui->comboBox_2->currentText()+"_"+ui->comboBox_3->currentText()+".txt";
    file_name = file_name.replace("/","");
    QFile file(file_name);
    if(!file.open(QIODevice::WriteOnly)) {
    qDebug() << "File open error,the premission may denied.";
    } else {
    qDebug() <<"File open!";
    }
    QByteArray file_byte = ui->textEdit->toPlainText().toUtf8();
    file.write(file_byte);
    file.close();
}