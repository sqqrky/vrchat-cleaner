#pragma once
#include <chrono>
#include <ctime>
#include <vector>
#include <Windows.h>
#include <tlhelp32.h>
#include <fstream>
#include <winternl.h>
#include <cstdint>
#include <DbgHelp.h>
#include <thread>
#include <functional>
#include <shlobj.h>
#include <filesystem>
#include <map>

#include <dep/oxorany/include.h>

#include <src/utilities/logger/logger.hxx>
#include <src/utilities/utilities.hxx>

#include <src/utilities/exception/exception.hxx>

#include <src/hosts/hosts.hxx>
#include <src/reg/reg.hxx>
#include <src/folder/folder.hxx>
#include <src/network/network.hxx>