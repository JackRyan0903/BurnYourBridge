#include "BYBExporter.h"

using namespace CSH::Util;
using namespace CSH::Model3D;
using CSH::Model3D::BYBExporter;
using CSH::Model3D::Geometry;
using CSH::Model3D::GeometryType;
using CSH::Model3D::VertexIndex;
using CSH::Model3D::VertexPosition;

//--------------------------------------------------------------------------------
/* 생성자 */

BYBExporter::BYBExporter()
{
	m_doExport=false;

	m_expInterface=nullptr;
	m_interface=nullptr;
	m_suppressPrompt=0;
	m_options=0;
	m_geometry=nullptr;
}

//--------------------------------------------------------------------------------





//--------------------------------------------------------------------------------
/* 3ds max 정보 추출 관련 */

void  BYBExporter::NodeGather(INode* pNode)
{
	if(!pNode)
		return;

	m_maxNode.push_back(pNode);

	int child = pNode->NumberOfChildren();

	for(int i=0; i<child; ++i)
	{
		INode* pChild = pNode->GetChildNode(i);

		if(pChild)
			NodeGather(pChild);
	}
}


void  BYBExporter::SetBone(Geometry* pGeom)
{
	INode*	pNode = pGeom->m_pNode;

	if(NULL == pNode)
		return ;


	ObjectState os = pNode->EvalWorldState(0);

	if (!os.obj)
		return;

	if( 0 == _tcsnicmp(pNode->GetName(), _T("Bone"), 4) ||
		0 == _tcsnicmp(pNode->GetName(), _T("Bip"), 3))
	{
		pGeom->SetIntInfo(Geometry::NODE_TYPE, GeometryType::BONE);
		return;
	}

	if(	os.obj->ClassID() == Class_ID(BONE_CLASS_ID, 0) ||
		os.obj->ClassID() == BONE_OBJ_CLASSID ||
		os.obj->ClassID() == Class_ID(DUMMY_CLASS_ID, 0) )
	{
		pGeom->SetIntInfo(Geometry::NODE_TYPE, GeometryType::BONE);
		return;
	}


	Control *cont = pNode->GetTMController();
	if(cont->ClassID() == BIPSLAVE_CONTROL_CLASS_ID ||		//others biped parts
		cont->ClassID() == BIPBODY_CONTROL_CLASS_ID	||		//biped root "Bip01"
		cont->ClassID() == FOOTPRINT_CLASS_ID				//Bip01 Footsteps
		)
		pGeom->SetIntInfo(Geometry::NODE_TYPE, GeometryType::BONE);
}


void  BYBExporter::SetParentIndex(Geometry* pGeom)
{
	INode*	pNode = pGeom->m_pNode;
	INode*	pParent = pNode->GetParentNode();

	if(pParent)
		pGeom->SetIntInfo(Geometry::PARENT_INDEX, BoneIDFind(pParent));
}


