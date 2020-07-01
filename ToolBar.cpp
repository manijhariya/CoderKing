/////////////////////////////////////////////////////////////////////////////
// Name:        ToolBar.cpp
// Purpose:     ToolBar file for text editor
// Author:      Manish Kumar
// Created:     21/06/20
// Copyright:   (c) Manish Kumar
// Licence:     GNU
/////////////////////////////////////////////////////////////////////////////

// ======================================================================================
// All function definations which is are showing in the toolbar has implimantation here!!
// ======================================================================================

#include "main.h"

Toolbar::Toolbar(MyFrame* frame)
{
	toolframe = frame;
	wxImage::AddHandler(new wxPNGHandler);
//Adding images in the toolbar with the text showing in bottom of all............
	wxBitmap exit(wxT("media/exit.png"),wxBITMAP_TYPE_PNG);
	wxBitmap newb(wxT("media/new.png"),wxBITMAP_TYPE_PNG);
	wxBitmap open(wxT("media/open.png"),wxBITMAP_TYPE_PNG);
	wxBitmap save(wxT("media/save.png"),wxBITMAP_TYPE_PNG);
	wxBitmap load(wxT("media/load.png"),wxBITMAP_TYPE_PNG);
	wxBitmap revert(wxT("media/revert.png"),wxBITMAP_TYPE_PNG);
	wxBitmap close(wxT("media/close.png"),wxBITMAP_TYPE_PNG);
	wxBitmap undo(wxT("media/undo.png"),wxBITMAP_TYPE_PNG);
	wxBitmap redo(wxT("media/redo.png"),wxBITMAP_TYPE_PNG);
	wxBitmap compile(wxT("media/compile.png"),wxBITMAP_TYPE_PNG);
	wxBitmap build(wxT("media/build.png"),wxBITMAP_TYPE_PNG);
	wxBitmap execute(wxT("media/execute.png"),wxBITMAP_TYPE_PNG);
	wxBitmap find(wxT("media/find.png"),wxBITMAP_TYPE_PNG);
	wxBitmap jumpto(wxT("media/jumpto.png"),wxBITMAP_TYPE_PNG);

	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

	toolbar = new wxToolBar(frame,wxID_ANY,wxPoint(5,0),wxSize(100,70),wxTB_TEXT);
	//Adding all images to the toolbar..
	toolbar->AddTool(1,wxT("New"),newb);
	toolbar->AddTool(2,wxT("Open"),open);
	toolbar->AddTool(3,wxT("Save"),save);
	toolbar->AddTool(5,wxT("Revert"),revert);
	toolbar->AddTool(6,wxT("Close"),close);
	toolbar->AddTool(7,wxT("Undo"),undo);
	toolbar->AddTool(8,wxT("Redo"),redo);
	toolbar->AddTool(9,wxT("Compile"),compile);
	toolbar->AddTool(10,wxT("Build"),build);
	toolbar->AddTool(11,wxT("Execute"),execute);
	toolbar->AddTool(12,wxT("Find"),find);
	toolbar->AddTool(13,wxT("Jump To"),jumpto);
	toolbar->AddTool(14,wxT("Quit"),exit);

	toolbar->SetToolShortHelp(1,"Open a new file");
	toolbar->SetToolShortHelp(2,"Open a existing file");
	toolbar->SetToolShortHelp(3,"Save current file");
	toolbar->SetToolShortHelp(5,"Reload current file");
	toolbar->SetToolShortHelp(6,"Close current file");
	toolbar->SetToolShortHelp(7,"Undo recent action");
	toolbar->SetToolShortHelp(8,"Redo recent action");
	toolbar->SetToolShortHelp(9,"Compile current file");
	toolbar->SetToolShortHelp(10,"Build current file");
	toolbar->SetToolShortHelp(11,"Execute current Build file");
	toolbar->SetToolShortHelp(12,"Find a word/keyword");
	toolbar->SetToolShortHelp(13,"Jump to a line");
	toolbar->SetToolShortHelp(14,"Quit from CoderKing");

	toolbar->Realize();

	vbox->Add(toolbar,0,wxEXPAND);
	frame->SetSizer(vbox);

	// Binding as a main event in main window!!
	frame->Bind(wxEVT_MENU,&MyFrame::OnNew,frame,1);
	frame->Bind(wxEVT_MENU,&MyFrame::OnOpen,frame,2);
	frame->Bind(wxEVT_MENU,&Toolbar::OnSaveAs,this,3);
	frame->Bind(wxEVT_MENU,&Toolbar::OnReload,this,5);
	frame->Bind(wxEVT_MENU,&Toolbar::OnClose,this,6);
	frame->Bind(wxEVT_MENU,&Toolbar::OnUndo,this,7);
	frame->Bind(wxEVT_MENU,&Toolbar::OnRedo,this,8);
	frame->Bind(wxEVT_MENU,&Toolbar::OnCompile,this,9);
	frame->Bind(wxEVT_MENU,&Toolbar::OnBuild,this,10);
	frame->Bind(wxEVT_MENU,&Toolbar::OnExecute,this,11);
	frame->Bind(wxEVT_MENU,&Toolbar::OnFind,this,12);
	frame->Bind(wxEVT_MENU,&Toolbar::OnJump,this,13);
	frame->Bind(wxEVT_MENU,&Toolbar::OnQuit,this,14);

}
int Toolbar::getId()
{
	//Going to return the id of page in which user has currently focused!!
	wxWindow *temperary = toolframe->FindFocus();
	wxWindow *temp = temperary->GetParent();
	if(temp->GetId() == 30)
	{
		return temperary->GetId();
	}
	else
		return -1;
}
bool Toolbar::SaveCheck(int te)
{
	//Save check if the page is saved or not !!
	return strcmp(toolframe->FileNames->Item(te),("Untitled"));
}
void Toolbar::OnSaveAs(wxCommandEvent& event)
{
	//Save action for toolbar 
	int id = getId();
	if(id == -1) {return;}
	else{
		if(!SaveCheck(id))
		{
			wxFileDialog saveFileDialog(toolframe,("Save Program/Script file"),"","","",wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
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
				toolframe->FileNames->Insert(temp,id,1);
				toolframe->NoteBookFrame->AddedPage[id]->SaveText(toolframe->FileNames->Item(id));
				time_t now = time(0);
       			 	char* dt = ctime(&now);
       		 		const char text[] = "File Saved with Name:";
        			strcat(dt,text);
		        	strcat(dt,toolframe->FileNames->Item(id));
        			strcat(dt,";\n");
	         		toolframe->NoteBookFrame->SetTabText((uint8_t)1,dt);
				toolframe->SetStatusText(toolframe->FileNames->Item(id));
				wxString tempfile = toolframe->FileNames->Item(id);
                                tempfile << id << wxT(".ckg");
                                remove(tempfile);

			}
		}
		else {
			toolframe->NoteBookFrame->AddedPage[id]->SaveText(toolframe->FileNames->Item(id));
			wxString tempfile = toolframe->FileNames->Item(id);
                        tempfile << wxT(".ckg");
                        remove(tempfile);
			return; }
		toolframe->SetStatusText("Org",2);
	}
}
void Toolbar::OnReload(wxCommandEvent& event){
	//Reload action from toolbar
	toolframe->ReloadPage(event);
}
void Toolbar::OnClose(wxCommandEvent& event){
	//Closing focused page 
	int id = getId();
	if(id == -1) {} // -1 if no page is focused ...
	else{
	wxWindow *temparary = toolframe->FindFocus();
	if(SaveCheck(id))
	{
		delete temparary;
		toolframe->NoteBookFrame->Pages[id] = 0;  }
	else
	    { wxMessageDialog *savedialog = new wxMessageDialog(toolframe,wxT("File is not Saved,Save your file first"),wxT("Save"),wxOK|wxCANCEL);
		 int dialog = savedialog->ShowModal();
		if(dialog == wxID_OK)
		{	return; }
		else{	delete temparary;
			toolframe->NoteBookFrame->Pages[id] = 0;}
	    }

	toolframe->NoteBookFrame->ClosePage(toolframe->FileNames->Item(id));
	}
	return;
}
void Toolbar::OnUndo(wxCommandEvent& event){
	//Undo which is referencing/calling the function of another class which is of TextFrame... refer to TextFrame.cpp for more!!
        int id = getId();
	if(id == -1)	{return;}
	else
		toolframe->NoteBookFrame->AddedPage[id]->UndoOperation();
	return;
}
void Toolbar::OnRedo(wxCommandEvent& event){
	//Redo which is referencing/calling the function of another class which is of TextFrame... refer to TextFrame.cpp for more!!
	int id = getId();
	if(id == -1) {return;}
                toolframe->NoteBookFrame->AddedPage[id]->RedoOperation();
}
void Toolbar::OnCompile(wxCommandEvent& event){
	//Compile code which is going to make the command for Compile and it is referencing/calling the function of another class which is of TextFrame... refer to TextFrame.cpp for more!!
		int id = getId();
	if(id == -1)	{return;}
	else{
		if(SaveCheck(id)){
		wxString temp_command = wxT("gnome-terminal -e ' sh -c \" ");
		temp_command <<toolframe->compile_command << toolframe->FileNames->Item(id) << wxT(" &&echo Comiplied &&read x\"'");
                toolframe->NoteBookFrame->AddedPage[id]->CompileCode(temp_command);
		time_t now = time(0);
                char *dt = ctime(&now);
                const char text[] = "Compiled File ";
                strcat(dt,text);
                strcat(dt,toolframe->FileNames->Item(id));
                strcat(dt,";\n");
                toolframe->NoteBookFrame->SetTabText(2,text);
		return; }
		else{
			wxLogMessage("Save Your File first"); return; }
	}
}
void Toolbar::OnBuild(wxCommandEvent& event){
	//Build code which is going to make the command for build and it is referencing/calling the function of another class which is of TextFrame... refer to TextFrame.cpp for more!!
		int id = getId();
	if(id == -1) {return;}
	else{
		if(SaveCheck(id)){
			wxString temp_filename = toolframe->FileNames->Item(id);
			temp_filename.Replace(wxT(".cpp"),wxT(""));
			temp_filename.Replace(wxT(".c"),wxT(""));
			wxString temp_command = wxT("gnome-terminal -e ' sh -c \" ");
			temp_command <<toolframe->build_command << toolframe->FileNames->Item(id) << wxT(" -o ")<< temp_filename << wxT(" && echo build Press any key to exit && read i\"'");
			toolframe->NoteBookFrame->AddedPage[id]->BuildCode(temp_command);
			time_t now = time(0);
                        char *dt = ctime(&now);
                        const char text[] = "Build File ";
                        strcat(dt,text);
                        strcat(dt,toolframe->FileNames->Item(id));
                        strcat(dt,";\n");
                        toolframe->NoteBookFrame->SetTabText(2,text);
			return;
		}
		else{
			wxLogMessage("You should Save Your File First");
			return; }
	}
}
void Toolbar::OnExecute(wxCommandEvent& event){
	//Execute code which is going to make the command for Execute and it is referencing/calling the function of another class which is of TextFrame... refer to TextFrame.cpp for more!!
	int id = getId();
	if(id == -1)  {return;}
	else{
		if(SaveCheck(id)){
			wxString temp_command = wxT("gnome-terminal -e ' sh -c \" ");
			wxString temp_filename = toolframe->FileNames->Item(id);
                        temp_filename.Replace(wxT(".cpp"),wxT(""));
			temp_filename.Replace(wxT(".c"),wxT(""));

			temp_command <<toolframe->execute_command << temp_filename << wxT(" && echo execute Press any key to exit && read i\" '");
                	toolframe->NoteBookFrame->AddedPage[id]->ExecuteCode(temp_command);
			time_t now = time(0);
			char *dt = ctime(&now);
		      	const char text[] = "Executed File ";
			strcat(dt,text);
			strcat(dt,toolframe->FileNames->Item(id));
			strcat(dt,";\n");
			toolframe->NoteBookFrame->SetTabText(2,text);
			return;  }
		else{
			wxLogMessage("You should Save your File First"); return;}
        }
}
void Toolbar::OnJump(wxCommandEvent& event){
	// Line jumping or setting insertion point for which user want to look...
        id = getId();
	if(id == -1)
		return;
	else{
	panel = new wxMDIParentFrame(toolframe,-1,wxT("Jumpe Line"),wxPoint(450,250),wxSize(200,200),wxDEFAULT_FRAME_STYLE,wxFrameNameStr);
        wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
        wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);

        wxStaticText *C_Command = new wxStaticText(panel,wxID_ANY,wxT("Line Number:\t\n\t"),wxDefaultPosition,wxSize(70,-1));
        hbox1->Add(C_Command,0);

        SaveTime = new wxTextCtrl(panel,wxID_ANY,wxT(""),wxDefaultPosition,wxDefaultSize,wxTE_DONTWRAP);
        hbox1->Add(SaveTime,1);
        vbox->Add(hbox1,0,wxEXPAND|wxLEFT|wxRIGHT|wxTOP,10);

	wxBoxSizer *hbox4 = new wxBoxSizer(wxHORIZONTAL);
	wxButton *m_buttonApply = new wxButton(panel,80,wxT("Cancel"));
        hbox4->Add(m_buttonApply);

        wxButton *m_buttonCancel = new wxButton(panel,81,wxT("Ok"));
        hbox4->Add(m_buttonCancel);
        vbox->Add(hbox4,0,wxALIGN_TOP|wxALIGN_RIGHT|wxRIGHT|wxBOTTOM,10);

        toolframe->Bind(wxEVT_BUTTON,&Toolbar::OnButtonEventLineReset,this,80);
        toolframe->Bind(wxEVT_BUTTON,&Toolbar::OnButtonEventLineOk,this,81);

	panel->SetSizer(vbox);
        panel->Center();
        panel->Show(true);
	}
}
void Toolbar::OnButtonEventLineReset(wxCommandEvent& event)
{
	SaveTime->SetValue("");
}
void Toolbar::OnButtonEventLineOk(wxCommandEvent& event)
{
		wxString temp = SaveTime->GetValue();
		toolframe->NoteBookFrame->AddedPage[id]->JumpToLine(wxAtoi(temp));
		panel->Close();
}

