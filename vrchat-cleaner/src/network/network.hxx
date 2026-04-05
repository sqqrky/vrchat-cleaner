#pragma once

namespace network {

    void execute_command( std::string_view command ) {
        std::string full_command = oxorany( "cmd /c " ) + std::string( command );

        STARTUPINFOA m_si{ 0 };
        PROCESS_INFORMATION m_pi{ 0 };
        m_si.cb = sizeof( m_si );
        m_si.dwFlags = STARTF_USESHOWWINDOW;
        m_si.wShowWindow = SW_HIDE;

        if ( !CreateProcessA(
                nullptr,
                full_command.data( ),
                nullptr,
                nullptr,
                FALSE,
                CREATE_NO_WINDOW | CREATE_UNICODE_ENVIRONMENT,
                nullptr,
                nullptr,
                &m_si,
                &m_pi
            ) )
        {
            logging::print( oxorany( "Failed to execute command: %s" ), command.data( ) );
            return;
        }

        WaitForSingleObject( m_pi.hProcess, INFINITE );

        DWORD m_exit = 0;
        GetExitCodeProcess( m_pi.hProcess, &m_exit );

        CloseHandle( m_pi.hProcess );
        CloseHandle( m_pi.hThread );

        if ( m_exit != 0 )
            if ( command != "netsh int ip reset" ) {
                logging::print( oxorany( "Command failed with exit code: %lu | %s" ), m_exit, command.data( ) );
            }
        else
            logging::print( oxorany( "Command executed successfully: %s" ), command.data( ) );
    }

    void reset_network( ) {
        logging::print( oxorany( "Resetting network..." ) );

        std::vector< std::string > m_commands = {
            oxorany( "ipconfig /release" ),
            oxorany( "ipconfig /renew" ),
            oxorany( "netsh winsock reset" ),
            oxorany( "netsh int ip reset" )
        };

        for ( const auto& m_cmd : m_commands )
            execute_command( m_cmd );

        logging::print( oxorany( "Network reset complete." ) );
    }

}