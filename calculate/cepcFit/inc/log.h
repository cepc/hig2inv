// Author      : Stefan Gadatsch
// Email       : stefan.gadatsch@cern.ch
// Date        : 2016-03-17
// Description : Minimal logging system, adapted from https://github.com/dominikschnitzer/minilog

#ifndef _LOG_
#define _LOG_

#include <iostream>
#include <sstream>
#include <sys/time.h>

// _____________________________________________________________________________
enum LogLevel {logERROR, logWARNING, logINFO, logDEBUG};

// _____________________________________________________________________________
// Declarations of functions used in this file
inline std::string GetTime();

// _____________________________________________________________________________
class Log
{
public:
  Log(LogLevel _loglevel);
  virtual ~Log();
public:
  static LogLevel& ReportingLevel();
  static std::string ToString(LogLevel _loglevel);
  static LogLevel FromString(const std::string& _loglevel);
  template <typename T>
  Log& operator <<(T const& value)
  {
    _os << value;
    return *this;
  }
protected:
  std::ostringstream _os;
private:

};

// _____________________________________________________________________________
inline Log::Log(LogLevel _loglevel)
{
  _os << "- " << GetTime();
  _os << " " << ToString(_loglevel) << ": ";
  _os << std::string(_loglevel > logDEBUG ? (_loglevel - logDEBUG) : 0, '\t');
}

// _____________________________________________________________________________
inline Log::~Log()
{
  _os << std::endl;
  std::cout << _os.str();
}

// _____________________________________________________________________________
inline LogLevel& Log::ReportingLevel()
{
  static LogLevel reportingLevel = logDEBUG;
  return reportingLevel;
}

// _____________________________________________________________________________
inline std::string Log::ToString(LogLevel _loglevel)
{
  static const char* const buffer[] = {"ERROR", "WARNING", "INFO", "DEBUG"};
  return buffer[_loglevel];
}

// _____________________________________________________________________________
inline LogLevel Log::FromString(const std::string& _loglevel)
{
  if (_loglevel == "DEBUG") return logDEBUG;
  if (_loglevel == "INFO") return logINFO;
  if (_loglevel == "WARNING") return logWARNING;
  if (_loglevel == "ERROR") return logERROR;
  Log(logWARNING) << "Unknown logging level '" << _loglevel << "'. Using INFO level as default.";
  return logINFO;
}

// _____________________________________________________________________________
typedef Log LOG;

#define LOG(_loglevel) \
  if (_loglevel > LOG::ReportingLevel()) ;          \
  else Log(_loglevel)

// _____________________________________________________________________________
inline std::string GetTime()
{
  struct timeval tv;
  gettimeofday(&tv, 0);
  char buffer[100];
  tm r;
  strftime(buffer, sizeof(buffer), "%X", localtime_r(&tv.tv_sec, &r));
  char result[100];
  sprintf(result, "%s.%06ld", buffer, (long)tv.tv_usec);
  return result;
}

#endif /* _LOG_ */
