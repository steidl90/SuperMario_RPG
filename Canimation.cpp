#include "framework.h"
#include "Canimation.h"

Canimation::Canimation()
{
}

Canimation::~Canimation()
{
}

HRESULT Canimation::init()
{
	ANIMATION->addAnimation("마리오하", "마리오이동", 0, 2, 8, false, true);
	ANIMATION->addAnimation("마리오상", "마리오이동", 5, 7, 8, false, true);
	ANIMATION->addAnimation("마리오좌", "마리오이동", 10, 12, 8, false, true);
	ANIMATION->addAnimation("마리오우", "마리오이동", 15, 17, 8, false, true);
	ANIMATION->addAnimation("마리오좌하", "마리오이동", 20, 22, 8, false, true);
	ANIMATION->addAnimation("마리오좌상", "마리오이동", 25, 27, 8, false, true);
	ANIMATION->addAnimation("마리오우하", "마리오이동", 30, 32, 8, false, true);
	ANIMATION->addAnimation("마리오우상", "마리오이동", 35, 37, 8, false, true);
	ANIMATION->addAnimation("마리오기본공격", "마리오공격", 0, 6, 8, false, true);
	ANIMATION->addAnimation("피치기본공격", "피치공격", 0, 8, 8, false, true);
	ANIMATION->addAnimation("쿠파기본공격", "쿠파공격", 0, 9, 8, false, true);

	ANIMATION->addAnimation("사망", "사망이펙트", 0, 7, 8, false, true);

	ANIMATION->addDefAnimation("마리오상태", "마리오아이콘", 2, false, true);
	ANIMATION->addDefAnimation("피치상태", "피치아이콘", 2, false, true);
	ANIMATION->addDefAnimation("쿠파상태", "쿠파아이콘", 2, false, true);

	ANIMATION->addAnimation("굼바좌하", "굼바이동", 0, 2, 5, false, true);
	ANIMATION->addAnimation("굼바좌상", "굼바이동", 3, 5, 5, false, true);
	ANIMATION->addAnimation("굼바기본공격", "굼바공격", 0, 9, 8, false, true);

	ANIMATION->addAnimation("날개거북이좌하", "날개거북이이동", 0, 2, 5, false, true);
	ANIMATION->addAnimation("날개거북이좌상", "날개거북이이동", 3, 5, 5, false, true);
	ANIMATION->addAnimation("날개거북이기본공격", "날개거북이공격", 0, 2, 8, false, true);

	ANIMATION->addAnimation("가시돌이좌하", "가시돌이이동", 0, 2, 5, false, true);
	ANIMATION->addAnimation("가시돌이좌상", "가시돌이이동", 3, 5, 5, false, true);
	ANIMATION->addAnimation("가시돌이기본공격", "가시돌이공격", 0, 4, 8, false, true);

	return S_OK;
}
