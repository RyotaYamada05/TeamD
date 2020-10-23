//=============================================================================
//
// �����_���[���� [renderer.cpp]
// Author : �R�c�ˑ�
//
//=============================================================================
#include "renderer.h"
#include "scene.h"
#include "fade.h"
#include "shader.h"
#include "manager.h"
#include "camera.h"
#include "game.h"

//=============================================================================
//�����_�����O�N���X�̃R���X�g���N�^
//=============================================================================
CRenderer::CRenderer()
{
	m_pShader = NULL;
	m_pD3D = NULL;			// Direct3D�I�u�W�F�N�g
}

//=============================================================================
//�����_�����O�N���X�̃f�X�g���N�^
//=============================================================================
CRenderer::~CRenderer()
{
}

//=============================================================================
//�����_�����O�N���X�̏���������
//=============================================================================
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;	//�v���[���e�[�V�����p�����[�^
	D3DDISPLAYMODE d3ddm;	//�f�B�X�v���C���[�h

	// Direct3D�I�u�W�F�N�g�̍쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));				// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;						// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;			// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;			// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;			// �J���[���[�h�̎w��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		// �f���M���ɓ������ăt���b�v����
	d3dpp.EnableAutoDepthStencil = TRUE;			// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;		// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;						// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��


	m_pD3DInterface = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3DInterface == NULL)
	{
		// �쐬���s
		return E_FAIL;
	}

	m_pD3DPresentParam = new D3DPRESENT_PARAMETERS;
	if (m_pD3DPresentParam == NULL)
	{
		return E_FAIL;
	}
	ZeroMemory(m_pD3DPresentParam, sizeof(D3DPRESENT_PARAMETERS));

	// �o�b�N�o�b�t�@�̐� => 1
	m_pD3DPresentParam->BackBufferCount = 1;
	// �o�b�N�o�b�t�@�̃t�H�[�}�b�g => D3DFMT_UNKNOWN(�t�H�[�}�b�g��m��܂���)
	m_pD3DPresentParam->BackBufferFormat = D3DFMT_UNKNOWN;
	// �E�B���h�E���[�h�ݒ� => �萔�Ő؂�ւ�
	m_pD3DPresentParam->Windowed = true;

	// �X���b�v�G�t�F�N�g�ݒ� => �f�B�X�v���C�h���C�o�ˑ�
	// �X���b�v�G�t�F�N�g => �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�ւ̐؂�ւ����@
	m_pD3DPresentParam->SwapEffect = D3DSWAPEFFECT_DISCARD;

	// �[�x�o�b�t�@�̗L��
	m_pD3DPresentParam->EnableAutoDepthStencil = TRUE;

	// �[�x�o�b�t�@�̃t�H�[�}�b�g
	m_pD3DPresentParam->AutoDepthStencilFormat = D3DFMT_D24S8;

	// ���l�ȃt���O�ݒ�
	m_pD3DPresentParam->Flags = 0;

	// �f�o�C�X�̐���
	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,				// D3DDEVTYPE_HAL�F�n�[�h�E�F�A�Ń��X�^���ƃV�F�[�f�B���O���s���A(���W�ϊ��ƏƖ��v�Z)���s��
		D3DDEVTYPE_HAL,												// D3DDEVTYPE_REF:���t�@�����X���X�^���C�U�B�h���C�o�̃o�O���`�F�b�N�ł���
		hWnd,														// D3DCREATE_PUREDEVICE                :���X�^���A���W�ϊ��A�Ɩ��v�Z�A�V�F�[�f�B���O���w��A��̃t���O�̏C���q
		D3DCREATE_HARDWARE_VERTEXPROCESSING,						// D3DCREATE_SOFTWARE_VERTEXPROCESSING�F�\�t�g�E�F�A�ɂ�钸�_�������w��
		&d3dpp, &m_pD3DDevice)))									// D3DCREATE_HARDWARE_VERTEXPROCESSING�F�n�[�h�E�F�A�ɂ�钸�_�����B
	{																// D3DCREATE_MIXED_VERTEXPROCESSING   �F�~�b�N�X(�\�t�g�E�F�A�ƃn�[�h�E�F�A�̗���)�ɂ�钸�_�������w�肵�܂��B
		// ��L�̐ݒ肪���s������								
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pD3DDevice)))
			{
				// �������s
				return E_FAIL;
			}
		}
	}

	// �r���[�|�[�g�̐ݒ�
	D3DVIEWPORT9 view_port;

	// �r���[�|�[�g�̍�����W
	view_port.X = 0;
	view_port.Y = 0;

	// �r���[�|�[�g�̕�
	view_port.Width = SCREEN_WIDTH;

	// �r���[�|�[�g�̍���
	view_port.Height = SCREEN_HEIGHT;

	// �r���[�|�[�g�[�x�ݒ�
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 1.0f;
	
	// �r���[�|�[�g�ݒ�
	if (FAILED(m_pD3DDevice->SetViewport(&view_port)))
	{
		return E_FAIL;
	}

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	if (m_pShader == NULL)	//�}�l�[�W���[�N���X�̃|�C���^
	{
		//�}�l�[�W���[�N���X�̃C���X�^���X����
		m_pShader = new CShader;

		//���������m�ۂł��Ă�����
		if (m_pShader != NULL)
		{
			m_pShader->Init();
		}
	}

	// �����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);					// ���ʂ��i�����j���J�����O
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);							// Z�o�b�t�@���g�p
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);					// ���u�����h���s��
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			// ���\�[�X�J���[�̎w��
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// ���f�X�e�B�l�[�V�����J���[�̐ݒ�

	// �T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);		// �e�N�X�`����U�l�̌J��Ԃ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);		// �e�N�X�`����V�l�̌J��Ԃ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);		// �e�N�X�`���g�厞�̕⊮�ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);		// �e�N�X�`���k�����̕⊮�ݒ�

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);		// �A���t�@�u�����f�B���O����
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		// �ŏ��̃A���t�@�����i�����l�j
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);		// 2�Ԗڂ̃A���t�@�����i�����l�j

	return S_OK;
}

