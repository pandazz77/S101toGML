#pragma once

#include "targetver.h"
#include <stdio.h>
#ifdef _WIN32
#include <tchar.h>
#endif
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit
#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS         // remove support for MFC controls in dialogs

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#ifdef _WIN32
#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#ifdef _WIN32
#include <afxext.h>         // MFC extensions
#endif
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Control
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#else
#include "../libS101/compat/compat_mfc.h"
#endif

#include <iostream>
