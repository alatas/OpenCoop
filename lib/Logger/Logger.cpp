#include "Logger.h"

Logger::Logger() : Logger(VerboseLevels::INFO)
{
}

Logger::Logger(VerboseLevels _verboseLevel)
{
  verboseLevel = _verboseLevel;
}

void Logger::Setup()
{

  Serial.begin(9600);

  while (!Serial)
  {
    // do nothing
  }

  Serial.println("Serial logger is ready!");
  delay(500);
  Serial.println("Verbose level is: ");
  Serial.println((int)verboseLevel);
  delay(500);
}

void Logger::Raw(char *str)
{
  Serial.println(str);
}

void Logger::Debug(Messages msg)
{
  if (verboseLevel >= VerboseLevels::DEBUG)
    PrintMessage(VerboseLevels::DEBUG, msg);
}

void Logger::Info(Messages msg)
{
  if (verboseLevel >= VerboseLevels::INFO)
    PrintMessage(VerboseLevels::INFO, msg);
}

void Logger::Warn(Messages msg)
{
  if (verboseLevel >= VerboseLevels::WARN)
    PrintMessage(VerboseLevels::WARN, msg);
}

void Logger::Error(Messages msg)
{
  if (verboseLevel >= VerboseLevels::ERROR)
    PrintMessage(VerboseLevels::ERROR, msg);
}
