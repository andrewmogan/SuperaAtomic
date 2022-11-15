#include <algorithm>

#include "Logger.h"
#include <mutex>
#include "supera/base/meatloaf.h"
std::mutex __logger_mtx;

namespace supera {

    Logger *Logger::_shared_logger = nullptr;
    std::map<std::string,Logger> *Logger::_logger_m = nullptr;
    msg::Level_t Logger::_level_default = msg::kINFO;

    std::ostream& Logger::send(const msg::Level_t level) const
    {
        __logger_mtx.lock();
        (*_ostrm)  << msg::kStringPrefix[level].c_str()
        << "\033[0m ";
        __logger_mtx.unlock();
        return (*_ostrm);
    }

    std::ostream& Logger::send(const msg::Level_t level,
       const std::string& function ) const
    {
        auto& strm(send(level));
        strm << "\033[94m<" << _name << "::" << function.c_str() << ">\033[00m ";
        return strm;
    }

    std::ostream& Logger::send(const msg::Level_t level,
       const std::string& function,
       const unsigned int line_num ) const
    {
        auto& strm(send(level));
        strm << "\033[94m<" << _name << "::" << function.c_str() << "::L" << line_num << ">\033[00m ";
        return strm;
    }

    std::ostream& Logger::send(const msg::Level_t level,
       const std::string& function,
       const unsigned int line_num,
       const std::string& file_name) const
    {
        auto& strm(send(level,function));
    // FIXME temporary operation to fetch file name from full path
        strm << file_name.substr(file_name.rfind("/")+1,file_name.size()).c_str() << "::L" << line_num << " ";
        return strm;
    }

    Logger& Logger::get_shared()
    {
        __logger_mtx.lock();
        if(!_shared_logger) _shared_logger = new Logger("SHARED");
        __logger_mtx.unlock();
        return *_shared_logger;

    }
}
