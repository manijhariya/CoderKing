/////////////////////////////////////////////////////////////////////////////
// Name:        GUIFrame.h
// Purpose:     GUIFrame(header) file for text editor
// Author:      Manish Kumar
// Created:     21/06/20
// Copyright:   (c) Manish Kumar
// Licence:     GNU
/////////////////////////////////////////////////////////////////////////////

// =================================================================================================
// All classes and function declaration. refer to individual class defination files for more details
// =================================================================================================

#ifndef __GUIFrame__
#define __GUIFrame__
#include <wx/wx.h>
#include <wx/wfstream.h>
#include <wx/filepicker.h>
#include <wx/dataview.h>
#include <glob.h>
#include <vector>
#include <wx/animate.h>
#include <wx/panel.h>
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <ctime>
#include <wx/uiaction.h>
#include <wx/fontpicker.h>
#include <wx/colordlg.h>
#include <wx/webview.h>
#include <wx/thread.h>

class TextFrame;
class TreeApp;
class wxNotebook1Frame;
class Toolbar;
class TreeFrame;
class MyFrame:public wxFrame
{
        public:
		wxString compile_command = "gcc ";
		wxString build_command = "gcc ";
		wxString execute_command = "./";
		wxString AutoSaveTime = "10";
                MyFrame();
		Toolbar *tools;
		TreeApp *_treeapp;
		wxNotebook1Frame *NoteBookFrame;
		wxArrayString FileNames[10];
		void setFileTree();
		void OnOpen(wxCommandEvent& event);
		void OnSaveAs(wxCommandEvent& event);
		void OnNew(wxCommandEvent& event);
		void ReloadPage(wxCommandEvent& event);
		~MyFrame();
        private:
		wxTimer *m_timer,*s_timer;
		uint16_t ss=0,mm=0,hh=0;
		wxDECLARE_EVENT_TABLE();
		wxMDIParentFrame *panel;
		wxTextCtrl *C_CommandEntry,*B_CommandEntry,*E_CommandEntry,*SaveTime;
		TextFrame *tf;
		wxSize prevsize;
		std::vector<std::string> globvector(const std::string&);
		void timer(wxTimerEvent& event);
		void AutoSave(wxTimerEvent& event);
		void setMenu();
		void setSecondMenu();


                void OnExit(wxCommandEvent& event);
		void OnSaveAll(wxCommandEvent& event);
		void OnReload(wxCommandEvent& event);
		void OnClose(wxCommandEvent& event);
		void OnCloseAll(wxCommandEvent& event);
		void OnProperties(wxCommandEvent& event);

		void OnUndo(wxCommandEvent& event);
		void OnRedo(wxCommandEvent& event);
		void OnCut(wxCommandEvent& event);
		void OnCopy(wxCommandEvent& event);
		void OnPaste(wxCommandEvent& event);
		void OnDelete(wxCommandEvent& event);
		void OnSelectAll(wxCommandEvent& event);

		void OnChangeFont(wxCommandEvent& event);
		void OnTextColoring(wxCommandEvent& event);
		void OnFullScreen(wxCommandEvent& event);
		void OnEnableTransparent(wxCommandEvent& event);
		void OnShowHideDirectories(wxCommandEvent& event);
		void OnZoomIn(wxCommandEvent& event);
		void OnZoomOut(wxCommandEvent& event);
		void OnNormalSize(wxCommandEvent& event);
		void OnPageTab(wxCommandEvent& event);
		void OnPosition(wxCommandEvent& event);

		void OnCompile(wxCommandEvent& event);
		void OnBuild(wxCommandEvent& event);
		void OnExecute(wxCommandEvent& event);
		void OnTotalErrors(wxCommandEvent& event);
		void OnSetBuildCommand(wxCommandEvent& event);

		void OnReloadConfiguration(wxCommandEvent& event);
		void OnColorChooser(wxCommandEvent& event);
		void OnLineCount(wxCommandEvent& event);
		void OnScreenshot(wxCommandEvent& event);