void  BYBExporter::SetGeometry(Geometry* pGeom)
{
	int		n;

	INode*	pNode = pGeom->m_pNode;


	Object* pObj = pNode->EvalWorldState(0).obj;

	if(!pObj)
		return;

	SClass_ID lSuperID = pObj->SuperClassID();
	Class_ID lClassID = pObj->ClassID();


	if(GEOMOBJECT_CLASS_ID != lSuperID)
		return;


	// 삼각형으로 메쉬를 바꾼다.
	TriObject* pTri = (TriObject *)pObj->ConvertToType(0, Class_ID(TRIOBJ_CLASS_ID, 0));
	if(NULL == pTri)
		return;

	// 메쉬 객체를 얻는다.
	Mesh* pMesh	= &pTri->GetMesh();
	if(NULL ==pMesh)
		return;


	// 인덱스와 정점의 숫자를 얻는다.
	int	nIndex	= pMesh->getNumFaces();
	int	nVertex	= pMesh->getNumVerts();

	// Setup Index and Vertex Number
	pGeom->SetIntInfo(Geometry::N_INDEX, nIndex);
	pGeom->SetIntInfo(Geometry::N_POSITION, nVertex);


	// 인덱스와 정점이 없으면 빠져 나간다.
	if(nIndex <=0 || nVertex <=0)
		return;


	// Setup Type
	if(GeometryType::BONE != pGeom->GetIntInfo(Geometry::NODE_TYPE))
		pGeom->SetIntInfo(Geometry::NODE_TYPE, GeometryType::MESH);


	//	Matrix3	tmWSM = pNode->GetObjectTM(0);
	Matrix3	tmWSM = pNode->GetObjTMAfterWSM(0); // Skinning을 위해서 이것이 필요

	// Index Vertex 생성
	pGeom->m_indexList=new VertexIndex[nIndex];
	pGeom->m_positionList=new VertexPosition[nVertex];


	// 인덱스 데이터 저장
	for (n=0; n<nIndex; ++n)
	{
		pGeom->m_indexList[n].SetIndex(VertexIndex::FIRST,  pMesh->faces[n].v[0]);
		pGeom->m_indexList[n].SetIndex(VertexIndex::SECOND, pMesh->faces[n].v[2]);	// b <--> c 교환
		pGeom->m_indexList[n].SetIndex(VertexIndex::THIRD,  pMesh->faces[n].v[1]);
	}

	// 정점 데이터 저장
	for (n=0; n<nVertex; ++n)
	{
		Point3 v = tmWSM * pMesh->verts[n];	// 변환된 정점을 사용한다.

		pGeom->m_positionList[n].SetPosition(VertexPosition::X, v.x);
		pGeom->m_positionList[n].SetPosition(VertexPosition::Y, v.z);//y <--> z 교환
		pGeom->m_positionList[n].SetPosition(VertexPosition::Z, v.y);
	}
}


void  BYBExporter::SetAnimation(Geometry* pGeom)
{
	int n;

	if(GeometryType::BONE != pGeom->GetIntInfo(Geometry::NODE_TYPE))
		return;


	DWORD	dTick	= m_head.GetFrameInfo(HeadInfo::TICK_FRAME);
	DWORD	dTimeB	= m_head.GetFrameInfo(HeadInfo::START_FRAME) * dTick;
	DWORD	dTimeE	= m_head.GetFrameInfo(HeadInfo::END_FRAME) * dTick;

	INT		nAni	=0;
	DWORD	dTime	=0;

	// Total Animation
	nAni = m_head.GetFrameInfo(HeadInfo::END_FRAME) - m_head.GetFrameInfo(HeadInfo::START_FRAME) +1;

	INode*	pNode = pGeom->m_pNode;
	pGeom->SetIntInfo(Geometry::N_ANIMATION, nAni);
	
	pGeom->m_animationMatrix=new D3DXMATRIX[nAni];


	D3DXMATRIX	mtPivot;
	Matrix3	tmPivot	= pNode->GetNodeTM(0);
	tmPivot.Invert();
	MaxMatrixToD3D(&mtPivot, &tmPivot);

	for(n=0, dTime = dTimeB; dTime<=dTimeE ; dTime += dTick, ++n)
	{
		D3DXMATRIX* pDest = &pGeom->m_animationMatrix[n];

		Matrix3 tmWorld = pNode->GetObjTMAfterWSM(dTime);
		tmWorld.NoScale();

		D3DXMATRIX	mtAni;
		MaxMatrixToD3D(&mtAni, &tmWorld);
		mtAni  = mtPivot * mtAni;

		*pDest = mtAni;
	}
}


int   BYBExporter::BoneIDFind(INode* pNode)
{
	for(int n=0; n<m_head.GetNumberOfGeometry(); ++n)
	{
		Geometry*	pGeom	= &m_geometry[n];
		if(pGeom->m_pNode == pNode)
			return n;
	}

	return -1;
}


void  BYBExporter::SetBoneWeight(Geometry* pGeom)
{
	INode*		pNode = pGeom->m_pNode;		// Current Node
	Modifier*	pMod = NULL;


	// Physique 선택
	pMod = (Modifier*)ModifierFind(pNode, PHYSQ_CLASSID);

	if(pMod)
	{
		SetPhysiqueWeight(pGeom, pMod);
		return;
	}

	// Skin 선택
	pMod = (Modifier*)ModifierFind(pNode, SKIN_CLASSID);

	if(pMod)
		SetSkinWeight(pGeom, pMod);
}


