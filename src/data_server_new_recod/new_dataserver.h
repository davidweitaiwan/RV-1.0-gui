#ifndef NEW_DATASERVER_H
#define NEW_DATASERVER_H

#include <QWidget>
#include <rclcpp/rclcpp.hpp>

#include "vehicle_interfaces/msg/data_server_status.hpp"
#include "vehicle_interfaces/srv/data_server.hpp"
namespace Ui {
class new_dataserver;
}

class new_dataserver : public QWidget
{
    Q_OBJECT

public:
    explicit new_dataserver(QWidget *parent = nullptr);
    ~new_dataserver();
    class DataServerControlNode : public rclcpp::Node{
        private:
            std::shared_ptr<rclcpp::Node> ClientNode_;
            rclcpp::Client<vehicle_interfaces::srv::DataServer>::SharedPtr reqClient_;
            std::string data_server_service_name;

        public:
            DataServerControlNode(const std::string& nodeName, const std::string& data_server_service_name);
            bool requestDataServer(std::string serviceName, vehicle_interfaces::srv::DataServer::Request::SharedPtr req, vehicle_interfaces::msg::DataServerStatus& dst);
    };
    void on_click_requestDataServer();
private:
    Ui::new_dataserver *ui;
    std::shared_ptr<new_dataserver::DataServerControlNode> control;

};

#endif // NEW_DATASERVER_H
