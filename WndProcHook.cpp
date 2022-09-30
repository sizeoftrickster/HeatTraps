/*
* Copyright © 2022 s1zeoftr1ckster. Contacts: <sizeoftrickster@gmail.com>
* License: http://opensource.org/licenses/MIT
*/

#include "WndProcHook.h"
#include "Utility.hpp"
#include <CPlane.h>
#include <CHeli.h>

WndProcHook::WndProcHook() {
	wndprocHook.set_cb( [this]( auto&&... args ) { return WndProcHook::WndProcHooked( args... ); } );
	wndprocHook.install();
}

WndProcHook::~WndProcHook() {
	wndprocHook.remove();
}

LRESULT WndProcHook::WndProcHooked( const decltype( wndprocHook )& hook, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {
	if ( Utility::IsInSupportedAirVehicle() && uMsg == WM_KEYDOWN ) {
		if ( wParam == VK_SPACE ) {
//          Опираясь на видосы я понял, что за один раз выпускается 2 ловушки, и каждая в разные стороны, соответственно 1 нажатие = 2 тепловых ловушки.
			CVehicle* veh = FindPlayerVehicle( -1, true );
			if ( veh->m_nModelIndex == 520 ) {
				CPlane* plane = reinterpret_cast<CPlane*>( veh );

				heatTraps->Add( true,
					plane->m_aCarNodes[PLANE_ELEVATOR_L]->ltm.pos.x, 
					plane->m_aCarNodes[PLANE_ELEVATOR_L]->ltm.pos.y, 
					plane->m_aCarNodes[PLANE_ELEVATOR_L]->ltm.pos.z );
				heatTraps->Add( false, 
					plane->m_aCarNodes[PLANE_ELEVATOR_R]->ltm.pos.x, 
					plane->m_aCarNodes[PLANE_ELEVATOR_R]->ltm.pos.y, 
					plane->m_aCarNodes[PLANE_ELEVATOR_R]->ltm.pos.z );	
			} else {
				CHeli* heli = reinterpret_cast<CHeli*>( veh );
				
				heatTraps->Add( true,
					heli->m_aCarNodes[HELI_MOVING_ROTOR2]->ltm.pos.x,
					heli->m_aCarNodes[HELI_MOVING_ROTOR2]->ltm.pos.y,
					heli->m_aCarNodes[HELI_MOVING_ROTOR2]->ltm.pos.z );
				heatTraps->Add( false,
					heli->m_aCarNodes[HELI_STATIC_ROTOR2]->ltm.pos.x,
					heli->m_aCarNodes[HELI_STATIC_ROTOR2]->ltm.pos.y,
					heli->m_aCarNodes[HELI_STATIC_ROTOR2]->ltm.pos.z );
			}

		}
	}
	return wndprocHook.get_trampoline()( hWnd, uMsg, wParam, lParam );
}