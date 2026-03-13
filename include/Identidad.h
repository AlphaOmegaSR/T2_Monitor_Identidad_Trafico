#pragma once

std::string getMAC(const std::string& iface);
std::string getIP(const std::string& iface);
std::string getTimestamp();
void logEvent(const std::string& msg);

void iniciarIdentidad();