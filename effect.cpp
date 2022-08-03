//**************************************************
// 
// effect.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "effect.h"
#include "application.h"
#include "camera.h"
#include "utility.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const int CEffect::MAX_LIFE = 100;
const float CEffect::STD_WIDTH = 24.0f;
const float CEffect::STD_HEIGHT = 60.0f;

//==================================================
// �ÓI�����o�ϐ�
//==================================================
int CEffect::m_numAll = 0;

//--------------------------------------------------
// ����
//--------------------------------------------------
CEffect* CEffect::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const D3DXCOLOR& col)
{
	if (m_numAll >= CObject::MAX_OBJECT)
	{// �ő吔���z����
		return nullptr;
	}

	CEffect* pEffect = nullptr;

	pEffect = new CEffect;
	
	if (pEffect != nullptr)
	{// null�`�F�b�N
		pEffect->Init();
		pEffect->m_move = move;
		pEffect->SetPos(pos);
		pEffect->SetCol(col);
	}

	return pEffect;
}

//--------------------------------------------------
// �����̎擾
//--------------------------------------------------
int CEffect::GetNumAll()
{
	return m_numAll;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CEffect::CEffect() :
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_life(0)
{
	m_numAll++;
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CEffect::~CEffect()
{
	m_numAll--;
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CEffect::Init()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_life = MAX_LIFE;

	// ������
	CObject3D::Init();

	// �T�C�Y�̐ݒ�
	CObject3D::SetSize(D3DXVECTOR3(STD_WIDTH, STD_HEIGHT, 0.0f));

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::LABEL_Effect);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CEffect::Uninit()
{
	// �I��
	CObject3D::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CEffect::Update()
{
	m_life--;

	if (m_life <= 0)
	{
		CObject::Release();
		return;
	}

	D3DXVECTOR3 pos = CObject3D::GetPos();

	pos += m_move;

	//�����E�ړ��ʂ��X�V (����������)
	m_move.x += (0.0f - m_move.x) * 0.05f;
	m_move.y += (0.0f - m_move.y) * 0.05f;

	float size = 5.0f;
	float width = 600.0f - ((STD_WIDTH * 0.5f) + size);
	float height = 400.0f - ((STD_HEIGHT * 0.5f) + size);

	// �͈͓��Ŕ���
	InRangeReflect(&pos, &m_move, D3DXVECTOR3(width, height, 0.0f));
	
	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	// �����̐ݒ�
	CObject3D::SetRot(atan2f(m_move.x, m_move.y));

	{
		float ratio = ((float)(MAX_LIFE - m_life) / MAX_LIFE);

		D3DXCOLOR col = CObject3D::GetCol();
		col.a = 1.0f - (ratio * ratio);

		// �F�̐ݒ�
		CObject3D::SetCol(col);
	}

	// �`��
	CObject3D::Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CEffect::Draw()
{
	// �`��
	CObject3D::Draw();
}
