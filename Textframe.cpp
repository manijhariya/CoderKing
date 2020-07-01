/////////////////////////////////////////////////////////////////////////////
// Name:        Textframe.cpp
// Purpose:     Textframe.cpp file for text editor
// Author:      Manish Kumar
// Created:     21/06/20
// Copyright:   (c) Manish Kumar
// Licence:     GNU
/////////////////////////////////////////////////////////////////////////////

// =========================================================================================================================
// All function defination of class TextFrame.. which is mostly the middle-most window(Pages!!)
// =========================================================================================================================
#include "main.h"

bool TextFrame::SaveText(wxString FilePath)
{
	//Save function .. for pages!

	return textbox->SaveFile(FilePath,wxTEXT_TYPE_ANY);
}
TextFrame::TextFrame(wxNotebook *notebook,FILE *file,int PageAdded,wxString FileName){
	//Opens and write the content of the existing file in page

        textbox = new wxTextCtrl(notebook,PageAdded,wxT("\t\t\t#Your Code Goes From Here..(erase me when you compile)\n"),wxDefaultPosition,wxDefaultSize,wxTE_MULTILINE);
	textbox->Bind(wxEVT_CHAR_HOOK,&TextFrame::NewLineText,this);
	wxString temp;
	temp << PageAdded << wxT("exi");
	notebook->AddPage(textbox,temp);
	char c;
	while ((c = getc(file)) != EOF){
        	textbox->AppendText(c);
	}
	fclose(file);
	textbox->CanUndo();
	textbox->Bind(wxEVT_CHAR_HOOK,&TextFrame::NewLineText,this);
	return;
}
TextFrame::TextFrame()
{}
TextFrame::TextFrame(wxNotebook *notebook,int PageAdded,wxString FileName)
{
	//Opens a new page empty with name as untitled...
	textbox = new wxTextCtrl(notebook,PageAdded,wxT("\t\t\tYour Code Goes From Here..(erase me when you compile)\n"),wxDefaultPosition,wxDefaultSize,wxTE_MULTILINE);
	textbox->Bind(wxEVT_CHAR_HOOK,&TextFrame::NewLineText,this);
	wxString temp;
	temp << PageAdded << wxT("new");
	notebook->AddPage(textbox,temp);
}
void TextFrame::NewLineText(wxKeyEvent& event)
{
	wxChar uc = event.GetUnicodeKey();
	if(uc != WXK_NONE)
	{
		if(uc == 317 || uc == 319 || uc == 318 || uc == 316 || uc == 13)
		{
			// For future references!!!
		}
	}
	else{}
	event.Skip();

}

void TextFrame::UndoOperation()
{
	//Referenced From ToolBar class same name for file
	textbox->Undo();
	//wxLogMessage("At undo operation");
}
void TextFrame::RedoOperation()
{
	//Referenced From ToolBar class same name for file
	textbox->Redo();
	//wxLogMessage("At Redo operation");

}
void TextFrame::CompileCode(wxString command)
{
	//Referenced From ToolBar class same name for file
	system(command);
	return;
}

void TextFrame::BuildCode(wxString command)
{
	//Referenced From ToolBar class same name for file
//	system("gnome-terminal -e 'sh -c \"ls && read i\"'");
	system(command);
	return;
}
void TextFrame::ExecuteCode(wxString command)
{
	//Referenced From ToolBar class same name for file
	system(command);
	return;
}
void TextFrame::JumpToLine(long int LineNumber)
{
	//Referenced From ToolBar class same name for file
	long int TotalLines = textbox->GetNumberOfLines();
	if(TotalLines >= LineNumber && LineNumber > 0){
		long Position = textbox->XYToPosition(2,LineNumber);
		textbox->SetInsertionPoint(Position);
		return;
	}
	else{
		wxLogMessage("Enter a valid Line Number");
		return;
		}
}
void TextFrame::FindLine(wxString word)
{
	//Referenced From ToolBar class same name for file
	long int i=0; long int TotalLines = textbox->GetNumberOfLines();
	wxString TextFromLine;
	int found;
	while(i <= TotalLines){
		TextFromLine = textbox->GetLineText(i);
		found = TextFromLine.Find(word);
		if(found != wxNOT_FOUND){
			wxLogMessage("word found");
			JumpToLine(i); return;}
		else{
			continue; }
	i++;
	}
	wxLogMessage("Word Not found in Text");
	return;
}
void TextFrame::SetReadOnly()
{
	//Referenced From ToolBar class same name for file
	if(textbox->IsEditable())
		textbox->SetEditable(false);
	else
		textbox->SetEditable(true);
}
TextFrame::~TextFrame()
{
}
