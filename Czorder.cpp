#include "framework.h"
#include "Czorder.h"

void Czorder::release()
{
	_vZorder.clear();
}

void Czorder::zorderRender(image* img, float z, float bottom, int destX, int destY)
{
	tagZorder _zo(ZORDERKIND::IMG_NOMAL, img, z, destX, destY);
	_zo.bottom = bottom;
	_vZorder.push_back(_zo);
}

void Czorder::zorderRender(image* img, float z, float bottom, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	tagZorder _zo(ZORDERKIND::IMG_NOMAL_SOUR, img, z, destX, destY);
	_zo.bottom = bottom;
	_zo.sourX = sourX;
	_zo.sourY = sourY;
	_zo.sourWidth = sourWidth;
	_zo.sourHeight = sourHeight;
	_vZorder.push_back(_zo);
}

void Czorder::zorderFrameRender(image* img, float z, float bottom, int destX, int destY, int frameX, int frameY)
{
	tagZorder _zo(ZORDERKIND::IMG_FRAME, img, z, destX, destY);
	_zo.bottom = bottom;
	_zo.frameX = frameX;
	_zo.frameY = frameY;
	_vZorder.push_back(_zo);
}

void Czorder::zorderAlphaRender(image* img, float z, float bottom, int destX, int destY, BYTE alpha)
{
	tagZorder _zo(ZORDERKIND::IMG_ALPHA, img, z, destX, destY);
	_zo.bottom = bottom;
	_zo.alpha = alpha;
	_vZorder.push_back(_zo);
}

void Czorder::zorderAlphaRender(image* img, float z, float bottom, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	tagZorder _zo(ZORDERKIND::IMG_ALPHA_SOUR, img, z, destX, destY);
	_zo.bottom = bottom;
	_zo.sourX = sourX;
	_zo.sourY = sourY;
	_zo.sourWidth = sourWidth;
	_zo.sourHeight = sourHeight;
	_zo.alpha = alpha;
	_vZorder.push_back(_zo);
}

void Czorder::zorderAlphaFrameRender(image* img, float z, float bottom, int destX, int destY, int frameX, int frameY, BYTE alpha)
{
	tagZorder _zo(ZORDERKIND::IMG_ALPHA_FRAME, img, z, destX, destY);
	_zo.bottom = bottom;
	_zo.frameX = frameX;
	_zo.frameY = frameY;
	_zo.alpha = alpha;
	_vZorder.push_back(_zo);
}

void Czorder::zorderAniRender(image* img, float z, float bottom, int destX, int destY, animation* ani)
{
	tagZorder _zo(ZORDERKIND::IMG_ANI, img, z, destX, destY);
	_zo.bottom = bottom;
	_zo.ani = ani;
	_vZorder.push_back(_zo);
}

void Czorder::zorderRectangle(RECT rc, float z)
{
	tagZorder _zo(ZORDERKIND::IMG_RECTANGLE, nullptr, z, 0, 0);
	_zo.bottom = rc.bottom;
	_zo.rc = rc;
	_vZorder.push_back(_zo);
}



inline void Czorder::zorderSort()
{
	stable_sort(_vZorder.begin(), _vZorder.end(), zordorCompare);
}

bool Czorder::zordorCompare(const tagZorder& z1, const tagZorder& z2)
{
	if (z1.z < z2.z)
	{
		return true;
	}
	else if (z1.z == z2.z)
	{
		if (z1.bottom < z2.bottom)
		{
			return true;
		}
		else if (z1.bottom == z2.bottom)
		{
			if (z1.destX < z2.destX)
			{
				return true;
			}
			else if (z1.destX == z2.destX)
			{
				if (&z1 < &z2) return true;
			}
		}
	}
	return false;
}

void Czorder::zorderTotalRender(HDC hdc)
{
	this->zorderSort();

	for (int i = 0; i < _vZorder.size(); i++)
	{
		switch (_vZorder[i].kind)
		{
		case ZORDERKIND::IMG_NOMAL:
			_vZorder[i].img->render(hdc, _vZorder[i].destX, _vZorder[i].destY);
			break;
		case ZORDERKIND::IMG_NOMAL_SOUR:
			_vZorder[i].img->render(hdc, _vZorder[i].destX, _vZorder[i].destY, _vZorder[i].sourX, _vZorder[i].sourY, _vZorder[i].sourWidth, _vZorder[i].sourHeight);
			break;
		case ZORDERKIND::IMG_FRAME:
			_vZorder[i].img->frameRender(hdc, _vZorder[i].destX, _vZorder[i].destY, _vZorder[i].frameX, _vZorder[i].frameY);
			break;
		case ZORDERKIND::IMG_ALPHA:
			_vZorder[i].img->alphaRender(hdc, _vZorder[i].destX, _vZorder[i].destY, _vZorder[i].alpha);
			break;
		case ZORDERKIND::IMG_ALPHA_SOUR:
			_vZorder[i].img->alphaRender(hdc, _vZorder[i].destX, _vZorder[i].destY, _vZorder[i].sourX, _vZorder[i].sourY, _vZorder[i].sourWidth, _vZorder[i].sourHeight, _vZorder[i].alpha);
			break;
		case ZORDERKIND::IMG_ALPHA_FRAME:
			_vZorder[i].img->alphaFrameRender(hdc, _vZorder[i].destX, _vZorder[i].destY, _vZorder[i].frameX, _vZorder[i].frameY, _vZorder[i].alpha);
			break;
		case ZORDERKIND::IMG_ANI:
			_vZorder[i].img->aniRender(hdc, _vZorder[i].destX, _vZorder[i].destY, _vZorder[i].ani);
			break;
		case ZORDERKIND::IMG_RECTANGLE:
			Rectangle(hdc, _vZorder[i].rc.left, _vZorder[i].rc.top, _vZorder[i].rc.right, _vZorder[i].rc.bottom);
		}
	}
	//∫§≈Õ√ ±‚»≠
	_vZorder.clear();
}