void  BYBExporter::SetPhysiqueWeight(Geometry* pGeom, Modifier* pMod)
{
	INode*				pNode = pGeom->m_pNode;	// Current Node
	IPhysiqueExport*	pExport = NULL;
	IPhyContextExport*	pContext = NULL;


	pExport = (IPhysiqueExport*)pMod->GetInterface(I_PHYINTERFACE);		// Physique에 객체
	if(!pExport)
		return;


	pContext = (IPhyContextExport*)pExport->GetContextInterface(pNode);	// Physique Export에 대한 Context를 구한다.
	if(!pContext)
	{
		pMod->ReleaseInterface(I_PHYINTERFACE, pExport);
		return;
	}

	pContext->ConvertToRigid(TRUE);					// Context에 대해서 모든 정점을 Rigid로 바꾼다.
	pContext->AllowBlending(TRUE);					// Blending 활성화

	int nVtx = pContext->GetNumberVertices();		// Bone에 영향받는 정점의 개수

	if(nVtx <=0)
		return;


	pGeom->SetIntInfo(Geometry::N_BONE_DEPENDENT_VERTEX, nVtx);
	
	pGeom->m_boneSource=new BoneIndex[nVtx];


	for(int j=0; j<nVtx; ++j)
	{
		//get i-th vertex
		IPhyVertexExport*		pPhyVtxExpt = (IPhyVertexExport*)pContext->GetVertexInterface(j);
		IPhyBlendedRigidVertex* pPhyBlend	= (IPhyBlendedRigidVertex*)pPhyVtxExpt;

		if(!pPhyVtxExpt)
			continue;


		if(RIGID_TYPE == pPhyVtxExpt->GetVertexType())
		{
			//본 인덱스를 구한다.
			INode*	pBone	= ((IPhyRigidVertex*)pPhyVtxExpt)->GetNode();
			INT		nBone	= BoneIDFind(pBone);
			FLOAT	fWgt	= 1.f;		//RIGID_TYPE는 Weight=1 이다.


			pGeom->m_boneSource[j].m_boneIndex.insert(std::pair<INT, FLOAT>(nBone, fWgt));
			continue;
		}


		int numBones = pPhyBlend->GetNumberNodes();
		for(int k = 0; k< numBones; ++k)
		{
			// k번째의 본을 찾는다.
			INode*	pBone	= pPhyBlend->GetNode(k);
			INT		nBone	= BoneIDFind(pBone);
			FLOAT	fWgt	= pPhyBlend->GetWeight(k);


			// 값이 작으면 무시
			if(fWgt<0.00005f)
				continue;


			pGeom->m_boneSource[j].m_boneIndex.insert(std::pair<INT, FLOAT>(nBone, fWgt));
		}
	}


	pExport->ReleaseContextInterface(pContext);
	pMod->ReleaseInterface(I_PHYINTERFACE, pExport);
}


void  BYBExporter::SetSkinWeight(Geometry* pGeom, Modifier* pMod)
{
	INode*				pNode = pGeom->m_pNode;			// Current Node
	ISkin*				pExport = NULL;
	ISkinContextData*	pContext = NULL;


	pExport = (ISkin*)pMod->GetInterface(I_SKIN);		// Skin 객체
	if(!pExport)
		return;

	pContext = pExport->GetContextInterface(pNode);		// SKin Export에 대한 Context를 구한다.
	if(!pContext)
		return;

	int nVtx = pContext->GetNumPoints();				// Bone에 영향받는 정점의 개수

	if(nVtx <=0)
		return;

	pGeom->SetIntInfo(Geometry::N_BONE_DEPENDENT_VERTEX, nVtx);
	pGeom->m_boneSource = new BoneIndex[nVtx];


	for(int j=0; j<nVtx;  ++j)
	{
		int numBones = pContext->GetNumAssignedBones(j);

		for(int k=0; k<numBones; ++k)
		{
			int assignedBone = pContext->GetAssignedBone(j, k);

			if(assignedBone < 0)
				continue;

			INode*	pBone	= pExport->GetBone(assignedBone);
			INT		nBone	= BoneIDFind(pBone);
			FLOAT	fWgt	= pContext->GetBoneWeight(j, k);

			// 값이 작으면 무시
			if(fWgt<0.00005f)
				continue;

			pGeom->m_boneSource[j].m_boneIndex.insert(std::pair<INT, FLOAT>(nBone, fWgt));
		}
	}

	pMod->ReleaseInterface(I_SKIN, pExport);
}


