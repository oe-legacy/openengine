// Generic stream logger.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
// --------------------------------------------------------------------

#include <Logging/StreamLogger.h>
#include <Meta/Time.h>

#include <string.h>

namespace OpenEngine {
namespace Logging {

/**
 * Create a logger wrapping an output stream.
 *
 * @param stream Stream to use as log output.
 */
StreamLogger::StreamLogger(ostream* stream) : stream(stream){

}

/**
 * Destruct the stream logger.
 * Flushes the stream.
 */
StreamLogger::~StreamLogger(){
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
void StreamLogger::Write(LoggerType type, string msg) {
    time_t t; time(&t); // get the current time
    char buf[20]; memset (buf, '0', 20); // this terminates the string
	strftime (buf, sizeof(buf), "%Y/%m/%d %H:%M:%S", localtime(&t));
    *stream << TypeToString(type) << " ";
    *stream << string(buf) << ": ";
    *stream << msg << std::endl;
}

/**
 * Get string representation for a log message type.
 *
 * @param type Log message type.
 * @return String representation of type.
 */
string StreamLogger::TypeToString(LoggerType type){
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

} //NS Logging
} //NS OpenEngine
