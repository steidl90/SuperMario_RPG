#include "framework.h"
#include "CaStar.h"
#include "camera.h"
#include "Cplayer.h"
CaStar::CaStar()
{
    isButtonClick = false;
    isKeyUp = false;
}

CaStar::~CaStar(){}

HRESULT CaStar::init()
{
    _astarState = ASTAR_STATE::ASTAR_STATE_END;
    _selectType = TILE_TYPE::TILE_TYPE_EMPTY;
    _selectedTypeColor = RGB(255, 255, 255);

    _startPointSet = false;
    _endPointSet = false;

    for (size_t i = 0; i < TILE_Y; i++)
    {
        for (size_t j = 0; j < TILE_X; j++)
        {
            _tile[i][j].type = TILE_TYPE::TILE_TYPE_EMPTY;
            _tile[i][j].color = RGB(255, 255, 255);
            _tile[i][j].parent = NULL;
            _tile[i][j].F = BIGNUM;
            _tile[i][j].H = 0;
            _tile[i][j].i = i;
            _tile[i][j].j = j;
            _tile[i][j].rc = RectMake(WINSIZEX - (TILE_X + 1) * WIDTH + WIDTH * j,
                WINSIZEX / 3 + 9 - (TILE_Y / 2) * HEIGHT + HEIGHT * i, WIDTH, HEIGHT);
        }
    }
    //for (size_t i = 0; i < 5; i++)
    //{
    //    rc[i] = RectMake(15, 300 + i * 50, 25, 25);
    //}
    return S_OK;
}

HRESULT CaStar::init2()
{
    _astarState = ASTAR_STATE::ASTAR_STATE_END;
    _selectedTypeColor = RGB(255, 255, 255);

    _endPointSet = false;

    for (size_t i = 0; i < TILE_Y; i++)
    {
        for (size_t j = 0; j < TILE_X; j++)
        {
            //_tile[i][j].type = TILE_TYPE::TILE_TYPE_EMPTY;
            _tile[i][j].color = RGB(255, 255, 255);
            _tile[i][j].parent = NULL;
            _tile[i][j].F = BIGNUM;
            _tile[i][j].H = 0;
            _tile[i][j].i = i;
            _tile[i][j].j = j;
            _tile[i][j].rc = RectMake(WIDTH * j,
               WIDTH * i, WIDTH, HEIGHT);
        }
    }
    return S_OK;
}

void CaStar::release()
{

}

void CaStar::update()
{
    if ((m_currentTarget.x != m_targetIndex.x) || (m_currentTarget.y != m_targetIndex.y))
    {
        m_currentTarget.x = m_targetIndex.x;
        m_currentTarget.y = m_targetIndex.y;

        _openList.clear();
        _closeList.clear();
        m_fastLoad.clear();
        m_fastLoadLocation.clear();
        init2();
    }

   /* if (InputManager->isOnceKeyDown(VK_RBUTTON))
    {
        _openList.clear();
        _closeList.clear();
        m_fastLoad.clear();
        m_fastLoadLocation.clear();
        init2();
        isButtonClick = true;
    }
    else
    {
        isButtonClick = false;
        isKeyUp = true;
    }*/
  
    if (_astarState == ASTAR_STATE::ASTAR_STATE_END)
    {
        tileComposition();
    }
    if (_startPointSet && _endPointSet && _astarState == ASTAR_STATE::ASTAR_STATE_END)
    {
        tileInitializing();
    }
    if (_astarState == ASTAR_STATE::ASTAR_STATE_END || _astarState == ASTAR_STATE::ASTAR_STATE_FOUND || _astarState == ASTAR_STATE::ASTAR_STATE_NOWAY) return;

    addOpenList();
    caculateH();
    caculateF();
    addCloseList();
    checkArrive();
}

void CaStar::render()
{
}

