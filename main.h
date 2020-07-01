/////////////////////////////////////////////////////////////////////////////
// Name:        main.h
// Purpose:     Main.h file for text editor
// Author:      Manish Kumar
// Created:     21/06/20
// Copyright:   (c) Manish Kumar
// Licence:     GNU
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// Driver Declaration
// ============================================================================

#ifndef __main__
#define __main__
#include <wx/wx.h>
#include "GUIFrame.h"

class MyApp: public wxApp
{
        public:
                virtual bool OnInit();
};

#endif
