// AutoCompleteStudy.cpp
// Copyright (C) 2018 Katayama Hirofumi MZ <katayama.hirofumi.mz@gmail.com>
// This file is public domain software.
#include <windows.h>
#include <windowsx.h>
#include <shlobj.h>
#include <shlwapi.h>

#define SHAutoComplete SHAutoComplete_

#ifdef SHAutoComplete
extern "C"
HRESULT WINAPI
SHAutoComplete_(HWND hwndEdit, DWORD dwFlags);
#endif

BOOL OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    HWND hCmb1 = GetDlgItem(hwnd, cmb1);
    HWND hwndEdit = (HWND)SendMessage(hCmb1, CBEM_GETEDITCONTROL, 0, 0);

    if (1)
        SHAutoComplete(hwndEdit, SHACF_FILESYS_ONLY | SHACF_FILESYS_DIRS);
    else if (0)
        SHAutoComplete(hwndEdit, SHACF_FILESYS_ONLY);
    else if (0)
        SHAutoComplete(hwndEdit, SHACF_URLALL);
    else
        SHAutoComplete(hwndEdit, SHACF_DEFAULT);

    return TRUE;
}

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id)
    {
    case IDOK:
    case IDCANCEL:
        EndDialog(hwnd, id);
        break;
    }
}

INT_PTR CALLBACK
DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        HANDLE_MSG(hwnd, WM_INITDIALOG, OnInitDialog);
        HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
    }
    return 0;
}

INT WINAPI
WinMain(HINSTANCE   hInstance,
        HINSTANCE   hPrevInstance,
        LPSTR       lpCmdLine,
        INT         nCmdShow)
{
    DialogBox(hInstance, MAKEINTRESOURCE(1), NULL, DialogProc);
    return 0;
}
