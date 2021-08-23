#include "framework.h"
#include "animation.h"

animation::animation() :_frameNum(0), _frameWidth(0), _frameHeight(0), _loop(false),
_elapseSec(0), _nowPlayIndex(0), _play(false)
{
}

animation::~animation()
{
}

HRESULT animation::init(int totalW, int totalH, int frameW, int frameH)
{
	//가로 프레임 갯수
	_frameWidth = frameW;
	int frameWidthNum = totalW / _frameWidth;

	//세로 프레임 갯수
	_frameHeight = frameH;
	int frameHeightNum = totalH / _frameHeight;

	//총 프레임 수
	_frameNum = frameWidthNum * frameHeightNum;


	//프레임 위치 목록 셋팅 하자.
	_frameList.clear();

	for (int i = 0; i < frameHeightNum; i++)
	{
		for (int j = 0; j < frameWidthNum; j++)
		{
			POINT framePos;
			framePos.x = j * _frameWidth;
			framePos.y = i * _frameHeight;

			//프레임 위치 목록 추가하기
			_frameList.push_back(framePos);
		}
	}

	//기본 프레임으로 셋팅하자.
	setDefPlayFrame();
	return S_OK;
}

void animation::setDefPlayFrame(bool reverse, bool loop)
{
	_loop = loop;
	_playList.clear();

	if (reverse)
	{
		if (_loop)
		{
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
			for (int i = _frameNum - 1; i > 0; i--)
			{
				_playList.push_back(i);
			}

		}
		else
		{
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
			for (int i = _frameNum - 1; i >= 0; i--)
			{
				_playList.push_back(i);
			}
		}
	}
	else
	{
		for (int i = 0; i < _frameNum; i++)
		{
			_playList.push_back(i);
		}
	}

}

void animation::setPlayFrame(int* playArr, int arrLen, bool loop)
{
	_loop = loop;
	_playList.clear();

	for (int i = 0; i < arrLen; i++)
	{
		_playList.push_back(playArr[i]);
	}
}

void animation::setPlayFrame(int start, int end, bool reverse, bool loop)
{
	_endPlayIndex = end;
	_loop = loop;
	_playList.clear();

	//시작과 끝이 같은경우(프레임구간) 재생 하지 말자
	if (start == end)
	{
		_playList.clear();
		stop();
		return;
	}

	else if (start > end)
	{

		if (reverse)
		{
			if (_loop)
			{

				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}

				for (int i = end + 1; i < start; i++)
				{
					_playList.push_back(i);
				}
			}

			else
			{

				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}

				for (int i = end + 1; i <= start; i++)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			for (int i = start; i <= end; i--)
			{
				_playList.push_back(i);
			}
		}
	}

	else
	{
		if (reverse)
		{
			if (_loop)
			{
				for (int i = start; i <= end; i++)
				{
					_playList.push_back(i);
				}
				for (int i = end - 1; i > start; i--)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i <= end; i++)
				{
					_playList.push_back(i);
				}

				for (int i = end - 1; i <= start; i--)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{

			for (int i = start; i <= end; i++)
			{
				_playList.push_back(i);
			}
		}
	}
}

void animation::setFPS(int framePerSec)
{
	_frameUpdateSec = 1.0f / framePerSec;
}

void animation::frameUpdate(float elapsedTime)
{
	if (_play)
	{
		_elapseSec += elapsedTime;

		if (_elapseSec >= _frameUpdateSec)
		{
			_elapseSec -= _frameUpdateSec;
			_nowPlayIndex++;

			if (_nowPlayIndex == _playList.size())
			{
				if (_loop)
				{
					_nowPlayIndex = 0;
				}
				else
				{
					_nowPlayIndex--;
					_play = false;
				}
			}
		}
	}
}

void animation::start()
{
	_play = true;
	_nowPlayIndex = 0;
}

void animation::fullstart()
{
	_play = true;
	if (_nowPlayIndex == _endPlayIndex)
	{
		stop();
	}
}

void animation::stop()
{
	_play = false;
	_nowPlayIndex = 0;
}


void animation::pause()
{
	_play = false;
}

void animation::resume()
{
	_play = true;
}

