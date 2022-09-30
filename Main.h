/*
* Copyright © 2022 s1zeoftr1ckster. Contacts: <sizeoftrickster@gmail.com>
* License: http://opensource.org/licenses/MIT
*/
#ifndef _MAIN_H_
#define _MAIN_H_

#include <memory> // std::unique_ptr
#include <kthook/kthook.hpp> // kthook::kthook_simple
#include "HeatTraps.h"

using GameloopPrototype = void( __cdecl* )();

class AsiPlugin
{
	kthook::kthook_simple<GameloopPrototype> gameloopHook{ 0x748DA3 };

	std::unique_ptr<class WndProcHook> wndprocHook;

	ULONGLONG Time = GetTickCount64();
public:
	explicit AsiPlugin();
	virtual ~AsiPlugin();
private:
	void GameloopHooked( const decltype( gameloopHook )& hook );
} AsiPlugin; // class AsiPlugin

#endif // !_MAIN_H_