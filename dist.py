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
import urllib, zipfile, tarfile

def commands():
    return ((update, "update"),
            (data,   "data"),
            (darcs,  "darcs"),
            (mkproj, "mkproj"),
            (mkext,  "mkext"),
            (help,   "help"))

def update(*args):
    """
    update [dists] -- default target. update all repositories.
    """
    run_repo(parse(*args)["darcs"])

def data(*args):
    """
    data   [dists] -- fetch all data and libraries for your platform.
    """
    d = parse(*args)
    run_data(d["any"])
    run_data(d[system()])

def darcs(*args):
    """
    darcs  <cmd>   -- run darcs command on all extensions, projects and openengine
    """
    cmd = " ".join(args)
    ds = [path.join("extensions", e) for e in os.listdir("extensions")] + \
         [path.join("projects", p) for p in os.listdir("projects")]
    print "**** OpenEngine"
    execute("darcs %s --repodir %s" % (cmd, "."))
    for d in ds:
        if path.isdir(path.join(d, "_darcs")):
            print "**** %s" % d
            execute("darcs %s --repodir %s" % (cmd, d))

def mkext(name):
    """
    mkext  <name>  -- create new extension extensions/<name> from the ExampleExtension
    """
    mkrepo(name, "extensions", "http://openengine.dk/code/extensions/ExampleExtension")

def mkproj(name):
    """
    mkproj <name>  -- create new project projects/<name> from the ExampleProject
    """
    mkrepo(name, "projects", "http://openengine.dk/code/projects/ExampleProject")

def help():
    """
    help           -- this message
    """
    print "Small script to help working on OpenEngine repositories."
    print "Some useful targets are:"
    printCommands(commands())

def run_repo(repos):
    """
    fetch/update repositories
    """
    for p,r in repos:
        if path.isdir(path.join(p, "_darcs")):
            cmd = "pull"
        else:
            cmd = "get"
        print "Updating %s from %s" % (relpath(p), r)
        execute("darcs %s %s --repodir %s" % (cmd, r, p))

def run_data(data):
    """
    fetch data
    """
    for dir, res in data:
        file = path.join(dir, res.split("/")[-1])
        # ignore files that exist
        if path.isfile(file):
            continue
        # make the containing directory
        if not path.isdir(dir):
            os.makedirs(dir)
        print "Retrieving %s from %s" % (relpath(file), res)
        f, h = urllib.urlretrieve(res, file)
        if h.gettype() == "application/zip":
            unzip(file, dir)
        elif h.gettype() == "application/x-tar":
            untar(file, dir)

def parse(*args):
    """
    Parse a list of distribution files.
    Returns a dictionary of path*resource mapping for each type of
    distribution file operation.
    """
    # set args as file list or find dist files in the oe root dir
    if args:
        files = list(args)
    else:
        files = [ f for f in os.listdir(".")
                  if f.endswith(".dist")
                  and f[0] not in (".","#") ]
    # check that all files exist
    invalid = [f for f in files if not path.isfile(f)]
    if invalid:
        error("Could not find the distribution files:\n" +
              ", ".join(invalid))
    # error queue
    errors = []
    # entry dict with entries of type: [(path, resource)]
    entries = { "darcs":[], "any":[], "gnu":[], "mac":[], "win":[] }
    # parse each line in each file
    for file in files:
        f = open(file, "r")
        line = 0
        for l in f:
            line += 1
            l = l.strip()
            # ignore blank lines and comments
            if len(l) == 0 or l[0] == "#":
                continue
            # validate entry
            e = filter(len, l.split(" "))
            if len(e) != 3:
                errors.append("%s(%i): invalid entry." % (file, line))
            # check if the entry operation is valid
            if e[0] not in entries.keys():
                errors.append("%s(%i): invalid operation '%s'." % (file, line, e[0]))
            # check if the entry path is valid
            if e[1][0] != "/":
                errors.append("%s(%i): invalid path '%s'" % (file, line, e[1]))
            # if no errors were found and the path+resource pair is
            # not in the set add it
            if not errors:
                p = path.join(os.getcwd(), e[1][1:])
                if (p, e[2]) not in entries[e[0]]:
                    entries[e[0]].append((p, e[2]))

    # exit if errors were found
    if errors:
        error("\n".join(errors))
    return entries

def untar(file, dir):
    tar = tarfile.open(file)
    tar.extractall(dir)
    tar.close()

def unzip(file, dir):
    zip = zipfile.ZipFile(file)
    for n in zip.namelist():
        if n.endswith('/'):
            os.mkdir(path.join(dir, n))
        else:
            out = open(path.join(dir, n), "wb")
            out.write(zip.read(n))
            out.close()

def mkrepo(name, dir, repo):
    if len(sys.argv) < 3:
        error("Invalid extension or project name")
    name = sys.argv[2]
    loc = path.join(dir, name)
    print "Creating new repository at: %s" % loc
    execute("darcs get %s --repodir %s" % (repo, loc))
    execute("rm -r %s" % path.join(loc,"_darcs"))
    execute("darcs init --repodir %s" % loc)

def relpath(path):
    return path.replace(os.getcwd(), "")

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
    # map from py names to our names
    m = {"posix":"gnu", "mac":"mac", "nt":"win"}
    return m[os.name]

def main():
    # check run location
    if not path.isfile(path.join(os.getcwd(), "dist.py")):
        print "You must run dist.py from the OpenEngine root directory."
    # if no command is given run default
    if len(sys.argv) < 2:
        update()
        sys.exit(0)
    # get command
    cmd = sys.argv[1]
    fn = None
    for f,c in commands():
        if cmd == c: fn = f
    if fn: fn(*sys.argv[2:])
    else:
        print "Invalid command."
        print "Possible commands are:"
        printCommands(commands())
        sys.exit(1)

if __name__ == '__main__':
    main()
