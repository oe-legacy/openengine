// LoggerType
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
// --------------------------------------------------------------------

#ifndef _LOGGERTYPE_H_
#define _LOGGERTYPE_H_

namespace OpenEngine {
namespace Logging {

/**
 * LoggerTypes
 * Enumeration of logger types
 *
 * @enum LoggerType
 */
typedef enum {
    Info       = 0,
    Warning    = 10,
    Error      = 20
} LoggerType;

} //NS Logging
} //NS OpenEngine

#endif // _LOGGERTYPE_H_
