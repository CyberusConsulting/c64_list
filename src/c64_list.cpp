/* ---------------------------------------------------------------------------
Copyright:      Cyberus Consulting, (c) 2022
Name:           c64_list.cpp
Description:    c64 style directory listing
Created:        04/29/2022

NOTES:

    The c64 font 'C64_Pro_Mono-STYLE.ttf' was downloaded from:
    http://style64.org

TODO:
    Todo items are marked with a $$$ comment

Revisions:

--------------------------------------------------------------------------- */

#include <windows.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>


//---------------------------------------------------------
int main(int argc, char *argv[]) {

    WIN32_FIND_DATAA ffd;
    CHAR szCurDirSearch[MAX_PATH] = "*.*";
    CHAR szCurDirName[MAX_PATH];
    HANDLE hFind = INVALID_HANDLE_VALUE;

    printf("\n");

    // Find the first file in the current directory
    hFind = FindFirstFileA(szCurDirSearch, &ffd);
    if (INVALID_HANDLE_VALUE == hFind) {
        printf("FindFirstFile() failed!\n");
        return 0;
    }

    // Get the current directory path name
    DWORD retval = GetCurrentDirectoryA(MAX_PATH, szCurDirName);
    if (0 == retval) {
        printf("GetCurrentDirectoryA() failed!\n");
        return 0;
    }

    // Print the current path name in the disk label
    // Set the console mode to UTF16 so we can use the inverted characters from the c64 font
    printf("0 ");
    int prev_mode = _setmode(_fileno(stdout), _O_U16TEXT);
    wchar_t wlabel[24] = { 0 };
    int label_len = (int)strlen(szCurDirName);

    wlabel[0] = 0xE222;
    for (int l=0; l<16; l++) {
        if (l < (label_len - 2)) {
            char clabel = szCurDirName[l + 2];
            if ('\\' == clabel) { clabel = '/'; }
            if (clabel >= 0x61 && clabel <= 0x7A) {
                wlabel[l+1] = 0xE300 + clabel - 0x20;
            } else {
                wlabel[l+1] = 0xE200 + clabel;
            }
        } else {
            wlabel[l+1] = 0xE220;
        }
    }

    // Add drive letter and path length
    unsigned int wlabel_len = ((label_len - 2) > 255) ? 255 : (label_len - 2);
    if (wlabel_len < 0) { wlabel_len = 0; }
    char slabel_len[3];
    sprintf_s(slabel_len, sizeof(slabel_len), "%02X", label_len);

    wlabel[17] = 0xE222; wlabel[18] = 0xE220;
    wlabel[19] = 0xE200 + szCurDirName[0];
    wlabel[20] = 0xE200 + szCurDirName[1];
    wlabel[21] = 0xE220;
    wlabel[22] = 0xE200 + slabel_len[0];
    wlabel[23] = 0xE200 + slabel_len[1];
    for (int x=0; x<24; x++) {
        wprintf(L"%lc", wlabel[x]);
    }

    // Set console mode back to normal
    _setmode(_fileno(stdout), prev_mode);
    printf("\n");

    // List all files/directories
    do {

        // Format file size
        unsigned int iDisplaySize = 0;
        char size_label = ' ';
        char size_final[6];
        ULONGLONG iSize = ffd.nFileSizeHigh;
        iSize <<= sizeof(ffd.nFileSizeHigh) * 8;
        iSize |= ffd.nFileSizeLow;

        // { 'B', 'K', 'M', 'G', "T" };
        if (iSize > 0) {
            if (iSize < 1024ULL)                { size_label = 'B'; iDisplaySize = (unsigned int)(iSize); }
            else if (iSize < 1048576ULL)        { size_label = 'K'; iDisplaySize = (unsigned int)(iSize / 1024ULL); }
            else if (iSize < 1073741824ULL)     { size_label = 'M'; iDisplaySize = (unsigned int)(iSize / 1048576ULL); }
            else if (iSize < 1099511627776ULL)  { size_label = 'G'; iDisplaySize = (unsigned int)(iSize / 1073741824ULL); }
            else                                { size_label = 'T'; iDisplaySize = (unsigned int)(iSize / 1099511627776ULL); }
        }
        sprintf_s(size_final, sizeof(size_final), "%d%c", iDisplaySize, size_label);

        // Get name length indicator
        char name_too_long = ' ';
        if (strlen(ffd.cFileName) > 16) { name_too_long = '>'; }

        // $$$ TODO: Support more file types

        // Print the line [size][name][type]
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            printf("%-5s\"%-16.16s\"%cDIR\n", size_final, ffd.cFileName, name_too_long);
        } else {
            printf("%-5s\"%-16.16s\"%cPRG\n", size_final, ffd.cFileName, name_too_long);
        }

    } while (FindNextFileA(hFind, &ffd));

    return 0;
}
