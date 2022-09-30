/*
* Copyright © 2022 s1zeoftr1ckster. Contacts: <sizeoftrickster@gmail.com>
* License: http://opensource.org/licenses/MIT
*/

#ifndef _UTILITY_HPP_
#define _UTILITY_HPP_

#include <plugin_sa.h>

class Utility
{
public:
	static bool IsInSupportedAirVehicle() {
		CPed* ped = FindPlayerPed( -1 );
		CVehicle* veh = FindPlayerVehicle( -1, true );
		if ( !ped || !veh )
			return false;
		return veh->m_nModelIndex == 520 || veh->m_nModelIndex == 425 && veh->IsDriver( ped );
	}
}; // class Utility

#endif // !_UTILITY_HPP_