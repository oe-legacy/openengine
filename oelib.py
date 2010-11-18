#!/usr/bin/env python
# -------------------------------------------------------------------
# Helper script to manage OpenEngine distributions.
# For usage information run ./dist.py help
# -------------------------------------------------------------------
# Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
#
# This program is free software; It is covered by the GNU General
# Public License version 2 or any later version.
# See the GNU General Public License for more details (see LICENSE).
#--------------------------------------------------------------------

import string, sys, subprocess, os, os.path as path
import urllib, urllib2, zipfile, tarfile

class ExecError(Exception):
    "Exception thrown if execute(cmd) exited with error code != 0"

def printCommands(cmds):
    print "\n".join([f.__doc__.strip() for f,c in cmds])

def execute(cmd):
    proc = subprocess.Popen(cmd, shell=True)
    proc.wait()
    if proc.returncode != 0:
        raise ExecError("%s exited with error code %i\n"
                        % (cmd, proc.returncode))

def error(err):
    print err
    sys.exit(1)

def system(name):
    return name == "any" or sys.platform.startswith(name)

def cores():
    '''
    Returns the number of CPUs in the system
    '''
    # ------------------------------------- #
    # From: http://pyprocessing.berlios.de/ #
    # ------------------------------------- #
    try:
        count = 0
        if system("linux"):
            count = os.sysconf('SC_NPROCESSORS_ONLN')
        elif system("darwin"):
            count = int(os.popen('sysctl -n hw.ncpu').read())
        elif system("win"):
            count = int(os.environ['NUMBER_OF_PROCESSORS'])
        return max(count, 1)
    # if an error occurs simply return one
    except Exception: pass
    return 1