//=============================================================================
//�����_�����O�N���X�̏I������
//=============================================================================
void CRenderer::Uninit(void)
{
	// �f�o�C�X�̔j��
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	// Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//=============================================================================
//�����_�����O�N���X�̍X�V����
//=============================================================================
void CRenderer::Update(void)
{
	CScene::AllUpdate();
}

//=============================================================================
//�����_�����O�N���X�̕`�揈��
//=============================================================================
void CRenderer::Draw(void)
{
	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		for (int nCount = 0; nCount < 2; nCount++)
		{

			// �ˉe�s��/�r���[/���[���h
			D3DXMATRIX matProj, matView, matWorld;
			D3DXMATRIX trans;

			if (CGame::GetCamera(nCount) != NULL)
			{
				CCamera *pCamera = CGame::GetCamera(nCount);
				pCamera->SetCamera();

				D3DXVECTOR3 posV = pCamera->GetposV();
				D3DXVECTOR3 posR = pCamera->GetposR();

				D3DXMatrixLookAtLH(&matView,
					&posV,								// �J�������W
					&posR,								// �����_���W
					&D3DXVECTOR3(0.0f, 1.0f, 0.0f));	// �J�����̏�̌����̃x�N�g��

				SetUpViewport(nCount);

				// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
				m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 255, 255, 0), 1.0f, 0);
			}

			//�I�u�W�F�N�g�N���X�̑S�`�揈���Ăяo��
			CScene::AllDraw();

			//���C�e�B���O�𖳌��ɂ���B
			m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			// WVP�����ꎞ�I�ȍs����쐬���A
			// ���ɓ]�u���āA�i�[����
			D3DXMatrixTranspose(&trans, &(matWorld * matView * matProj));

			// �s��̃A�h���X�𑗂�i���������ł�4�s��4���������_)
			// ���W�X�^r0�Ŏn�܂�S����4�̃��W�X�^�ɒu��
			m_pD3DDevice->SetVertexShaderConstantF(
				0,				// �J�n���W�X�^�ԍ�
				trans,			// �l�̃A�h���X
				4);				// ���[�h����4�����l�̐�

			// �F�̐ݒ�
			float fteal[4] = { 0.0f, 1.0f, 0.7f, 0.0f };	// rgba�̒l

			// ���W�X�^c12���w�肷��
			m_pD3DDevice->SetVertexShaderConstantF(
				12,				// �ݒ肷��萔���W�X�^
				fteal,			// �l�̔z��
				1);				// ���[�h����4�����l�̐�

			//�ˉe���W�ϊ��E���ߕϊ��̐ݒ�
			D3DXMatrixPerspectiveFovLH(&matProj,
				D3DX_PI / 4.0f,
				4.0f / 3.0f,
				0.1f,
				500.0f);

			m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

			//�r���[���W�ϊ�
			D3DXMatrixIdentity(&matView);
			m_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

			//���[���h���W�ϊ�
			D3DXMatrixIdentity(&matWorld);
			m_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);


			//���������m�ۂł��Ă�����
			if (m_pShader != NULL)
			{
				m_pShader->Draw(matProj);
			}

			//���C�e�B���O�𖳌��ɂ���B
			m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			
			CFade *pFade = CManager::GetFade();

			if (pFade != NULL)
			{
				pFade->Draw();
			}

			// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	//		m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
		}

		// Direct3D�ɂ��`��̏I��
		m_pD3DDevice->EndScene();
	}

	//�����i�A���r�G���g�j�̐ݒ�
	D3DMATERIAL9 material;

	SecureZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Ambient.r = 1.0f;
	material.Ambient.g = 1.0f;
	material.Ambient.b = 1.0f;
	material.Ambient.a = 1.0f;

	m_pD3DDevice->SetMaterial(&material);
	m_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x44444444);

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

