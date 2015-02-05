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





INT_PTR CALLBACK BYBFileExporterOptionsDlgProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam) {
	static BYBFileExporter* imp = nullptr;

	WPARAM wLoParam = LOWORD(wParam);
	WPARAM wHiParam = HIWORD(wParam);

	switch(message) {
		case WM_INITDIALOG:
			imp = (BYBFileExporter *)lParam;
			CenterWindow(hWnd,GetParent(hWnd));
			return TRUE;

		case WM_CLOSE:
			EndDialog(hWnd, 0);
			return 1;

		case WM_COMMAND:
			if(imp && IDC_EXPORT_BUTTON == wLoParam)
			{
				imp->m_bybExporter.m_doExport = true;
				SendMessage(hWnd, WM_CLOSE, 0, 0);
			}

		return true;
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


int	BYBFileExporter::DoExport(const TCHAR *sFile,ExpInterface *ei,Interface *pi, BOOL suppressPrompts, DWORD options)
{
	if(!suppressPrompts)
		DialogBoxParam(hInstance, 
				MAKEINTRESOURCE(IDD_PANEL), 
				GetActiveWindow(), 
				BYBFileExporterOptionsDlgProc, (LPARAM)this);


	if(FALSE == m_bybExporter.m_doExport)
		return FALSE;

	int		n = 0;
	int		i =0;


	m_bybExporter.m_expInterface	= ei;
	m_bybExporter.m_interface		= pi;
	m_bybExporter.m_suppressPrompt	= suppressPrompts;
	m_bybExporter.m_options			= options;


	// 0. Prepare: 파일 이름 설정
	memset(m_bybExporter.m_binaryFileName, 0, sizeof(m_bybExporter.m_binaryFileName));	// Export Binary File Name
	memset(m_bybExporter.m_textFileName, 0, sizeof(m_bybExporter.m_textFileName));	// Export Text File Name
	_tcscpy(m_bybExporter.m_binaryFileName, sFile);


	// 파일이름 소문자 전환
	TCHAR *s = (TCHAR*)sFile;
	TCHAR *e = (TCHAR*)sFile;
	TCHAR *d = (TCHAR*)m_bybExporter.m_binaryFileName;

	e+= _tcslen( m_bybExporter.m_binaryFileName );
	for( ; s<e; ++s, ++d)
		*d = tolower(*s);


	// 0. 파일 이름 설정
	m_bybExporter.FileRename(m_bybExporter.m_textFileName, m_bybExporter.m_binaryFileName, NULL, _T("bybt"));



	// 0. 헤더의 정보를 모은다.
	int		 iTick = GetTicksPerFrame();
	Interval range = m_bybExporter.m_interface->GetAnimRange();

	m_bybExporter.m_head.SetFrameInfo(HeadInfo::START_FRAME, range.Start() / iTick);
	m_bybExporter.m_head.SetFrameInfo(HeadInfo::END_FRAME, range.End() / iTick);
	m_bybExporter.m_head.SetFrameInfo(HeadInfo::FRAME_RATE, GetFrameRate());
	m_bybExporter.m_head.SetFrameInfo(HeadInfo::TICK_FRAME, iTick);




	// 1. Gather Node
	INode*	pRoot = m_bybExporter.m_interface->GetRootNode();
	m_bybExporter.NodeGather(pRoot);


	// 2. Create Geometry
	m_bybExporter.m_head.SetNumberOfGeometry(m_bybExporter.m_maxNode.size());
	if(m_bybExporter.m_head.GetNumberOfGeometry()<1)
		return -1;

	int nGeom=m_bybExporter.m_head.GetNumberOfGeometry();

	//m_pI->ProgressStart(_T("Exporting Acm File..."), TRUE, fn, NULL);
	m_bybExporter.m_geometry=new Geometry[m_bybExporter.m_head.GetNumberOfGeometry()];


	// 3. Binding Bone to LcGeo
	for(n =0; n<nGeom; ++n)
	{
		Geometry*	pGeom = &m_bybExporter.m_geometry[n];
		INode*	pNode = m_bybExporter.m_maxNode[n];
		pGeom->m_pNode=pNode;

		TCHAR*	sName  = (TCHAR*)pNode->GetName();
		_stprintf(pGeom->m_nodeName, sName);
	}


	//m_pI->ProgressUpdate(2, TRUE, _T("Prepare"));

	// 4. Bone or Not
	for(n =0; n<nGeom; ++n)
	{
		Geometry*	pGeom = &m_bybExporter.m_geometry[n];
		m_bybExporter.SetBone(pGeom);
	}


	// 5. Setup Parent Index
	for(n =0; n<nGeom; ++n)
	{
		Geometry*	pGeom = &m_bybExporter.m_geometry[n];
		m_bybExporter.SetParentIndex(pGeom);
	}


	// 6. Physique or Skinning을 설정한다.
	for(i=0; i<nGeom; ++i)
	{
		Geometry*	pGeom	= &m_bybExporter.m_geometry[i];
		m_bybExporter.SetBoneWeight(pGeom);
	}


	//m_pI->ProgressUpdate(4, TRUE, _T("Setup Mesh"));

	// 7. Setup Geometry
	for(n =0; n<nGeom; ++n)
	{
		Geometry*	pGeom = &m_bybExporter.m_geometry[n];
		m_bybExporter.SetGeometry(pGeom);
	}



	// 8. Setup Animation
	for(n =0; n<nGeom; ++n)
	{
		//m_pI->ProgressUpdate(6 + int(float(n*92)/m_Header.nGeo), TRUE, _T("Setup Animation"));

		Geometry*	pGeom = &m_bybExporter.m_geometry[n];
		m_bybExporter.SetAnimation(pGeom);
	}


	//m_pI->ProgressUpdate(99, TRUE, _T("Write Files"));

	// 9. 파일 출력
	m_bybExporter.BinaryFileWrite();
	m_bybExporter.TextFileWrite();


	SafeDeleteArray(m_bybExporter.m_geometry);
	m_bybExporter.m_doExport=false;

	//m_pI->ProgressEnd();

	return TRUE;
}


