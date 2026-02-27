//*****************************************************************************
// Copyright(c) Trenser Tehnology solutions(P) Ltd
// All Rights are reserved
//*****************************************************************************
// File     :   client.c
// Note     :   Establish client conection
// Author   :   Arunya   
// Date     :   26-02-2027  

//*****************************************************************************
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "client.h"
#include "udp.h"
#include <unistd.h>

//************************* Include Files**************************************

//************************* Local Types ***************************************

//************************* Local Constants ***********************************
#define IP_ADDRESS      "127.0.0.1"
#define PORT_ADDRESS    (9090)
#define MAX_SIZE        (512)
#define MENU_SIZE       (2)
#define CHOICE_BUFF     (3)

//************************* Local Functions ***********************************
static void ClientConnection(void);

//************************* Local Variable ************************************
const _MENU stMenu[]=
{
    {
        .cIndex = '1',
        .cMenuName = "TCP server-Client",
        .pvMenuOperation = ClientConnection
    },
    {
        .cIndex = '2',
        .cMenuName = "UDP Sender-Receiver",
        .pvMenuOperation = UdpClientConnection
    },
};

//*****************************************************************************
//Purpose   : Establish client communication
//Input     : None
//Output    : None   
//Return    : None
//Note      : None
//*****************************************************************************
static void ClientConnection(void)
{
    int32_t lClientSock = 0;
    int32_t lConnectionStatus = 0;
    int8_t cBuffer[MAX_SIZE] = {0};
    
    struct sockaddr_in stClientAddr = {0};

    lClientSock = socket(AF_INET, SOCK_STREAM, 0);
    if(lClientSock < 0)
    {
        printf("socket connection error\n");
        return;
    }

    printf("socket connection established successfully..\n");
    stClientAddr.sin_family = AF_INET;
    stClientAddr.sin_port = PORT_ADDRESS;
    stClientAddr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    lConnectionStatus = connect(lClientSock,
                                 (const struct sockaddr *)&stClientAddr, 
                                 sizeof(stClientAddr));

    if(lConnectionStatus < 0)
    {
        perror(" connection error!");
        return;
    }

    printf("Connected to serever\n");
    memset(cBuffer, 0, MAX_SIZE);
    snprintf((char *)cBuffer, MAX_SIZE, "Hi i am client");
    send(lClientSock, cBuffer, MAX_SIZE, 0);
    close(lClientSock);

}

//*****************************************************************************
//Purpose   : calling TCP/UDP menu
//Input     : None
//Output    : None   
//Return    : None
//Note      : None
//*****************************************************************************
void ClientMenu(void)
{
    uint8_t ucIndex = 0;
    int32_t lChoice = 0;
    char cChoiceBuffer[CHOICE_BUFF] = {0};

    for(ucIndex = 0; ucIndex < MENU_SIZE; ucIndex++)
    {
        printf("%d.%s",stMenu->cIndex, stMenu->cMenuName);
    }
    sscanf(cChoiceBuffer, "%d", &lChoice);
    stMenu[lChoice].pvMenuOperation();
}