void* BYBExporter::ModifierFind(INode* pNode, Class_ID classID)
{
	// 노드에 연결된 오브젝트를 구한다.
	Object* ObjectPtr = pNode->GetObjectRef();

	if(!ObjectPtr)
		return NULL;

	// Derived 오브젝트라면 이 오브젝트에서 수정자를 찾는다.
	while(ObjectPtr && ObjectPtr->SuperClassID() == GEN_DERIVOB_CLASS_ID)
	{
		IDerivedObject *pDerivedObj = (IDerivedObject *)ObjectPtr;

		
		// 수정자 스택을 전부 탐색한다.
		int ModStackIndex = 0;
		while(ModStackIndex < pDerivedObj->NumModifiers())
		{
			// 스택 인덱스에 대한 수정자를 얻는다.
			Modifier* ModifierPtr = pDerivedObj->GetModifier(ModStackIndex);
			
			//이 수정자의 아이디가 PHYSIQUE 또는 SKIN인지 비교한다.
			if(classID == ModifierPtr->ClassID())
				return ModifierPtr;


			// 수정자가 PHYSIQUE 또는 SKIN이 아니면 인덱스를 올린다.
			ModStackIndex++;
		}

		// Derived 오브젝트에 연결된 다른 오브젝트를 얻는다.
		ObjectPtr = pDerivedObj->GetObjRef();
	}

	// 발견 못함.
	return NULL;
}

//--------------------------------------------------------------------------------





//--------------------------------------------------------------------------------
/* 3ds max -> directx 변환 관련 */

void  BYBExporter::MaxMatrixToD3D(D3DXMATRIX* pDest, Matrix3* pSrc, bool identity)
{
	Point3	v3;
	v3	= pSrc->GetRow(0);	pDest->_11 = v3.x;	pDest->_12 = v3.z;	pDest->_13 = v3.y;
	v3	= pSrc->GetRow(2);	pDest->_21 = v3.x;	pDest->_22 = v3.z;	pDest->_23 = v3.y;
	v3	= pSrc->GetRow(1);	pDest->_31 = v3.x;	pDest->_32 = v3.z;	pDest->_33 = v3.y;
	v3	= pSrc->GetRow(3);	pDest->_41 = v3.x;	pDest->_42 = v3.z;	pDest->_43 = v3.y;

	if(identity)
	{
		pDest->_14 = 0.f;
		pDest->_24 = 0.f;
		pDest->_34 = 0.f;
		pDest->_44 = 1.f;
	}
}

//--------------------------------------------------------------------------------





//--------------------------------------------------------------------------------
/* 파일 출력 관련 */

