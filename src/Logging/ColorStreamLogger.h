// Color stream logger.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
// --------------------------------------------------------------------

#ifndef _COLOR_STREAM_LOGGER_H_
#define _COLOR_STREAM_LOGGER_H_

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
 * @class ColorStreamLogger ColorStreamLogger.h Logging/ColorStreamLogger.h
 */
class ColorStreamLogger : public ILogger {
private:
    ostream* stream;
    bool colorsEnabled;

    int ColorForType(LoggerType);

public:
    ColorStreamLogger(ostream* stream);
    virtual ~ColorStreamLogger();
    void Write(LoggerType, string);
    std::string TypeToString(LoggerType);
};

} //NS Logger
} //NS OpenEngine

#endif // _COLOR_STREAM_LOGGER_H_
