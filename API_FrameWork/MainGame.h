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

public:
	//����
	void Spwan_Normal_Monster(float _fX, float _fY);
	void Spwan_Kamikaze_Monster(float _fX, float _fY);
	void Spwan_Focus_Monster(float _fX, float _fY);
	void Spwan_Bounce_Monster(float _fX, float _fY);
	void Spwan_Shotgun_Monster(float _fX, float _fY);
	void Spwan_Shield_Monster(float _fX, float _fY);
	void Spwan_Trap_Monster(float _fX, float _fY);


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



	int iTime;
	MAINGAME::STATE		m_eState;
	MAINGAME::STATE		m_ePrev;
	HFONT				m_Font, m_Old_Font;
	HBRUSH				m_Screen;

};


#endif // !__MAINGAME_H__