void  BYBExporter::BinaryFileWrite()
{
	INT n;
	INT	j;

	FILE*	fp = _tfopen(m_binaryFileName, _T("wb"));

	fwrite(&m_head, 1, sizeof(HeadInfo), fp);
	fseek(fp, FrameOffset::FRAME_OFFSET, SEEK_SET);

	// Write Geometry
	for(n =0; n<m_head.GetNumberOfGeometry(); ++n)
	{
		Geometry* pGeom = &m_geometry[n];

		fwrite(pGeom->m_nodeName ,32, sizeof(char), fp);	// Node Name
		fwrite(pGeom->GetIntInfoPointer(Geometry::NODE_TYPE), 1, sizeof(int), fp);	// Node Type
		fwrite(pGeom->GetIntInfoPointer(Geometry::PARENT_INDEX) , 1, sizeof(int), fp);	// Parent Index

		fwrite(pGeom->GetIntInfoPointer(Geometry::N_INDEX) , 1, sizeof(int), fp);	// Index Number
		fwrite(pGeom->GetIntInfoPointer(Geometry::N_POSITION) , 1, sizeof(int), fp);	// Vertex Number
		fwrite(pGeom->GetIntInfoPointer(Geometry::N_ANIMATION) , 1, sizeof(int), fp);	// Animation Number


		if(1 > pGeom->GetIntInfo(Geometry::N_INDEX) || 1 > pGeom->GetIntInfo(Geometry::N_POSITION))
			continue;

		// Write Mesh
		fwrite(pGeom->m_indexList, pGeom->GetIntInfo(Geometry::N_INDEX)
			, sizeof(VertexIndex), fp);
		fwrite(pGeom->m_positionList, pGeom->GetIntInfo(Geometry::N_POSITION)
			, sizeof(VertexPosition), fp);
	}

	// Write Animation
	for(n =0; n<m_head.GetNumberOfGeometry(); ++n)
	{
		Geometry* pGeom = &m_geometry[n];

		if(1>pGeom->GetIntInfo(Geometry::N_ANIMATION))
			continue;

		fwrite(pGeom->m_animationMatrix, pGeom->GetIntInfo(Geometry::N_ANIMATION)
			, sizeof(D3DXMATRIX), fp);	// Animation Matrix
	}



	// Export Vertex Weight Data
	for(n=0; n<m_head.GetNumberOfGeometry(); ++n)
	{
		Geometry*	pGeom	= &m_geometry[n];

		fwrite(pGeom->GetIntInfoPointer(Geometry::N_BONE_DEPENDENT_VERTEX), sizeof(int), 1, fp);

		if(0>=pGeom->GetIntInfo(Geometry::N_BONE_DEPENDENT_VERTEX))
			continue;

		for(j=0; j<pGeom->GetIntInfo(Geometry::N_POSITION); ++j)
		{
			BoneIndex*	pBlnd = &pGeom->m_boneSource[j];//>pBlnd[j];
			INT			iBone = pBlnd->m_boneIndex.size();

			fwrite(&iBone, sizeof(int), 1, fp);

			std::map<INT, FLOAT >::iterator	__F = pBlnd->m_boneIndex.begin();
			std::map<INT, FLOAT >::iterator	__L = pBlnd->m_boneIndex.end();

			for(; __F != __L; ++__F)
			{
				INT		nB = (*__F).first;
				FLOAT	fW = (*__F).second;
				fwrite(&nB, sizeof(INT  ), 1, fp);
				fwrite(&fW, sizeof(FLOAT), 1, fp);
			}

		}
	}

	fclose(fp);
}