		void OnReadOnly(wxCommandEvent& event);
		void OnCloneFile(wxCommandEvent& event);
		void OnAutoIndentation(wxCommandEvent& event);
		void OnFontSettings(wxCommandEvent& event);
		void OnAutoSaveTime(wxCommandEvent& event);

		void OnHelp(wxCommandEvent& event);
		void OnKeyBoardShortcuts(wxCommandEvent& event);
		void OnMessages(wxCommandEvent& event);
		void OnGithub(wxCommandEvent& event);
		void OnDonate(wxCommandEvent& event);
		void OnAbout(wxCommandEvent& event);

		void OnButtonEventReset(wxCommandEvent& event);
		void OnButtonEventCancel(wxCommandEvent& event);
		void OnButtonEventApply(wxCommandEvent& event);

		void OnButtonEventTimeReset(wxCommandEvent& event);
		void OnButtonEventTimeCancel(wxCommandEvent& event);
		void OnButtonEventTimeApply(wxCommandEvent& event);

		void OnButtonEventProjectCancel(wxCommandEvent& event);
		void OnButtonEventProjectOk(wxCommandEvent& event);
		void OnButtonEventProjectCreate(wxCommandEvent& event);

		void OnClose(int);
		void SaveAPage(int);
};

class TextFrame{
	public:
		TextFrame(wxNotebook*,int,wxString);
		TextFrame();
		TextFrame(wxNotebook*,FILE*,int,wxString);
		~TextFrame();
		void StatusTab(wxString*);
		bool SaveText(wxString);
		wxTextCtrl *textbox;
		void UndoOperation();
		void RedoOperation();
		void CompileCode(wxString);
		void BuildCode(wxString);
		void ExecuteCode(wxString);
		void JumpToLine(long int);
		void FindLine(wxString);
		void SetReadOnly();
	private:
		uint32_t counter=0;
		void NewLineText(wxKeyEvent& event);
};
class TreeApp
{
	public:TreeApp();
		bool OnInit(MyFrame *frame,std::vector<std::string>*);
		TreeFrame *_treeFrame;
		~TreeApp();
};
class wxNotebook1Frame
{
	public:
		wxNotebook1Frame();
		~wxNotebook1Frame();
		void SetTabText(uint8_t,const char[]);
    		wxNotebook1Frame(MyFrame*);
		void AddPageToBook(MyFrame*);
		void AddWritePageToBook(MyFrame*,FILE*,wxString);
		void setSizer(MyFrame*);
		TextFrame *TextObject;
		wxTextCtrl *textbox3;
		TextFrame* AddedPage[10];
		void ClosePage(wxString);
		int Pages[10] = {0};
		void SetText(wxString);
	private:
		int getPageNumber();
		wxTextCtrl *textbox1;
		wxTextCtrl *textbox2;
		wxNotebook *notebook;
		wxPanel *panel;
};

class Toolbar{
	private:
		MyFrame* toolframe;
		void OnNew(wxCommandEvent& event);
		void OnOpen(wxCommandEvent& event);
		void OnLoad(wxCommandEvent& event);
		void OnFind(wxCommandEvent& event);
		void OnJump(wxCommandEvent& event);
		void OnQuit(wxCommandEvent& event);
		wxTextCtrl *SaveTime;
		wxMDIParentFrame *panel;
		int id;

      public:   Toolbar(MyFrame*);
		~Toolbar();
		wxToolBar *toolbar;
		bool SaveCheck(int);
		void OnSaveAs(wxCommandEvent& event);
		void OnReload(wxCommandEvent& event);
		void OnClose(wxCommandEvent& event);
		void OnUndo(wxCommandEvent& event);
		void OnRedo(wxCommandEvent& event);
		void OnCompile(wxCommandEvent& event);
		void OnBuild(wxCommandEvent& event);
		void OnExecute(wxCommandEvent& event);

		void OnButtonEventLineReset(wxCommandEvent& event);
		void OnButtonEventLineOk(wxCommandEvent& event);
		void OnButtonEventFindReset(wxCommandEvent& event);
		void OnButtonEventFindOk(wxCommandEvent& event);
		int getId();
};

#endif

