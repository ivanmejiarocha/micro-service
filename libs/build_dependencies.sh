#!/bin/bash

RESTSDK_VERSION="v2.10.6"
DEFAULT_LIB_DIRECTORY_PATH="."

libDir=${1:-$DEFAULT_LIB_DIRECTORY_PATH}

install_cpprestsdk(){
	restsdkDir="$libDir/cpprestsdk"
	restsdkBuildDir="$restsdkDir/build.release"
   
   if ! [ -d "$restsdkDir" ]; then
        git clone https://github.com/Microsoft/cpprestsdk.git "$restsdkDir"
   fi
   

	(cd $restsdkDir && git checkout tags/$RESTSDK_VERSION -b $RESTSDK_VERSION)
	mkdir "$restsdkBuildDir"
	if [[ "$OSTYPE" == "linux-gnu" ]]; then
		export CXX=g++
	fi
	(cd "$restsdkBuildDir" && cmake ../Release -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF -DBUILD_TESTS=OFF -DBUILD_SAMPLES=OFF)
	(cd "$restsdkBuildDir" && make -j$(nproc))
}

mkdir -p "$libDir"
install_cpprestsdk
