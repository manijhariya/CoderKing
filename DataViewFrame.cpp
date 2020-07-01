/////////////////////////////////////////////////////////////////////////////
// Name:        DataViewFrame.cpp
// Purpose:     DataViewFrame file for text editor
// Author:      Manish Kumar
// Created:     21/06/20
// Copyright:   (c) Manish Kumar
// Licence:     GNU
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// All Left-Most panel's functions for main window.. 
// ============================================================================
#include "main.h"
#include <wx/dataview.h>
#include <wx/hashset.h>

// This class is actually not fully complete is a by default code which is a sample code by wxWidgets.. I couldn't just get the code
// so not fully customised this code but it is going to get working.
class TreeFrame;
enum identifiers{
	IDTREEAPP = wxID_HIGHEST + 1,
	IDDATAVIEW = wxID_HIGHEST + 2,
	IDREDO = wxID_HIGHEST + 3
};

WX_DECLARE_HASH_SET(wxString,wxStringHash,wxStringEqual,StringHash);
StringHash strings;
	wxStringCharType* asPointer(const wxString s){
	if(s.length() < 2){
		return NULL;
	}
	strings.insert(s);
	StringHash::iterator it = strings.find(s);
	assert(it != strings.end());
	wxStringCharType* res = const_cast<wxStringCharType* >(it->wx_str());
		return res;
	}

class TestModel:public wxDataViewModel{
	public:
		std::vector<std::string>* FileNames;
		TestModel(std::vector<std::string>* Files):wxDataViewModel(),topic(0) {
				FileNames = Files;
				}
		~TestModel() {}
		unsigned int GetColumnCount() const{
			return 1;
		}
		wxString GetColumnType(unsigned int column) const{
			return "string";
		}
		void GetValue(wxVariant& val,const wxDataViewItem& item,unsigned int column) const{
		wxVariant v(_asString(item));
			val = v;
		}
		bool SetValue(const wxVariant& val,const wxDataViewItem& item,unsigned int column){
			return true;
		}
		wxDataViewItem GetParent(const wxDataViewItem& item) const{
			wxString par = _asString(item);
			if(par.length() != 1) {
				return wxDataViewItem(asPointer(par.Left(par.length() - 1)));
				}
			return wxDataViewItem(NULL);
		}
		bool IsContainer(const wxDataViewItem& item) const {
			wxString par = _asString(item);
			return (par.length() < 3);
		}
		unsigned GetChildren(const wxDataViewItem& item,wxDataViewItemArray& children)  const {
			wxString par = _asString(item);
			if(topic == 0 or par.length() == 3){
				return 0;
			}
			children.Add(wxDataViewItem(asPointer(par + "a")));
			children.Add(wxDataViewItem(asPointer(par + "b")));
			children.Add(wxDataViewItem(asPointer(par + "c")));
			return 3;
		}
		void setTopic(int ptopic){
			topic = ptopic;
			if(topic > 1){
				Cleared();
			}
		}
		int topic = 0;
		private:
			wxString _asString(const wxDataViewItem& item) const {
			if(item.IsOk()){
					return static_cast<wxStringCharType*>(item.GetID());
				}
			wxStringCharType ch = '.' + topic;
			return wxString(ch);
		}
};
class TreeFrame:public wxFrame{
	public:
		TreeFrame(MyFrame* frame)
		{
			_sizer = new wxFlexGridSizer(650,1,1);
			dataView = new wxDataViewCtrl(frame,IDDATAVIEW,wxPoint(7,70),wxSize(150,575),wxDV_NO_HEADER | wxDV_VARIABLE_LINE_HEIGHT);
			wxDataViewTextRenderer* rend0 = new wxDataViewTextRenderer("string",wxDATAVIEW_CELL_EDITABLE);
			_column0 = new wxDataViewColumn("string",rend0,0,100,wxAlignment(wxALIGN_LEFT | wxALIGN_TOP),wxDATAVIEW_COL_RESIZABLE);
			dataView->AppendColumn(_column0);
			dataView->SetExpanderColumn(_column0);
			_sizer->Add(dataView);
			frame->SetSizer(_sizer,true);
		}
		void OnRedo(){
		testModel->setTopic(testModel->topic + 1);
	}
	TestModel* testModel;
	wxDataViewCtrl* dataView;
	private:
		wxFlexGridSizer* _sizer;
		wxDataViewColumn* _column0;
};

TreeApp::TreeApp(){}
bool TreeApp::OnInit(MyFrame *frame,std::vector<std::string>* s){
	 _treeFrame = new TreeFrame(frame);
	_treeFrame->testModel = new TestModel(s);
	_treeFrame->dataView->AssociateModel(_treeFrame->testModel);
	_treeFrame->testModel->setTopic(1);
	_treeFrame->OnRedo();
	return true;
}
TreeApp::~TreeApp()
{
	delete _treeFrame;
}
