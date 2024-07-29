
#include <QDebug>
#include "vehicle_interfaces/params.h"
#include "new_dataserver.h"
#include "./../../ui_new_dataserver.h"
// chrono
#include <chrono>

using namespace std::chrono_literals;


new_dataserver::new_dataserver(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::new_dataserver)
{
    ui->setupUi(this);
    this->setWindowTitle("Data Server 3 Record");
    control = std::make_shared<DataServerControlNode>("gui_new_data_server_0_node", "/V0/dataserver_0");
    connect(ui->pushButton, &QPushButton::clicked, this, &new_dataserver::on_click_requestDataServer);
}

new_dataserver::~new_dataserver()
{
    delete ui;
}
void new_dataserver::on_click_requestDataServer()
{
    vehicle_interfaces::srv::DataServer::Request::SharedPtr req = std::make_shared<vehicle_interfaces::srv::DataServer::Request>();

    // switch server action case
    uint8_t server_action = 0;
     if(ui->comboBox->currentText() == "SERVER_ACTION_STOP")
    {
        server_action = 1;
    }
    else if(ui->comboBox->currentText() == "SERVER_ACTION_START")
    {
        server_action = 2;
    }
    else if(ui->comboBox->currentText() == "SERVER_ACTION_SET_TIMER")
    {
        server_action = 4;
    }else if(ui->comboBox->currentText() == "SERVER_ACTION_SET_PERIOD")
    {
        server_action = 8;
    }
    else
    {
        server_action = 0;
    }
    uint8_t server_scan_timer_status = 0;
    if(ui->comboBox_5->currentText() == "TIMER_STATUS_STOP")
    {
        server_scan_timer_status = 1;
    }
    else if(ui->comboBox_5->currentText() == "TIMER_STATUS_START")
    {
        server_scan_timer_status = 2;
    }
    else
    {
        server_scan_timer_status = 0;
    }

    uint8_t server_sample_timer_status = 0;
    if(ui->comboBox_4->currentText() == "TIMER_STATUS_STOP")
    {
        server_sample_timer_status = 1;
    }
    else if(ui->comboBox_4->currentText() == "TIMER_STATUS_START")
    {
        server_sample_timer_status = 2;
    }
    else
    {
        server_sample_timer_status = 0;
    }

    uint8_t server_dump_timer_status = 0;
    if(ui->comboBox_3->currentText() == "TIMER_STATUS_STOP")
    {
        server_dump_timer_status = 1;
    }
    else if(ui->comboBox_3->currentText() == "TIMER_STATUS_START")
    {
        server_dump_timer_status = 2;
    }
    else
    {
        server_dump_timer_status = 0;
    }

    uint8_t server_countdown_timer_status = 0;
    if(ui->comboBox_2->currentText() == "TIMER_STATUS_STOP")
    {
        server_countdown_timer_status = 1;
    }
    else if(ui->comboBox_2->currentText() == "TIMER_STATUS_START")
    {
        server_countdown_timer_status = 2;
    }
    else
    {
        server_countdown_timer_status = 0;
    }
    // data server status
    vehicle_interfaces::msg::DataServerStatus data_server_status;
    data_server_status.server_action = server_action;
    data_server_status.server_scan_timer_status = server_scan_timer_status;
    data_server_status.server_scan_period_ms = ui->lineEdit_2->text().toDouble();
    data_server_status.server_sample_timer_status = server_sample_timer_status;
    data_server_status.server_sample_period_ms = ui->lineEdit_6->text().toDouble();
    data_server_status.server_dump_timer_status = server_dump_timer_status;
    data_server_status.server_dump_period_ms = ui->lineEdit_8->text().toDouble();
    data_server_status.server_countdown_timer_status = server_countdown_timer_status;
    data_server_status.server_countdown_period_ms = ui->lineEdit_10->text().toDouble();

    req->request = data_server_status;



    vehicle_interfaces::msg::DataServerStatus dst;
    if(this->control->requestDataServer("/V0/dataserver_0", req, dst))
    {
        ui->textBrowser->setText("Server response: " + QString::number(dst.server_action));
    }
    else
    {
        ui->textBrowser->setText("Failed to get response from server");
    }
}


new_dataserver::DataServerControlNode::DataServerControlNode(const std::string& nodeName, const std::string& data_service_name): rclcpp::Node(nodeName)
{
    this->data_server_service_name = data_service_name;
    this->ClientNode_ = rclcpp::Node::make_shared(nodeName + "_dataserver_client");
    this->reqClient_ = ClientNode_->create_client<vehicle_interfaces::srv::DataServer>(data_server_service_name);
}

bool new_dataserver::DataServerControlNode::requestDataServer(std::string serviceName, vehicle_interfaces::srv::DataServer::Request::SharedPtr req, vehicle_interfaces::msg::DataServerStatus& dst)
{
    auto request = std::make_shared<vehicle_interfaces::srv::DataServer::Request>();
    auto result = this->reqClient_->async_send_request(request);

    #if ROS_DISTRO == 0
        if (rclcpp::spin_until_future_complete(this->ClientNode_, result, 1000ms) == rclcpp::executor::FutureReturnCode::SUCCESS)
#else
        if (rclcpp::spin_until_future_complete(this->ClientNode_, result, 1000ms) == rclcpp::FutureReturnCode::SUCCESS)
#endif
    {
        dst = result.get()->status;
        
        return true;
    }
    else
    {
        qDebug() << "Failed to get response from server";
        return false;
    }
}
