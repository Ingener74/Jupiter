/*
 * Log.h
 *
 *  Created on: May 26, 2014
 *      Author: pavel
 */

#ifndef LOG_H_
#define LOG_H_

#include <Engine/Common.h>

namespace ndk_game
{

enum Level
{
    DEBUG, ERROR
};

class Log
{
public:
    class ILog
    {
    public:
        using Ptr = std::shared_ptr<ILog>;

        virtual ~ILog()
        {
        }

        virtual void Error(const std::string& message) throw ()= 0;
        virtual void Debug(const std::string& message) throw ()= 0;

    protected:
        ILog()
        {
        }
    };

    Log(Level level = Level::DEBUG) :
            _level(level)
    {
    }
    virtual ~Log()
    {
        switch (_level)
        {
        case Level::DEBUG:
            getLog()->Debug(logStream.str());
            break;
        case Level::ERROR:
            getLog()->Error(logStream.str());
            break;
        default:
            break;
        }
    }

    template<typename T>
    Log& operator<<(const T& logMe)
    {
        logStream << logMe;
        return *this;
    }

    static ILog::Ptr getLog() throw ()
    {
        if(regLog().empty()){
            class CoutLog: public ILog
            {
            public:
                CoutLog()
                {
                }
                virtual ~CoutLog()
                {
                }
                virtual void Error(const std::string& message) throw ()
                {
                    std::cerr << message << std::endl;
                }
                virtual void Debug(const std::string& message) throw ()
                {
                    std::cout << message << std::endl;
                }

            private:
            };
            pushLog(std::make_shared<CoutLog>());
        }
        return regLog().back();
    }
    static void pushLog(ILog::Ptr log) throw ()
    {
        regLog().push_back(log);
    }
    static void popLog() throw ()
    {
        if (regLog().size() > 1) regLog().pop_back();
    }

private:
    using Register = std::list<ILog::Ptr>;
    static Register& regLog()
    {
        static Register reg;
        return reg;
    }
    Level _level;
    std::stringstream logStream;
};

} /* namespace ndk_game */

#endif /* LOG_H_ */
