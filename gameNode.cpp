#include "framework.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::init()
{
	//Ÿ�̸Ӷ� ������ �ֱ⸶�� ������ �Լ��� �����Ѵ�.
	//1 : ������ �ڵ�
	//2 :  Ÿ�̸� ��ȣ
	//3 :  Ÿ�̸��ֱ� 1000=1��
	//4 :  �ֱ⸶�� ������ �Լ�
	//NULL�̸� WM_TIMER�� ����
	//SetTimer(m_hWnd, 1, 10, NULL);
	//�Ŵ��� �ʱ�ȭ
	//setBackBuffer();
	/*InputManager->init();
	IMAGE->init();*/
	_hdc = GetDC(m_hWnd);
	_managerInit = false;

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(m_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		SetTimer(m_hWnd, 1, 10, NULL);
		//�Ŵ��� �ʱ�ȭ
		InputManager->init();
		IMAGE->init();
		TIME->init();
		SOUND->init();
		// �����߰�
		ITEM->init();
	}


	return E_NOTIMPL;
}

//void gameNode::setBackBuffer()
//{
//	_backBuffer = new image;
//	_backBuffer->init(WINSIZEX, WINSIZEY);
//}

void gameNode::release()
{	//Ÿ�̸� ����


	if (_managerInit)
	{
		//������ ���ϸ� ���Ḧ �ص� �޸𸮰� ������~
		KillTimer(m_hWnd, 1);
		//�Ŵ��� ����
		InputManager->releaseSingleton();
		IMAGE->releaseSingleton();
		TIME->releaseSingleton();
		RND->releaseSingleton();
		TXT->releaseSingleton();
		SCENE->releaseSingleton();
		SOUND->releaseSingleton();
		EFFECT->releaseSingleton();
		// �����߰�
		ITEM->releaseSingleton();
		DATA->releaseSingleton();


		EFFECT->release();
		SCENE->release();
		IMAGE->release();
		TIME->release();
		SOUND->release();
	}

	ReleaseDC(m_hWnd, _hdc);
	//SAFE_DELETE(_backBuffer);

}

void gameNode::update()
{
	//������� ���� ������� �ʴ´� true->false
	InvalidateRect(m_hWnd, NULL, false);
}
void gameNode::render(/*HDC hdc*/)
{
}

void CALLBACK zDeltaReset(HWND hWnd, UINT iMessage, UINT_PTR nIDEvent, DWORD dwTime)
{
	zDelta = 0;
}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (iMessage)
	{
	/*case WM_TIMER:
		this->update();
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		this->render(hdc);
		EndPaint(hWnd, &ps);
		break;*/
	case WM_MOUSEWHEEL:
		zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
		break;
	case WM_TIMER:
		SetTimer(hWnd, 1, 25, zDeltaReset);
		break;
	case WM_MOUSEMOVE:
		m_ptMouse.x = LOWORD(lParam);
		m_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:
			//PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		break;
	}//end of switch

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}