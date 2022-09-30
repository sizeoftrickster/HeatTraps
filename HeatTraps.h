/*
* Copyright © 2022 s1zeoftr1ckster. Contacts: <sizeoftrickster@gmail.com>
* License: http://opensource.org/licenses/MIT
*/

#ifndef _HEAT_TRAPS_H_
#define _HEAT_TRAPS_H_

#include <tuple>
#include <plugin.h>
#include <deque>

class HeatTraps
{
	HeatTraps() = delete;
	~HeatTraps() = delete;
public:
	void Process();
	void Add( bool side, float x, float y, float z );
private:
	void MakeObjectFall( CObject* obj, bool side );
	void ReleaseObject( CObject* obj, bool side );
}; // class HeatTraps

#endif // !_HEAT_TRAPS_H_