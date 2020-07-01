/////////////////////////////////////////////////////////////////////////////
// Name:        GUIframe.cpp
// Purpose:     GUIframe.cpp file for text editor
// Author:      Manish Kumar
// Created:     21/06/20
// Copyright:   (c) Manish Kumar
// Licence:     GNU
/////////////////////////////////////////////////////////////////////////////

// =========================================================================================================================
// Driver function for all the inner classes all the constructor , Menubar and Toolbar are going to initialise by this class
// =========================================================================================================================

#include "main.h"
MyFrame::MyFrame():wxFrame(NULL,wxID_ANY,"CoderKing",wxDefaultPosition,wxSize(1000,700))
{
       wxIcon mainicon;
       mainicon.LoadFile("media/icon");
       SetIcon(mainicon);

	prevsize = GetSize();
	Centre();
	setMenu();
	setFileTree();
	NoteBookFrame = new wxNotebook1Frame(this);
	tools = new Toolbar(this);
	m_timer = new wxTimer(this,101);
	s_timer = new wxTimer(this,102);
	m_timer->Start(1000);                                   //There is some proble with this it is an api but i don't know why it is not woking
	s_timer->Start(300000);                                  //In every 5minutes Autosave
}
wxBEGIN_EVENT_TABLE(MyFrame,wxFrame)
	EVT_TIMER(101,MyFrame::timer)
	EVT_TIMER(102,MyFrame::AutoSave)
wxEND_EVENT_TABLE()

