/////////////////////////////////////////////////////////////////////////////
// Name:        MenuFunctions.cpp
// Purpose:     MenuFunctions.cpp file for text editor
// Author:      Manish Kumar
// Created:     21/06/20
// Copyright:   (c) Manish Kumar
// Licence:     GNU
/////////////////////////////////////////////////////////////////////////////

// ======================================================================================
// It consist of all the function defination of MenuBar actions which is of class MyFrame. Names for functions make them
// understand all button action functions are in bottomost of file
// ======================================================================================

#include "main.h"

//File Menu
void MyFrame::OnNew(wxCommandEvent& event)
{
	//New File
	NoteBookFrame->AddPageToBook(this);
}
void MyFrame::OnOpen(wxCommandEvent& event)
{
	//Open a existing file
	SetStatusText("Open Menu");
	wxFileDialog openFileDialog(this,("Open a Program/Script file"),"","","C/CPP files(.cpp;.c)|*.cpp;*.c|H Files(.h)|*.h",wxFD_OPEN|wxFD_FILE_MUST_EXIST);
	if(openFileDialog.ShowModal() == wxID_CANCEL)
		return;
	wxFileInputStream input_stream(openFileDialog.GetFilename());
	if(!input_stream.IsOk())
	{
		wxLogError("Cannot open file '%s'.",openFileDialog.GetPath());
		return;
	}
	else
	{
		FILE *file;
		file = fopen(openFileDialog.GetPath(),"r");
		if(file)
		{
			wxString FileName = openFileDialog.GetPath();
			NoteBookFrame->AddWritePageToBook(this,file,FileName);
		}
		else
		{
			wxLogMessage("Unable to open file");
			return;
		}
	}
}

void MyFrame::ReloadPage(wxCommandEvent& event)
{
	// Reload page..
	wxWindow *temparary = FindFocus();
	wxWindow *temp = temparary->GetParent();
	if(temp->GetId() == 30){
		int id = temparary->GetId();
		if(strcmp(FileNames->Item(id),wxString("Untitled")))
		{
			FILE *file;
			file = fopen(FileNames->Item(id),"r");
			NoteBookFrame->AddWritePageToBook(this,file,FileNames->Item(id));
		}
		else
			OnNew(event);
	}
	else { }

}

