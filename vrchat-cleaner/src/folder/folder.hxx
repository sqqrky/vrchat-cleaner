#pragma once

namespace folder {
	bool delete_folder( std::string_view path ) {
		try {
			std::filesystem::remove_all( path );
			return true;
		}
		// unknown exception
		catch ( ... ) {
			// cba + runtime 
			logging::print( "Failed to delete folder: %s", path.data( ) );
			return false;
		}
	}

	void cleanup( ) {
		char m_appdata[ MAX_PATH ];
		char m_local_appdata[ MAX_PATH ];

		SHGetFolderPathA( NULL, CSIDL_APPDATA, NULL, 0, m_appdata );
		SHGetFolderPathA( NULL, CSIDL_LOCAL_APPDATA, NULL, 0, m_local_appdata );

		// obvious stuff
		logging::print( oxorany( "Deleting Easy Anti Cheat Folder..." ) );
		delete_folder( std::string( m_appdata ) + oxorany( "\\EasyAntiCheat" ) );

		logging::print( oxorany( "Deleting Unity Folder..." ) );
		delete_folder( std::string( m_appdata ) + oxorany( "\\Unity" ) );

		logging::print( oxorany( "Deleting VRChat Local Folder..." ) );
		delete_folder( std::string( m_local_appdata ) + oxorany( "\\VRChat" ) );

		logging::print( oxorany( "Deleting VRChat Temp Folder..." ) );
		delete_folder( std::string( m_local_appdata ) + oxorany( "\\Temp\\VRChat" ) );

		logging::print( oxorany( "Deleting VRChat Low Folder..." ) );
		delete_folder( std::string( m_local_appdata ) + oxorany( "\\Low\\VRChat" ) );

		logging::print( oxorany( "Deleting VRChat Unity Temp Folder..." ) );
		delete_folder( std::string( m_local_appdata ) + oxorany( "\\Temp\\DefaultCompany" ) );

		logging::print( oxorany( "Deleting VRChat Unity Low Folder..." ) );
		delete_folder( std::string( m_local_appdata ) + oxorany( "\\Low\\DefaultCompany" ) );

		// yeah this is probably something a steam eac game would check
		logging::print( oxorany( "Deleting Steam User Data folder..." ) );
		delete_folder( oxorany( "C:\\Program Files (x86)\\Steam\\userdata" ) );

		logging::print( oxorany( "Folder cleanup complete." ) );
	}

}