// FINDER.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib> // for system()
#include <string>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib") // link winsock library

void showSplash() {
    std::cout << R"(
███████╗██╗███╗   ██╗██████╗ ███████╗██████╗ 
██╔════╝██║████╗  ██║██╔══██╗██╔════╝██╔══██╗
███████╗██║██╔██╗ ██║██║  ██║█████╗  ██████╔╝
╚════██║██║██║╚██╗██║██║  ██║██╔══╝  ██╔═══╝ 
███████║██║██║ ╚████║██████╔╝███████╗██║     
╚══════╝╚═╝╚═╝  ╚═══╝╚═════╝ ╚══════╝╚═╝     

        SINDEP OSINT Tool v1.0
        https://github.com/Ghostie-ctrl-z/SINDEP
)";
}


// Declares a funtion that takes a constant reference to a string( domain name)


void runWhoisDirect(const std::string& domain) {
    WSADATA wsa;

    SOCKET s;

    struct sockaddr_in server;
    char buffer[4096];
    int recv_size;



    std::cout << "[*] Running WHOIS lookup for: " << domain << "\n\n";

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "[!] Winsock initialization failed. \n";
        return;

    }

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {

        std::cerr << "[!] Could not create sockets .\n";
        WSACleanup();
        return;
    }

    server.sin_addr.s_addr = inet_addr("199.7.83.42"); // whois.verisign-grs.com
    server.sin_family = AF_INET;
    server.sin_port = htons(43);





}

// Declares a funtion that prints help menu; returns nothing 
void showHelp() {

	std::cout << "Finder OSINT Tool \n";
	std::cout << "Usage: \n";
	std::cout << "\t finder --domain <domain>  Run WHOIS lookup \n";
	std::cout << "\t finder --help \t\t\t\t\t Show this help message\n";


} 




int main(int argc, char* argv[])
{
    if (argc < 2) {
        showHelp();
        return 1;
    }

    std::string command = argv[1];

    if (command == "--domain") {
        if (argc < 3) {
            std::cerr << "[!] Please provide a domain name. \n";
            return 1;
        }
        runWhois(argv[2]); // Pass the domain name to the runWhois function
    }
    else if (command == "--help") {
        showHelp();
    }
    else {
        std::cerr << "[!] Unknown command: " << command << "\n";
        showHelp();
        return 1;
    }

    return 0;
}