void MyFrame::SaveAPage(int id)
{
	//Save a page not direct not referenced but called from save all..
		if(!tools->SaveCheck(id))
                        {
                                wxFileDialog saveFileDialog(this,("Save Program/Script file"),"","","",wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
                                if(saveFileDialog.ShowModal() == wxID_CANCEL)
                                        return;
                                wxFileOutputStream output_stream(saveFileDialog.GetPath());
                                if(!output_stream.IsOk())
                                {
                                        wxLogError("Cannot Save current contents in file '%s'.",saveFileDialog.GetPath());
                                 	return;
                                }
                                else
                                {
                                        wxString temp = saveFileDialog.GetPath();
                                        FileNames->Insert(temp,id,1);
                                        NoteBookFrame->AddedPage[id]->SaveText(this->FileNames->Item(id));
                                        time_t now = time(0);
                                        char* dt = ctime(&now);
                                        const char text[] = "File Saved with Name:";
                                        strcat(dt,text);
                                        strcat(dt,FileNames->Item(id));
                                        strcat(dt,";\n");
                                        NoteBookFrame->SetTabText((uint8_t)1,dt);
                        		wxString tempfile = FileNames->Item(id);
                	                tempfile << id << wxT(".ckg");
					remove(tempfile);
			       }
                        }
                        else {
                                NoteBookFrame->AddedPage[id]->SaveText(FileNames->Item(id)); 
				wxString tempfile = FileNames->Item(id);
                                tempfile << wxT(".ckg");
                                remove(tempfile);
				return; }
}

void MyFrame::OnSaveAs(wxCommandEvent& event)
{  //save as action
	tools->OnSaveAs(event);
	return;
}
void MyFrame::OnSaveAll(wxCommandEvent& event)
{
	// save all the pages which are in showing in the window going to call for Save a file function
	for(int id=0;id<10;id++)
	{	if(NoteBookFrame->Pages[id] == 1)
		{
			SaveAPage(id);
		}
		else {	continue; }
	}
	return;
}
void MyFrame::OnReload(wxCommandEvent& event)
{
	tools->OnReload(event);
}
void MyFrame::OnProperties(wxCommandEvent& event)
{
// showing all the properties of the file which is current focused..
	int id = tools->getId();
	if(id == -1) {}
	else{
	wxMDIParentFrame *panel = new wxMDIParentFrame(this,-1,wxT("Properties"),wxDefaultPosition,wxSize(400,500),wxDEFAULT_FRAME_STYLE,wxFrameNameStr);
	wxTextCtrl *book = new wxTextCtrl(panel,100,wxT("\n\nDefault"),wxDefaultPosition,wxSize(400,500),wxTE_MULTILINE|wxTE_READONLY|wxNO_BORDER|wxTE_CENTER|wxTE_DONTWRAP,wxDefaultValidator,wxT("Sample Window"));
	FILE *f;
    	f = fopen(FileNames->Item(id), "r");
    	fseek(f, 0, SEEK_END);
    	unsigned long len = (unsigned long)ftell(f);
    	fclose(f);

	wxString temp;
	temp << wxT("\n\nName:\t") << FileNames->Item(id) << wxT("\n");
	temp << wxT("Size:\t") << len << wxT("  bytes\n");
	temp << wxT("Type:\t") << wxT("C-C++ Source File\n");
	temp << wxT("Parent Folder:\t") << FileNames->Item(id) << wxT("\n");
	temp << wxT("Accessed:\t") << wxT("Just Now") << wxT("\n");
	temp << wxT("Permissions:\n\n");
	temp << wxT("Read:\tYes\nWrite:\tYes\nExecute:\tNo\n");
	book->AppendText(temp);
	panel->Show();
	}
}

void MyFrame::OnClose(wxCommandEvent& event)
{
	tools->OnClose(event);
}

void MyFrame::OnCloseAll(wxCommandEvent& event)
{
	//Closing all the pages!!!!!!
	wxMessageDialog *savedialog = new wxMessageDialog(this,wxT("Do you want to Save Files Before Closing All files"),wxT("Save"),wxOK|wxCANCEL);
	int dialog = savedialog->ShowModal();
	if(dialog == wxID_OK)
	{	OnSaveAll(event); 	}
	else
		{
			for(int id=0;id < 10; id++)
			{	if(NoteBookFrame->Pages[id] == 1)
				{	delete NoteBookFrame->AddedPage[id]; }
			}
		}
}
void MyFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}


//Edit Menu -- some functions are going to call for the ToolBar.cpp functions which is class with the same name as (ToolBar)
void MyFrame::OnUndo(wxCommandEvent& event)
{
	tools->OnUndo(event);
}
void MyFrame::OnRedo(wxCommandEvent& event)
{
	tools->OnRedo(event);
}
//Some very funny functions i am just simulating the keys!! 
void MyFrame::OnCut(wxCommandEvent& event)
{
	//wxLogMessage("Cut");
	wxUIActionSimulator *action = new wxUIActionSimulator();
	action->Char(88,wxMOD_CONTROL);
}
void MyFrame::OnCopy(wxCommandEvent& event)
{
	wxUIActionSimulator *action = new wxUIActionSimulator();
	action->Char(67,wxMOD_CONTROL);
}

void MyFrame::OnPaste(wxCommandEvent& event)
{
        //wxLogMessage("Paste");
	wxUIActionSimulator *action = new wxUIActionSimulator();
        action->Char(86,wxMOD_CONTROL);
}

void MyFrame::OnDelete(wxCommandEvent& event)
{
        //wxLogMessage("Delete");
	wxUIActionSimulator *action = new wxUIActionSimulator();
        action->Char(8,wxMOD_NONE);
}