bool CRenderer::SetUpViewport(int nNumber)
{
	switch (nNumber)
	{
	case 0:
		// �r���[�|�[�g�̍�����W
		m_view_port[nNumber].X = 0;
		m_view_port[nNumber].Y = 0;

		// �r���[�|�[�g�̕�
		m_view_port[nNumber].Width = SCREEN_WIDTH / 2;

		// �r���[�|�[�g�̍���
		m_view_port[nNumber].Height = SCREEN_HEIGHT;

		// �r���[�|�[�g�[�x�ݒ�
		m_view_port[nNumber].MinZ = 0.0f;
		m_view_port[nNumber].MaxZ = 1.0f;

		// �r���[�|�[�g�ݒ�
		if (FAILED(m_pD3DDevice->SetViewport(&m_view_port[nNumber])))
		{
			return false;
		}
		break;

	case 1:
		// �r���[�|�[�g�̍�����W
		m_view_port[nNumber].X = SCREEN_WIDTH / 2;
		m_view_port[nNumber].Y = 0;

		// �r���[�|�[�g�̕�
		m_view_port[nNumber].Width = SCREEN_WIDTH / 2;

		// �r���[�|�[�g�̍���
		m_view_port[nNumber].Height = SCREEN_HEIGHT;

		// �r���[�|�[�g�[�x�ݒ�
		m_view_port[nNumber].MinZ = 0.0f;
		m_view_port[nNumber].MaxZ = 1.0f;

		// �r���[�|�[�g�ݒ�
		if (FAILED(m_pD3DDevice->SetViewport(&m_view_port[nNumber])))
		{
			return false;
		}

		break;

	default:
		break;
	}
	return true;
}

//=============================================================================
//�f�o�C�X�̎擾����
//=============================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}

D3DVIEWPORT9 CRenderer::GetViewPort(int nCount)
{
	return m_view_port[nCount];
}



