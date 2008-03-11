#!/usr/bin/env python
# -------------------------------------------------------------------
# Helper script to manage compiling and running OpenEngine.
# For usage information run ./make.py help
# -------------------------------------------------------------------
# Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
# 
# This program is free software; It is covered by the GNU General 
# Public License version 2 or any later version. 
# See the GNU General Public License for more details (see LICENSE). 
#--------------------------------------------------------------------

import string, sys, subprocess, os, os.path as path

# reuse the helpers from repo.py
from repo import printCommands, error, execute

build_dir = path.join(os.getcwd(), "build")

def commands():
    return ((build,   "all"),
            (rebuild, "rebuild"),
            (clean,   "clean"),
            (targets, "targets"),
            (doc,     "doc"),
            (help,    "help"),
            (make,    None))

def build():
    """
    all (default) -- set up the build system and compile the source
    """
    if not path.isdir(build_dir):
        os.mkdir(build_dir)
    if not path.isfile(path.join(build_dir, "Makefile")):
        owd = os.getcwd()
        os.chdir(build_dir)
        execute("cmake ..")
        os.chdir(owd)
    make("all")

def rebuild():
    """
    rebuild       -- remove the build system and rebuild from source
    """
    clean(False)
    build()

def clean(delroot=True):
    """
    clean         -- delete all build files
    """
    if path.isdir(build_dir):
        for root, dirs, files in os.walk(build_dir, topdown=False):
            for name in files:
                os.remove(path.join(root, name))
            for name in dirs:
                os.rmdir(path.join(root, name))
    if delroot:
        os.rmdir(build_dir)

def targets():
    """
    targets       -- list of make targets
    """
    make("help")

def doc():
    """
    doc           -- build the doxygen documentation (requires doxygen)
    """
    make("doc")

def help():
    """
    help          -- this message
    """
    print "Small script to help compiling and running OpenEngine."
    print "Some useful targets are:"
    printCommands(commands())

def make(target):
    """
    <other>       -- forwarded to make in the build directory
    """
    owd = os.getcwd()
    os.chdir(build_dir)
    execute("make "+target)
    os.chdir(owd)

def main():
    # check run location
    if not path.isfile(path.join(os.getcwd(), "make.py")):
        print "You must run make.py from the OpenEngine root directory."
    # if no command is given run default
    if len(sys.argv) < 2:
        build()
        sys.exit(0)
    # get command
    cmd = sys.argv[1]
    fn = None
    for f,c in commands():
        if cmd == c: fn = f
    if fn: fn()
    elif len(sys.argv) == 2:
        make(sys.argv[1])
    else:
        print "Invalid command."
        print "Possible commands are:"
        printCommands(commands())
        sys.exit(1)

if __name__ == '__main__':
    main()
