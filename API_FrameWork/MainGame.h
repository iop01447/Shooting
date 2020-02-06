#pragma once
#ifndef __MAINGAME_H__
#define __MAINGAME_H__

class CObj;
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize();	// �ʱ�ȭ
	void Update();		// �� �����Ӹ��� ����(����)
	void Late_Update();
	void Render();		// �� �����Ӹ��� ����Լ�
	void Release();		// �޸� ���� �Լ�

	void Generate_Boss(); //���� ����
	void Generate_Monster_0();

private:
	HDC				m_DC;	// �׸��� �׸��� ���� ��ȭ��
	HDC				m_BackBufferDC;	
	HBITMAP			m_hBit, m_OldBit;

	CObj*			m_pPlayer;

	list<CObj*>		m_listObj[OBJID::END];


	DWORD		m_dwTime;
	int			m_iFPS;
	TCHAR		m_szFPS[16];

	int			m_iStage;
};


#endif // !__MAINGAME_H__
