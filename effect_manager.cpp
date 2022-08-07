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
const int CEffectManager::MIN_CHANGE_TIMING = 1;
const int CEffectManager::MAX_CHANGE_TIMING = 120;
const int CEffectManager::STD_QUANTITY = 300;
const float CEffectManager::MIN_WIDTH = 0.0f;
const float CEffectManager::MAX_WIDTH = 600.0f;
const float CEffectManager::MIN_HEIGHT = 0.0f;
const float CEffectManager::MAX_HEIGHT = 400.0f;
const float CEffectManager::MIN_MOVE = 0.0f;
const float CEffectManager::MAX_MOVE = 100.0f;
const float CEffectManager::STD_MOVE = 20.0f;

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
	m_col(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)),
	m_time(0),
	m_changeTiming(0),
	m_interval(0),
	m_quantity(0),
	m_width(0.0f),
	m_height(0.0f),
	m_minMove(0.0f),
	m_maxMove(0.0f),
	m_colRandom(false)
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
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_time = 0;
	m_changeTiming = MIN_CHANGE_TIMING;
	m_interval = STD_INTERVAL;
	m_quantity = STD_QUANTITY;
	m_width = MAX_WIDTH;
	m_height = MAX_HEIGHT;
	m_minMove = MIN_MOVE;
	m_maxMove = STD_MOVE;
	m_colRandom = true;
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

	pos.x = FloatRandam(m_width, -m_width);
	pos.y = FloatRandam(m_height, -m_height);

	if (m_colRandom && ((m_time % m_changeTiming) == 0))
	{// �����_������
		m_col.r = FloatRandam(1.0f, 0.0f);
		m_col.g = FloatRandam(1.0f, 0.0f);
		m_col.b = FloatRandam(1.0f, 0.0f);
	}

	D3DXCOLOR col = m_col;
	
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
// �ύX�̃^�C�~���O�̐ݒ�
//--------------------------------------------------
void CEffectManager::SetChangeTiming(const int timing)
{
	m_changeTiming = timing;
}

//--------------------------------------------------
// �ύX�̃^�C�~���O�̎擾
//--------------------------------------------------
const int CEffectManager::GetChangeTiming() const
{
	return m_changeTiming;
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
// ���̐ݒ�
//--------------------------------------------------
void CEffectManager::SetWidth(const float width)
{
	m_width = width;
}

//--------------------------------------------------
// ���̎擾
//--------------------------------------------------
const float CEffectManager::GetWidth() const
{
	return m_width;
}

//--------------------------------------------------
// �����̐ݒ�
//--------------------------------------------------
void CEffectManager::SetHeight(const float height)
{
	m_height = height;
}

//--------------------------------------------------
// �����̎擾
//--------------------------------------------------
const float CEffectManager::GetHeight() const
{
	return m_height;
}

//--------------------------------------------------
// �ړ��ʂ̍ŏ��l�̐ݒ�
//--------------------------------------------------
void CEffectManager::SetMinMove(const float move)
{
	m_minMove = move;
}

//--------------------------------------------------
// �ړ��ʂ̍ŏ��l�̎擾
//--------------------------------------------------
const float CEffectManager::GetMinMove() const
{
	return m_minMove;
}

//--------------------------------------------------
// �ړ��ʂ̍ő�l�̐ݒ�
//--------------------------------------------------
void CEffectManager::SetMaxMove(const float move)
{
	m_maxMove = move;
}

//--------------------------------------------------
// �ړ��ʂ̍ő�l�̎擾
//--------------------------------------------------
const float CEffectManager::GetMaxMove() const
{
	return m_maxMove;
}

//--------------------------------------------------
// �F�̃����_�����邩�ǂ����̐ݒ�
//--------------------------------------------------
void CEffectManager::SetColRandom(const bool random)
{
	m_colRandom = random;
}

//--------------------------------------------------
// �F�̃����_�����邩�ǂ����̎擾
//--------------------------------------------------
const bool CEffectManager::GetColRandom() const
{
	return m_colRandom;
}

//--------------------------------------------------
// �F�̐ݒ�
//--------------------------------------------------
void CEffectManager::SetCol(const D3DXCOLOR& col)
{
	m_col = col;
}

//--------------------------------------------------
// �F�̎擾
//--------------------------------------------------
const D3DXCOLOR& CEffectManager::GetCol() const
{
	return m_col;
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

		float random = FloatRandam(m_maxMove, m_minMove);

		move.x = sinf(rot) * random;
		move.y = cosf(rot) * random;

		randomCol.r = col.r + FloatRandam(0.25f, -0.25f);
		randomCol.g = col.g + FloatRandam(0.25f, -0.25f);
		randomCol.b = col.b + FloatRandam(0.25f, -0.25f);

		// ����
		CEffect::Create(pos, move, randomCol);
	}
}
