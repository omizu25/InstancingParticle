//**************************************************
// 
// effect.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _EFFECT_H_	//���̃}�N����`������ĂȂ�������
#define _EFFECT_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "object3D.h"

//==================================================
// ��`
//==================================================
class CEffect : public CObject3D
{
	/* ��` */
public:
	static const float MAX_WIDTH;	// ���̍ő�l
	static const float MIN_WIDTH;	// ���̍ŏ��l
	static const float STD_WIDTH;	// ���̕W���l
	static const float MAX_HEIGHT;	// �����̍ő�l
	static const float MIN_HEIGHT;	// �����̍ŏ��l
	static const float STD_HEIGHT;	// �����̕W���l

private:
	static const int MAX_LIFE;		// �����̍ő�l

	/* ���ÓI�����o�֐��� */
public:
	static CEffect* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const D3DXCOLOR& col);	// ����
	static int GetNumAll();	// �����̎擾
	static void SetScale(const D3DXVECTOR2& scale);	// �X�P�[���̐ݒ�
	static const D3DXVECTOR2& GetScale();			// �X�P�[���̎擾

	/* ���ÓI�����o�ϐ��� */
private:
	static int m_numAll;		// ����
	static D3DXVECTOR2 m_scale;	// �X�P�[��

	/* �������o�֐��� */
public:
	CEffect();				// �f�t�H���g�R���X�g���N�^
	~CEffect() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

	/* �������o�ϐ��� */
private:
	D3DXVECTOR3 m_move;	// �ړ���
	int m_life;			// ����
};

#endif // !_EFFECT_H_
