// Generic stream logger.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
// --------------------------------------------------------------------

#include <Logging/ColorStreamLogger.h>
#include <Meta/Time.h>
#include <Utils/DateTime.h>

#include <string.h>

namespace OpenEngine {
namespace Logging {

/**
 * Create a logger wrapping an output stream.
 *
 * @param stream Stream to use as log output.
 */
ColorStreamLogger::ColorStreamLogger(ostream* stream) : stream(stream) {
    char *term = getenv("TERM");
    colorsEnabled = term?(strcmp(term,"xterm-color") == 0):false;
}

/**
 * Destruct the stream logger.
 * Flushes the stream.
 */
ColorStreamLogger::~ColorStreamLogger(){
    if (stream!=NULL) {
        stream->flush();
        delete stream;
    }
}

/**
 * Write a log message.
 *
 * @param type Log message type.
 * @param msg Message to log.
 */
void ColorStreamLogger::Write(LoggerType type, string msg) {
    if (colorsEnabled) {
        *stream << "\033["; // print the CSI
        *stream << ColorForType(type);
        *stream << 'm'; // the previous was a SGR
        
    }
    *stream << TypeToString(type) << " ";
    *stream << Utils::DateTime::GetCurrent() << ": ";
    *stream << msg ;
    if (colorsEnabled) {
        // reset color
        *stream << "\033["; // print the CSI
        *stream << 'm'; // the previous was a SGR        
    }
    *stream << std::endl;
}

/**
 * Get string representation for a log message type.
 *
 * @param type Log message type.
 * @return String representation of type.
 */
string ColorStreamLogger::TypeToString(LoggerType type){
    string str;
    if (type == Error)
        str ="[EE]";
    else if (type == Warning)
        str = "[WW]";
    else if (type == Info)
        str = "[II]";
    else {
        str = "[";
        str += type;
        str += "]";
    }
    return str;
}

int ColorStreamLogger::ColorForType(LoggerType type) {
    switch (type) {
    case Info: return 32;
    case Warning: return 33;
    case Error: return 31;
    }
    return 30;
}

} //NS Logging
} //NS OpenEngine
