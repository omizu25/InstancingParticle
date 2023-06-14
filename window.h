//**************************************************
// 
// window.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _WINDOW_H_	//���̃}�N����`������ĂȂ�������
#define _WINDOW_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>

//==================================================
// �N���X
//==================================================
class CWindow
{
	/* ��` */
public:

	/* �������o�֐��� */
public:
	CWindow();	// �f�t�H���g�R���X�g���N�^
	~CWindow();	// �f�X�g���N�^

public:
	HRESULT Init(HINSTANCE hInstance);	// ������
	void Uninit();	// �I��
	void Update();	// �X�V
	void Draw();	// �`��

public:
	LPDIRECT3DDEVICE9 GetDevice();	// �f�o�C�X�̎擾
	HWND GetWnd();					// �E�C���h�E�̎擾
	
	/* �������o�ϐ��� */
private:
	HWND m_hWnd;					// �E�C���h�E���
	LPDIRECT3D9 m_pD3D;				// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9 m_pD3DDevice;	// Device�I�u�W�F�N�g
};

#endif // !_WINDOW_H_
