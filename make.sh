#!/bin/sh
HELP="Small script to help working on the OpenEngine source.
Some useful targets are:
  all (default)      -- set up the build system and compile the source
  rebuild            -- remove the build system and rebuild from source
  darcs <cmd>        -- run darcs command on all extensions, projects and openengine
  deploy-proj <name> -- create new project projects/<name> from the ExampleProject
  deploy-ext <name>  -- create new extension extensions/<name> from the ExampleExtension
  test               -- run all tests
  test-auto          -- run all automatic tests
  test-manual        -- run all tests that need interaction
  targets            -- list of make targets
  doc                -- build the doxygen documentation (requires doxygen)
  help               -- this message
  [other]            -- forwarded to make in the build directory"

# check the current working dir is the oe root.
if [ ! -f `pwd`/make.sh ]; then
    echo "You must run make.sh from the openengine root directory."
    exit 1
fi

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
elif [ "$1" = "deploy-proj" ]; then
    NAME=$2
    echo "*** Deploying new project to: projects/${NAME}"
    cd projects
    darcs get http://daimi.au.dk/~cgd/projects/ExampleProject $NAME
    cd ..
    exit
elif [ "$1" = "deploy-ext" ]; then
    NAME=$2
    echo "*** Deploying new extension to: extensions/${NAME}"
    cd extensions
    darcs get http://daimi.au.dk/~cgd/extensions/ExampleExtension $NAME
    cd ..
    exit
elif [ "$1" = "darcs" ]; then
    echo "**** $@ in OpenEngine"
    $@
    for e in extensions/* projects/*; do
	cd $e
	if [ -d "_darcs" ]; then
	    echo "**** $@ in $e"
	    $@
	fi
	cd ../../
    done
    exit
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
