//====================================================================
//
// �V�F�[�_�̏����w�b�_�[	[shader.cpp]
// Author : Konishi Yuuto
//
//====================================================================

//====================================================================
// �C���N���[�h
//====================================================================
#include "shader.h"
#include "renderer.h"
#include "manager.h"

//=================================================================================================
// �R���X�g���N�^
//=================================================================================================
CShader::CShader()
{
}

//=================================================================================================
// �f�X�g���N�^
//=================================================================================================
CShader::~CShader()
{
}

//=================================================================================================
// ����������
//=================================================================================================
BOOL CShader::Init()
{
	// Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�̃t�H�[�}�b�g�錾
	D3DVERTEXELEMENT9 vertex_elements[] =
	{
		{
			0,
			0,
			D3DDECLTYPE_FLOAT3,
			D3DDECLMETHOD_DEFAULT,
			D3DDECLUSAGE_POSITION,
			0
		},
		D3DDECL_END()
	};

	pDevice->CreateVertexDeclaration(vertex_elements, &m_pDecl);

	// ���_�̍쐬
	if (FAILED(pDevice->CreateVertexBuffer(
		4 * sizeof(VERTEX),
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED,
		&m_pBuffer,
		NULL)))
	{
		return false;
	}

	VERTEX *tmp_vertex;

	// ���_��ҏW���邽�߂Ƀ��b�N
	m_pBuffer->Lock(0, 0, (void**)&tmp_vertex, 0);

	// ���_���W�̕ύX
	tmp_vertex[0].m_Pos = D3DXVECTOR3(-100.0f, 50.0f, -100.0f);
	tmp_vertex[1].m_Pos = D3DXVECTOR3(100.0f, 50.0f, -100.0f);
	tmp_vertex[2].m_Pos = D3DXVECTOR3(-100.0f, 0.0f, 100.0f);
	tmp_vertex[3].m_Pos = D3DXVECTOR3(100.0f, 0.0f, 100.0f);

	// ���_�̃��b�N������
	m_pBuffer->Unlock();

	// �V�F�[�_�̓ǂݍ���
	LPD3DXBUFFER error = NULL;

	D3DXCreateEffectFromFile(pDevice,
		TEXT("Shader.hlsl"),
		0,
		0,
		D3DXSHADER_DEBUG,
		0,
		&m_pShader,
		&error);

	if (m_pShader == NULL)
	{
		return false;
	}

	// �e�N�j�b�N�̃n���h���擾
	m_Tech = m_pShader->GetTechniqueByName("StandardDraw");			// �e�N�j�b�N�擾

	// �O���[�o���ϐ��̃n���h���擾
	m_Matrix = m_pShader->GetParameterByName(NULL, "m_Matrix");		// �p�����[�^�擾
	m_Color = m_pShader->GetParameterByName(NULL, "m_Color");

	return true;
}

//=================================================================================================
// �`�揈��
//=================================================================================================
void CShader::Draw(D3DXMATRIX Matrix)
{
	// Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�̗�������
	pDevice->SetStreamSource(0, m_pBuffer, 0, sizeof(VERTEX));

	// �F�ύX
	D3DXVECTOR4 color;
	color.x = 1.0f;
	color.y = 1.0f;
	color.z = 1.0f;
	color.w = 1.0f;

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetVertexDeclaration(m_pDecl);

	// �e�N�j�b�N�̐ݒ�
	m_pShader->SetTechnique(m_Tech);

	// �p�����[�^(�O���[�o���ϐ��̐ݒ�)
	m_pShader->SetMatrix(m_Matrix, &Matrix);		// �}�e���A��
	m_pShader->SetVector(m_Color, &color);			// ���_

	// �p�����[�^�X�V
	m_pShader->CommitChanges();			// GPU���̃f�[�^���X�V����

	// �V�F�[�_�N��
	m_pShader->Begin(0, 0);		// �����F�V�F�[�_�̃p�X���A�f�o�C�X�X�e�[�g�̕ۑ��ݒ�t���O

	// �p�X�N��
	m_pShader->BeginPass(0);	// �����F�N�������V�F�[�_�̃p�X���̐�

	// �|���S���`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		2);

	// �p�X�I��
	m_pShader->EndPass();

	// �V�F�[�_�I��
	m_pShader->End();

}

//=================================================================================================
// ��������
//=================================================================================================
void CShader::Delete(void)
{
	if (m_pBuffer != NULL)
	{
		m_pBuffer->Release();
		m_pBuffer = NULL;
	}

	if (m_pDecl != NULL)
	{
		m_pDecl->Release();
		m_pDecl = NULL;
	}

	if (m_pShader != NULL)
	{
		m_pShader->Release();
		m_pShader = NULL;
	}

}
