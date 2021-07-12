#include <windows.h>

extern HDC dc;
extern HWND primer;
extern HWND input;
extern HWND info;
extern HWND gen;
extern HWND qbut;
extern HBITMAP hnextbut, hfinishbut, hnextbutdark, hfinishbutdark,
saveicon, openicon, nighticon, lighticon;

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
        Rectangle(dc, 0, 0, 600, 480);

        ShowWindow(primer, SW_SHOW);
        ShowWindow(input, SW_SHOW);
        ShowWindow(info, SW_SHOW);
        ShowWindow(gen, SW_SHOW);
        ShowWindow(qbut, SW_SHOW);

        SendMessage(gen, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hnextbutdark);
        SendMessage(qbut, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hfinishbutdark);
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
        Rectangle(dc, 0, 0, 600, 480);

        ShowWindow(primer, SW_SHOW);
        ShowWindow(input, SW_SHOW);
        ShowWindow(info, SW_SHOW);
        ShowWindow(gen, SW_SHOW);
        ShowWindow(qbut, SW_SHOW);

        SendMessage(gen, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hnextbut);
        SendMessage(qbut, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hfinishbut);
    }
}