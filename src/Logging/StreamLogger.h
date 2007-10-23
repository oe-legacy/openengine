// Generic stream logger.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
// --------------------------------------------------------------------

#ifndef _STREAM_LOGGER_H_
#define _STREAM_LOGGER_H_

#include <Logging/ILogger.h>

#include <string>
#include <ostream>

namespace OpenEngine {
namespace Logging {

using std::ostream;
using std::string;

/**
 * Generic stream logger.
 * @todo Add some usage code to the documentation.
 *
 * @class StreamLogger StreamLogger.h Logging/StreamLogger.h
 */
class StreamLogger : public ILogger {
private:
    ostream* stream;
public:
    StreamLogger(ostream* stream);
    virtual ~StreamLogger();
    void Write(LoggerType, string);
    std::string TypeToString(LoggerType);
};

} //NS Logger
} //NS OpenEngine

#endif // _STREAM_LOGGER_H_