void MyFrame::OnSelectAll(wxCommandEvent& event)
{
        //wxLogMessage("SelectAll");
	wxUIActionSimulator *action = new wxUIActionSimulator();
        action->Char(65,wxMOD_CONTROL);

}

//View Menu
void MyFrame::OnChangeFont(wxCommandEvent& event)
{
	panel = new wxMDIParentFrame(this,-1,wxT("Font Settings"),wxPoint(450,250),wxSize(200,200),wxDEFAULT_FRAME_STYLE,wxFrameNameStr);
        wxFontPickerCtrl *oldfonts = new wxFontPickerCtrl(panel,-1,wxNullFont,wxDefaultPosition,wxDefaultSize,wxFNTP_USE_TEXTCTRL,wxDefaultValidator,wxT("Select Font"));
	wxFont newfonts = oldfonts->GetSelectedFont();
	oldfonts->SetMaxPointSize((unsigned int)64);
	oldfonts->SetSelectedFont(newfonts);
	panel->Show(true);
	return;
}

void MyFrame::OnTextColoring(wxCommandEvent& event)
{
	int id = tools->getId();
	if(id == -1) {}
	else{
	wxTextAttr styletext;
	styletext.SetFontFaceName(wxT("rsfs10"));
	styletext.SetTextColour(93707);
        styletext.SetTextEffects(wxTEXT_ATTR_EFFECT_SUPERSCRIPT);

	NoteBookFrame->AddedPage[id]->textbox->SetBackgroundColour(2031873);
        NoteBookFrame->AddedPage[id]->textbox->SetStyle(1,10,styletext);
	}
//        wxLogMessage("TextColoring");
}

void MyFrame::OnFullScreen(wxCommandEvent& event)
{
	wxSize nowsize;
	nowsize = GetSize();
	if(prevsize == nowsize)
	{
		SetSize(1400,1200);
	}
	else{
		SetSize(prevsize);
		Center();
      }
	 // wxLogMessage("Full Screen");
	return;
}

void MyFrame::OnEnableTransparent(wxCommandEvent& event)
{
	if(this->SetTransparent(230))
	{   }
	else
	{ wxLogMessage("You System doesn't have Transparancy Feature",wxOK);
	   return;		}
       // wxLogMessage("Transparancy");
}

void MyFrame::OnShowHideDirectories(wxCommandEvent& event)
{
        //wxLogMessage("Directories");
//	this->_treeapp->_treeFrame->Hide();
}

void MyFrame::OnZoomIn(wxCommandEvent& event)
{
        wxLogMessage("Zoom In");
}

void MyFrame::OnZoomOut(wxCommandEvent& event)
{
        wxLogMessage("Zoom Out");
}

void MyFrame::OnNormalSize(wxCommandEvent& event)
{
        wxLogMessage("Normal Size");
}
void MyFrame::OnPosition(wxCommandEvent& event)
{
	int id = tools->getId();
	if(id == -1) {}
	else{
		      long a=0,b=0;
                      long *x=&a,*y=&b;
		      long  pos = NoteBookFrame->AddedPage[id]->textbox->GetInsertionPoint();
                      NoteBookFrame->AddedPage[id]->textbox->PositionToXY(pos,x,y);
                      wxString temp;
                      temp << wxT("(") << (*x) << wxT(",") << (*y) << wxT(")");
                      SetStatusText(temp,3);
		      wxMDIParentFrame *panel = new wxMDIParentFrame(this,-1,wxT("Current Position"),wxDefaultPosition,wxSize(220,220),wxDEFAULT_FRAME_STYLE,wxFrameNameStr);
                      new wxTextCtrl(panel,100,temp,wxDefaultPosition,wxSize(200,200),wxTE_MULTILINE|wxTE_READONLY|wxNO_BORDER);
		      panel->Center();
		      panel->Show();
	}
}
void MyFrame::OnPageTab(wxCommandEvent& event)
{
     wxMDIParentFrame *panel = new wxMDIParentFrame(this,-1,wxT("Pages Information"),wxDefaultPosition,wxSize(510,610),wxDEFAULT_FRAME_STYLE,wxFrameNameStr);
     wxTextCtrl *book = new wxTextCtrl(panel,100,wxT(""),wxDefaultPosition,wxSize(500,600),wxTE_MULTILINE|wxTE_READONLY|wxNO_BORDER|wxTE_DONTWRAP);
     wxString temp;
     temp << wxT("\n\n\tPage Number:\t\t") << wxT("FileName:\n");
     for(int id=0;id<10;id++)
	{
	  if(NoteBookFrame->Pages[id] == 1)
		temp << wxT("\t") << id << wxT("\t\t\t\t\t") << FileNames->Item(id) << wxT("\n");
	}
     book->AppendText(temp);
     panel->Center();
     panel->Show();

}

