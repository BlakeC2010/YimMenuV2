#include "core/hooking/DetourHook.hpp"
#include "game/backend/Players.hpp"
#include "game/hooks/Hooks.hpp"

namespace YimMenu::Hooks
{
	void Info::NetworkPlayerMgrShutdown(CNetworkPlayerMgr* mgr)
	{
		if (!g_Running)
			return BaseHook::Get<Info::NetworkPlayerMgrShutdown, DetourHook<decltype(&Info::NetworkPlayerMgrShutdown)>>()->Original()(mgr);

		// A shutdown also occurs during normal session changes; this is not an error on its own.
		LOGF(INFO, "[SessionDiag] Network player manager shutdown observed (reason not available)");
		Players::Shutdown();
		BaseHook::Get<Info::NetworkPlayerMgrShutdown, DetourHook<decltype(&Info::NetworkPlayerMgrShutdown)>>()->Original()(mgr);
	}
}