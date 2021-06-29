////=============================================================================
////
//// ���b�V���X�t�B�A�N���X [meshshape.cpp]
//// Author : Konishi Yuuto
////
////=============================================================================
//
////=============================================================================
//// �C���N���[�h
////=============================================================================
//#include "shape.h"
//#include "renderer.h"
//#include "manager.h"
//#include "model.h"
//
////=============================================================================
//// static������
////=============================================================================
//LPD3DXMESH CMeshShape::m_pMesh = NULL;			//���b�V�����ւ̃|�C���^
//LPD3DXBUFFER CMeshShape::m_pBuffMat = NULL;	//�}�e���A�����ւ̃|�C���^
//DWORD CMeshShape::m_nNumMat = 0;				//�}�e���A�����̐�
////LPDIRECT3DTEXTURE9 CMeshShape::m_apTexture[MAX_MESHFIELD_TEXTURE] = {};
//
////=============================================================================
//// �R���X�g���N�^
////=============================================================================
//CMeshShape::CMeshShape()
//{
//	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//}
//
////=============================================================================
//// �f�X�g���N�^
////=============================================================================
//CMeshShape::~CMeshShape()
//{
//}
//
////=============================================================================
//// ����������
////=============================================================================
//HRESULT CMeshShape::Init(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
//
//	//���p�`���b�V���̐���
//	//D3DXCreatePolygon(pDevice,100,6,&m_pMesh,&m_pBuffMat);
//	//�����b�V���̐���
//	//D3DXCreateSphere(pDevice,50, 32, 32,&m_pMesh, &m_pBuffMat);
//	//�l�p���b�V���̐���
//	D3DXCreateBox(pDevice, 100, 100, 100, &m_pMesh, &m_pBuffMat);
//	//�~�����b�V���̐���
//	//D3DXCreateCylinder(pDevice, 50, 50, 50, 32, 32, &m_pMesh, &m_pBuffMat);
//	//�g�[���X���b�V���̐���
//	//D3DXCreateTorus(pDevice, 10, 100, 32, 32, &m_pMesh, &m_pBuffMat);
//
//	MODEL model;
//	model.dwNumMat = 1;
//	model.pBuffMat = m_pBuffMat;
//	model.pMesh = m_pMesh;
//
//	//���f������ݒ�
//	CModel::BindModel(model);
//
//	m_pos = D3DXVECTOR3(0.0f, 200.0f, 100.0f);					// �ʒu
//	CModel::SetPos(m_pos);
//	CModel::SetRot(m_move);
//
//	return S_OK;
//}
//
////=============================================================================
//// �I������
////=============================================================================
//void CMeshShape::Uninit(void)
//{
//	// �I������
//	CModel::Uninit();
//}
//
////=============================================================================
//// �X�V����
////=============================================================================
//void CMeshShape::Update(void)
//{
//}
//
////=============================================================================
//// �`�揈��
////=============================================================================
//void CMeshShape::Draw(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
//	D3DXMATERIAL*pMat;	//�}�e���A���f�[�^�ւ̃|�C���^
//
//	//�}�e���A���f�[�^�ւ̃|�C���^���擾
//	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
//
//	pMat->MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
//	pMat->MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.1f);
//	pMat->MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
//	pMat->MatD3D.Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
//
//	// �A���t�@�e�X�g��L�͉�
//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
//
//	// �A���t�@�e�X�g��l�̐ݒ�
//	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
//
//	// �A���t�@�e�X�g�̔�r���@�̐ݒ�(GREATER�͊�l���傫���ꍇ)
//	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
//
//	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
//
//	//�`�揈��
//	CModel::Draw();
//
//	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
//
//	// �A���t�@�e�X�g�𖳌���
//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
//}
//
////=============================================================================
//// �|���S������
////=============================================================================
//CMeshShape * CMeshShape::Create(void)
//{
//	CMeshShape *pMeshShape = new CMeshShape;
//
//	if (pMeshShape != NULL)
//	{
//		pMeshShape->Init();
//	}
//
//	return pMeshShape;
//}
//
////=============================================================================
//// �e�N�X�`�����[�h
////=============================================================================
//HRESULT CMeshShape::Load(void)
//{
//	// �����_���[�̏����󂯎��
//	CRenderer *pRenderer = NULL;
//	pRenderer = CManager::GetRenderer();
//	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
//
//	// �e�N�X�`���̓ǂݍ���
//	D3DXCreateTextureFromFile(pDevice, "data/Texture/stone_00124.jpg",
//		&m_apTexture[0]);
//
//	return S_OK;
//}
//
////=============================================================================
//// �e�N�X�`���A�����[�h
////=============================================================================
//void CMeshShape::UnLoad(void)
//{
//	for (int nCount = 0; nCount < MAX_MESHFIELD_TEXTURE; nCount++)
//	{
//		// �e�N�X�`���̊J��
//		if (m_apTexture[nCount] != NULL)
//		{
//			m_apTexture[nCount]->Release();
//			m_apTexture[nCount] = NULL;
//		}
//	}
//}
//
//D3DXVECTOR3 CMeshShape::GetPos(void)
//{
//	return m_pos;
//}
