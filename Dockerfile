# Ubuntu 18.04 base image
FROM ubuntu:18.04
MAINTAINER Md Sumsuddin <sumsuddinshojib@gmail.com>

RUN apt update

RUN apt-get install -y --no-install-recommends \
    build-essential \
    curl \
    libfreetype6-dev \
    libzmq3-dev \
    pkg-config \
    python \
    python-dev \
    rsync \
    software-properties-common \
    unzip \
	git \
	wget \
	libboost-all-dev \
	zlib1g-dev \
	cmake \
	openssl \
	libssl-dev \
	sudo \
	fish \
	nano

# cd to /tmp and clone repos for OpenCV and extra modules
WORKDIR /tmp
RUN echo "Building opencv..."
RUN git clone http://192.168.105.3:7777/shojib/opencv.git

# Create build folder
WORKDIR /tmp/opencv
RUN git checkout 2.4.8
RUN mkdir /tmp/opencv/build
WORKDIR /tmp/opencv/build

# Build OpenCV
RUN cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_V4L=ON -D INSTALL_PYTHON_EXAMPLES=ON -D WITH_CUDA=OFF ..
RUN make -j$(nproc)
RUN make install
RUN echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf
RUN ldconfig

# Move to working dir and clean up
WORKDIR /
RUN rm -rf /tmp/*

RUN echo "Asia/Dhaka" > /etc/timezone
RUN rm -f /etc/localtime
RUN dpkg-reconfigure -f noninteractive tzdata

RUN useradd -ms /bin/bash -g root -G sudo -p dockeruser dockeruser
RUN echo dockeruser:dockeruser | chpasswd
USER dockeruser
WORKDIR /home/dockeruser
