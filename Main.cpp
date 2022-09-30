/*
* Copyright © 2022 s1zeoftr1ckster. Contacts: <sizeoftrickster@gmail.com>
* License: http://opensource.org/licenses/MIT
*/

#include "Main.h"
#include "WndProcHook.h"

HeatTraps* obj;

AsiPlugin::AsiPlugin() {
	gameloopHook.set_cb( [this]( auto&&... args ) { return AsiPlugin::GameloopHooked( args... ); } );
	gameloopHook.install();
}

AsiPlugin::~AsiPlugin() {
	gameloopHook.remove();
}

void AsiPlugin::GameloopHooked( const decltype( gameloopHook )& hook ) {
	static bool isInitialized = false;
	if ( !isInitialized ) {
		wndprocHook = std::make_unique<WndProcHook>();
		isInitialized = true;
	} else {
		if ( GetTickCount64() - Time > 75 ) {
			obj->Process();
			Time = GetTickCount64();
		}
	}
	return hook.get_trampoline()();
}