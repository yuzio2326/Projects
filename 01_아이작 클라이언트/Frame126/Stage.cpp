#include "stdafx.h"
#include "Stage.h"
#include "ObjMgr.h"
#include "AbstactFactory.h"
#include "Player.h"
#include "PlayerBody.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "Monster.h"
#include "Tears.h"
#include "Monster_Head.h"
#include "Rock.h"
#include "PlayerBullet.h"
#include "BombFly.h"
#include "Bomb.h"
#include "BossIsaac.h"
#include "TrollBomb.h"
#include "Goblin.h"
#include "SceneMgr.h"
#include "Wall.h"
#include "SideWall.h"
#include "Delerium.h"
#include "HeartInclude.h"
#include "ItemInclude.h"
#include "Door.h"
#include "OwnPickup.h"
#include "SoundMgr.h"
#include "ActiveUi1.h"
#include "Switch.h"





CStage::CStage()
{
}


CStage::~CStage()
{
	Release();
}

void CStage::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ground.bmp", L"Stage");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/maja2.bmp", L"Player");

	CTileMgr::Get_Instance()->Load_Tile();

	CObjMgr::Get_Instance()->AddObject(OBJ_PLAYER, CAbstactFactory<CPlayer>::Create());
	CObjMgr::Get_Instance()->AddObject(OBJ_PLAYER, CAbstactFactory<CPlayerBody>::Create());
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/the caves.ogg", SOUND_BGM, 0.5f);


	/*	CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CHPBar>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CHeart2>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CHeart3>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CHeart4>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CHeart5>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<COwnBomb>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<COwnKey>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<COwnCoin>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CBombNum>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CBombNum2>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CCoinNum>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CCoinNum2>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CKeyNum>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CKeyNum2>::Create());
*/



	/*CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CHPBar>::Create());
	CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CHeart2>::Create());
	CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CHeart3>::Create());
	CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CHeart4>::Create());
	CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CHeart5>::Create());
*/

	//CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CHPBar>::Create(128.f, 32.f));
	//CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CHPBar>::Create(160.f, 32.f));

	//실행확인용
	//CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstactFactory<CDelerium>::Create());

	//몬스터 스폰 스위치
	CObjMgr::Get_Instance()->AddObject(OBJ_DOOR, CAbstactFactory<CSwitch>::Create(400,400));

	//벽만들기
	CObjMgr::Get_Instance()->AddObject(OBJ_WALL, CAbstactFactory<CSideWall>::Create(32.f, 32.f));
	CObjMgr::Get_Instance()->AddObject(OBJ_WALL, CAbstactFactory<CSideWall>::Create(32.f, 704.f, 90.f));
	CObjMgr::Get_Instance()->AddObject(OBJ_WALL, CAbstactFactory<CSideWall>::Create(768.f, 704.f,180.f));
	CObjMgr::Get_Instance()->AddObject(OBJ_WALL, CAbstactFactory<CSideWall>::Create(768.f, 32.f,270.f));
	for (int i = 3; i <= 22; ++i)
	{
		CObjMgr::Get_Instance()->AddObject(OBJ_WALL, CAbstactFactory<CWall>::Create(32.f*i, 32.f));
		CObjMgr::Get_Instance()->AddObject(OBJ_WALL, CAbstactFactory<CWall>::Create(32.f*i, 704.f,180.f));
	}
	for (int j = 3; j <= 20; j++)
	{
		CObjMgr::Get_Instance()->AddObject(OBJ_WALL, CAbstactFactory<CWall>::Create(32.f, 32.f*j,90.f));
		CObjMgr::Get_Instance()->AddObject(OBJ_WALL, CAbstactFactory<CWall>::Create(768.f, 32.f*j, 270.f));
	}
	//for (int i = 3; i <= 22; ++i)
	//{
	//	CObjMgr::Get_Instance()->AddObject(OBJ_WALL, CAbstactFactory<CWall>::Create(32.f, 32.f*i));
	//	CObjMgr::Get_Instance()->AddObject(OBJ_WALL, CAbstactFactory<CWall>::Create(32.f, 568.f, 90.f));
	//}

	//CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, CAbstactFactory<CMagicMushroom>::Create());
	//CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, CAbstactFactory<CActive1>::Create(450,200));
	//CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, CAbstactFactory<CMagicMushroom>::Create(400,200));
	//CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, CAbstactFactory<Cmutantspider>::Create(350,200));
	//CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, CAbstactFactory<CPrismItem>::Create(300, 200));
	//CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, CAbstactFactory<CBigFan>::Create(250, 200));

	//CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, CAbstactFactory<CPickupCoin>::Create(420, 300));
	//CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, CAbstactFactory<CPickupBomb>::Create(480, 300));
	//CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, CAbstactFactory<CPickupHeart>::Create(450, 300));
	



	//CObjMgr::Get_Instance()->AddObject(OBJ_BOMB, CAbstactFactory<CTrollBomb>::Create());
	//CObjMgr::Get_Instance()->AddObject(OBJ_BULLET, CAbstactFactory<CPlayerBullet>::Create());
	//CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstactFactory<CGoblin>::Create());
	
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CHPBar>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CHeart2>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CHeart3>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CHeart4>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CHeart5>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<COwnBomb>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<COwnKey>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<COwnCoin>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CBombNum>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CBombNum2>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CCoinNum>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CCoinNum2>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CKeyNum>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CKeyNum2>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CActiveUi1>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CAtkStatus>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CAtkStatusNum>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CSpeedStatus>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CSpeedStatusNum>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CShotSpeedStatus>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CShotSpeedStatusNum>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CRangeStatus>::Create());
		CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CRangeStatusNum>::Create());


}

void CStage::Update(void)
{
	CTileMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
	//CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CHPBar>::Create());
	//CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CHeart2>::Create());
	//CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CHeart3>::Create());
	//CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CHeart4>::Create());
	//CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CHeart5>::Create());
	CSoundMgr::Get_Instance()->PlaySoundW(L"burning basement guitar layer_04.ogg", SOUND_BGM, 0.1f);

}

void CStage::Late_Update(void)
{
	CTileMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage::Render(HDC _DC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Stage");
	BitBlt(_DC, iScrollX, iScrollY, 1920, 1280, hMemDC, 0, 0, SRCCOPY);
	
	CTileMgr::Get_Instance()->Render(_DC);
	CObjMgr::Get_Instance()->Render(_DC);
}

void CStage::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BULLET);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BOMB);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_EXPLOSION);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_MONSTER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_FYING_MONSTER);
	CSoundMgr::Get_Instance()->StopAll();


}
