
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <regex>

//Format the IP address
std::vector<int>splitIP(const std::string& ip) {
  std::vector<int> result;
  std::stringstream ss(ip);
  std::string item;
  while (std::getline(ss,item,'.')) {
    result.push_back(std::stoi(item));
  }
  return result;
}

//Checking for validity of IP
bool isValidIP(const std::string& ip){
  std::regex ipPattern("^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
  if (std::regex_match(ip,ipPattern)) {
    std::cout << "Valid IP address" << std::endl;
    return true;
  }else {
    std::cout << "Invalid IP address" << std::endl;
    return false;
  }
}

bool isLocalHost(const std::string& ip) {
  if (ip=="127.0.0.1") {
    std::cout << "IP Address is a local IP address" << std::endl;
    return true;
  }else {
    return false;
  }
}

bool isPublicAddress(const std::vector<int>& ipParts) {
  if ((ipParts[0]==10)||((ipParts[0]==192)&&(ipParts[1]==168))||((ipParts[0]==172)&&(ipParts[1]>=16 || ipParts[1]<=31))) {
    return true;
  }else {
    return false;
  }
}

int main() {
  int no_of_times;
  std::cin >> no_of_times;
  for (int i=0;i<no_of_times;i++) {
    std::string ip;
    std::cin >> ip;
    if (!isValidIP(ip)) {
      std::cout << "Invalid IP address" << std::endl;
      return -1;
    }

    if (isLocalHost(ip)) {
      std::cout << "Local IP address is a local IP address" << std::endl;
      return 1;
    }else {
      std::vector<int> ipParts = splitIP(ip);
      if (isPublicAddress(ipParts)) {
        std::cout << "IP address is a public IP address" << std::endl;
        return 1;
      }else {
        std::cout << "IP address is private IP address" << std::endl;
        return 1;
      }
    }
  }
  return 0;
}