#include "Identidad.h"
#include <iostream>
#include <fstream>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <ctime>

using namespace std;

string getMAC(const string& iface) {
    string path = "/sys/class/net/" + iface + "/address";
    ifstream file(path);
    string mac;

    if (file.is_open()) {
        getline(file, mac);
        file.close();
    }

    return mac;
}

string getIP(const string& iface) {

    struct ifaddrs *ifaddr, *ifa;
    string ip = "";

    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
        return "";
    }

    for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {

        if (ifa->ifa_addr == nullptr)
            continue;

        if (ifa->ifa_addr->sa_family == AF_INET &&
            iface == ifa->ifa_name) {

            char host[NI_MAXHOST];
            struct sockaddr_in *sa = (struct sockaddr_in *)ifa->ifa_addr;

            inet_ntop(AF_INET, &sa->sin_addr, host, NI_MAXHOST);
            ip = host;
        }
    }

    freeifaddrs(ifaddr);
    return ip;
}

string getTimestamp() {
    time_t now = time(0);
    char* dt = ctime(&now);
    return string(dt);
}

void logEvent(const string& msg) {

    ofstream log("network_identity_monitor.log", ios::app);
    log << getTimestamp() << " - " << msg << endl;
    log.close();
}

void iniciarIdentidad() {

    string iface;

    cout << "Ingrese la interfaz a monitorear: ";
    cin >> iface;

    string lastMAC = getMAC(iface);
    string lastIP = getIP(iface);

    cout << "Monitoreando interfaz: " << iface << endl;
    cout << "MAC inicial: " << lastMAC << endl;
    cout << "IP inicial: " << lastIP << endl;

    logEvent("Inicio de monitoreo - IP: " + lastIP + " MAC: " + lastMAC);

    while (true) {

        string currentMAC = getMAC(iface);
        string currentIP = getIP(iface);

        if (currentMAC != lastMAC) {
            logEvent("Cambio de MAC detectado: " + lastMAC + " -> " + currentMAC);
            cout << "Cambio de MAC detectado" << endl;
            lastMAC = currentMAC;
        }

        if (currentIP != lastIP) {
            logEvent("Cambio de IP detectado: " + lastIP + " -> " + currentIP);
            cout << "Cambio de IP detectado" << endl;
            lastIP = currentIP;
        }

        sleep(5);
    }
}