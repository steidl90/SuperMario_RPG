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
	//타이머란 일정한 주기마다 정해진 함수를 실행한다.
	//1 : 윈도우 핸들
	//2 :  타이머 번호
	//3 :  타이머주기 1000=1초
	//4 :  주기마다 실행할 함수
	//NULL이면 WM_TIMER가 실행
	//SetTimer(m_hWnd, 1, 10, NULL);
	//매니저 초기화
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
		//매니저 초기화
		InputManager->init();
		IMAGE->init();
		TIME->init();
		SOUND->init();
		// 새로추가
		PLAYERDATA->init();
	}


	return E_NOTIMPL;
}

//void gameNode::setBackBuffer()
//{
//	_backBuffer = new image;
//	_backBuffer->init(WINSIZEX, WINSIZEY);
//}

void gameNode::release()
{	//타이머 해제
	if (_managerInit)
	{
		//해제를 안하면 종료를 해도 메모리가 줄줄줄~
		KillTimer(m_hWnd, 1);
		//매니저 해제
		InputManager->releaseSingleton();
		IMAGE->releaseSingleton();
		TIME->releaseSingleton();
		RND->releaseSingleton();
		TXT->releaseSingleton();
		SCENE->releaseSingleton();
		SOUND->releaseSingleton();
		EFFECT->releaseSingleton();

		EFFECT->release();
		SCENE->release();
		IMAGE->release();
		TIME->release();
		SOUND->release();
		// 새로추가
		PLAYERDATA->releaseSingleton();
		PLAYERDATA->release();
		ZORDER->releaseSingleton();
		ZORDER->release();
	}

	ReleaseDC(m_hWnd, _hdc);
	//SAFE_DELETE(_backBuffer);

}

void gameNode::update()
{
	//더블버퍼 이후 사용하지 않는다 true->false
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
	case WM_SIZE:
		GetClientRect(hWnd, &_rect);		//20210816추가 - 윈도우창 사이즈 담기
		break;

	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		break;
	}//end of switch

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}