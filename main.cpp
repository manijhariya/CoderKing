/////////////////////////////////////////////////////////////////////////////
// Name:        main.cpp
// Purpose:     Main file for text editor
// Author:      Manish Kumar
// Created:     21/06/20
// Copyright:   (c) Manish Kumar
// Licence:     GNU
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// Driver function
// ============================================================================

#include "main.h"

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
        MyFrame *frame = new MyFrame();
        frame->Show(true);
	SetTopWindow(frame);
//	frame->SetSizerAndFit();
        return true;
}
