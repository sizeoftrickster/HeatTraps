/*
* Copyright © 2022 s1zeoftr1ckster. Contacts: <sizeoftrickster@gmail.com>
* License: http://opensource.org/licenses/MIT
*/

#include "HeatTraps.h"
#include <CStreaming.h>
#include <CWorld.h>
#include <eModelID.h>
#include "extensions/ScriptCommands.h"

std::deque<std::tuple<bool, CObject*>> deq;

void HeatTraps::Process() {
	for ( auto n : deq ) {

		auto side = std::get<0>( n );
		auto obj = std::get<1>( n );

		if ( obj->GetPosition().x > 0.f ) MakeObjectFall( obj, side );
		if ( obj->GetPosition().z <= 0.f ) ReleaseObject( obj, side );
	}
}

void HeatTraps::Add( bool side, float x, float y, float z ) {
	CStreaming::RequestModel( eModelID::MODEL_FLARE, eStreamingFlags::PRIORITY_REQUEST );

	CObject* obj = CObject::Create( eModelID::MODEL_FLARE );
	obj->SetPosn( x, y, z );
	CWorld::Add( obj );

	deq.push_back( std::make_tuple( side, obj ) );
}

void HeatTraps::MakeObjectFall( CObject* obj, bool side ) {
	// 01BC: SET_OBJECT_COORDINATES | Object.SetCoordinates(self: Object, x: float, y: float, z: float)

	// Down
	plugin::Command<COMMAND_SET_OBJECT_COORDINATES>( obj, obj->GetPosition().x, obj->GetPosition().y, obj->GetPosition().z - 0.9f );
	// Away
	plugin::Command<COMMAND_SET_OBJECT_COORDINATES>( obj, obj->GetPosition().x, side ? obj->GetPosition().y - 0.5f : obj->GetPosition().y + 0.5f, obj->GetPosition().z );
}

void HeatTraps::ReleaseObject( CObject* obj, bool side ) {
	CWorld::Remove( obj );
	CWorld::RemoveReferencesToDeletedObject( obj );
	auto it = std::remove( deq.begin(), deq.end(), std::make_tuple( side, obj ) );
	deq.erase( it );
}