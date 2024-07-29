#include "control_server.h"
#include "./../../ui_control_server.h"
#include<QDebug>
#include<QString>
#include <chrono>
using namespace std::chrono_literals;



control_server::control_server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::control_server)
{
    ui->setupUi(this);
    tthis->setWindowTitle("Control Server");
    controlInfoNode = std::make_shared<ControllerInfoNode>("gui_controller_info_node", "/V0/controlserver_0_ControllerInfoReq");
    controlServerSettingNode = std::make_shared<ControlServerSettingNode>("gui_control_server_setting_node", "/V0/controlserver_0");
    connect(ui->pushButton, &QPushButton::clicked, this, &control_server::on_controllerInfo_pushButton_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &control_server::on_controlServerSetting_pushButton_clicked);
}
void control_server::on_controllerInfo_pushButton_clicked()
{

    vehicle_interfaces::srv::ControllerInfoReq::Request::SharedPtr req = std::make_shared<vehicle_interfaces::srv::ControllerInfoReq::Request>();
    req->service_name = "all";
    ui->textBrowser->setText(controlInfoNode->requestControllerInfoServer(req));

}

void control_server::on_controlServerSetting_pushButton_clicked()
{
    vehicle_interfaces::srv::ControlServer::Request::SharedPtr req = std::make_shared<vehicle_interfaces::srv::ControlServer::Request>();
    vehicle_interfaces::msg::ControlServerStatus controlServerStatus;
    controlServerStatus.controller_action = static_cast<uint8_t> (ui->comboBox_6->currentIndex());
    controlServerStatus.controller_service_name = ui->lineEdit_5->text().toStdString().c_str();
    controlServerStatus.server_action = static_cast<uint8_t> (ui->comboBox->currentIndex());
    controlServerStatus.server_output_timer_status = static_cast<uint8_t> (ui->comboBox_2->currentIndex());
    controlServerStatus.server_output_period_ms = ui->lineEdit->text().toDouble();
    controlServerStatus.server_safety_timer_status = static_cast<uint8_t> (ui->comboBox_3->currentIndex());
    controlServerStatus.server_safety_period_ms = ui->lineEdit_2->text().toDouble();
    controlServerStatus.server_idclient_timer_status = static_cast<uint8_t> (ui->comboBox_4->currentIndex());
    controlServerStatus.server_idclient_period_ms = ui->lineEdit_3->text().toDouble();
    controlServerStatus.server_publish_timer_status = static_cast<uint8_t> (ui->comboBox_5->currentIndex());
    controlServerStatus.server_publish_period_ms = ui->lineEdit_4->text().toDouble();
    controlServerStatus.chassis_action = 0;

    
    req->request = controlServerStatus;
    if(controlServerSettingNode->requestControlServerSetting(req))
    {
        qDebug() << "Control Server Setting Success";
        ui->textBrowser_2->setText("Control Server Setting Success");
    }
    else
    {
        qDebug() << "Control Server Setting Failed";
    }
}

control_server::~control_server()
{
    delete ui;
}

control_server::ControllerInfoNode::ControllerInfoNode(const std::string& nodeName, const std::string& controllerInfo_service_name)
    :rclcpp::Node(nodeName)
{

    this->InfoClientNode_ = std::make_shared<rclcpp::Node>(nodeName);
    this->InforeqClient_ = InfoClientNode_->create_client<vehicle_interfaces::srv::ControllerInfoReq>(controllerInfo_service_name);

}
control_server::ControlServerSettingNode::ControlServerSettingNode(const std::string& nodeName, const std::string& controlServeSetting_service_name)
    :rclcpp::Node(nodeName)
{

    this->ControlServerSettingClientNode_ = std::make_shared<rclcpp::Node>(nodeName);
    this->ControlServerSettingreqClient_ = ControlServerSettingClientNode_->create_client<vehicle_interfaces::srv::ControlServer>(controlServeSetting_service_name);

}
bool control_server::ControlServerSettingNode::requestControlServerSetting( vehicle_interfaces::srv::ControlServer::Request::SharedPtr req)
{
    auto request = std::make_shared<vehicle_interfaces::srv::ControlServer::Request>();
    vehicle_interfaces::msg::ControlServerStatus controlServerRequstStatus;
    request =req;
    auto result = ControlServerSettingreqClient_->async_send_request(request);

        #if ROS_DISTRO == 0
        if (rclcpp::spin_until_future_complete(ControlServerSettingClientNode_, result, 1000ms) == rclcpp::executor::FutureReturnCode::SUCCESS)
#else
        if (rclcpp::spin_until_future_complete(ControlServerSettingClientNode_, result, 1000ms) == rclcpp::FutureReturnCode::SUCCESS)
#endif  
    {
        auto response = result.get();
        controlServerRequstStatus = response->status;
        return true;
    }
    else
    {
        RCLCPP_ERROR(this->get_logger(), "Failed to get response");
        return false;
    }
}





QString control_server::ControllerInfoNode::requestControllerInfoServer( vehicle_interfaces::srv::ControllerInfoReq::Request::SharedPtr req)
{
    auto request = std::make_shared<vehicle_interfaces::srv::ControllerInfoReq::Request>();
    request->service_name = req->service_name;
    qDebug() << "request->service_name: " << QString::fromStdString(request->service_name);
    auto result = InforeqClient_->async_send_request(request);

        #if ROS_DISTRO == 0
        if (rclcpp::spin_until_future_complete(InfoClientNode_, result, 1000ms) == rclcpp::executor::FutureReturnCode::SUCCESS)
#else
        if (rclcpp::spin_until_future_complete(InfoClientNode_, result, 1000ms) == rclcpp::FutureReturnCode::SUCCESS)
#endif
    {
        auto response = result.get();
        // for loop from vector
        QString text_browser_content;

        for (int i = 0; i < response->control_info_vec.size(); i++)
        {
            vehicle_interfaces::msg::ControllerInfo control_info = response->control_info_vec[i];
            text_browser_content += "========================================\n";
            text_browser_content += "msg_type: " + QString::number(control_info.msg_type) + "\n";
            text_browser_content += "controller_mode: " + QString::number(control_info.controller_mode) + "\n";
            text_browser_content += "node_name: " + QString::fromStdString(control_info.node_name) + "\n";
            text_browser_content += "service_name: " + QString::fromStdString(control_info.service_name) + "\n";
            text_browser_content += "timeout_ms: " + QString::number(control_info.timeout_ms) + "\n";
            text_browser_content += "period_ms: " + QString::number(control_info.period_ms) + "\n";
            text_browser_content += "privilege: " + QString::number(control_info.privilege) + "\n";
            text_browser_content += "pub_type: " + QString::number(control_info.pub_type) + "\n";

        }
        return text_browser_content;
    }
    else
    {
        RCLCPP_ERROR(this->get_logger(), "Failed to get response");
        return "Failed to get response";
    }
}