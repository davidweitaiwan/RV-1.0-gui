#include "mainwindow.h"
#include "./../ui_mainwindow.h"
#include <rclcpp/rclcpp.hpp>
#include <thread>
#include <unistd.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /** cocobird231*/
    this->devInfoThPtr_ = nullptr;

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_QosPushButton_clicked);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::on_SensorPushButton_clicked);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::on_data_server_record_puchButton_clicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::on_install_shell_PushButton_clicked);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::on_image_display_PushButton_clicked);
    connect(ui->pushButton_7, &QPushButton::clicked, this, &MainWindow::on_safety_PushButton_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::on_control_server_PushButton_clicked);
    name_node =rclcpp::Node::make_shared("get_the_name");
    QObject::connect(&timmer, &QTimer::timeout,this, &MainWindow::refresh_topic_name_list);
    /** cocobird231*/
    QObject::connect(&device_timer, &QTimer::timeout,this, &MainWindow::_refresh_device_info_th);
    device_timer.start(5000);
    timmer.start(1000);
}
MainWindow::~MainWindow()
{
    the_sensor_form->close();
    qosdevicedialog->close();
    the_install_shell->close();
    delete ui;

}
/** cocobird231*/
void MainWindow::_refresh_device_info_th()
{
    if (this->devInfoThPtr_ != nullptr)// Thread running
    {
        if (!this->devInfoThPtr_->joinable())
            return;
        this->devInfoThPtr_->join();
        delete devInfoThPtr_;

        // Update textbox
        ui->textBrowser_2->setText(QString::fromStdString(this->devInfoMsg_));
    }
    this->devInfoThPtr_ = new std::thread(std::bind(&MainWindow::refresh_device_info, this));
}
/** cocobird231*/
void MainWindow::refresh_device_info()
{
    this->devInfoMsg_ = "";
    this->the_install_shell->reqDevInfo.node_name = "all";
    bool reqSuccess = the_install_shell->DeviceInforcontrol->reqDeviceInfor(the_install_shell->reqDevInfo, the_install_shell->devInfoVec);
    if(reqSuccess)
    {
        for (const vehicle_interfaces::msg::DevInfo & i : the_install_shell->devInfoVec)
        {
            this->devInfoMsg_ = this->devInfoMsg_ + i.hostname + "／" + i.mac_addr + "／" + i.ipv4_addr + "／" + i.node_name + "\n";
        }
    }
}
void MainWindow::refresh_topic_name_list(){


        // ui->textBrowser->clear();
        this->topic="";
        auto topic_name_list = name_node->get_topic_names_and_types();
        for(const auto& i :topic_name_list){
            this->topic=this->topic +QString::fromStdString(i.first.c_str());
            this->topic=this->topic +"\n";

        }
        ui->textBrowser->setText(this->topic);

}
void MainWindow::on_QosPushButton_clicked(){
    qosdevicedialog->show();
}
void MainWindow::on_SensorPushButton_clicked(){
    the_sensor_form= new sensor_form;
    the_sensor_form->show();
}
void MainWindow::on_data_server_record_puchButton_clicked(){
    the_data_server_record->show();
    the_new_dataserver ->show();

}
void MainWindow::on_install_shell_PushButton_clicked(){
    the_install_shell->show();
}
void MainWindow::on_image_display_PushButton_clicked(){
    image_id++;
    Image_form *the_image_form = new Image_form(nullptr,image_id);
    the_image_form->show();
}
void MainWindow:: on_safety_PushButton_clicked(){
    the_safety = new safety;
    the_safety->show();
}

void MainWindow::on_control_server_PushButton_clicked()
{
    control_server *the_control_server = new control_server;
    the_control_server->show();
}