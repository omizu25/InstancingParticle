//**************************************************
// 
// effect_manager.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _EFFECT_MANAGER_H_	//���̃}�N����`������ĂȂ�������
#define _EFFECT_MANAGER_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>

//==================================================
// ��`
//==================================================
class CEffectManager
{
	/* ��` */
public:
	static const int MIN_INTERVAL;	// �Ԋu�̍ŏ��l
	static const int MAX_INTERVAL;	// �Ԋu�̍ő�l
	static const int MIN_QUANTITY;	// �ʂ̍ŏ��l
	static const float MIN_WIDTH;	// ���̍ŏ��l
	static const float MAX_WIDTH;	// ���̍ő�l
	static const float MIN_HEIGHT;	// �����̍ŏ��l
	static const float MAX_HEIGHT;	// �����̍ő�l
	static const float MIN_MOVE;	// �ړ��ʂ̍ŏ��l
	static const float MAX_MOVE;	// �ړ��ʂ̍ő�l
	
private:
	static const int STD_INTERVAL;	// �Ԋu�̕W���l
	static const int STD_QUANTITY;	// �ʂ̕W���l
	static const float STD_MOVE;	// �ړ��ʂ̕W���l

	/* ���ÓI�����o�֐��� */
public:
	static CEffectManager* GetInstanse();	// �C���X�^���X�̎擾

	/* ���ÓI�����o�ϐ��� */
private:
	static CEffectManager* m_pEffectManager;	// �����̃N���X

	/* �������o�֐��� */
private:
	CEffectManager();	// �f�t�H���g�R���X�g���N�^

public:
	~CEffectManager();	// �f�X�g���N�^

public:
	void Reset();	// ���Z�b�g
	void ParticleCreate();	// �p�[�e�B�N������

public:
	void SetInterval(const int interval);	// �Ԋu�̐ݒ�
	const int GetInterval() const;			// �Ԋu�̎擾
	void SetQuantity(const int quantity);	// �ʂ̐ݒ�
	const int GetQuantity() const;			// �ʂ̎擾
	void SetWidth(const float width);		// ���̐ݒ�
	const float GetWidth() const;			// ���̎擾
	void SetHeight(const float height);		// �����̐ݒ�
	const float GetHeight() const;			// �����̎擾
	void SetMinMove(const float move);		// �ړ��ʂ̍ŏ��l�̐ݒ�
	const float GetMinMove() const;			// �ړ��ʂ̍ŏ��l�̎擾
	void SetMaxMove(const float move);		// �ړ��ʂ̍ő�l�̐ݒ�
	const float GetMaxMove() const;			// �ړ��ʂ̍ő�l�̎擾

private:
	void Particle(const D3DXVECTOR3& pos, const D3DXCOLOR& col);	// �p�[�e�B�N��

	/* �������o�ϐ��� */
private:
	int m_time;			// �^�C��
	int m_interval;		// �Ԋu
	int m_quantity;		// ��
	float m_width;		// ��
	float m_height;		// ����
	float m_minMove;	// �ړ��ʂ̍ŏ��l
	float m_maxMove;	// �ړ��ʂ̍ő�l
};

#endif // !_EFFECT_MANAGER_H_