//Build Menu
void MyFrame::OnCompile(wxCommandEvent& event)
{
	tools->OnCompile(event);
//        wxLogMessage("Compile");
}

void MyFrame::OnBuild(wxCommandEvent& event)
{
	tools->OnBuild(event);
   //     wxLogMessage("Build");
}

void MyFrame::OnExecute(wxCommandEvent& event)
{
	tools->OnExecute(event);
        wxLogMessage("Execute");
}

void MyFrame::OnTotalErrors(wxCommandEvent& event)
{
	//tools->OnCompile(event);
      //  wxLogMessage("Tool Errors");
}

void MyFrame::OnSetBuildCommand(wxCommandEvent& event)
{
	panel = new wxMDIParentFrame(this,-1,wxT("Set Build Commands"),wxDefaultPosition,wxSize(500,500),wxDEFAULT_FRAME_STYLE,wxFrameNameStr);
//	wxPanel *panel = new wxPanel(menuframe,wxID_ANY,wxDefaultPosition,wxSize(500,700));
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);

	wxStaticText *C_Command = new wxStaticText(panel,wxID_ANY,wxT("Compile\nCommand:\t\n\t"),wxDefaultPosition,wxSize(70,-1),0,wxStaticTextNameStr);
	hbox1->Add(C_Command,0);

	C_CommandEntry = new wxTextCtrl(panel,wxID_ANY,wxT(""),wxDefaultPosition,wxDefaultSize,wxTE_DONTWRAP);
	hbox1->Add(C_CommandEntry,1);
	vbox->Add(hbox1,0,wxEXPAND|wxLEFT|wxRIGHT|wxTOP,10);

	wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText *B_Command = new wxStaticText(panel,wxID_ANY,wxT("Build\nCommand:\t\n\t"),wxDefaultPosition,wxSize(70,-1),0,wxStaticTextNameStr);
	hbox2->Add(B_Command,0);

	B_CommandEntry = new wxTextCtrl(panel,wxID_ANY);
	hbox2->Add(B_CommandEntry,1);
	vbox->Add(hbox2,0,wxEXPAND|wxLEFT|wxTOP|wxRIGHT,10);

	wxBoxSizer *hbox3 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText *E_Command = new wxStaticText(panel,wxID_ANY,wxT("Execute\nCommand:\t\n\t"),wxDefaultPosition,wxSize(70,-1),0,wxStaticTextNameStr);
	hbox3->Add(E_Command);

	E_CommandEntry = new wxTextCtrl(panel,wxID_ANY);
	hbox3->Add(E_CommandEntry,1);
	vbox->Add(hbox3,0,wxEXPAND|wxLEFT|wxTOP|wxRIGHT,10);

	wxBoxSizer *hbox4 = new wxBoxSizer(wxHORIZONTAL);
	wxButton *m_buttonReset = new wxButton(panel,99,wxT("Reset"));
	hbox4->Add(m_buttonReset);

	wxButton *m_buttonApply = new wxButton(panel,98,wxT("Apply"));
	hbox4->Add(m_buttonApply);

	wxButton *m_buttonCancel = new wxButton(panel,97,wxT("Cancel"));
	hbox4->Add(m_buttonCancel);
	vbox->Add(hbox4,0,wxALIGN_TOP|wxALIGN_RIGHT|wxRIGHT|wxBOTTOM,10);

	Bind(wxEVT_BUTTON,&MyFrame::OnButtonEventReset,this,99);
	Bind(wxEVT_BUTTON,&MyFrame::OnButtonEventApply,this,98);
	Bind(wxEVT_BUTTON,&MyFrame::OnButtonEventCancel,this,97);

	panel->SetSizer(vbox);
	Center();
	panel->Show(true);
}

