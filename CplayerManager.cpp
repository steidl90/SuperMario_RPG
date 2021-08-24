#include "framework.h"
#include "CplayerManager.h"
CplayerManager::CplayerManager():m_mario(nullptr), m_peach(nullptr), m_bowser(nullptr)
{
}

CplayerManager::~CplayerManager()
{
}


HRESULT CplayerManager::init()
{
    m_mario = new Cmario;
    m_mario->init();
    
    m_peach = new Cpeach;
    m_peach->init();

    m_bowser = new Cbowser;
    m_bowser->init();

    return S_OK;
}

void CplayerManager::release()
{
    SAFE_DELETE(m_mario);
    SAFE_DELETE(m_peach);
    SAFE_DELETE(m_bowser);
}

void CplayerManager::update()
{
    
}

void CplayerManager::render()
{
   
}
