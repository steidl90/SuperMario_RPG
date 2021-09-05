#include "framework.h"
#include "CplayerManager.h"
CplayerManager::CplayerManager() :m_mario(new Cmario), m_peach(new Cpeach), m_bowser(new Cbowser), m_FSM(new CFSMController), m_marioBattle(new CmarioBattle)
{
}

HRESULT CplayerManager::init()
{
    m_mario->init();
    m_marioBattle->init();
    m_peach->init();
    m_bowser->init();
    m_FSM = new CFSMController;
    m_FSM->initState(m_mario, CHARACTER_TYPE::PLAYER_WORLD);
    return S_OK;
}

void CplayerManager::release()
{
    SAFE_DELETE(m_mario);
    SAFE_DELETE(m_marioBattle);
    SAFE_DELETE(m_peach);
    SAFE_DELETE(m_bowser);
    SAFE_DELETE(m_FSM);
}

void CplayerManager::update()
{
    if (m_FSM->getstate() == STATE_TYPE::IDLE || m_FSM->getstate() == STATE_TYPE::MOVE)
    {
        m_mario->update();
    }
    else if (m_FSM->getstate() == STATE_TYPE::BATTLE)
    {
        m_marioBattle->update();
        m_peach->update();
        m_bowser->update();
    }

    m_FSM->updateState();
}

void CplayerManager::render()
{
    if (m_FSM->getstate() == STATE_TYPE::IDLE || m_FSM->getstate() == STATE_TYPE::MOVE)
    {
        m_mario->render();
    }
    else if (m_FSM->getstate() == STATE_TYPE::BATTLE)
    {
        m_marioBattle->render();
        m_peach->render();
        m_bowser->render();
    }
}

void CplayerManager::attack()
{
}

void CplayerManager::move()
{
}

void CplayerManager::isMyTurn()
{
    
}
