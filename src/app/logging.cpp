//!
//! Contains the implementation of logging.
//!
//! \file app/logging.cpp
//! \author Lachlan McCalman
//! \date 2014
//! \license Lesser General Public License version 3 or later
//! \copyright (c) 2014, NICTA
//!

#include "app/logging.hpp"

#include <vector>
#include <cstdlib>
#include <iostream>

#include <easylogging/easylogging++.h>

INITIALIZE_EASYLOGGINGPP;

namespace stateline
{
  void initLogging(int logLevel, bool stdOut, const std::string& filename)
  {
    int normLog = logLevel;
    int vLevel = 0;
    if (logLevel < 0)
    {
      vLevel = -logLevel;
      normLog = 0;
    }

    el::Configurations defaultConf;
    defaultConf.setToDefault();

    defaultConf.setGlobally(
        el::ConfigurationType::Format, "%datetime %level %msg");
    defaultConf.setGlobally(
        el::ConfigurationType::ToStandardOutput, stdOut ? "true" : "false");
    defaultConf.setGlobally(
        el::ConfigurationType::ToFile, stdOut ? "false" : "true");
    defaultConf.setGlobally(
        el::ConfigurationType::Filename, filename);

    LOG(INFO) << "Logging initialised with level " << normLog << " and verbosity " << vLevel;
  }

} // namespace stateline
