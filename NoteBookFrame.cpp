/////////////////////////////////////////////////////////////////////////////
// Name:        NoteBookFrame.cpp
// Purpose:     NotebookFrame.cpp file for text editor
// Author:      Manish Kumar
// Created:     21/06/20
// Copyright:   (c) Manish Kumar
// Licence:     GNU
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// It consist of all the function defination of class wxNotebook1Frame..
// ============================================================================
#include "main.h"

wxNotebook1Frame::wxNotebook1Frame(MyFrame* frame)
{
   //Constructor for initilising all the panels of the right-most panel and most important middle panel is initialised in here and they are 
   // Going to shown in the Main window
    panel = new wxPanel(frame, wxID_ANY,wxPoint(155,70),wxSize(600,575),wxTRANSPARENT_WINDOW,wxString("MyTabs"));
    notebook = new wxNotebook(panel, 30,wxDefaultPosition,wxSize(600,550),wxNB_BOTTOM,wxString("NewTab"));
    wxPanel *Statuspanel = new wxPanel(frame, wxID_ANY,wxPoint(760,70),wxSize(220,565),wxTRANSPARENT_WINDOW,wxString("LastTab"));
    wxNotebook *notebookStatus = new wxNotebook(Statuspanel,wxID_ANY,wxDefaultPosition,wxSize(220,565),wxNB_BOTTOM,wxString("1NewTab"));

    textbox1 = new wxTextCtrl(notebookStatus,-1,wxT("This Session\n"),wxDefaultPosition,wxDefaultSize,wxTE_MULTILINE|wxTE_DONTWRAP);
    textbox1->SetEditable(false);
    textbox2 = new wxTextCtrl(notebookStatus,-1,wxT("Compile Session\n"),wxDefaultPosition,wxDefaultSize,wxTE_MULTILINE|wxTE_DONTWRAP);
    textbox2->SetEditable(false);
    textbox3 = new wxTextCtrl(notebookStatus,-1,wxT("Your Working Time\n"),wxDefaultPosition,wxDefaultSize,wxTE_MULTILINE|wxTE_DONTWRAP);
    textbox3->SetEditable(false);

    notebookStatus->AddPage(textbox1,L"Status\n");
    notebookStatus->AddPage(textbox2,L"Compile\n");
    notebookStatus->AddPage(textbox3,L"Time\n");

    wxBoxSizer* panelSizer = new wxBoxSizer(wxHORIZONTAL);
    panelSizer->Add(notebookStatus, 1, wxEXPAND);
    frame->SetSizer(panelSizer);

    wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
    topSizer->Add(Statuspanel,1,wxGROW|wxALIGN_TOP);
}
int wxNotebook1Frame::getPageNumber()
{	//this function as a part of my page replacing and checking to which page has to be initilised when a new/open a file action
	// is going to happen!!
	for(int i=0;i<10;i++)
	{	if(Pages[i] == 0)
		{
			Pages[i] = 1;
			return i;
		}
		else
			continue;
	}
	return -1;
}
void wxNotebook1Frame::AddPageToBook(MyFrame* frame)
{
	// Add page to window(a empty page) with untitled name...
	int PageAdded = getPageNumber();
	if(PageAdded != -1){
    	AddedPage[PageAdded] = new TextFrame(notebook,PageAdded,wxT("Untitled"));
	frame->FileNames->Insert(wxT("Untitled"),PageAdded,1);
    	setSizer(frame);
    	const char text[] = "Added a new File With 'Untitled Name'";
    	time_t now = time(0);
    	char* dt = ctime(&now);
    	strcat(dt,text);
    	strcat(dt,";\n");
    	SetTabText((uint8_t)1,dt);
   	}
   else{
		wxLogMessage("Unable to add any more page");
	}

}
void wxNotebook1Frame::AddWritePageToBook(MyFrame* frame,FILE *file,wxString FileName)
{
    // The one is the result of open action in window... the  file is going to be with path you are going to select for the file//
    int PageAdded = getPageNumber();
     if(PageAdded != -1){
	AddedPage[PageAdded] = new TextFrame(notebook,file,PageAdded,FileName);
	frame->FileNames->Insert(FileName,PageAdded,1);
	setSizer(frame);
	char text[] = "A File Opened with Name:";
	time_t now = time(0);
	char* dt = ctime(&now);
	strcat(dt,text);
	strcat(dt,FileName);
	strcat(dt,";\n");
	SetTabText((uint8_t)1,dt);
	}
	else{

			wxLogMessage("Unable to add any more page");
	}

}
void wxNotebook1Frame::setSizer(MyFrame* frame)
{
   // Sizer for every new page which is going to add in the window ..
    wxBoxSizer* panelSizer = new wxBoxSizer(wxHORIZONTAL);
    panelSizer->Add(notebook, 1, wxEXPAND);
    frame->SetSizer(panelSizer);

    wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
    topSizer->SetMinSize(250, 100);
    topSizer->Add(panel,1,wxGROW|wxALIGN_TOP);
}
void wxNotebook1Frame::SetTabText(uint8_t TabNumber,const char text[])
{
	// write things in status and compile tabs!!
	switch(TabNumber)
	{
	   case 1:textbox1->AppendText(text);  break;
	   case 2:textbox2->AppendText(text);  break;
	   case 3:textbox3->AppendText(text);  break;
	   default:break;
	}
	return;
}

void MyFrame::timer(wxTimerEvent &event)
{
	//This is a simple timer which is going to sleep for 1 second and continuesly print or counting the seconds on the timer set
	// It is fully working but it is not going to show on the page because i couldn't understand the threads in wxWidgets but i am going 
	// To make that happen !!
	char c[30];
	int length;
		if(ss > 60)
		{
			ss = 0;
			if(mm > 60)
			{
				mm = 0;
			}
			else{  mm+=1;}
		}
		else
		{ ss += 1;}
		sprintf(c,"\nhh:%d mm:%d ss:%d",hh,mm,ss);
		length = NoteBookFrame->textbox3->GetLineLength(2);
		NoteBookFrame->textbox3->Remove(17,length);
		NoteBookFrame->textbox3->AppendText(c);
}

void wxNotebook1Frame::ClosePage(wxString FileName)
{
	// after closing the page it is going to write the things on status tab!!
	char text[] = "A File has closed with the name as:";
	time_t now = time(0);
	char* dt = ctime(&now);
	strcat(dt,text);
	strcat(dt,FileName);
	strcat(dt,";\n");
	SetTabText(1,dt);
	return;
}
wxNotebook1Frame::~wxNotebook1Frame()
{
	delete TextObject;
	delete textbox1;
	delete textbox2;
	delete textbox3;
	delete panel;

}
