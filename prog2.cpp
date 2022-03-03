#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;


int main()
{
    int sock, listener;
    struct sockaddr_in addr;
    char buf[1024];
    int bytes_read;

    listener = socket(AF_INET, SOCK_STREAM, 0);

    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }

    listen(listener, 1);
    
    while(1)
    {
        sock = accept(listener, NULL, NULL);
        if(sock < 0)
        {
            perror("accept");
            exit(3);
        }

        while(1)
        {
            bytes_read = recv(sock, buf, 1024, 0);
            if(bytes_read <= 0) break;
std::string s= "Error";
//if (bytes_read > 2 && (bytes_read % 32) == 0) s = "True"; else s = "Error";
for (auto i = 0; i < s.length(); i++) buf[i] = s[i];
std::cout <<  "prog2:  " << buf << " \n";
            send(sock, buf, sizeof(buf), 0);
        }
    
        close(sock);
    }
    
    return 0;
}

