#pragma once

namespace utilites {
	bool is_admin( ) {
        HANDLE m_token = nullptr;
        BOOL m_is_admin = FALSE;

        if ( OpenProcessToken( GetCurrentProcess( ), TOKEN_QUERY, &m_token ) ) {
            TOKEN_ELEVATION m_elevation{ };
            DWORD m_size = 0;

            if ( GetTokenInformation( m_token, TokenElevation, &m_elevation, sizeof( m_elevation ), &m_size ) ) {
                m_is_admin = m_elevation.TokenIsElevated;
            }

            CloseHandle( m_token );
        }

        return m_is_admin;
    }
	
	void enable_utf8( ) {
		auto m_std_handle = GetStdHandle( STD_OUTPUT_HANDLE );

		DWORD m_mode;
		GetConsoleMode( m_std_handle, &m_mode );

		m_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		SetConsoleMode( m_std_handle, m_mode);
	}

	bool is_process_running( std::wstring_view name ) {
		auto m_snapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
		if ( m_snapshot == INVALID_HANDLE_VALUE )
			return false;

		PROCESSENTRY32W m_entry{ };
		m_entry.dwSize = sizeof( PROCESSENTRY32W );
		// address of operator for entry ( & )
		if ( Process32FirstW( m_snapshot, &m_entry ) ) {
			do {
				if ( _wcsicmp( m_entry.szExeFile, name.data( ) ) == 0 ) {
					CloseHandle( m_snapshot );
					return true;
				}
			} while ( Process32NextW( m_snapshot, &m_entry ) );
		}

		CloseHandle( m_snapshot );
		return false;
	}

	void kill_process( std::wstring_view name ) {
		auto m_snapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
		if ( m_snapshot == INVALID_HANDLE_VALUE )
			return;

		PROCESSENTRY32W m_entry{ };
		m_entry.dwSize = sizeof( PROCESSENTRY32W );
		// address of operator, again, for entry ( & )
		if ( Process32FirstW( m_snapshot, &m_entry ) ) {
			do {
				if ( _wcsicmp( m_entry.szExeFile, name.data( ) ) == 0 ) {
					auto handle = OpenProcess( PROCESS_TERMINATE, FALSE, m_entry.th32ProcessID );
					if ( handle != nullptr ) {
						TerminateProcess( handle, 1 );
						CloseHandle( handle );
					}
				}
			} while ( Process32NextW( m_snapshot, &m_entry ) );
		}

		CloseHandle( m_snapshot );
	}

	void kill_processes( ) {
		const wchar_t* m_processes[ ] = {
			oxorany( L"VRChat.exe" ),
			oxorany( L"EasyAntiCheat_EOS.exe" ),
			oxorany( L"start_protected_game.exe" )
		};

		for ( auto& m_process : m_processes ) {
			if ( is_process_running( m_process ) ) {
				logging::print( oxorany( "Process running, killing..." ) );
				kill_process( m_process );
			} else {
				logging::print( oxorany( "Process not running." ) );
			}
		}
	}
}