void MyFrame::setMenu()
{
	// All Menubar content declaration all the defination for these is going to be in another file Named as "MenuFunction.cpp"
	wxMenu *menuFile = new wxMenu;
	menuFile->Append(wxID_NEW,"&New\tCtrl-N",
					"Get a new file");
	menuFile->Append(20,"&Open\tCtrl-O",
					"Open a file");
	menuFile->Append(wxID_SAVE,"&Save\tCtrl-s",
					"Save a file");
	menuFile->Append(wxID_SAVEAS,"&SaveAs",
					"Save a file As");
	menuFile->Append(40,"&Save All\tctrl+shift+s",
					"Save all Files");
	menuFile->Append(41,"&Reload\tCtrl+R",
				"Reload CoderKing");
	menuFile->Append(42,"&Properties",
				"Properties for CoderKing");
	menuFile->Append(43,"&Close\tCtrl+W",
				"Close this Page");
	menuFile->Append(44,"&Close All\tShift+Ctrl+W",
				"Close All Pages");
	menuFile->Append(wxID_EXIT,"&Quit\tCtrl+Q");


	wxMenu *menuEdit = new wxMenu;
	menuEdit->Append(wxID_UNDO,"&Undo\tCtrl+Z",
				"Undo Last Operation");
	menuEdit->Append(wxID_REDO,"&Redo\tCtrl+Y",
				"Redo Last Operation");
	menuEdit->Append(wxID_CUT,"&Cut\tCtrl+X",
				"Cut Buffer in Page");
	menuEdit->Append(wxID_COPY,"&Copy\tCtrl+C",
				"Copy Buffer in Page");
	menuEdit->Append(wxID_PASTE,"&Paste\tCtrl+V",
				"Paste Buffer on Page");
	menuEdit->Append(wxID_DELETE,"&Delete\t",
				"Delete Buffer from Page");
	menuEdit->Append(45,"&Select All\tCtrl-A",
				"Select all Buffer in Page");

	wxMenu *menuView = new wxMenu;
	menuView->Append(47,"&Change Font",
				"Prefer To Your Fonts");
	menuView->Append(48,"&Text Coloring",
				"Prefer Colour for you Page");
	menuView->Append(49,"&FullScreen\tF11",
				"Enter Full Screen");
	menuView->Append(50,"&Enable/Disable Transparancy",
				"Hide Or Show Timer window");
	menuView->Append(51,"&Show/Hide Directories Window",
				"Show or Hide Directories windows");
	menuView->Append(52,"&Zoom In\tCtrl++",
				"Zoom In For Current Page");
	menuView->Append(53,"&Zoom Out\tCtrl--",
				"Zoom Out For Current Page");
	menuView->Append(54,"&Noraml Size\tCtrl+O",
				"Noraml Size Window");
	menuView->Append(55,"GetPosition\tCtrl+L",
			    "Get Position");
	menuView->Append(56,"Page Tab\tCtrl+P",
	                    "Page tab list");

	wxMenu *menuBuild = new wxMenu;
	menuBuild->Append(59,"&Compile\tF7",
				"Compile Current File");
	menuBuild->Append(60,"&Build\tF8",
				"Build Current File");
	menuBuild->Append(61,"&Execute\tF9",
				"Execute Current File");
	menuBuild->Append(62,"&Errors",
				"Errors in Current File");
	menuBuild->Append(63,"&Set Build Commands",
				"Set Build Commands to Run Files");

	wxMenu *menuTools = new wxMenu;
	menuTools->Append(64,"&Reload Configuration",
				"Reload All configuration");
	menuTools->Append(65,"&Color Chooser",
				"Choose Your Color Preferences");
	menuTools->Append(66,"&Line Count",
				"Word Count in Current File");
	menuTools->Append(77,"&ScreenShot",
				"Take Screnshot for current window");

	wxMenu *menuSettings = new wxMenu;
	menuSettings->Append(67,"&Read Only",
				"Pages can't be edited");
	menuSettings->Append(68,"&Clone File",
				"Clone the Current Page");
	menuSettings->Append(69,"&Auto Indentataion",
				"Set Auto Indentation");
	menuSettings->Append(70,"Font Settings",
				"Set Preferences for Fonts");
	menuSettings->Append(78,"Auto Save Time",
				"Set Auto Save Time for Files");


	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(71,"&Help\tF1",
				"Help/Documentation of CoderKing");
	menuHelp->Append(72,"&Keyboard Shortcuts",
				"All Keyboard Shortcuts used in CoderKing");
	menuHelp->Append(73,"&Messages",
				"Messages from Developers");
	menuHelp->Append(74,"&GitHub",
				"Report a bug..");
	menuHelp->Append(75,"&Donate..",
				"Donate a Pizza..");
	menuHelp->Append(76,"&About.",
				"About Developers");

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile,"&File");
	menuBar->Append(menuEdit,"&Edit");
	menuBar->Append(menuView,"&View");
	menuBar->Append(menuBuild,"&Build");
	menuBar->Append(menuTools,"&Tools");
	menuBar->Append(menuSettings,"&Settings");
	menuBar->Append(menuHelp,"&Help");

	SetMenuBar( menuBar );
	CreateStatusBar(4);
	SetStatusText("CoderKing",1);

	//File Menu_s
	Bind(wxEVT_MENU,&MyFrame::OnNew,this,wxID_NEW);
	Bind(wxEVT_MENU,&MyFrame::OnOpen,this,20);
	Bind(wxEVT_MENU,&MyFrame::OnSaveAs,this,wxID_SAVE);
	Bind(wxEVT_MENU,&MyFrame::OnSaveAs,this,wxID_SAVEAS);
	Bind(wxEVT_MENU,&MyFrame::OnSaveAll,this,40);
	Bind(wxEVT_MENU,&MyFrame::OnReload,this,41);
	Bind(wxEVT_MENU,&MyFrame::OnProperties,this,42);
	Bind(wxEVT_MENU,&MyFrame::OnClose,this,43);
	Bind(wxEVT_MENU,&MyFrame::OnCloseAll,this,44);
	Bind(wxEVT_MENU,&MyFrame::OnExit,this,wxID_EXIT);


	//Edit Menu
	Bind(wxEVT_MENU,&MyFrame::OnUndo,this,wxID_UNDO);
	Bind(wxEVT_MENU,&MyFrame::OnRedo,this,wxID_REDO);
	Bind(wxEVT_MENU,&MyFrame::OnCut,this,wxID_CUT);
	Bind(wxEVT_MENU,&MyFrame::OnCopy,this,wxID_COPY);
	Bind(wxEVT_MENU,&MyFrame::OnPaste,this,wxID_PASTE);
	Bind(wxEVT_MENU,&MyFrame::OnDelete,this,wxID_DELETE);
	Bind(wxEVT_MENU,&MyFrame::OnSelectAll,this,45);

	//View Menu
	Bind(wxEVT_MENU,&MyFrame::OnChangeFont,this,47);
	Bind(wxEVT_MENU,&MyFrame::OnTextColoring,this,48);
	Bind(wxEVT_MENU,&MyFrame::OnFullScreen,this,49);
	Bind(wxEVT_MENU,&MyFrame::OnEnableTransparent,this,50);
	Bind(wxEVT_MENU,&MyFrame::OnShowHideDirectories,this,51);
	Bind(wxEVT_MENU,&MyFrame::OnZoomIn,this,52);
	Bind(wxEVT_MENU,&MyFrame::OnZoomOut,this,53);
	Bind(wxEVT_MENU,&MyFrame::OnNormalSize,this,54);
	Bind(wxEVT_MENU,&MyFrame::OnPosition,this,55);
	Bind(wxEVT_MENU,&MyFrame::OnPageTab,this,56);


	//Build Menu
	Bind(wxEVT_MENU,&MyFrame::OnCompile,this,59);
	Bind(wxEVT_MENU,&MyFrame::OnBuild,this,60);
	Bind(wxEVT_MENU,&MyFrame::OnExecute,this,61);
	Bind(wxEVT_MENU,&MyFrame::OnTotalErrors,this,62);
	Bind(wxEVT_MENU,&MyFrame::OnSetBuildCommand,this,63);

	//Tools
	Bind(wxEVT_MENU,&MyFrame::OnReloadConfiguration,this,64);
	Bind(wxEVT_MENU,&MyFrame::OnColorChooser,this,65);
	Bind(wxEVT_MENU,&MyFrame::OnLineCount,this,66);
	Bind(wxEVT_MENU,&MyFrame::OnScreenshot,this,77);

	//Settings
	Bind(wxEVT_MENU,&MyFrame::OnReadOnly,this,67);
	Bind(wxEVT_MENU,&MyFrame::OnCloneFile,this,68);
	Bind(wxEVT_MENU,&MyFrame::OnAutoIndentation,this,69);
	Bind(wxEVT_MENU,&MyFrame::OnFontSettings,this,70);
	Bind(wxEVT_MENU,&MyFrame::OnAutoSaveTime,this,78);

	//Help
	Bind(wxEVT_MENU,&MyFrame::OnHelp,this,71);
	Bind(wxEVT_MENU,&MyFrame::OnKeyBoardShortcuts,this,72);
	Bind(wxEVT_MENU,&MyFrame::OnMessages,this,73);
	Bind(wxEVT_MENU,&MyFrame::OnGithub,this,74);
	Bind(wxEVT_MENU,&MyFrame::OnDonate,this,75);
	Bind(wxEVT_MENU,&MyFrame::OnAbout,this,76);

	Bind(wxEVT_MENU,&MyFrame::OnAbout,this,wxID_ABOUT);
}

