//=============================================================================
//
// ���͏��� [input.h]
// Author1 : KOZUNA HIROHITO
//
//=============================================================================
#ifndef _INPUT_H_		//���̃}�N����`������Ȃ�������
#define _INPUT_H_		//2�d�C���N���[�h�h�~�̃}�N����`

//----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------------------------------------------
#include "input_keyboard.h"

//----------------------------------------------------------------------------
//�N���X��`
//----------------------------------------------------------------------------
class CInput
{
public:
	enum STAN_DART_INPUT_KEY
	{
		KEY_UP = 0,
		KEY_DOWN,
		KEY_LEFT,
		KEY_RIGHT,
		KEY_DECISION,
	};

	CInput();
	~CInput();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//���͏����S���̏�����
	void Uninit();									//���͏����S���̏I������
	void Update();									//���͏����S���̍X�V����
	static CInput *Create();
	static CInput *GetKey() { return m_Input; }
	bool Press(STAN_DART_INPUT_KEY key);
	bool Trigger(STAN_DART_INPUT_KEY key);
	bool Shot(D3DXVECTOR3* pRot);

private:
	CInputKeyboard *m_pKeyboard;
	static CInput *m_Input;
};

#endif
