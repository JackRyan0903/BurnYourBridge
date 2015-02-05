//**************************************************************************/
// Copyright (c) 1998-2007 Autodesk, Inc.
// All rights reserved.
// 
// These coded instructions, statements, and computer programs contain
// unpublished proprietary information written by Autodesk, Inc., and are
// protected by Federal copyright law. They may not be disclosed to third
// parties or copied or duplicated in any form, in whole or in part, without
// the prior written consent of Autodesk, Inc.
//**************************************************************************/
// DESCRIPTION: Appwizard generated plugin
// AUTHOR: 
//***************************************************************************/

#include "BYBFileExporter.h"

//3DS MAX PLUGIN 고유 아이디_3DS MAX SDK -> HELP -> GENID로 생성
#define BYBFileExporter_CLASS_ID	Class_ID(0x66d827f4, 0x10ec7e8d)

class BYBFileExporter : public SceneExport {
public:
	BYBExporter m_bybExporter;

	//Constructor/Destructor
	BYBFileExporter();
	~BYBFileExporter();

	int				ExtCount();					// Number of extensions supported
	const TCHAR *	Ext(int n);					// Extension #n (i.e. "3DS")
	const TCHAR *	LongDesc();					// Long ASCII description (i.e. "Autodesk 3D Studio File")
	const TCHAR *	ShortDesc();				// Short ASCII description (i.e. "3D Studio")
	const TCHAR *	AuthorName();				// ASCII Author name
	const TCHAR *	CopyrightMessage();			// ASCII Copyright message
	const TCHAR *	OtherMessage1();			// Other message #1
	const TCHAR *	OtherMessage2();			// Other message #2
	unsigned int	Version();					// Version number * 100 (i.e. v3.01 = 301)
	void			ShowAbout(HWND hWnd);		// Show DLL's "About..." box

	BOOL SupportsOptions(int ext, DWORD options);
	int  DoExport(const TCHAR *name,ExpInterface *ei,Interface *i, BOOL suppressPrompts=FALSE, DWORD options=0);
};



class BYBFileExporterClassDesc : public ClassDesc2 
{
public:
	virtual int IsPublic() 							{ return TRUE; }
	virtual void* Create(BOOL /*loading = FALSE*/) 		{ return new BYBFileExporter(); }
	virtual const TCHAR *	ClassName() 			{ return GetString(IDS_CLASS_NAME); }
	virtual SClass_ID SuperClassID() 				{ return SCENE_EXPORT_CLASS_ID; }
	virtual Class_ID ClassID() 						{ return BYBFileExporter_CLASS_ID; }
	virtual const TCHAR* Category() 				{ return GetString(IDS_CATEGORY); }

	virtual const TCHAR* InternalName() 			{ return _T("BYBFileExporter"); }	// returns fixed parsable name (scripter-visible name)
	virtual HINSTANCE HInstance() 					{ return hInstance; }					// returns owning module handle
	

};


ClassDesc2* GetBYBFileExporterDesc() { 
	static BYBFileExporterClassDesc BYBFileExporterDesc;
	return &BYBFileExporterDesc; 
}





INT_PTR CALLBACK BYBFileExporterOptionsDlgProc(HWND hWnd,UINT message,WPARAM,LPARAM lParam) {
	static BYBFileExporter* imp = nullptr;

	switch(message) {
		case WM_INITDIALOG:
			imp = (BYBFileExporter *)lParam;
			CenterWindow(hWnd,GetParent(hWnd));
			return TRUE;

		case WM_CLOSE:
			EndDialog(hWnd, 0);
			return 1;
	}
	return 0;
}


//--- BYBFileExporter -------------------------------------------------------
BYBFileExporter::BYBFileExporter()
{

}

BYBFileExporter::~BYBFileExporter() 
{

}

int BYBFileExporter::ExtCount()
{
	//#pragma message(TODO("Returns the number of file name extensions supported by the plug-in."))
	return 1;
}

const TCHAR *BYBFileExporter::Ext(int /*i*/)
{		
	//#pragma message(TODO("Return the 'i-th' file name extension (i.e. \"3DS\")."))
	return _T("BFE");
}

const TCHAR *BYBFileExporter::LongDesc()
{
	//#pragma message(TODO("Return long ASCII description (i.e. \"Targa 2.0 Image File\")"))
	return _T("");
}
	
const TCHAR *BYBFileExporter::ShortDesc() 
{			
	//#pragma message(TODO("Return short ASCII description (i.e. \"Targa\")"))
	return _T("Burn Your Bridge File Export");
}

const TCHAR *BYBFileExporter::AuthorName()
{			
	//#pragma message(TODO("Return ASCII Author name"))
	return _T("");
}

const TCHAR *BYBFileExporter::CopyrightMessage() 
{	
	//#pragma message(TODO("Return ASCII Copyright message"))
	return _T("");
}

const TCHAR *BYBFileExporter::OtherMessage1() 
{		
	//TODO: Return Other message #1 if any
	return _T("");
}

const TCHAR *BYBFileExporter::OtherMessage2() 
{		
	//TODO: Return other message #2 in any
	return _T("");
}

unsigned int BYBFileExporter::Version()
{				
	//#pragma message(TODO("Return Version number * 100 (i.e. v3.01 = 301)"))
	return 100;
}

void BYBFileExporter::ShowAbout(HWND /*hWnd*/)
{			
	// Optional
}

BOOL BYBFileExporter::SupportsOptions(int /*ext*/, DWORD /*options*/)
{
	//#pragma message(TODO("Decide which options to support.  Simply return true for each option supported by each Extension the exporter supports."))
	return TRUE;
}


int	BYBFileExporter::DoExport(const TCHAR* /*name*/, ExpInterface* /*ei*/, Interface* /*ip*/, BOOL suppressPrompts, DWORD /*options*/)
{
	//#pragma message(TODO("Implement the actual file Export here and"))

	if(!suppressPrompts)
		DialogBoxParam(hInstance, 
				MAKEINTRESOURCE(IDD_PANEL), 
				GetActiveWindow(), 
				BYBFileExporterOptionsDlgProc, (LPARAM)this);

	#pragma message(TODO("return TRUE If the file is exported properly"))
	return FALSE;
}


