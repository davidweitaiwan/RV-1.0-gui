#ifndef CONTROL_SERVER_H
#define CONTROL_SERVER_H

#include <QWidget>
#include <rclcpp/rclcpp.hpp>
#include "vehicle_interfaces/srv/controller_info_req.hpp"
#include "vehicle_interfaces/msg/controller_info.hpp"
#include "vehicle_interfaces/srv/control_server.hpp"
#include "vehicle_interfaces/msg/control_server_status.hpp"
#include <QString>
namespace Ui {
class control_server;
}

class control_server : public QWidget
{
    Q_OBJECT

public:
    explicit control_server(QWidget *parent = nullptr);
    ~control_server();
    class ControllerInfoNode : public rclcpp::Node{
        private:
            std::shared_ptr<rclcpp::Node> InfoClientNode_;
            rclcpp::Client<vehicle_interfaces::srv::ControllerInfoReq>::SharedPtr InforeqClient_;
            std::string controllerInfo_service_name;

        public:
            ControllerInfoNode(const std::string& nodeName, const std::string& controllerInfo_service_name);
            QString requestControllerInfoServer( vehicle_interfaces::srv::ControllerInfoReq::Request::SharedPtr req);
    };
        class ControlServerSettingNode : public rclcpp::Node{
        private:
            std::shared_ptr<rclcpp::Node> ControlServerSettingClientNode_;
            rclcpp::Client<vehicle_interfaces::srv::ControlServer>::SharedPtr ControlServerSettingreqClient_;
            std::string controlServeSetting_service_name;

        public:
            ControlServerSettingNode(const std::string& nodeName, const std::string& controlServeSetting_service_name);
            bool requestControlServerSetting( vehicle_interfaces::srv::ControlServer::Request::SharedPtr req);
    };

private:
    Ui::control_server *ui;
    std::shared_ptr<control_server::ControllerInfoNode> controlInfoNode;
    std::shared_ptr<control_server::ControlServerSettingNode> controlServerSettingNode;
    void on_controllerInfo_pushButton_clicked();
    void on_controlServerSetting_pushButton_clicked();
};

#endif // CONTROL_SERVER_H
