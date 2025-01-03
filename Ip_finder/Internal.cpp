#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include <regex>
#include <sstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

class CurlGlobalSetup {
public:
    CurlGlobalSetup() {
        curl_global_init(CURL_GLOBAL_DEFAULT);
    }
    ~CurlGlobalSetup() {
        curl_global_cleanup();
    }
};

//Parseing Json
std::string safeGetString(const json& j, const std::string& key) {
    if (j.contains(key) && !j[key].is_null()) {
        return j[key].get<std::string>();
    }
    return "N/A";
}

struct Location_info{
    std::string city;
    std::string region;
    std::string country;
    std::string location;
    std::string org;
    std::string postal;
};

//Parsing
Location_info parseJsonResponse(const std::string& jsonStr) {
    Location_info info;
    try {
        json j = json::parse(jsonStr);
        info.city = safeGetString(j, "city");
        info.region = safeGetString(j, "region");
        info.country = safeGetString(j, "country");
        info.location = safeGetString(j, "loc");
        info.org = safeGetString(j, "org");
        info.postal = safeGetString(j, "postal");

    } catch (const json::exception& e) {
        info.city = "Error";
        info.region = "Error";
        info.country = "Error";
        info.location = "Error";
        info.org = "Error";
        info.postal = "Error";
    }
    return info;
};


std::string fetchData(const std::string& ip) {
    std::string response;
    CURL* curl = curl_easy_init();

    if (curl) {
        std::string api_url = "https://ipinfo.io/" + ip + "/json";

        curl_easy_setopt(curl, CURLOPT_URL, api_url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Curl error: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    return response;
}

//Extraction
std::string extractIP(const std::string& line) {
    std::regex ip_pattern(R"(from\s+(\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}))");
    std::smatch match;
    if (std::regex_search(line, match, ip_pattern)) {
        return match[1];
    }
    return "";
}

int main() {
    CurlGlobalSetup curlSetup;
    std::ifstream read_file("server_log.txt");
    if (!read_file) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<std::string> ips;

    while (std::getline(read_file, line)) {
        std::string ip = extractIP(line);
        if (!ip.empty()) {
            ips.push_back(ip);
        }
    }
    read_file.close();

    for (const auto& ip : ips) {
        std::cout << "\nFetching data for IP: " << ip << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::string response = fetchData(ip);

        if (!response.empty()) {
            Location_info info = parseJsonResponse(response);
            std::cout << "Location Information:" << std::endl;
            std::cout << "City: " << info.city << std::endl;
            std::cout << "Region: " << info.region << std::endl;
            std::cout << "Country: " << info.country << std::endl;
            std::cout << "Coordinates: " << info.location << std::endl;
            std::cout << "Organization: " << info.org << std::endl;
            std::cout << "Postal Code: " << info.postal << std::endl;
        }
    }

    return 0;
}