//Settings Menu
void MyFrame::OnReloadConfiguration(wxCommandEvent& event)
{
        wxLogMessage("Reload Config.");
}

void MyFrame::OnColorChooser(wxCommandEvent& event)
{
	wxColourDialog *color = new wxColourDialog(this,NULL);
	if(color->ShowModal() == wxID_OK)
	{	SetBackgroundColour(color->GetColourData().GetColour());
		return;	}
	else
		{return;		}
//        wxLogMessage("Color Chooser");
}

void MyFrame::OnLineCount(wxCommandEvent& event)
{
	int id = tools->getId();
	if(id == -1) {return;}
	else{
		wxString temp;
		int TotalLines = NoteBookFrame->AddedPage[id]->textbox->GetNumberOfLines();
		temp << TotalLines;
		wxMessageBox(wxT("Total number of Lines in this Page is::")+temp,wxT("TotalLines"),wxICON_INFORMATION);
	}
       // wxLogMessage("Word Count");
}

void MyFrame::OnScreenshot(wxCommandEvent& event)
{
	wxUIActionSimulator *action = new wxUIActionSimulator();
        action->Char(350,wxMOD_NONE);
}

void MyFrame::OnReadOnly(wxCommandEvent& event)
{
	int id = tools->getId();
	if(id == -1) {}
	else
	{
		NoteBookFrame->AddedPage[id]->SetReadOnly();
		return;
	}
      //  wxLogMessage("Read Only");
}

void MyFrame::OnCloneFile(wxCommandEvent& event)
{
	int id = tools->getId();
	if(id == -1) {}
	else{
		wxString temptext = FileNames->Item(id);
		FILE *file;
		file = fopen(temptext,"r");
		NoteBookFrame->AddWritePageToBook(this,file,wxT("Untitled"));
	//	fclose(file);
	}
       // wxLogMessage("Clone File");
}

void MyFrame::OnAutoIndentation(wxCommandEvent& event)
{
        wxLogMessage("Auto Indentation");
}

void MyFrame::OnFontSettings(wxCommandEvent& event)
{
	panel = new wxMDIParentFrame(this,-1,wxT("Font Settings"),wxPoint(450,250),wxSize(200,200),wxDEFAULT_FRAME_STYLE,wxFrameNameStr);
        wxFontPickerCtrl *oldfonts = new wxFontPickerCtrl(panel,-1,wxNullFont,wxDefaultPosition,wxDefaultSize,wxFNTP_USE_TEXTCTRL,wxDefaultValidator);
        wxFont newfonts = oldfonts->GetSelectedFont();
        oldfonts->SetMaxPointSize((unsigned int)64);
        oldfonts->SetSelectedFont(newfonts);
        panel->Show(true);
        return;

//        wxLogMessage("Font Settings");
}

