#include "provider_system/ProviderSystemNode.hpp"
#include <chrono>

using namespace std::chrono_literals;

ProviderSystemNode::ProviderSystemNode() : Node("provider_system_node")
{
    _temp_pub = this->create_publisher<sensor_msgs::msg::Temperature>("/provider_system/temperature", 10);
    _get_temp_timer = this->create_wall_timer(5s, std::bind(&ProviderSystemNode::checkTemp, this));
}

void ProviderSystemNode::checkTemp()
{
    std::string cmdResult = executeCmd(_cpuTempCmd);
    float cpuTemp = std::stof(cmdResult);
    sensor_msgs::msg::Temperature temperature;
    temperature.header.stamp = this->get_clock()->now();
    temperature.temperature = cpuTemp;
    temperature.variance = 0;

    _temp_pub->publish(temperature);
}

std::string ProviderSystemNode::executeCmd(const std::string cmd)
{
    std::array<char, _PIPE_BUFFER> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd.data(), "r"), pclose);
    if (!pipe)
    {
        std::runtime_error("Wrror while executing command");
    }
    while (!feof(pipe.get()))
    {
        if (fgets(buffer.data(), _PIPE_BUFFER, pipe.get()) != NULL)
        {
            result += buffer.data();
        }
    }
    return result;
}