#include "stdafx.h"
#include "GameStudy.h"

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize();	
   
	return S_OK;
}

//해제
void GameStudy::release(void)
{
	GameNode::release();
}

//화면갱신
void GameStudy::update(void)
{
	GameNode::update();
 
}

//화면출력
void GameStudy::render(HDC hdc)
{
   
}

//숙제

//당구
//포켓볼 - 공 색도 있다. 번호도 있다.
//흰공. 클릭 후 땡기면 방향과 힘을 받아 공이 굴러간다.
//땡기면 방향 표시를 해줘야 한다.
//땡기면 공이 움직일 예상 경로가 뜬다.
//구멍이 6개 있고 그 안에 공을 넣는다.
//탄성충돌?

//가운데 탱크
//키보드 방향키로 탱크움직임. 앞 방향 개념이 있고, 죄우 누르면 방향이 앞뒤를 누르면 앞, 뒤로 움직인다.
//마우스로 포신 방향이 움직인다.
//마우스 클릭으로 발사
//적 등장 사방에서
//등장하면 플레이어를 보고 포탄을 쏜다.
//맞으면 에너지 달고, 적 맞으면 죽음 한방에

//이거 하면 실력 늘음
//1p 2p 개녕
//각각 원이 있다.
//원 끝에 작은 원ㅇ 있고, 방향이 잇다.
//좌우 누르면 방향바뀜
//스페이스바 누르면 총알 발사
//서로 몸통을 맟춰 점수 획득
//쏠수도 있지만 방어 가능
//작은 원 맞으면 총알이 튕겨나감
//화면 상하벽에 맞으면 튕겨나감
//좌우는 밖으로 나감
//20발 맥스
//자기총알 자기가 맞음
//총알끼리 부딛힘