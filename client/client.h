//***************************** Data Handler **********************************
// Copyright(c) 2026 Trenser Technology solutions(P) Ltd
// Allrights are reserved
//*****************************************************************************
// Summary  : This function establish a clinet connection to the server
// Note     : None
//*****************************************************************************
#ifndef CLIENT_TCP
#define CLIENT_TCP

//************************** Include File**************************************
#include <stdint.h>
#include <stdio.h>

//************************** Global types**************************************

//************************** Global constants *********************************

//************************** Global variable **********************************
typedef void (*pvMenuHandler)(void);
typedef struct _MENU
{
    int8_t cMenuName[24];
    int8_t cIndex;
    pvMenuHandler pvMenuOperation; 
}_MENU;
//************************** Forward declartion *******************************
void ClientMenu(void);

//************************** Inline function implementation *******************


#endif
//EOF