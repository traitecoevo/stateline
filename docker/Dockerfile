FROM ubuntu:15.04
MAINTAINER Lachlan McCalman <lachlan.mccalman@nicta.com.au>
RUN apt-get update && apt-get install -y \
  build-essential \
  git \
  bzip2 \
  cmake \
  wget \
  unzip \
  nmap

ENV PREREQ_DIR /usr/local

ENV LD_LIBRARY_PATH $LD_LIBRARY_PATH:/usr/local/lib

RUN mkdir -p /stateline /usr/local/src/stateline /tmp/build/prereqs \
  && git clone https://github.com/NICTA/stateline.git /usr/local/src/stateline \
  && cp -R /usr/local/src/stateline/tools /tmp/build/prereqs \
  && cd /tmp/build/prereqs \
  && ./tools/fetch-deps . \
  && rm -r /tmp/build/prereqs

# get stateline inside and compiled
RUN  cd /tmp/build \
  && cmake /usr/local/src/stateline -DCMAKE_BUILD_TYPE=Release -DLOCAL_INSTALL=OFF -DPREREQ_DIR=/usr/local \
  && make \
  && make install \
  && rm -r /tmp/build

# Clean up APT when done
RUN apt-get purge -y git cmake bzip2 wget unzip && apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

WORKDIR /stateline
EXPOSE 5555 5556