void  BYBExporter::TextFileWrite()
{
	INT n, j;

	FILE*	fp = _tfopen(m_textFileName, _T("wt"));

	fprintf(fp, "\nTotal_Node: %d\n", m_head.GetNumberOfGeometry());
	fprintf(fp, "Scene: %ld %ld %ld %ld\n"
		, m_head.GetFrameInfo(HeadInfo::START_FRAME)
		, m_head.GetFrameInfo(HeadInfo::END_FRAME)
		, m_head.GetFrameInfo(HeadInfo::FRAME_RATE)
		, m_head.GetFrameInfo(HeadInfo::TICK_FRAME));

	fprintf(fp, "\n");

	// Write Mesh
	for(n =0; n<m_head.GetNumberOfGeometry(); ++n)
	{
		Geometry* pGeom = &m_geometry[n];
		INode* pPrn = pGeom->m_pNode->GetParentNode();

		fprintf(fp, "Node: %2d (\"%s\")"
			" Type: %d"
			" Parent: %d"
			, n
			, pGeom->m_nodeName
			, pGeom->GetIntInfo(Geometry::NODE_TYPE)
			, pGeom->GetIntInfo(Geometry::PARENT_INDEX)
			);

		if(pPrn)
			fprintf(fp, " (\"%s\")\n", pPrn->GetName());
		else
			fprintf(fp, " (\"<NULL>\")\n");


		fprintf(fp, "IndexNumber:  %2d VertexNumber: %2d\n"
			, pGeom->GetIntInfo(Geometry::N_INDEX), pGeom->GetIntInfo(Geometry::N_POSITION));

		fprintf(fp, "AnimationNumber: %2d\n", pGeom->GetIntInfo(Geometry::N_ANIMATION));


		if(pGeom->GetIntInfo(Geometry::N_INDEX) <1 || pGeom->GetIntInfo(Geometry::N_POSITION) <1)
		{
			fprintf(fp, "\n");
			continue;
		}

		fprintf(fp, "Face {\n");

		for (j=0; j<pGeom->GetIntInfo(Geometry::N_INDEX); ++j)
		{
			int a, b, c;
			a= pGeom->m_indexList[j].GetIndex(VertexIndex::FIRST);
			b= pGeom->m_indexList[j].GetIndex(VertexIndex::SECOND);
			c= pGeom->m_indexList[j].GetIndex(VertexIndex::THIRD);

			fprintf(fp, "	%4d		%4d %4d %4d\n", j, a, b, c);
		}


		fprintf(fp, "}\n");


		fprintf(fp, "Vertex {\n");

		for (j=0; j<pGeom->GetIntInfo(Geometry::N_POSITION); ++j)
		{
			float x, y, z;
			x = pGeom->m_positionList[j].GetPosition(VertexPosition::X);
			y = pGeom->m_positionList[j].GetPosition(VertexPosition::Y);
			z = pGeom->m_positionList[j].GetPosition(VertexPosition::Z);

			fprintf(fp, "	%4d		%10.5f %10.5f %10.5f\n", j, x, y, z);
		}

		fprintf(fp, "}\n\n");
	}



	// Write Animation
	for(n =0; n<m_head.GetNumberOfGeometry(); ++n)
	{
		Geometry* pGeom = &m_geometry[n];
		INode* temp = pGeom->m_pNode;
		INode* pPrn = temp->GetParentNode();

		if(1>pGeom->GetIntInfo(Geometry::N_ANIMATION))
			continue;

		fprintf(fp, "Animation: %2d (\"%s\") {\n", n, pGeom->m_nodeName);

		for (j=0; j<pGeom->GetIntInfo(Geometry::N_ANIMATION); ++j)
		{
			D3DXMATRIX* pTM = &pGeom->m_animationMatrix[j];
			fprintf(fp, "	%2d ", j);
			fprintf(fp, " %9.5f %9.5f %9.5f %9.5f", pTM->_11, pTM->_12, pTM->_13, pTM->_14);
			fprintf(fp, " %9.5f %9.5f %9.5f %9.5f", pTM->_21, pTM->_22, pTM->_23, pTM->_24);
			fprintf(fp, " %9.5f %9.5f %9.5f %9.5f", pTM->_31, pTM->_32, pTM->_33, pTM->_34);
			fprintf(fp, " %9.5f %9.5f %9.5f %9.5f", pTM->_41, pTM->_42, pTM->_43, pTM->_44);
			fprintf(fp, "\n");
		}

		fprintf(fp, "}\n\n");
	}


	// Export Vertex Weight Data
	for(n=0; n<m_head.GetNumberOfGeometry(); ++n)
	{
		Geometry*	pGeom = &m_geometry[n];

		if(!pGeom->m_boneSource)
			continue;

		fprintf(fp, "Blend: %2d (\"%s\") {\n", n, pGeom->m_nodeName);

		for(j=0; j<pGeom->GetIntInfo(Geometry::N_POSITION); ++j)
		{
			BoneIndex*	pBlnd = &pGeom->m_boneSource[j];
			INT			iBone = pBlnd->m_boneIndex.size();

			fprintf(fp, "	%4d %2d : ", j, iBone);


			std::map<INT, FLOAT >::iterator	__F = pBlnd->m_boneIndex.begin();
			std::map<INT, FLOAT >::iterator	__L = pBlnd->m_boneIndex.end();

			for(; __F != __L; ++__F)
			{
				INT		nB = (*__F).first;
				FLOAT	fW = (*__F).second;
				fprintf(fp, "[%4d %7.6f]", nB, fW);
			}

			fprintf(fp, "\n");
		}

		fprintf(fp, "}\n\n");
	}

	fprintf(fp, "\n");

	fclose(fp);
}


void  BYBExporter::FileRename(TCHAR* pOut, TCHAR* pIn, TCHAR* fileName, TCHAR* ext)
{
	TCHAR tDrive[_MAX_DRIVE]={0};
	TCHAR tDir[_MAX_DIR]={0};
	TCHAR tFile[_MAX_FNAME]={0};
	TCHAR tExt[_MAX_EXT]={0};

	_tsplitpath( pIn, tDrive, tDir, tFile, tExt );

	if(fileName && ext)
	{
		_tmakepath( pOut, tDrive, tDir, fileName, ext );
	}
	else if(fileName && NULL == ext)
	{
		_tmakepath( pOut, tDrive, tDir, fileName, tExt );
	}

	else if(NULL == fileName && ext)
	{
		_tmakepath( pOut, tDrive, tDir, tFile, ext );
	}

	else
	{
		_tmakepath( pOut, tDrive, tDir, fileName, ext );
	}
}


//--------------------------------------------------------------------------------