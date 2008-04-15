#!/usr/bin/env python
# -------------------------------------------------------------------
# Helper script to manage OpenEngine repositories.
# For usage information run ./repo.py help
# -------------------------------------------------------------------
# Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
# 
# This program is free software; It is covered by the GNU General 
# Public License version 2 or any later version. 
# See the GNU General Public License for more details (see LICENSE). 
#--------------------------------------------------------------------

import string, sys, subprocess, os, os.path as path

def commands():
    return ((update, "update"),
            (darcs,  "darcs"),
            (mkproj, "mkproj"),
            (mkext,  "mkext"),
            (help,   "help"))

def update():
    """
    update [group] -- update from all repositories in the repositories group file.
                  if no groups are specified it will update from all group files
    """
    # find all repository group files
    gs = filter(lambda f: f[-6:]==".repos" and f[0] not in (".","#"),
                os.listdir("."))
    # if groups are given on the command line filter out the others
    fs = map(string.lower,
             map(lambda f: f[-6:] != ".repos" and f+".repos" or f,
                 sys.argv[2:]))
    if len(fs) > 0:
        gs = filter(lambda g: g.lower() in fs, gs)
    # check that all filters triggered
    if len(gs) < len(fs):
        error("Could not find the repository group files: " +
              ", ".join(filter(lambda f: f not in map(string.lower, gs), fs)))
    # repository set: [(Path * Repo)]
    rs = []
    for g in gs:
        f = open(g,"r")
        for l in f:
            # ignore comments and blank lines
            if len(l.strip()) == 0 or l.strip()[0] == "#":
                continue
            # split by spaces
            v = filter(len, map(string.strip, l.split(" ")))
            if len(v) != 2 or v[0][0] != "/":
                error("Invalid repository line %s" % v)
            # if an identical path+repo is not in the set add it
            t = (v[0][1:], v[1])
            if t not in rs:
                rs.append(t)
        f.close()
    # for each path+repo run darcs on it
    for p,r in rs:
        if path.isdir(path.join(os.getcwd(), p, "_darcs")):
            cmd = "pull"
        else:
            cmd = "get"
            print 'Getting from "%s"...' % r
        if p == "": p = "."
        execute("darcs %s %s --repodir %s" % (cmd, r, p))

def darcs():
    """
    darcs <cmd>    -- run darcs command on all extensions, projects and openengine
    """
    cmd = " ".join(sys.argv[2:])
    ds = [path.join("extensions", e) for e in os.listdir("extensions")] + \
         [path.join("projects", p) for p in os.listdir("projects")]
    print "**** OpenEngine"
    execute("darcs %s --repodir %s" % (cmd, "."))
    for d in ds:
        if path.isdir(path.join(d, "_darcs")):
            print "**** %s" % d
            execute("darcs %s --repodir %s" % (cmd, d))

def mkext():
    """
    mkext <name>   -- create new extension extensions/<name> from the ExampleExtension
    """
    mkrepo("extensions", "http://daimi.au.dk/~cgd/extensions/ExampleExtension")

def mkproj():
    """
    mkproj <name>  -- create new project projects/<name> from the ExampleProject
    """
    mkrepo("projects", "http://daimi.au.dk/~cgd/projects/ExampleProject")

def help():
    """
    help           -- this message
    """
    print "Small script to help working on OpenEngine repositories."
    print "Some useful targets are:"
    printCommands(commands())

def mkrepo(dir, repo):
    if len(sys.argv) < 3:
        error("Invalid extension or project name")
    name = sys.argv[2]
    loc = path.join(dir, name)
    print "Creating new repository at: %s" % loc
    execute("darcs get %s --repodir %s" % (repo, loc))
    execute("rm -r %s" % path.join(loc,"_darcs"))
    execute("darcs init --repodir %s" % loc)

def printCommands(cmds):
    print "\n".join([f.__doc__.strip() for f,c in cmds])

def execute(cmd):
    proc = subprocess.Popen(cmd,
                            shell=True,
                            stderr=subprocess.PIPE,
                            #stdout=subprocess.PIPE
                            )
    proc.wait()
    errors = proc.stderr.read()
    if bool(errors):
        error(errors)

def error(err):
    print err
    sys.exit(1)

def system():
    return os.name

def main():
    try:
        # check run location
        if not path.isfile(path.join(os.getcwd(), "repo.py")):
            print "You must run repo.py from the OpenEngine root directory."
        # get command
        cmd = sys.argv[1]
        fn = None
        for f,c in commands():
            if cmd == c: fn = f
        if not fn:
            raise IndexError()
        # run command
        fn()
    except IndexError:
        print "Invalid command."
        print "Possible commands are:"
        printCommands(commands())
        sys.exit(1)

if __name__ == '__main__':
    main()
