# c64 style LIST command for the PC


------------------------------------------------------------<br>
<b>Notes:</b><br>
------------------------------------------------------------<br>

- Compiled with Visual Studio 2017<br>

- Settings are only for "Release/x64", if you want to compile for other targets, 
you need to make sure you have the correct settings/pathnames copied from the "Release/x64" target<br>

- By default, the .exe is copied to the ./bin folder as "c64_list_win.exe". 
I renamed it to "list.exe" and copied it to my path for convinience.<br>

------------------------------------------------------------<br>
<b>Terminal:</b><br>
------------------------------------------------------------<br>

In order to get a more authentic experience, i modified my default terminal window as follows:<br>

- Install the supplied truetype font "C64_Pro_Mono-STYLE.ttf" on your system (Control Panel/Fonts)<br>

In the terminal settings:<br>

- Select the font and use size 16<br>
- Set screen buffer width to 40 and height to 9999<br>
- Set window size width to 40 and height to 50 (or 25 if you want a more c64-ish experience)<br>
- Set screen background to the 2nd color (dark blue)<br>
- Set screen text to the 4th color (lighter blue)<br>
- Set cursor shape to Solid Box<br>
- Make sure the cursor color matches your foreground color<br>

- Optionally, you can also run the supplied batch file "c64.bat" (You need to edit the drive and path in the file) to get a c64 startup screen<br>

------------------------------------------------------------<br>
<b>Display:</b><br>
------------------------------------------------------------<br>

- The title bar shows the current path (truncated to 16 chars) followed by the drive letter and the hex length of the path name (max of FF)<br>

- File sizes are displayed in B(ytes), K(ilobytes), M(egabytes), G(igabytes), T(errabytes)<br>

- File names are turncated at 16 chars, a ">" after a file name indicates that the name was truncated<br>

- Currently only two file types are displayed, "DIR" for directories and "PRG" for everything else<br>


![Screenshot](utils/list.png)
