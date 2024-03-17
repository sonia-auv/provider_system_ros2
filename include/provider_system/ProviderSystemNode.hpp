#pragma once
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/temperature.hpp>
#include <string>

class ProviderSystemNode : public rclcpp::Node
{

public:
    ProviderSystemNode();
    ~ProviderSystemNode() {};

private:
    void checkTemp();

    std::string executeCmd(const std::string cmd);

    static const uint8_t _PIPE_BUFFER = 128;
    const std::string _cpuTempCmd = "echo \"scale=1;`cat /sys/class/thermal/thermal_zone0/temp`/1000\" | bc"; // TODO Ask Ewan what this command is.
    rclcpp::Publisher<sensor_msgs::msg::Temperature>::SharedPtr _temp_pub;
    rclcpp::TimerBase::SharedPtr _get_temp_timer;
};
