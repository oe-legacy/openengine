// Logging facility.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
// --------------------------------------------------------------------

#include <Logging/Logger.h>
#include <Logging/ILogger.h>

namespace OpenEngine {
namespace Logging {

// initialization of static members
list<ILogger*> Logger::loggerList;

Logger::Logger() : info(Info), warning(Warning), error(Error), end() {}
 
/**
 * Add a new logger instance to list of active loggers.
 *
 * @param logger Logger to add.
 */
void Logger::AddLogger(ILogger* logger){
    loggerList.push_back(logger);
}

/**
 * Remove a logger instance from list of active loggers.
 *
 * @param logger Logger to remove.
 */
void Logger::RemoveLogger(ILogger* logger){
    loggerList.remove(logger);
}

/**
 * Write a message to the log.
 *
 * @param type Logging type.
 * @param str Message to log.
 */
void Logger::WriteToLog(LoggerType type, string msg){
    list<ILogger*>::const_iterator itr = loggerList.begin();
    while( itr != loggerList.end() ){
        (*itr)->Write(type, msg);
        itr++;
    }
}

/**
 * Overload of << to find log end.
 *
 * @param e Log end type
 */
Logger::LoggerTypeObj& Logger::LoggerTypeObj::operator<<(LogEnd e){
    if(logger.end==e){
        Logger::WriteToLog(type, buffer.str());
        buffer.flush();
        buffer.str("");
        buffer.clear();
    }
    return *this;
}

/**
 * Deinitialize the logger.
 */
void Logger::Deinitialize() {
    list<ILogger*>::const_iterator itr = loggerList.begin();
    while (itr != loggerList.end()) {
        ILogger* logger = (*itr);
        delete logger;
        itr++;
    }
    loggerList.clear();
}

} //NS Logging
} //NS OpenEngine
