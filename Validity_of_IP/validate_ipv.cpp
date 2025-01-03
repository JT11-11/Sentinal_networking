#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <sstream>

void validate_ipv(std::string& ip) {
  std::string temp;
  std::vector<std::string>indiv_dot_result;
  std::istringstream iss(ip);
  std::string temp_part;

  if (indiv_dot_result.size() != 4) {
    std::cout << "This is not a valid IP address." << std::endl;
    return;
  }

  //check if all are integers
  temp.erase(std::remove(ip.begin(), ip.end(), '.'), ip.end());
  for(int i = 0; i < temp.size(); i++){
    if(!isdigit(temp[i])){
      std::cout<<"This is not a valid IP address."<<std::endl;
      return;
    }

  }

  //checking for all are between 0 to 255
  while(std::getline(iss,temp_part,'.')){
    indiv_dot_result.push_back(temp_part);
  }

  for(int z=0;z<indiv_dot_result.size();z++) {
    int part = std::stoi(indiv_dot_result[z]);
    if (part<0||part>255){
      std::cout<<"This is not a valid IP address."<<std::endl;
      return;
    }

    if (indiv_dot_result[z].size() > 1 && indiv_dot_result[z][0] == '0'){
      std::cout<<"This is not a valid IP address."<<std::endl;
      return;
    }
  }
  std::cout<<"This is a valid IP address."<<std::endl;

}

int main(){
  std::string ip;
  std::cin>>ip;
  validate_ipv(ip);
  return 0;
}