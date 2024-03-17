#include "provider_system/ProviderSystemNode.hpp"

int main(int argc, char const *argv[])
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<ProviderSystemNode>();

    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