void CaStar::tileComposition()
{
    typeColor(_selectType);

    //_startPointSet = false;

    for (size_t i = 0; i < TILE_Y; i++)
    {
        for (size_t j = 0; j < TILE_X; j++)
        {
            if (m_attribute[i * TILEX + j] == ATTRIBUTE::COLLISION_ON)
                _tile[i][j].type = TILE_TYPE::TILE_TYPE_WALL;
           if (m_startIndex.y == i && m_startIndex.x == j)
            {
                 _selectType = TILE_TYPE::TILE_TYPE_START;
                if (_tile[i][j].type == TILE_TYPE::TILE_TYPE_START)_startPointSet = false;

                _tile[i][j].type = _selectType;
                _tile[i][j].color = _selectedTypeColor;

                if (_selectType == TILE_TYPE::TILE_TYPE_START)
                {
                    if (_startPointSet)
                    {
                        _tile[_startY][_startX].color = RGB(255, 255, 255);
                        _tile[_startY][_startX].type = TILE_TYPE::TILE_TYPE_EMPTY;
                    }
                    _startPointSet = true;
                    _startX = j;
                    _startY = i;
                }
            }
        }
    }
    //POINT cameraMouse = m_ptMouse; // x y
    //cameraMouse.x += m_camera->getCameraPoint().x;
    //cameraMouse.y += m_camera->getCameraPoint().y;

    for (size_t i = 0; i < TILE_Y; i++)
    {
        for (size_t j = 0; j < TILE_X; j++)
        {
            //if (PtInRect(&_tile[i][j].rc, cameraMouse))
            //{
            //}
            if (m_targetIndex.y + 1 == i && m_targetIndex.x + 1 == j)
            {
                _selectType = TILE_TYPE::TILE_TYPE_END;
                if (_tile[i][j].type == TILE_TYPE::TILE_TYPE_END)_endPointSet = false;

                if (_selectType == TILE_TYPE::TILE_TYPE_END)
                {
                    if (_endPointSet)
                    {
                        _tile[_endY][_endX].color = RGB(255, 255, 255);
                        _tile[_endY][_endX].type = TILE_TYPE::TILE_TYPE_EMPTY;
                    }
                    _endPointSet = true;
                    _endX = j;
                    _endY = i;
                }
            }
        }
    }

}

void CaStar::tileInitializing()
{
    for (size_t i = 0; i < TILE_Y; i++)
    {
        for (size_t j = 0; j < TILE_X; j++)
        {
            switch (_tile[i][j].type)
            {
            case TILE_TYPE::TILE_TYPE_EMPTY:
            {
                _tile[i][j].walkable = true;
                _tile[i][j].listOn = false;
            }
            break;
            case TILE_TYPE::TILE_TYPE_WALL:
            {
                _tile[i][j].walkable = false;
                _tile[i][j].listOn = false;
            }
            break;
            case TILE_TYPE::TILE_TYPE_START:
            {
                _tile[i][j].walkable = false;
                _tile[i][j].listOn = false;
                _closeList.push_back(&_tile[i][j]);
            }
            break;
            case TILE_TYPE::TILE_TYPE_END:
            {
                _endX = j;
                _endY = i;
                _tile[i][j].walkable = true;
                _tile[i][j].listOn = false;
            }
            break;
            }
        }
    }
    _astarState = ASTAR_STATE::ASTAR_STATE_SEARCHING;
    _lastIndex = 0;
}