void MyFrame::AutoSave(wxTimerEvent& event)
{
	for(int id=0;id<10;id++)
	{
		if(NoteBookFrame->Pages[id] == 1)
		{
			wxString tempfile = FileNames->Item(id);
			if(tempfile.Cmp(wxT("Untitled")))
				tempfile << id << wxT(".ckg");
			else
				tempfile << wxT(".ckg");
			NoteBookFrame->AddedPage[id]->SaveText(tempfile);
		}
		else{
			continue;
		}
	}
	return;
}

void MyFrame::setFileTree()
{
	// The right most window is going to be initialsed by this function and it is going to show all the files with
	// with different (.)extension separated  
	 _treeapp = new TreeApp();
	std::vector<std::string> Files = globvector("*");
	_treeapp->OnInit(this,&Files);
}
std::vector<std::string> MyFrame::globvector(const std::string& pattern)
{
	glob_t glob_result;
	glob(pattern.c_str(),GLOB_TILDE,NULL,&glob_result);
	std::vector<std::string> files;
	for(unsigned int i=0;i<glob_result.gl_pathc;++i){
		files.push_back(std::string(glob_result.gl_pathv[i]));
	}
	globfree(&glob_result);
	return files;
}
MyFrame::~MyFrame()
{
	delete tools;
	delete _treeapp;
	delete NoteBookFrame;
	delete panel;
	delete C_CommandEntry;
	delete B_CommandEntry;
	delete E_CommandEntry;
	delete SaveTime;
	delete tf;
}
