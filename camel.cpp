#include "framework.h"
#include "camel.h"

camel::camel()
{
}

camel::~camel()
{
}

HRESULT camel::init()
{
	//_camel = IMAGE->addImage("camel", "images/camel.bmp", 300, 267, true, RGB(255, 0, 255));

	////ó�������� ������
	//_ani1 = new animation;
	//_ani1->init(_camel->getWidth(), _camel->getHeight(), 75, 89);
	//_ani1->setDefPlayFrame(false, true);
	//_ani1->setFPS(1);

	////�迭���� ��Ƽ�
	//int arrAni[] = { 0,1,2,3,4,5,6,7,8,9 };
	//_ani2 = new animation;
	//_ani2->init(_camel->getWidth(), _camel->getHeight(), 75, 89);
	//_ani2->setPlayFrame(arrAni, 10, true);
	//_ani2->setFPS(1);


	//_ani3 = new animation;
	//_ani3->init(_camel->getWidth(), _camel->getHeight(), 75, 89);
	//_ani3->setPlayFrame(1, 10, false, true);
	//_ani3->setFPS(1);
	
	isLeft = false;
	isRight = false;
	isDown = false;
	isUp = false;

	//�Ŵ�����
	_camel = IMAGE->addFrameImage("camel", "images/camel.bmp", 300, 267, 4, 3, true, RGB(255, 0, 255));
	_red = IMAGE->addFrameImage("red", "images/����.bmp", 256, 88, 8, 2, true, RGB(255, 0, 255));

	_redRc = RectMake(WINSIZEX / 2, WINSIZEY / 2, _red->getFrameWidth(), _red->getFrameHeight());
	_x = 100;
	_y = 100;
	_speed = 2;

	ANIMATION->addDefAnimation("ani1", "red", 10, true, false);


	int arrLen[] = { 0,1,2,3 };
	ANIMATION->addAnimation("ani2", "red", arrLen, 4, 5, true);

	ANIMATION->addAnimation("ani3", "red", 4, 7, 10, false, true);


	ANIMATION->addAnimation("redUp", "red", 4, 7, 5, false, true);
	ANIMATION->addAnimation("redDown", "red", 0, 3, 5, false, true);
	ANIMATION->addAnimation("redRight", "red", 8, 11, 5, false, true);
	ANIMATION->addAnimation("redLeft", "red", 12, 15, 5, false, true);

	//����  �ִϸ��̼� ����
	_ani = ANIMATION->findAnimation("ani1");

	isKeyDown = false;

	return S_OK;
}

void camel::release()
{
	//SAFE_DELETE(_ani1);
	//SAFE_DELETE(_ani2);
	//SAFE_DELETE(_ani3);
}

