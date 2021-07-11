#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "logic.h"

#define IDENedit 3
#define IDENgen 4
#define IDENqbut 5

#define HELPpress 6

#define primlen 8

HMENU hMenu;

int primcount = 0;
int correctanswers = 0;
int procent;
char outputstr[255] = "You solve correctly ";
char buffer[255];
char str[9], real[5];
char myexp;
HWND primer;
HWND input;
HWND info;
HWND gen;
HWND qbut;

LRESULT Mydef(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam){
    if(message == WM_DESTROY) //If exit button pressed
        exit(0);

    else if(message == WM_COMMAND){
        if(wparam == HELPpress) //If it is Help button in menu
            MessageBox(NULL, "Documentation can be found on\nhttps://github.com/Nikita-bunikido/Multiplication_table.git.\n                          -Nikita Donskov 2021", "Help", MB_ICONINFORMATION);
        else
        if((HWND)lparam == gen){ //If it is continue button
            if(check(myexp, real)){ //If correct answer
                SetWindowText(info, "Correct answer."); //Information
                printf("OK!\n");
                correctanswers++; //Increment correct answers
            } else
                SetWindowText(info, "Incorrect answer.");

            myexp = generate(str); //Expexted answer and prim generate
            printf("%s\n", str);
            SetWindowText(primer, str);  //Exercise set
            SetWindowText(input, "");    //Null in the input
            primcount++;
        } else
        if((HWND)lparam == qbut){ //If it is end of test button
            if(primcount == 0)
                 MessageBox(NULL, "You can see your result if you solve more than zero exercices.", "Error", MB_ICONERROR);
            else{
            printf("%d - Primers\n%d - Correct.", primcount, correctanswers);
            procent = (correctanswers * 100 / primcount); //Calculating percents
            printf("\nCorrect - %d%%", procent);
            
            itoa(procent, buffer, 10); //Percent to str
            strcat(outputstr, buffer); 
            strcat(outputstr, "% of exercises.");

            MessageBox(NULL, outputstr, "Results", MB_ICONINFORMATION);
            
            correctanswers = 0; //Restart
            primcount = 0;

            myexp = generate(str);
            printf("%s\n", str);
            SetWindowText(primer, str);

            strcpy(outputstr, "You solve correctly ");
            }
        }
        else
        if(LOWORD(wparam) == IDENedit){
            GetWindowText((HWND)lparam, real, 5); //Input text to string
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

    qbut = CreateWindow("button", "End", WS_VISIBLE | WS_CHILD, 
    330, 215, 100, 50, hwnd, (HMENU)IDENqbut, NULL, NULL);

    info = CreateWindow("edit", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_RIGHT | ES_NUMBER | ES_READONLY, 
    148, 176, 280, 20, hwnd, NULL, NULL, NULL);
    //ShowWindow(GetConsoleWindow(), SW_HIDE);

    hMenu = CreateMenu();
    HMENU hThemeMenu = CreateMenu();
    HMENU hResultsMenu = CreateMenu();

    AppendMenu(hThemeMenu, MF_STRING, NULL, "Light");
    AppendMenu(hThemeMenu, MF_STRING, NULL, "Dark");

    AppendMenu(hResultsMenu, MF_STRING, NULL, "Save");
    AppendMenu(hResultsMenu, MF_STRING, NULL, "Open");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hResultsMenu, "Results");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hThemeMenu, "Theme");
    SetMenu(hwnd, hMenu);
    AppendMenu(hMenu, MF_STRING, HELPpress, "Help");


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