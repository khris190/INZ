#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <map>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <memory>
#include <source_location>

#include "Profiler.hpp"

using std::cerr;
using std::cout;
using std::endl;
using std::map;
using std::ofstream;
using std::shared_ptr;
using std::string;
using std::chrono::system_clock;

enum class Target : short
{
    DISABLED = 1,
    STDOUT = 2,
    STDERR = 4,
    LOG_FILE = 8
};

enum class Level : short
{
    DEB = 1,
    INFO = 2,
    NOTICE = 3,
    WARNING = 4,
    ERR = 5,
    CRIT = 6,
    ALERT = 7,
    EMERG = 8
};

// String representations of Logger levels
map<Level, string> levelMap = {
    {Level::DEB, "DEBUG"},
    {Level::INFO, "INFO"},
    {Level::NOTICE, "NOTICE"},
    {Level::WARNING, "WARNING"},
    {Level::ERR, "ERROR"},
    {Level::CRIT, "CRITICAL"},
    {Level::ALERT, "ALERT"},
    {Level::EMERG, "EMERGENCY"}};

std::string getLoggerfunctionInfo(Level level, bool enableLevel = true, bool enableTimeStamp = true, bool enableFunctionInfo = true, const std::source_location location = std::source_location::current());

class Logger
{
public:
// write() uses these variables to determine which messages should be written where.
#ifdef DEBUG
    Level LoggerLevel = Level::DEB;
#else
    Level LoggerLevel = Level::INFO;
#endif
    short LoggerTarget = (short)Target::STDOUT;
    string LoggerFile = "log.log";
    ofstream LoggingStream;

    // this can speed up time stamp aquisition by 75%
    std::time_t lastTime = 0;
    char timeStr[80];

    // Flags that change Logger style
    bool timestampEnabled = true;
    bool levelEnabled = true;
    bool fileEnabled = true;
    bool deletePrevLog = true;

    bool fastTimeEnabled = false;

    ~Logger()
    {
        this->LoggingStream.close();
    }

#pragma region Target and level

    /* Set the location to Logger messages.
     *
     * \param   Target	The Logger target
     */
    void setTarget(Target target)
    {
        this->LoggerTarget = (short)target;
    }

    void xorTarget(Target target)
    {
        this->LoggerTarget ^= (short)target;
    }
    /* Set the severity of messages to Logger.
     *
     * \param	Level	The Logger level to set
     */
    void setLevel(Level level)
    {
        this->LoggerLevel = level;
    }

    /* Get the current Logger level. Only messages
     * with equal or higher severity will be written.
     *
     * \return	Level	The current Logger level
     */
    Level getLevel()
    {
        return this->LoggerLevel;
    }

    /* Convert the Level enum to a string.
     *
     * \param	Level	The level to convert
     * \return	string	The converted level
     */
    string levelToString(Level level)
    {
        return levelMap[level];
    }

#pragma endregion Target and level

#pragma region setFile
    /* Set a file to Logger to if the target is LOG_FILE.
     *
     * \param	string	The file to which we will Logger
     */
    short setFile(string fileName, bool deleteFile = false, const std::source_location location = std::source_location::current())
    {
        if (this->LoggingStream.is_open())
        {
            this->LoggingStream.close();
        }
        // Make sure we can open the file for writing
        if (deleteFile)
        {
            remove(fileName.c_str());
        }
        this->LoggingStream.open(fileName, ofstream::app);
        if (!this->LoggingStream.is_open())
        {
            // Logger the failure and return an error code
            this->write(Level::ERR, "Failed to open Logger file '" + fileName + "'", location);
            return 1;
        }
        this->LoggerFile = fileName;
        return 0;
    }
    short setFile(string fileName, ofstream::openmode mode, bool deleteFile = false, const std::source_location location = std::source_location::current())
    {
        if (this->LoggingStream.is_open())
        {
            this->LoggingStream.close();
        }
        if (deleteFile)
        {
            remove(fileName.c_str());
        }
        this->LoggingStream.open(fileName, ofstream::app);
        if (!this->LoggingStream.is_open())
        {
            // Logger the failure and return an error code
            this->write(Level::ERR, "Failed to open Logger file '" + fileName + "'", location);
            return 1;
        }
        this->LoggerFile = fileName;
        return 0;
    }
#pragma endregion setFile

    // TODO change string to c_str cause it might be way faster to do it by myself
    /* Log a message.
     *
     * \param	Level	The severity of the message
     * \param	string	The message to write
     */
    void write(Level level, string message, const std::source_location location)
    {
        string toLogger;

        if (!this->LoggingStream.is_open())
        {
            setFile(this->LoggerFile);
        }

        // Only Logger if we're at or above the pre-defined severity
        if (level < this->LoggerLevel)
        {
            return;
        }

        // Target::DISABLED takes precedence over other targets
        if ((this->LoggerTarget & (short)Target::DISABLED))
        {
            return;
        }
        {
            newTimer("getFunctioninfo and shiz");
            toLogger += getLoggerfunctionInfo(level, location);
        }

        // Append the message to our Logger statement
        if (this->fileEnabled || this->timestampEnabled || this->levelEnabled)
        {
            toLogger += ":\n" + message + "\n";
        }
        else
        {
            toLogger += message + "\n";
        }
        newTimer("writing to outputs");
        // printf makes printing a bit faster
        // Logger to stdout if it's one of our targets
        if ((this->LoggerTarget & (short)Target::STDOUT))
        {
            printf(toLogger.c_str());
        }

        // Logger to stderr if it's one of our targets
        if ((this->LoggerTarget & (short)Target::STDERR))
        {
            fprintf(stderr, toLogger.c_str());
        }

        // Logger to a file if it's one of our targets and we've set a LoggerFile
        if ((this->LoggerTarget & (short)Target::LOG_FILE) && this->LoggerFile != "")
        {
            this->LoggingStream << toLogger;
        }
    }