void CaStar::addOpenList()
{
    Ci = _closeList[_lastIndex]->i;
    Cj = _closeList[_lastIndex]->j;
    Cg = _closeList[_lastIndex]->G;

    if (Ci != 0)//0번째 줄이 아니면 상단라인 계산
    {
        if (_tile[Ci - 1][Cj].walkable)
        {
            if (!_tile[Ci - 1][Cj].listOn)
            {
                _tile[Ci - 1][Cj].listOn = true;
                _tile[Ci - 1][Cj].color = RGB(220, 255, 220);
                _tile[Ci - 1][Cj].G = Cg + 10;
                _tile[Ci - 1][Cj].parent = _closeList[_lastIndex];
                _openList.push_back(&_tile[Ci - 1][Cj]);
            }
            else
            {
                if (Cg + 10 < _tile[Ci - 1][Cj].G)
                {
                    _tile[Ci - 1][Cj].G = Cg + 10;
                    _tile[Ci - 1][Cj].parent = _closeList[_lastIndex];
                }
            }
        }
        if (Cj != 0) //좌상단 : 0번째 열이 아니라면
        {
            //좌상단 타일의 왼쪽이나 아래에 벽이 없다면
            if (_tile[Ci - 1][Cj - 1].walkable && (_tile[Ci - 1][Cj].walkable && _tile[Ci][Cj - 1].walkable))
            {
                if (!_tile[Ci - 1][Cj - 1].listOn)
                {
                    _tile[Ci - 1][Cj - 1].listOn = true;
                    _tile[Ci - 1][Cj - 1].color = RGB(220, 255, 220);
                    _tile[Ci - 1][Cj - 1].G = Cg + 14; //대각선 이므로
                    _tile[Ci - 1][Cj - 1].parent = _closeList[_lastIndex];
                    _openList.push_back(&_tile[Ci - 1][Cj - 1]);
                }
                else
                {
                    if (Cg + 14 < _tile[Ci - 1][Cj - 1].G)
                    {
                        _tile[Ci - 1][Cj - 1].G = Cg + 14;
                        _tile[Ci - 1][Cj - 1].parent = _closeList[_lastIndex];
                    }
                }
            }
        }
        if (Cj != TILE_X - 1) //우상단 : 마지막열이 아니라면
        {
            //우상단 타일의 왼쪽이나 아래에 벽이 없다면
            if (_tile[Ci - 1][Cj + 1].walkable && (_tile[Ci - 1][Cj].walkable && _tile[Ci][Cj + 1].walkable))
            {
                if (!_tile[Ci - 1][Cj + 1].listOn)
                {
                    _tile[Ci - 1][Cj + 1].listOn = true;
                    _tile[Ci - 1][Cj + 1].color = RGB(220, 255, 220);
                    _tile[Ci - 1][Cj + 1].G = Cg + 14;
                    _tile[Ci - 1][Cj + 1].parent = _closeList[_lastIndex];
                    _openList.push_back(&_tile[Ci - 1][Cj + 1]);
                }
                else
                {
                    if (Cg + 14 < _tile[Ci - 1][Cj + 1].G)
                    {
                        _tile[Ci - 1][Cj + 1].G = Cg + 14;
                        _tile[Ci - 1][Cj + 1].parent = _closeList[_lastIndex];
                    }
                }
            }
        }
    }
    if (Cj != 0) //좌측 : 0번째 열이 아니라면
    {
        //좌측타일이 이동가능하다면
        if (_tile[Ci][Cj - 1].walkable)
        {
            if (!_tile[Ci][Cj - 1].listOn)
            {
                _tile[Ci][Cj - 1].listOn = true;
                _tile[Ci][Cj - 1].color = RGB(220, 255, 220);
                _tile[Ci][Cj - 1].G = Cg + 10;
                _tile[Ci][Cj - 1].parent = _closeList[_lastIndex];
                _openList.push_back(&_tile[Ci][Cj - 1]);
            }
            else
            {
                if (Cg + 10 < _tile[Ci][Cj - 1].G)
                {
                    _tile[Ci][Cj - 1].G = Cg + 10;
                    _tile[Ci][Cj - 1].parent = _closeList[_lastIndex];
                }
            }
        }
    }
    if (Cj != TILE_X - 1) //우측 : 마지막열이 아니라면
    {
        if (_tile[Ci][Cj + 1].walkable) //우측타일이 이동가능하다면
        {
            if (!_tile[Ci][Cj + 1].listOn)
            {
                _tile[Ci][Cj + 1].listOn = true;
                _tile[Ci][Cj + 1].color = RGB(220, 255, 220);
                _tile[Ci][Cj + 1].G = Cg + 10;
                _tile[Ci][Cj + 1].parent = _closeList[_lastIndex];
                _openList.push_back(&_tile[Ci][Cj + 1]);
            }
            else
            {
                if (Cg + 10 < _tile[Ci][Cj + 1].G)
                {
                    _tile[Ci][Cj + 1].G = Cg + 10;
                    _tile[Ci][Cj + 1].parent = _closeList[_lastIndex];
                }
            }
        }
    }
    if (Ci != TILE_Y - 1) //마지막 행이 아니라면 하단 라인 계산
    {
        if (_tile[Ci + 1][Cj].walkable) //하단 가운데 타일이 이동가능하다면
        {
            if (!_tile[Ci + 1][Cj].listOn)
            {
                _tile[Ci + 1][Cj].listOn = true;
                _tile[Ci + 1][Cj].color = RGB(220, 255, 220);
                _tile[Ci + 1][Cj].G = Cg + 10;
                _tile[Ci + 1][Cj].parent = _closeList[_lastIndex];
                _openList.push_back(&_tile[Ci + 1][Cj]);
            }
            else
            {
                if (Cg + 10 < _tile[Ci + 1][Cj].G)
                {
                    _tile[Ci + 1][Cj].G = Cg + 10;
                    _tile[Ci + 1][Cj].parent = _closeList[_lastIndex];
                }
            }
        }
        if (Cj != 0) //좌하단 : 0번째 열이 아니라면
        {
            //좌하단 타일의 오른쪽이나 위에 벽이 없다면
            if (_tile[Ci + 1][Cj - 1].walkable && (_tile[Ci + 1][Cj].walkable && _tile[Ci][Cj - 1].walkable))
            {
                if (!_tile[Ci + 1][Cj - 1].listOn)
                {
                    _tile[Ci + 1][Cj - 1].listOn = true;
                    _tile[Ci + 1][Cj - 1].color = RGB(220, 255, 220);
                    _tile[Ci + 1][Cj - 1].G = Cg + 14;
                    _tile[Ci + 1][Cj - 1].parent = _closeList[_lastIndex];
                    _openList.push_back(&_tile[Ci + 1][Cj - 1]);
                }
                else
                {
                    if (Cg + 14 < _tile[Ci + 1][Cj - 1].G)
                    {
                        _tile[Ci + 1][Cj - 1].G = Cg + 14;
                        _tile[Ci + 1][Cj - 1].parent = _closeList[_lastIndex];
                    }
                }
            }
        }
        if (Cj != TILE_X - 1) //우하단 : 마지막 열이 아니라면
        {
            //우하단 타일의 오른쪽이나 위가 이동가능하다면
            if (_tile[Ci + 1][Cj + 1].walkable && (_tile[Ci + 1][Cj].walkable && _tile[Ci][Cj + 1].walkable))
            {
                if (!_tile[Ci + 1][Cj + 1].listOn)
                {
                    _tile[Ci + 1][Cj + 1].listOn = true;
                    _tile[Ci + 1][Cj + 1].color = RGB(220, 255, 220);
                    _tile[Ci + 1][Cj + 1].G = Cg + 14;
                    _tile[Ci + 1][Cj + 1].parent = _closeList[_lastIndex];
                    _openList.push_back(&_tile[Ci + 1][Cj + 1]);
                }
                else
                {
                    if (Cg + 14 < _tile[Ci + 1][Cj + 1].G)
                    {
                        _tile[Ci + 1][Cj + 1].G = Cg + 14;
                        _tile[Ci + 1][Cj + 1].parent = _closeList[_lastIndex];
                    }
                }
            }
        }
    }
}

