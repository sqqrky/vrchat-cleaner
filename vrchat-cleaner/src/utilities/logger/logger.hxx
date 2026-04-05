#pragma once

namespace logging {
    template<typename... Args>
    void print( const char* format, Args... args ) {
        auto now = std::chrono::system_clock::now( );
        std::time_t time = std::chrono::system_clock::to_time_t( now );

        tm local_tm;
        localtime_s( &local_tm, &time );

        printf( oxorany( "\x1b[38;2;90;90;90m[\x1b[38;2;110;110;110m%02d\x1b[38;2;120;120;120m/\x1b[38;2;130;130;130m%02d\x1b[38;2;140;140;140m/\x1b[38;2;150;150;150m%04d\x1b[38;2;160;160;160m \x1b[38;2;170;170;170m%02d\x1b[38;2;180;180;180m:\x1b[38;2;190;190;190m%02d\x1b[38;2;210;210;210m:\x1b[38;2;230;230;230m%02d\x1b[38;2;200;200;200m]\x1b[0m " ),
            local_tm.tm_mon + 1,
            local_tm.tm_mday,
            local_tm.tm_year + 1900,
            local_tm.tm_hour,
            local_tm.tm_min,
            local_tm.tm_sec );
        printf( oxorany( "\x1b[37m" ) );
        printf( format, args... );
        printf( oxorany( "\x1b[0m\n" ) );
    }

    void new_line( ) {
        printf( "\n" );
    }
}