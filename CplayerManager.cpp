#include "framework.h"
#include "CplayerManager.h"
CplayerManager::CplayerManager():m_mario(new Cmario), m_peach(new Cpeach), m_bowser(new Cbowser)
{
}

CplayerManager::~CplayerManager()
{
}


HRESULT CplayerManager::init()
{
    m_mario->init();
    m_peach->init();
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
    m_mario->update();
    
    isMyTurn();
}

void CplayerManager::render()
{
    m_mario->render();
}

void CplayerManager::attack()
{
}

void CplayerManager::move()
{
}

void CplayerManager::isMyTurn()
{
    //m_command = m_button->buttonInput();
    if (m_command)
    {
        m_command->execute(*m_mario);
    }
}
