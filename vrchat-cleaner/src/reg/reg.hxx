#pragma once
#include <windows.h>
#include <dep/oxorany/oxorany.h>

namespace reg {
	bool delete_registry( ) {
		// define these as vars to get the status returned
		LONG m_1 = RegDeleteKeyW( HKEY_CURRENT_USER, oxorany( L"Software\\VRChat" ) );
		LONG m_2 = RegDeleteKeyW( HKEY_CURRENT_USER, oxorany( L"Software\\Unity Technologies" ) );

		// we aren't going to return false because this doesn't need to be neccessairly fatal to cleaning lol
		if ( m_1 != ERROR_SUCCESS || m_2 != ERROR_SUCCESS )
			logging::print( oxorany( "Failed to delete both registry keys, may have already been removed." ) );

		return true;
	}
}