    std::string getLoggerfunctionInfo(Level level, const std::source_location location)
    {
        string toLogger;

        // Append the current date and time if enabled
        if (this->timestampEnabled)
        {
            std::time_t time = system_clock::to_time_t(system_clock::now());
            if (!this->fastTimeEnabled || this->lastTime + 1 < time)
            {
                this->lastTime = time;
                struct tm *timeStruct = std::localtime(&time);
                strftime(this->timeStr, 80, "%d/%b/%Y:%H:%M:%S", timeStruct);
            }
            toLogger += "[" + string(this->timeStr) + "] ";
        }

        if (this->levelEnabled)
        {
            toLogger += levelMap[level] + " ";
        }

        if (this->fileEnabled)
        {
            toLogger += location.file_name();
            toLogger += ":";
            toLogger += std::to_string(location.line());
            toLogger += ":";
            toLogger += std::to_string(location.column());
            toLogger += "  ";
            toLogger += location.function_name();
        }
        return toLogger;
    }

#pragma region Logs
    /* Log a Debug(lvl 1) message.
     *
     * \param	string	The message to write
     */
    void LogDeb(string message, const std::source_location location = std::source_location::current())
    {
        this->write(Level::DEB, message, location);
    }
    /* Log a Info(lvl 2) message.
     *
     * \param	string	The message to write
     */
    void LogInfo(string message, const std::source_location location = std::source_location::current())
    {
        this->write(Level::INFO, message, location);
    }
    /* Log a Notice(Lvl 3) message.
     *
     * \param	string	The message to write
     */
    void LogNotice(string message, const std::source_location location = std::source_location::current())
    {
        this->write(Level::NOTICE, message, location);
    }
    /* Log a Warning(lvl 4) message.
     *
     * \param	string	The message to write
     */
    void LogWar(string message, const std::source_location location = std::source_location::current())
    {
        this->write(Level::WARNING, message, location);
    }
    /* Log a Error(lvl 5) message.
     *
     * \param	string	The message to write
     */
    void LogErr(string message, const std::source_location location = std::source_location::current())
    {
        this->write(Level::ERR, message, location);
    }
    /* Log a Critical(lvl 6) message.
     *
     * \param	string	The message to write
     */
    void LogCrit(string message, const std::source_location location = std::source_location::current())
    {
        this->write(Level::CRIT, message, location);
    }
    /* Log a Alert(lvl 7) message.
     *
     * \param	string	The message to write
     */
    void LogAlert(string message, const std::source_location location = std::source_location::current())
    {
        this->write(Level::ALERT, message, location);
    }
    /* Log a Emergency(lvl 8) message.
     *
     * \param	string	The message to write
     */
    void LogEmerg(string message, const std::source_location location = std::source_location::current())
    {
        this->write(Level::EMERG, message, location);
    }

#pragma endregion Logs

#pragma region boolSets
    /* Time will be calculated on each Log message.
     */
    void dontUseFastTime()
    {
        this->fastTimeEnabled = false;
    }

    /* Time might be up to a second behind the real time.
     */
    void useFastTime()
    {
        this->fastTimeEnabled = true;
    }

    /* Date and time will no longer be printed with each Logger message.
     */
    void excludeTimestamp()
    {
        this->timestampEnabled = false;
    }

    /* Date and time will be printed with each Logger message.
     */
    void includeTimestamp()
    {
        this->timestampEnabled = true;
    }

    /* Logger level will no longer be printed with each Logger message.
     */
    void excludeLoggerLevel()
    {
        this->levelEnabled = false;
    }

    /* Logger level will be printed with each Logger message.
     */
    void includeLoggerLevel()
    {
        this->levelEnabled = true;
    }

    /* Function info will no longer be printed with each Logger message.
     */
    void excludeFunctionInfo()
    {
        this->fileEnabled = false;
    }

    /* Function info will be printed with each Logger message.
     */
    void includeFunctionInfo()
    {
        this->fileEnabled = true;
    }

#pragma endregion boolSets
};

static Logger Log;

#pragma region Bit - wise operators
inline Target operator&(Target a, Target b)
{
    return static_cast<Target>(static_cast<short>(a) & static_cast<short>(b));
}
inline Target operator|(Target a, Target b)
{
    return static_cast<Target>(static_cast<short>(a) | static_cast<short>(b));
}
#pragma endregion Bit - wise operators

#endif