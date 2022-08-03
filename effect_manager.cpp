//**************************************************
// 
// effect_manager.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "effect_manager.h"
#include "utility.h"
#include "effect.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const int CEffectManager::MIN_INTERVAL = 1;
const int CEffectManager::STD_INTERVAL = 5;
const int CEffectManager::MAX_INTERVAL = 120;
const int CEffectManager::MIN_QUANTITY = 0;
const int CEffectManager::STD_QUANTITY = 300;

//==================================================
// �ÓI�����o�ϐ�
//==================================================
CEffectManager* CEffectManager::m_pEffectManager = nullptr;

//--------------------------------------------------
// �C���X�^���X�̎擾
//--------------------------------------------------
CEffectManager* CEffectManager::GetInstanse()
{
	if (m_pEffectManager == nullptr)
	{// null�`�F�b�N
		m_pEffectManager = new CEffectManager;
		m_pEffectManager->Reset();
	}

	return m_pEffectManager;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CEffectManager::CEffectManager() : 
	m_time(0),
	m_interval(0),
	m_quantity(0)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CEffectManager::~CEffectManager()
{
}

//--------------------------------------------------
// ���Z�b�g
//--------------------------------------------------
void CEffectManager::Reset()
{
	m_time = 0;
	m_interval = STD_INTERVAL;
	m_quantity = STD_QUANTITY;
}

//--------------------------------------------------
// �p�[�e�B�N������
//--------------------------------------------------
void CEffectManager::ParticleCreate()
{
	m_time++;

	if ((m_time % m_interval) != 0)
	{// ���Ԋu�҂�
		return;
	}

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	float width = 600.0f;
	float height = 400.0f;

	//pos.x = FloatRandam(width, -width);
	//pos.y = FloatRandam(height, -height);

	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	col.r = FloatRandam(1.0f, 0.0f);
	col.g = FloatRandam(1.0f, 0.0f);
	col.b = FloatRandam(1.0f, 0.0f);

	// �p�[�e�B�N��
	Particle(pos, col);
}

//--------------------------------------------------
// �Ԋu�̐ݒ�
//--------------------------------------------------
void CEffectManager::SetInterval(const int interval)
{
	m_interval = interval;
}

//--------------------------------------------------
// �Ԋu�̎擾
//--------------------------------------------------
const int CEffectManager::GetInterval() const
{
	return m_interval;
}

//--------------------------------------------------
// �ʂ̐ݒ�
//--------------------------------------------------
void CEffectManager::SetQuantity(const int quantity)
{
	m_quantity = quantity;
}

//--------------------------------------------------
// �ʂ̎擾
//--------------------------------------------------
const int CEffectManager::GetQuantity() const
{
	return m_quantity;
}

//--------------------------------------------------
// �p�[�e�B�N��
//--------------------------------------------------
void CEffectManager::Particle(const D3DXVECTOR3& pos, const D3DXCOLOR& col)
{
	D3DXCOLOR randomCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float rot = 0.0f;

	for (int i = 0; i < m_quantity; i++)
	{
		rot = (D3DX_PI * 2.0f) / m_quantity * i;

		// �p�x�̐��K��
		NormalizeAngle(&rot);

		float random = FloatRandam(20.0f, 0.1f);

		move.x = sinf(rot) * random;
		move.y = cosf(rot) * random;

		randomCol.r = col.r + FloatRandam(0.25f, -0.25f);
		randomCol.g = col.g + FloatRandam(0.25f, -0.25f);
		randomCol.b = col.b + FloatRandam(0.25f, -0.25f);

		// ����
		CEffect::Create(pos, move, randomCol);
	}
}
