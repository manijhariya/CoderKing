# A Light weight Text-Editor
A fully developed light weight text-editor for general purpose..

# How??
The goal is to develope a general purpose text-editor with as low as memory
it can use. Features can with extra memories uses. But i have tried to keep
it as simple and as efficeint as possible. 
This editor is general purpose for now. But the light weight graphical interface
is going to make writing fast and efficient on linux-like machines.

This project uses the [wxWidget](https://www.wxwidgets.org/) library to handle much
of the heavy lifting of graphical interface processing, and intends to build a library
ontop of wxwidgets without changing the wxWidgets source code. This project and its function
are their own isloated work (unless stated otherwise), however they require linking with
wxwidgets to operate correctly.
[view the wxwidgets Documentation] https://docs.wxwidgets.org/3.0/
[view the wxwidgets compilation guild] https://wiki.wxwidgets.org/Compiling_and_getting_started

If you would like to run this code you need to first install wxwidgets by compiling the source (link above).
After that u can run this by command in terminal/command prompt "g++ -Wall main.cpp DataViewFrame.cpp Textframe.cpp GUIframe.cpp NoteBookFrame.cpp ToolBar.cpp MenuFunctions.cpp `wx-config --cxxflags --libs` -o CoderKing"


### Files structure
- ** main.h             (source header file for main function)
- ** GUIFrame.h         (source header file for all the classes and functions which i have used)
- ** main.cpp           (source main file to initialise the code)
- ** GUIframe.cpp	(source file for classes to run)		
- ** MenuFunctions.cpp  (source function declaration for menu items)
- ** ToolBar.cpp	(source function declaration for toolbar items)
- ** NoteBookFrame.cpp  (source function declaration for pages of frame(editor))
- ** Textframe.cpp	(source function declaration for page processing writing and stuff)
- ** DataViewFrame.cpp  (source function declaration for files in current directory)
- ** media - (Directory) (all the media (images) the program is going to take..)

a work in progress by Mani. 