void camel::update()
{
	direct = DIRECTION::IDLE;
	if (isUp && (InputManager->isStayKeyDown(VK_RIGHT) || InputManager->isStayKeyDown(VK_LEFT)))
	{
		_y -= _speed;
		if (InputManager->isOnceKeyUp(VK_UP)) isUp = false;
		if (InputManager->isStayKeyDown(VK_RIGHT))_x += _speed;
		if (InputManager->isStayKeyDown(VK_LEFT))_x -= _speed;
		direct = DIRECTION::TOP;
	}
	else if (isRight && (InputManager->isStayKeyDown(VK_UP) || InputManager->isStayKeyDown(VK_DOWN)))
	{
		_x += _speed;
		if (InputManager->isOnceKeyUp(VK_RIGHT)) isRight = false;
		if (InputManager->isStayKeyDown(VK_DOWN))_y += _speed;
		if (InputManager->isStayKeyDown(VK_UP))_y -= _speed;
		direct = DIRECTION::RIGHT;
	}
	else if (isDown && (InputManager->isStayKeyDown(VK_RIGHT) || InputManager->isStayKeyDown(VK_LEFT)))
	{
		_y += _speed;
		if (InputManager->isOnceKeyUp(VK_DOWN)) isDown = false;
		if (InputManager->isStayKeyDown(VK_RIGHT))_x += _speed;
		if (InputManager->isStayKeyDown(VK_LEFT))_x -= _speed;
		direct = DIRECTION::DOWN;
	}
	else if (isLeft && (InputManager->isStayKeyDown(VK_UP) || InputManager->isStayKeyDown(VK_DOWN)))
	{
		_x -= _speed;
		if (InputManager->isOnceKeyUp(VK_LEFT)) isLeft = false;
		if (InputManager->isStayKeyDown(VK_DOWN))_y += _speed;
		if (InputManager->isStayKeyDown(VK_UP))_y -= _speed;
		direct = DIRECTION::LEFT;
	}
	else if (InputManager->isStayKeyDown(VK_UP))
	{
		_y -= _speed;
		isUp = true;
		isLeft = false;
		isRight = false;
		isDown = false;
		direct = DIRECTION::TOP;
	}
	else if (InputManager->isStayKeyDown(VK_RIGHT))
	{
		_x += _speed;
		isRight = true;
		isLeft = false;
		isDown = false;
		isUp = false;
		direct = DIRECTION::RIGHT;
	}
	else if (InputManager->isStayKeyDown(VK_DOWN))
	{
		_y += _speed;
		isDown = true;
		isLeft = false;
		isRight = false;
		isUp = false;
		direct = DIRECTION::DOWN;
	}
	else if (InputManager->isStayKeyDown(VK_LEFT))
	{
		_x -= _speed;
		isLeft = true;
		isRight = false;
		isDown = false;
		isUp = false;
		direct = DIRECTION::LEFT;
	}
	else
	{
		isLeft = false;
		isRight = false;
		isDown = false;
		isUp = false;
	}

	////���콺 ���� ��ư���� ȭ�� �̵� ��� -> ���� ĳ������ x,y�� ���� �����Ͽ� �̵� �ϴ� ������ �Ǿ�����
	//if (!isKeyDown) //���� ���콺�� ���� ��ǥ�� ǥ�� �뵵
	//{
	//	m_currentX =  _x + m_ptMouse.x;
	//	m_currentY =  _x + m_ptMouse.y;
	//}
	//if (InputManager->isStayKeyDown(VK_RBUTTON))
	//{
	//	isKeyDown = true;

	//	m_nextX = _x + m_ptMouse.x;
	//	m_nextY = _x + m_ptMouse.y;
	//	if (m_nextX < m_currentX) //���콺�� �������� �̵���Ű�� ȭ���� ���������� �̵��Ѵ�
	//	{
	//		_x = _x + (m_currentX - m_nextX);
	//		if (_x > MAPSIZE)  _x = MAPSIZE - IMAGE->findImage("red")->getFrameWidth(); //��ǥ(ĳ����)�� ȭ�� ������ �̵� ���� �� ����ó��
	//	}
	//	
	//	if (m_nextX > m_currentX) //���콺�� ���������� �̵���Ű�� ȭ���� �������� �̵��Ѵ�
	//	{
	//		_x = _x - (m_nextX - m_currentX);
	//		if (_x < 0) _x = 0; //��ǥ(ĳ����)�� ȭ�� ������ �̵� ���� �� ����ó��
	//	}

	//	if (m_nextY < m_currentY) //���콺�� �������� �̵���Ű�� ȭ���� �Ʒ������� �̵��Ѵ�
	//	{
	//		_y = _y + (m_currentY - m_nextY);
	//		if (_y > MAPSIZE) _y = MAPSIZE - IMAGE->findImage("red")->getFrameHeight() * 2; //��ǥ(ĳ����)�� ȭ�� ������ �̵� ���� �� ����ó��
	//	}

	//	if (m_nextY > m_currentY) //���콺�� �Ʒ������� �̵���Ű�� ȭ���� �������� �̵��Ѵ�
	//	{
	//		_y = _y - (m_nextY - m_currentY);
	//		if (_y < 0) _y = 0; //��ǥ(ĳ����)�� ȭ�� ������ �̵� ���� �� ����ó��
	//	}
	//}
	//else isKeyDown = false;

	switch (direct)
	{
	case DIRECTION::LEFT:
		_ani = ANIMATION->findAnimation("redLeft");
		ANIMATION->start("redLeft");
		break;
	case DIRECTION::RIGHT:
		_ani = ANIMATION->findAnimation("redRight");
		ANIMATION->start("redRight");
		break;
	case DIRECTION::TOP:
		_ani = ANIMATION->findAnimation("redUp");
		ANIMATION->start("redUp");
		break;
	case DIRECTION::DOWN:
		_ani = ANIMATION->findAnimation("redDown");
		ANIMATION->start("redDown");
		break;
	default:
		break;
	}

	/*_ani1->frameUpdate(0.4f);
	_ani2->frameUpdate(0.1f);
	_ani3->frameUpdate(1.0f);*/

	_redRc = RectMake(_x, _y, _red->getFrameWidth(), _red->getFrameHeight());

}

void camel::render()
{
	Rectangle(getMapDC(), _redRc.left, _redRc.top, _redRc.right, _redRc.bottom);
	_red->aniRender(getMapDC(), _redRc.left, _redRc.top, _ani);
	
	char str[100];
	sprintf_s(str, "left : %d, right : %d, down : %d, up : %d", isLeft, isRight, isDown, isUp);
	SetTextColor(getMemDC(), RGB(255, 255, 0));
	TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, str, lstrlen(str));
}