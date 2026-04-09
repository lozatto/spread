#pragma once

#include <cmath> // std::isfinite

enum E_PRINT
{
    NOTIFY = 1,
    CONSOLE = 2,
    CHAT = 3,
    CENTER = 4,
    RADIO = 5
};

// ---------------------------------------------------------------------------
// Safe entity validation helpers
// ---------------------------------------------------------------------------

inline bool IsValidEdict(edict_t *pEdict)
{
    if (!pEdict)
        return false;
    if (pEdict->free)
        return false;
    if (!pEdict->pvPrivateData)
        return false;
    return true;
}

inline CBasePlayer *EntityToValidPlayer(CBaseEntity *pEntity)
{
    if (!pEntity)
        return nullptr;

    if (!pEntity->pev)
        return nullptr;

    edict_t *pEdict = ENT(pEntity->pev);

    if (!IsValidEdict(pEdict))
        return nullptr;

    if (!FClassnameIs(pEntity->pev, "player"))
        return nullptr;

    int idx = ENTINDEX(pEdict);
    if (idx < 1 || idx > gpGlobals->maxClients)
        return nullptr;

    return static_cast<CBasePlayer *>(pEntity);
}

// ---------------------------------------------------------------------------

class CSpread
{
public:
    void ServerActivate();
    float GetSpread(CBaseEntity *pEntity, Vector &vecSrc, Vector &vecDirShooting, float vecSpread, float flDistance, int iPenetration, int iBulletType, int iDamage, float flRangeModifier, entvars_t *pevAttacker, bool bPistol, int shared_rand);
    void ClientPrint(edict_t *pEntity, int iMsgDest, const char *Format, ...);

    cvar_t *m_Debug        = nullptr;
    cvar_t *m_Active       = nullptr;
    cvar_t *m_GroundCheck  = nullptr;
    cvar_t *m_MaxSpeed     = nullptr;
    cvar_t *m_MaxPunchAngle= nullptr;
    cvar_t *m_Spread       = nullptr;
    cvar_t *m_Weapons      = nullptr;
};

extern CSpread gSpread;