void Toolbar::OnFind(wxCommandEvent& event){
	// Finding the word enter by user or setting insertion point for which user want to look...
	id = getId();
        if(id == -1)
                return;
        else{
        panel = new wxMDIParentFrame(toolframe,-1,wxT("Find Word"),wxPoint(450,250),wxSize(200,200),wxDEFAULT_FRAME_STYLE,wxFrameNameStr);
        wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
        wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);

        wxStaticText *C_Command = new wxStaticText(panel,wxID_ANY,wxT("A word:\t\n\t"),wxDefaultPosition,wxSize(70,-1));
        hbox1->Add(C_Command,0);

        SaveTime = new wxTextCtrl(panel,wxID_ANY,wxT(""),wxDefaultPosition,wxDefaultSize,wxTE_DONTWRAP);
        hbox1->Add(SaveTime,1);
        vbox->Add(hbox1,0,wxEXPAND|wxLEFT|wxRIGHT|wxTOP,10);

        wxBoxSizer *hbox4 = new wxBoxSizer(wxHORIZONTAL);
        wxButton *m_buttonApply = new wxButton(panel,82,wxT("Cancel"));
        hbox4->Add(m_buttonApply);

        wxButton *m_buttonCancel = new wxButton(panel,83,wxT("Ok"));
        hbox4->Add(m_buttonCancel);
        vbox->Add(hbox4,0,wxALIGN_TOP|wxALIGN_RIGHT|wxRIGHT|wxBOTTOM,10);

        toolframe->Bind(wxEVT_BUTTON,&Toolbar::OnButtonEventFindReset,this,82);
        toolframe->Bind(wxEVT_BUTTON,&Toolbar::OnButtonEventFindOk,this,83);

        panel->SetSizer(vbox);
        panel->Center();
        panel->Show(true);
	}
}
void Toolbar::OnButtonEventFindReset(wxCommandEvent& event)
{
        SaveTime->SetValue("");
}
void Toolbar::OnButtonEventFindOk(wxCommandEvent& event)
{
                wxString temp = SaveTime->GetValue();
                toolframe->NoteBookFrame->AddedPage[id]->FindLine(temp);
                panel->Close();
}

void Toolbar::OnQuit(wxCommandEvent& event){
	toolframe->Close(true);
}
Toolbar::~Toolbar()
{
	delete toolframe;
	delete SaveTime;
	delete toolbar;
	delete panel;
}