void MyFrame::OnAutoSaveTime(wxCommandEvent& event)
{
	panel = new wxMDIParentFrame(this,-1,wxT("Font Settings"),wxPoint(450,250),wxSize(200,200),wxDEFAULT_FRAME_STYLE,wxFrameNameStr);
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
        wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);

        wxStaticText *C_Command = new wxStaticText(panel,wxID_ANY,wxT("Time\n(In Minutes):\t\n\t"),wxDefaultPosition,wxSize(70,-1));
        hbox1->Add(C_Command,0);

        SaveTime = new wxTextCtrl(panel,wxID_ANY,wxT(""),wxDefaultPosition,wxDefaultSize,wxTE_DONTWRAP);
        hbox1->Add(SaveTime,1);
        vbox->Add(hbox1,0,wxEXPAND|wxLEFT|wxRIGHT|wxTOP,10);

	wxBoxSizer *hbox4 = new wxBoxSizer(wxHORIZONTAL);
        wxButton *m_buttonReset = new wxButton(panel,96,wxT("Reset"));
        hbox4->Add(m_buttonReset);

        wxButton *m_buttonApply = new wxButton(panel,95,wxT("Apply"));
        hbox4->Add(m_buttonApply);

        wxButton *m_buttonCancel = new wxButton(panel,94,wxT("Cancel"));
        hbox4->Add(m_buttonCancel);
        vbox->Add(hbox4,0,wxALIGN_TOP|wxALIGN_RIGHT|wxRIGHT|wxBOTTOM,10);

        Bind(wxEVT_BUTTON,&MyFrame::OnButtonEventTimeReset,this,96);
        Bind(wxEVT_BUTTON,&MyFrame::OnButtonEventTimeApply,this,95);
        Bind(wxEVT_BUTTON,&MyFrame::OnButtonEventTimeCancel,this,94);

        panel->SetSizer(vbox);
        Center();
        panel->Show(true);

       // wxLogMessage("Auto Save Time");
}

//Help Menu
void MyFrame::OnHelp(wxCommandEvent& event)
{
	FILE *file;
	file = fopen("media/README.md","r");
	NoteBookFrame->AddWritePageToBook(this,file,wxT("Documentation"));

      //  wxLogMessage("Help");
}

void MyFrame::OnKeyBoardShortcuts(wxCommandEvent& event)
{
	panel = new wxMDIParentFrame(this,-1,wxT("KeyBoard Shortcuts"),wxPoint(450,250),wxSize(400,600),wxDEFAULT_FRAME_STYLE,wxFrameNameStr);
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
        wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
	wxString temp;

        wxStaticText *C_Command = new wxStaticText(panel,wxID_ANY,wxT("The following keyboard shortcuts are configurable\t\n\n"),wxDefaultPosition,wxSize(500,-1));
	hbox1->Add(C_Command,0);

	wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);

	wxTextCtrl *textbox = new wxTextCtrl(panel,wxID_ANY,wxT(" File\n"),wxPoint(10,30),wxSize(380,500),wxTE_MULTILINE|wxTE_DONTWRAP|wxTE_READONLY);

	temp << wxT(" New\t\tCtrl+N\n");
	temp << wxT(" Open\t\tCtrl+O\n");
	temp << wxT(" Save\t\tCtrl+S\n");
	temp << wxT(" SaveAs\t\t\n");
	temp << wxT(" SaveAll\t\tShift+Ctrl+S\n");
	temp << wxT(" Properties\t\t\n");
	temp << wxT(" Reload\t\tCtrl+R\n");
	temp << wxT(" Close\t\tCtrl+W\n");
	temp << wxT(" Close All\t\tCtrl+Shift+W\n");
	temp << wxT(" Quit\t\tCtrl+Q\n\n\n");

	temp << wxT(" Editor\n");
	temp << wxT(" Undo\t\tCtrl+Z\n");
	temp << wxT(" Redo\t\tCtrl+Y\n");
	temp << wxT(" Cut\t\tCtrl+X\n");
	temp << wxT(" Copy\t\tCtrl+C\n");
	temp << wxT(" Paste\t\tCtrl+V\n");
	temp << wxT(" Delete\t\t\n");
	temp << wxT(" Select All\t\tCtrl+A\n");
	temp << wxT(" Select words\t\tCtrl+Shift+(Left,Right Arrow \n\n\n");


	temp << wxT(" Search\n");
	temp << wxT(" Search\t\tCtrl+F\n");
	temp << wxT(" Goto Line\t\tCtrl+L\n\n\n");

	temp << wxT(" View\n");
	temp << wxT(" Toggle All Additional Widgets\n");
	temp << wxT(" FullScreen\t\tCtrl+F11\n");
	temp << wxT(" Toggle Messages window\n");
	temp << wxT(" Zoom In\t\tCtrl++\n");
	temp << wxT(" Zoom Out\t\tCtrl+-\n");
	temp << wxT(" Zoom Reset\t\tCtrl+0\n");
	temp << wxT(" Show Position\t\tCtrl+L");
	temp << wxT(" Page Information\t\t\t");

	temp << wxT(" Settings\n");
	temp << wxT(" Toggle Line wrapping\n");
	temp << wxT(" Toggle Line breaking\n");
	temp << wxT(" Read Only\n");
	temp << wxT(" Clone\n\n\n");

	temp << wxT(" Build\n");
	temp << wxT(" Compile\t\tF7\n");
	temp << wxT(" Build\t\tF8\n");
	temp << wxT(" Execute\t\tF9\n");
	temp << wxT(" Total Errors\n");
	temp << wxT(" Set Build Commands\n\n\n");

	temp << wxT(" Help\n");
	temp << wxT(" Help\t\tF1\n");

	textbox->AppendText(temp);
	textbox->SetInsertionPoint(1);
	hbox2->Add(C_Command,0);
	vbox->Add(hbox2,0,wxEXPAND|wxLEFT|wxRIGHT|wxTOP,10);

	panel->SetSizer(vbox);
        Center();
        panel->Show(true);

       // wxLogMessage("Key Board shortCuts");
}

