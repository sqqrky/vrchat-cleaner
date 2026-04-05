 #include <impl/includes.h>
#include <src/hosts/hosts.hxx>

/*
    if you really wanna be safe, use the vrchat eac emulator, this is just for ppl who spoof serials n shit
    small project, i based this off of what i was told, deal w endpoints, general trace info, reg, folders, etc.
    https://github.com/ShimadaNanaki/vrc-eac-emulator/blob/master/SETUP_GUIDE.md
*/

int main( ) {
    SetConsoleTitleA( oxorany( "vrchat-cleaner" ) );
    SetUnhandledExceptionFilter( exception::exception_filter );
    if ( !utilites::is_admin( ) ) { 
        logging::print( oxorany( "Run this process as an administator, press any key to exit..." ) );
        return std::getchar( );
    }

    // so we can do unicode coloring, specifically the gradient logging
    utilites::enable_utf8( );
    logging::print( oxorany( "Console created." ) );
    logging::print( oxorany( "Credits to sqqrky, https://discord.gg/hvrc <3" ) );
    logging::new_line( );

    MessageBoxA( 0, oxorany( "Welcome to my Cleaner, Press OK to continue!" ), oxorany( "VRChat Cleaner" ), MB_ICONINFORMATION | MB_OK);

    utilites::kill_processes( );
    logging::new_line( );

    hosts::apply( );
    logging::new_line( );
 
    reg::delete_registry( );
    logging::new_line( );

    folder::cleanup( );
    logging::new_line( );

    network::reset_network( );
    logging::new_line( );

    logging::print( oxorany( "Finished cleaning, press any key to exit." ) );
    return std::getchar( );
}