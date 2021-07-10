#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "logic.h"

#define IDENedit 3
#define IDENgen 4
#define IDENqbut 5
#define primlen 8

char str[9], real[5];
char myexp;
HWND primer;
HWND input;
HWND info;
HWND gen;
HWND qbut;

LRESULT Mydef(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam){
    if(message == WM_DESTROY)
        exit(0);
    else if(message == WM_COMMAND){
        if((HWND)lparam == gen){
            if(check(myexp, real)){
                SetWindowText(info, "Correct answer.");
                printf("OK!\n");
            } else
                SetWindowText(info, "Incorrect answer.");
            myexp = generate(str);
            printf("%s\n", str);
            SetWindowText(primer, str);
        } else
        if((HWND)lparam == qbut)
            exit(0);
        else
        if(LOWORD(wparam) == IDENedit){
            GetWindowText((HWND)lparam, real, 5);
        }
    } else
    return DefWindowProcA(hwnd, message, wparam, lparam);
}

int main(int argc, char *argv[]){
    srand(time(NULL));
    WNDCLASSA wcl;
        memset(&wcl, 0, sizeof(WNDCLASSA));
        wcl.lpszClassName = "win1";
        wcl.lpfnWndProc = Mydef;
    RegisterClassA(&wcl);

    HWND hwnd;
    hwnd = CreateWindow("win1", "Multiplication-table", 
    WS_OVERLAPPEDWINDOW, 50, 50, 600, 430, NULL, NULL, 
    NULL, NULL);

    primer = CreateWindow("edit", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_RIGHT | ES_NUMBER | ES_READONLY, 
    148, 146, 235, 20, hwnd, NULL, NULL, NULL);
    
    input = CreateWindow("edit", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_RIGHT | ES_NUMBER, 
    394, 146, 35, 20, hwnd, (HMENU)IDENedit, NULL, NULL);

    gen = CreateWindow("button", "Continue", WS_VISIBLE | WS_CHILD, 
    148, 215, 100, 50, hwnd, (HMENU)IDENgen, NULL, NULL);

    qbut = CreateWindow("button", "Quiet", WS_VISIBLE | WS_CHILD, 
    330, 215, 100, 50, hwnd, (HMENU)IDENqbut, NULL, NULL);

    info = CreateWindow("edit", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_RIGHT | ES_NUMBER | ES_READONLY, 
    148, 176, 280, 20, hwnd, NULL, NULL, NULL);
    //ShowWindow(GetConsoleWindow(), SW_HIDE);

    MSG msg;

    ShowWindow(hwnd, SW_NORMAL);

    myexp = generate(str);
    printf("%s\n", str);
    SetWindowText(primer, str);

    while(GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        
    }
    return 0;
}