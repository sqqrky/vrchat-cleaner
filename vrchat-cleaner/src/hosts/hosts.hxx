#pragma once

namespace hosts {
    bool apply( ) {
        const std::wstring m_hosts_path = oxorany( L"C:\\Windows\\System32\\drivers\\etc\\hosts" );
        const std::vector<std::wstring> m_entries = {
            oxorany( L"0.0.0.0 api.amplitude.com" ),
            oxorany( L"0.0.0.0 api.lab.amplitude.com" ),
            oxorany( L"0.0.0.0 api.eu.amplitude.com" ),
            oxorany( L"0.0.0.0 api2.amplitude.com" ),
            oxorany( L"0.0.0.0 api3.amplitude.com" ),
            oxorany( L"0.0.0.0 cdn.amplitude.com" ),
            oxorany( L"0.0.0.0 stats.unity3d.com" ),
            oxorany( L"0.0.0.0 cdp.cloud.unity3d.com" ),
            oxorany( L"0.0.0.0 public.cloud.unity3d.com" ),
            oxorany( L"0.0.0.0 api.uca.cloud.unity3d.com" ),
            oxorany( L"0.0.0.0 config.uca.cloud.unity3d.com" ),
            oxorany( L"0.0.0.0 perf-events.cloud.unity3d.com" ),
            oxorany( L"0.0.0.0 data-optout-service.uca.cloud.unity3d.com" ),
            oxorany( L"0.0.0.0 ecommerce.iap.unity3d.com" ),
            oxorany( L"0.0.0.0 remote-config-proxy-prd.uca.cloud.unity3d.com" ),
            oxorany( L"0.0.0.0 thind-gke-euw.prd.data.corp.unity3d.com" ),
            oxorany( L"0.0.0.0 thind-gke-usc.prd.data.corp.unity3d.com" ),
            oxorany( L"0.0.0.0 thind-gke-ape.prd.data.corp.unity3d.com" )
        };

        // read existing hosts file so we can check if the lines alr exist
        std::wifstream m_infile( m_hosts_path );
        if ( !m_infile.is_open( ) ) {
            logging::print( oxorany( "Failed to open hosts file, exiting..." ) );
            return false;
        }

        std::vector<std::wstring> m_existing_lines;
        std::wstring m_line;
        while ( std::getline( m_infile, m_line ) )
            m_existing_lines.push_back( m_line );

        m_infile.close( );

        // check if they all exist alr
        bool all_exist = true;
        for ( const auto& m_entry : m_entries ) {
            if ( std::find( m_existing_lines.begin( ), m_existing_lines.end( ), m_entry ) == m_existing_lines.end( ) ) {
                all_exist = false;
                break;
            }
        }

        if ( all_exist ) {
            logging::print( oxorany( "Hosts file already modified, nothing to do." ) );
            return true;
        }

        std::wofstream m_outfile( m_hosts_path, std::ios::app );
        if ( !m_outfile.is_open( ) ) {
            logging::print( oxorany( "Failed to open hosts file for writing..." ) );
            return false;
        }

        // append missing, should be none if u run this twice
        for ( const auto& m_entry : m_entries ) {
            if ( std::find( m_existing_lines.begin( ), m_existing_lines.end( ), m_entry ) == m_existing_lines.end( ) )
                m_outfile << m_entry << oxorany( L"\n" );
        }

        m_outfile.close( );
        logging::print( oxorany( "Hosts file update complete." ) );
        return true;
    }
}