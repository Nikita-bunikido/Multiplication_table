#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "logic.h"

#define IDENedit 3
#define IDENgen 4
#define IDENqbut 5

#define HELPpress 6
#define DarkPress 7
#define LightPress 8
#define SavePress 9
#define OpenPress 10

#define primlen 8

#define w 600 
#define h 480

HMENU hMenu;

HDC dc;

int primcount;
int lastp = 0;
int correctanswers;
int procent = 0;
char outputstr[255] = "You solve correctly ";
char buffer[255];
char str[9], real[5];
char myexp;
HWND primer;
HWND input;
HWND info;
HWND gen;
HWND qbut;

void changetheme(int th, HDC dc){
    if(!th){
        ShowWindow(primer, SW_HIDE);
        ShowWindow(input, SW_HIDE);
        ShowWindow(info, SW_HIDE);
        ShowWindow(gen, SW_HIDE);
        ShowWindow(qbut, SW_HIDE);

        SelectObject(dc, GetStockObject(DC_BRUSH));
        SetDCBrushColor(dc, RGB(50, 50, 50));
        SelectObject(dc, GetStockObject(DC_PEN));
        SetDCPenColor(dc, RGB(50, 50, 50));
        Rectangle(dc, 0, 0, w, h);

        ShowWindow(primer, SW_SHOW);
        ShowWindow(input, SW_SHOW);
        ShowWindow(info, SW_SHOW);
        ShowWindow(gen, SW_SHOW);
        ShowWindow(qbut, SW_SHOW);
    } else {
        ShowWindow(primer, SW_HIDE);
        ShowWindow(input, SW_HIDE);
        ShowWindow(info, SW_HIDE);
        ShowWindow(gen, SW_HIDE);
        ShowWindow(qbut, SW_HIDE);

        SelectObject(dc, GetStockObject(DC_BRUSH));
        SetDCBrushColor(dc, RGB(255, 255, 255));
        SelectObject(dc, GetStockObject(DC_PEN));
        SetDCPenColor(dc, RGB(255, 255, 255));
        Rectangle(dc, 0, 0, w, h);

        ShowWindow(primer, SW_SHOW);
        ShowWindow(input, SW_SHOW);
        ShowWindow(info, SW_SHOW);
        ShowWindow(gen, SW_SHOW);
        ShowWindow(qbut, SW_SHOW);
    }
}

LRESULT Mydef(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam){
    if(message == WM_DESTROY) //If exit button pressed
        exit(0);

    else if(message == WM_COMMAND){
        if(wparam == HELPpress) //If it is Help button in menu
            MessageBox(NULL, "Documentation can be found on\nhttps://github.com/Nikita-bunikido/Multiplication_table.git.\n                          -Nikita Donskov 2021", "Help", MB_ICONINFORMATION);
        else
        if(wparam == DarkPress)
            changetheme(0, dc);
        else
        if(wparam == LightPress)
            changetheme(1, dc);
        else
        if(wparam == SavePress){
            FILE *results = fopen("RES/results.txt", "w");
            fprintf(results, "NMultiply results.\nExercises - %d\nCorrect exercises - %d\nCorrect exercises - %d%%\n          -Nikita Donskov 2021", primcount, correctanswers, procent);
            fclose(results);
        } else
        if(wparam == OpenPress){
            system("RES\\results.txt");
        } else
        if((HWND)lparam == gen){ //If it is continue button
            if(lastp){
                correctanswers = 0; //Restart
                primcount = 0;
                lastp = 0;
            }
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
            lastp = 1;
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
    WS_OVERLAPPEDWINDOW, 50, 50, w, h, NULL, NULL, 
    NULL, NULL);

    dc = GetDC(hwnd);

    //changetheme(1, dc);

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

    AppendMenu(hThemeMenu, MF_STRING, LightPress, "Light");
    AppendMenu(hThemeMenu, MF_STRING, DarkPress, "Dark");

    AppendMenu(hResultsMenu, MF_STRING, SavePress, "Save");
    AppendMenu(hResultsMenu, MF_STRING, OpenPress, "Open");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hResultsMenu, "Results");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hThemeMenu, "Theme");
    SetMenu(hwnd, hMenu);
    AppendMenu(hMenu, MF_STRING, HELPpress, "Help");

    


    MSG msg;

    ShowWindow(hwnd, SW_NORMAL);

    myexp = generate(str);
    printf("%s\n", str);
    SetWindowText(primer, str);

    changetheme(1, dc);

    while(GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        
    }
    return 0;
}