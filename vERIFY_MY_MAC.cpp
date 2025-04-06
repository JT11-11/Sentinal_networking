//
// Created by jaspe
//
#include <iostream>
#include <regex>
#include <string>

bool isValidMAC(const std::string& mac) {
    std::regex macRegex(R"(^([0-9A-Fa-f]{2}([-:]))([0-9A-Fa-f]{2}\2){4}[0-9A-Fa-f]{2}$)");
    return std::regex_match(mac, macRegex);
}

int main() {
    std::string macAddress;
    std::cout << "Enter a MAC address: ";
    std::getline(std::cin, macAddress);
    macAddress.erase(0, macAddress.find_first_not_of(" \t"));
    macAddress.erase(macAddress.find_last_not_of(" \t") + 1);

    if (isValidMAC(macAddress)) {
        std::cout << "Valid MAC address." << std::endl;
    } else {
        std::cout << "Invalid MAC address." << std::endl;
    }

    return 0;
}
