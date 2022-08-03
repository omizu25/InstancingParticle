//**************************************************
// 
// application.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _APPLICATION_H_	//���̃}�N����`������ĂȂ�������
#define _APPLICATION_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>

//==================================================
// �O���錾
//==================================================
class CRenderer;
class CInput;
class CTexture;
class CCamera;
class CInstancing;
class CImguiProperty;

//==================================================
// ��`
//==================================================
class CApplication
{
	/* ����`�� */
public:
	static const int SCREEN_WIDTH = 1280;	// �X�N���[���̕�
	static const int SCREEN_HEIGHT = 720;	// �X�N���[���̍���

private:
	static const bool FULL_SCREEN;	// �t���X�N���[���ɂ��邩�ǂ���

	/* ���ÓI�����o�֐��� */
public:
	static CApplication* GetInstanse();	// �C���X�^���X�̎擾

	/* ���ÓI�����o�ϐ��� */
private:
	static CApplication* m_pApplication;	// �����̃N���X

	/* �������o�֐��� */
private:
	CApplication();		// �f�t�H���g�R���X�g���N�^

public:
	~CApplication();	// �f�X�g���N�^

public:
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ������
	void Uninit(HWND hWnd, WNDCLASSEX wcex);		// �I��
	void Update();	// �X�V
	void Draw();	// �`��
	LPDIRECT3DDEVICE9 GetDevice();		// �f�o�C�X�̎擾
	CTexture* GetTexture();				// �e�N�X�`���̏��̎擾
	CCamera* GetCamera();				// �J�����̏��̎擾
	CInstancing* GetInstancing();		// �C���X�^���V���O�̎擾
	CImguiProperty* GetImguiProperty();	// imgui�̎擾

	/* �������o�ϐ��� */
private:
	CRenderer* m_pRenderer;				// �����_���[�̏��
	CInput* m_pInput;					// ���͂̏��
	CTexture* m_pTexture;				// �e�N�X�`���̏��
	CCamera* m_pCamera;					// �J�����̏��
	CInstancing* m_pInstancing;			// �C���X�^���V���O�̏��
	CImguiProperty* m_pImguiProperty;	// imgui�̏��
};

#endif // !_APPLICATION_H_
