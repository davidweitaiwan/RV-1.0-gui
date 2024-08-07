#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qos_device_dialog/qosdevicedialog.h"
#include "sensor_form/sensor_form.h"
#include "install_shell/install_shell.h"
#include "data_server_record/data_server_record.h"
#include "image_display/image_form.h"
#include "safety/safety.h"
#include <rclcpp/rclcpp.hpp>

#include"control_server/control_server.h"

#include "data_server_new_recod/new_dataserver.h"
/** cocobird231*/
#include <string>

#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_QosPushButton_clicked();
    void on_SensorPushButton_clicked();
    void on_data_server_record_puchButton_clicked();
    void on_install_shell_PushButton_clicked();
    void on_image_display_PushButton_clicked();
    void on_safety_PushButton_clicked();
    void on_control_server_PushButton_clicked();

private:
    Ui::MainWindow *ui;
    QosDeviceDialog *qosdevicedialog = new QosDeviceDialog;
    sensor_form *the_sensor_form ;
    install_shell *the_install_shell = new install_shell;
    data_server_record *the_data_server_record =new data_server_record;
    safety *the_safety ;

    new_dataserver *the_new_dataserver = new new_dataserver;

    std::shared_ptr<rclcpp::Node> name_node;
    QTimer timmer,device_timer;
    void refresh_device_info();
    QString device_info_message;
    QString topic;
    void refresh_topic_name_list();
    int image_id=0;
    /** cocobird231*/
    std::thread *devInfoThPtr_;
    std::string devInfoMsg_;
    void _refresh_device_info_th();
};
#endif // MAINWINDOW_H