void CaStar::caculateH()
{
    for (size_t i = 0; i < _openList.size(); i++)
    {
        int vertical = (_endX - _openList[i]->j) * 10;
        int horizontal = (_endY - _openList[i]->i) * 10;

        if (vertical < 0)vertical *= -1;
        if (horizontal < 0)horizontal *= -1;

        _openList[i]->H = vertical + horizontal;
    }
}

void CaStar::caculateF()
{
    for (size_t i = 0; i < _openList.size(); i++)
    {
        _openList[i]->F = _openList[i]->G + _openList[i]->H;
    }
}

void CaStar::addCloseList()
{
    if (_openList.size() == 0)
    {
        _astarState = ASTAR_STATE::ASTAR_STATE_NOWAY;
        return;
    }
    int index = 0;
    int lowest = BIGNUM;

    for (size_t i = 0; i < _openList.size(); i++)
    {
        if (_openList[i]->F < lowest)
        {
            lowest = _openList[i]->F;
            index = i;
        }
    }

    _openList[index]->color = RGB(180, 180, 255);
    _closeList.push_back(_openList[index]);
    _openList.erase(_openList.begin() + index);
    _lastIndex++;
}

void CaStar::checkArrive()
{
    if (_closeList[_lastIndex]->i == _endY && _closeList[_lastIndex]->j == _endX)
    {
        _astarState = ASTAR_STATE::ASTAR_STATE_FOUND;
        _closeList[_lastIndex]->color = RGB(255, 100, 100);
        showWay(_closeList[_lastIndex]);
    }
}

void CaStar::showWay(aStarTile* tile)
{
    if (!(tile->i == _endY && tile->j == _endX))
    {
        tile->color = RGB(255, 180, 180);
        m_fastLoad.push_back(PointMake(tile->j, tile->i));
       /* int centerX = tile->rc.left + (tile->rc.right - tile->rc.left) / 2;
        int centerY = tile->rc.top + (tile->rc.bottom - tile->rc.top) / 2;*/
        m_fastLoadLocation.push_front(PointMake(tile->rc.left, tile->rc.top));
    }
    tile = tile->parent;

    if (tile->parent == NULL) return;
    else showWay(tile);
}

void CaStar::typeColor(TILE_TYPE type)
{
    switch (type)
    {
    case TILE_TYPE::TILE_TYPE_EMPTY: _selectedTypeColor = RGB(255, 255, 255); break;
    case TILE_TYPE::TILE_TYPE_START: _selectedTypeColor = RGB(100, 255, 100); break;
    case TILE_TYPE::TILE_TYPE_END: _selectedTypeColor = RGB(255, 0, 0); break;
    case TILE_TYPE::TILE_TYPE_WALL: _selectedTypeColor = RGB(255, 255, 0); break;
    }
}
