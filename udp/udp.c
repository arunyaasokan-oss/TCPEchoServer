//*****************************************************************************
// Copyright(c) 2026 Trenser Tehnology solutions(P) Ltd
// All rights are reserved
//*****************************************************************************
// File     :   udp.c
// Note     :   Establish UDP server conection
// Author   :   Arunya   
// Date     :   26-02-2027  

//*****************************************************************************
//************************* Include Files**************************************
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

//************************* Local types ***************************************

//************************* Local constants ***********************************
#define IP_ADDRESS  ("127.0.0.1")
#define PORT_NUM    (9090)
#define MAXSIZE     (100)

//************************* Local variables ***********************************

//************************* Local Function ************************************

//*****************************************************************************
//Purpose   : establish UDP server connection
//Input     : none
//Output    : none
//Result    : none
//Note      : none
//*****************************************************************************
void UdpClientConnection(void)
{
    int32_t lClientSocketFd = 0;
    struct sockaddr_in stServerSockAddr = {0};
    uint8_t ucBuffer[MAXSIZE] = {0};

    lClientSocketFd = socket(AF_INET, SOCK_DGRAM, 0);
    if(lClientSocketFd < 0)
    {
        perror("Socket creation failed\n");
        return;
    }
    printf("Socket created successfully\n");

    stServerSockAddr.sin_family = AF_INET;
    stServerSockAddr.sin_port = PORT_NUM;
    stServerSockAddr.sin_addr.s_addr =  inet_addr(IP_ADDRESS);

    memset(ucBuffer, 0, MAXSIZE);
    strcpy(ucBuffer, "Hi UDP, I am client\n");
    sendto(lClientSocketFd, ucBuffer, strlen(ucBuffer), 0,
     (const struct sockaddr *)&stServerSockAddr,
      sizeof(stServerSockAddr));

    close(lClientSocketFd);
}