#!/bin/sh
HELP="Small script to help build the OpenEngine source.
Some useful targets are:
  all (default) -- set up the build system and compile the source
  rebuild       -- remove the build system and rebuild from source
  test          -- run the all the test
  test-auto     -- run all automatix tests
  test-manual   -- run all tests that need interaction
  targets       -- list of make targets
  doc           -- build the doxygen documentation (requires doxygen)
  help          -- this message
  [other]       -- forwarded to make in the build directory"

CMD=$1
if [ "$1" = "rebuild" ]; then
    rm -r build;
    CMD=""
elif [ "$1" = "run" ]; then
    ./build/cgd/game;
    exit
elif [ "$1" = "help" ]; then
    echo "$HELP"
    exit
elif [ "$1" = "targets" ]; then
    CMD="help"
fi

# create build dir if non existent
if [ ! -d build ]; then
    mkdir build
fi

# run cmake if no make system has been generated
if [ ! -f build/Makefile ]; then
    cd build
    cmake ..
    RET=$?
    cd ..
    if [ $RET -ne 0 ]; then exit $RET; fi
fi

# run make
cd build
make $CMD
RET=$?
cd ..
exit $RET
