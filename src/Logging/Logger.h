// Log facility.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
// --------------------------------------------------------------------

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <string>
#include <sstream>
#include <iostream>
#include <list>
#include <Logging/LoggerType.h>

namespace OpenEngine {
namespace Logging {

using namespace std;

//forward declarations
class ILogger;

/**
 * Log facility.
 *
 * @class Logger Logger.h Logging/Logger.h
 */
class Logger {
private:
    static list<ILogger*> loggerList;

    class LogEnd {
    public:
        bool operator==(const LogEnd& end){
            return true;
        }
    };
    class LoggerTypeObj {
    private:
        ostringstream buffer;
        LoggerType type;
        LoggerTypeObj(){}
    public:
        LoggerTypeObj(LoggerType t) : type(t) {}
        LoggerTypeObj& operator<<(LogEnd);
        template <class T>
        LoggerTypeObj& operator<<(T input) {
            buffer << input;
            return *this;
        }
        LoggerTypeObj& operator<<(int input) {
            buffer << input;
            return *this;
        }
        LoggerTypeObj& operator<<(float input) {
            buffer << input;
            return *this;
        }
        LoggerTypeObj& operator<<(char input) {
            buffer << input;
            return *this;
        }
        LoggerTypeObj& operator<<(char* input) {
            buffer << input;
            return *this;
        }
        ~LoggerTypeObj(){}
    };
    static void WriteToLog(LoggerType type, string str);
public:

    LoggerTypeObj info;         //!< Info log.
    LoggerTypeObj warning;      //!< Warning log.
    LoggerTypeObj error;        //!< Error log.
    LogEnd end;                 //!< Log-message-end type

    static void AddLogger(ILogger* logger);
    static void RemoveLogger(ILogger* logger);
    static void Deinitialize();
    Logger();
};

} //NS Logging
} //NS OpenEngine

static OpenEngine::Logging::Logger logger;

#endif // _LOG_H_