void MyFrame::OnMessages(wxCommandEvent& event)
{
	wxMessageBox(wxT("Check Developers Github page on regular basis for updates ,you can also Send me suggestions or any Bug report on  mannjhariya@gmail.com Or you can Raise questions on Github!!"),wxT("Message!"), wxICON_INFORMATION);
       // wxLogMessage("Messages");
}
void MyFrame::OnGithub(wxCommandEvent& event)
{
	wxLaunchDefaultBrowser(wxT("github.com/manijhariya"));
//	wxLogMessage("Github");
}
void MyFrame::OnDonate(wxCommandEvent& event)
{
	wxMessageBox(wxT("Developers are working so hard to make you editor more easy to use and To make it come to your all expectations. So, if you want make donation something(like a pizza) you can mail me mannjhariya@gmail.com and will come to you for your treat!!"),wxT("Donate"),wxICON_INFORMATION);
//	wxLogMessage("Donate");
}
void MyFrame::OnAbout(wxCommandEvent& event)
{
	panel = new wxMDIParentFrame(this,-1,wxT("About"),wxDefaultPosition,wxSize(500,600),wxDEFAULT_FRAME_STYLE,wxFrameNameStr);
	wxPanel *newpanel = new wxPanel(panel,-1,wxPoint(0,10),wxSize(500,600),wxTAB_TRAVERSAL,wxT("newPanel"));
	wxTextCtrl *textbox1 = new wxTextCtrl(panel,-1,wxT("\n"),wxPoint(0,10),wxSize(500,150),wxTE_READONLY|wxTE_MULTILINE|wxNO_BORDER);
	wxTextAttr styletext;

//	styletext.SetAlignment(wxTEXT_ALIGNMENT_CENTER);
	textbox1->AppendText(wxT("CoderKing 0.0.1"));
	styletext.SetFontFaceName(wxT("Hack"));
	styletext.SetFontSize(40);
	styletext.SetFontWeight(wxFONTWEIGHT_BOLD);
	styletext.GetFontUnderlined();
	styletext.SetTextEffects(wxTEXT_ATTR_EFFECT_SUPERSCRIPT);
	styletext.SetAlignment(wxTEXT_ALIGNMENT_CENTER);

	textbox1->SetStyle(1,10,styletext);
	wxPanel *newpanel1 = new wxPanel(panel,-1,wxPoint(20,155),wxSize(480,400),wxTAB_TRAVERSAL,wxT("BottomPanel"));
	wxNotebook *notebook = new wxNotebook(newpanel1,-1,wxPoint(20,155),wxSize(480,250),0,wxT("new note"));
	wxTextCtrl *textbox2 = new wxTextCtrl(notebook,-1,wxT("\n"),wxPoint(0,170),wxSize(480,250),wxTE_READONLY|wxTE_MULTILINE|wxNO_BORDER);
	textbox2->AppendText("A Light weight,fast and realiable Text-Editor for C/C++\n");
	textbox2->AppendText("\"Coderking\"\n");
	textbox2->AppendText("(Build On Or After (2020)\n\n");
	textbox2->AppendText("Copyright (c) 2019-2020\n\n");
	textbox2->AppendText("Manish Kumar\n");
	textbox2->AppendText("All Right Reserved\n");


	wxTextCtrl *textbox3 = new wxTextCtrl(notebook,-1,wxT("\n"),wxPoint(500,180),wxSize(400,380),wxTE_READONLY|wxTE_MULTILINE|wxNO_BORDER|wxTE_DONTWRAP);
	textbox3->LoadFile("media/LICENSE",wxTEXT_TYPE_ANY);

	notebook->AddPage(textbox2,wxT("Info"));
	notebook->AddPage(textbox3,wxT("License"));
	newpanel->SetBackgroundStyle(wxBG_STYLE_SYSTEM);
	newpanel->SetHelpText(wxT("THis is sample about!"));

	wxBoxSizer* panelSizer = new wxBoxSizer(wxHORIZONTAL);
        panelSizer->Add(notebook, 1, wxEXPAND);
        panel->SetSizer(panelSizer);

        wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
        topSizer->SetMinSize(250, 100);
        topSizer->Add(newpanel1,1,wxGROW|wxALIGN_TOP);


//	wxMessageBox("This is  a wxWidgets' made code/text-editor with named as CoderKing",
//		     "About CoderKing",wxOK | wxICON_INFORMATION);

	panel->Show(true);
	panel->Centre();
//	SetStatusText("About Menu");
}
void MyFrame::OnButtonEventReset(wxCommandEvent& event)
{
	C_CommandEntry->SetValue("");
	B_CommandEntry->SetValue("");
	E_CommandEntry->SetValue("");
	//wxLogMessage("Reset Message");
}
void MyFrame::OnButtonEventCancel(wxCommandEvent& event)
{
	panel->Show(false);
//	wxLogMessage("Cancel Message");
}
void MyFrame::OnButtonEventApply(wxCommandEvent& event)
{
	if(C_CommandEntry->GetValue().empty() || B_CommandEntry->GetValue().empty() || E_CommandEntry->GetValue().empty())
	{	wxMessageBox(wxT("Fill all required field"),wxT("Warning!"),wxICON_WARNING); }
	else
	{
		compile_command = C_CommandEntry->GetValue();
		build_command = B_CommandEntry->GetValue();
		execute_command = E_CommandEntry->GetValue();
		return;
	}

//	wxLogMessage("Apply Message");

}
void MyFrame::OnButtonEventTimeReset(wxCommandEvent& event)
{
	SaveTime->SetValue("");
	return;
}
void MyFrame::OnButtonEventTimeCancel(wxCommandEvent& event)
{
	panel->Show(false);
}
void MyFrame::OnButtonEventTimeApply(wxCommandEvent& event)
{
	if(SaveTime->GetValue().empty()){
		wxString str = SaveTime->GetValue();
		int num = wxAtoi(str);
	if(num < 5)
	{
		wxMessageBox("Time Can't be empty And Less Than 5",wxT("Warning!"),wxICON_WARNING);	return;
	}	}
	else
	{
		AutoSaveTime = SaveTime->GetValue();
		wxMessageBox("New Auto Save has Applied",wxT("Information!"),wxICON_INFORMATION);
	}
	return;
}
