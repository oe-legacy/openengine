// Logger interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
// --------------------------------------------------------------------

#ifndef _INTERFACE_LOGGER_H_
#define _INTERFACE_LOGGER_H_

#include <string>
#include <Logging/LoggerType.h>

namespace OpenEngine {
namespace Logging {

using std::string;

/**
 * Logger interface.
 * @todo Add more usage documentation here.
 *
 * @class ILogger ILogger.h Logging/ILogger.h
 */
class ILogger {
public:

    virtual ~ILogger(){}

    /**
     * Write string to a logger.
     *
     * @param type Logger type to log.
     * @param msg Message to log.
     */
    virtual void Write(LoggerType type, string msg) = 0;

};

} //NS Logging
} //NS OpenEngine

#endif // _INTERFACE_LOGGER_H_
