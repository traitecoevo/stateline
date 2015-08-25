//!
//! Main entry point for using stateline -- server side
//!
//! 
//!
//! \file app/serverwrapper.hpp
//! \author Lachlan McCalman
//! \date 2015
//! \license Lesser General Public License version 3 or later
//! \copyright (c) 2015, NICTA
//!

#include <future>
#include <zmq.hpp>
#include <json.hpp>
#include "../infer/adaptive.hpp"
#include "../infer/chainarray.hpp"
#include "../infer/sampler.hpp"

namespace stateline
{
  struct StatelineSettings
  {
      uint ndims;
      uint nstacks;
      uint nchains;
      uint annealLength;
      uint nsecs;
      uint swapInterval;
      int msLoggingRefresh;
      mcmc::SlidingWindowSigmaSettings sigmaSettings;
      mcmc::SlidingWindowBetaSettings betaSettings;
      mcmc::ChainSettings chainSettings;
      uint maxJobTypes;
      mcmc::ProposalBounds proposalBounds;

      static StatelineSettings fromJSON(const nlohmann::json& j)
      {
        StatelineSettings s;
        s.ndims = j["dimensionality"];
        s.nstacks = j["parallelTempering"]["stacks"];
        s.nchains = j["parallelTempering"]["chains"];
        s.annealLength = j["annealLength"];
        s.nsecs = j["duration"];
        s.swapInterval = j["parallelTempering"]["swapInterval"];
        s.msLoggingRefresh = 1000;
        s.sigmaSettings = mcmc::SlidingWindowSigmaSettings::fromJSON(j);
        s.betaSettings = mcmc::SlidingWindowBetaSettings::fromJSON(j);
        s.chainSettings.databasePath = j["output"]["directory"].get<std::string>();
        s.chainSettings.chainCacheLength = j["output"]["cacheLength"];
        s.maxJobTypes = j["maxJobTypes"];

        if (j.count("boundaries"))
          s.proposalBounds = mcmc::ProposalBounds::fromJSON(j);

        return s;
      }
  };

  class ServerWrapper
  {

    public:
      ServerWrapper(uint port, const StatelineSettings& s);
      ~ServerWrapper();
      void start();
      void stop();
      bool isRunning();

    private:
      uint port_;
      StatelineSettings settings_;
      bool running_;
      zmq::context_t* context_;
      std::future<void> serverThread_;
      std::future<void> samplerThread_;
  };
}
