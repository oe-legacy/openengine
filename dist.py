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

class ExecError(Exception):
    "Exception thrown if execute(cmd) exited with error code != 0"

def commands():
    return ((update,  "update"),
            (data,    "data"),
            (install, "install"),
            (darcs,   "darcs"),
            (mkproj,  "mkproj"),
            (mkext,   "mkext"),
            (help,    "help"))

def update(*args):
    """
    update  [dist] -- default target. update all repositories.
    """
    run_repo(parse(*args)["darcs"])

def data(*args):
    """
    data    [dist] -- fetch all data and libraries for your platform.
    """
    d = [ (p, r) for s, p, r in parse(*args)["data"] if system(s)]
    if d: run_data(d)
    else: print "Found no data entries for platform %s." % sys.platform

def install(dist):
    """
    install <dist> -- install the distribution <dist>
    """
    if dist.startswith("proj:"):
        dist = "http://openengine.dk/code/projects/%s/%s.dist" % (dist[5:], dist[5:])
    file = dist.split("/")[-1]
    print "Installing distribution to %s" % file
    urllib.urlretrieve(dist, file)
    if ask("Would you like to update the distribution repositories"):
        update(file)
    if ask("Would you like to fetch the distribution data"):
        data(file)

def darcs(*args):
    """
    darcs   <cmd>   -- run darcs command on all extensions, projects and openengine
    """
    cmd = " ".join(args)
    ds = [path.join("extensions", e) for e in os.listdir("extensions")] + \
         [path.join("projects", p) for p in os.listdir("projects")]
    print "**** OpenEngine"
    try: execute("darcs %s --repodir %s" % (cmd, "."))
    except ExecError: pass
    for d in ds:
        if path.isdir(path.join(d, "_darcs")):
            print "**** %s" % d
            try: execute("darcs %s --repodir %s" % (cmd, d))
            except ExecError: pass

def mkext(name):
    """
    mkext   <name>  -- create new extension extensions/<name> from the ExampleExtension
    """
    mkrepo(name, "extensions", "http://openengine.dk/code/extensions/ExampleExtension")

def mkproj(name):
    """
    mkproj  <name>  -- create new project projects/<name> from the ExampleProject
    """
    mkrepo(name, "projects", "http://openengine.dk/code/projects/ExampleProject")

def help():
    """
    help            -- this message
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
            print "Skipping exiting file %s" % relpath(file)
            continue
        # make the containing directory
        if not path.isdir(dir):
            os.makedirs(dir)
        print "Retrieving %s from %s" % (relpath(file), res)
        f, h = urllib.urlretrieve(res, file)
        unpack(h.gettype(), file, dir)

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
    # entry dict with types:
    #   darcs : [(path, resource)]
    #   data  : [(sys, path, resource)]
    entries = { "darcs":[], "data":[] }
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
            # validate entry length
            e = filter(len, l.split())
            if len(e) != 3:
                errors.append("%s(%i): invalid entry." % (file, line))
            # check if the entry path is valid
            if e[1][0] != "/":
                errors.append("%s(%i): invalid path '%s'" % (file, line, e[1]))
            # if no errors were found and the tuple is not in the set add it
            if not errors:
                p = path.join(os.getcwd(), e[1][1:])
                if e[0] == "darcs":
                    typ = "darcs"
                    elm = (p, e[2])
                else:
                    typ = "data"
                    elm = (e[0], p, e[2])
                if elm not in entries[typ]:
                    entries[typ].append(elm)

    # exit if errors were found
    if errors:
        error("\n".join(errors))
    return entries

def unpack(type, file, dir):
    handles = {
        "application/zip" : unzip,
        "application/x-tar" : untar,
        "application/x-gzip" : untar
        }
    if type in handles.keys():
        print "Unpacking %s" % relpath(file)
        handles[type](file, dir)

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
    loc = path.join(dir, name)
    print "Creating new repository at: %s" % loc
    execute("darcs get %s --repodir %s" % (repo, loc))
    execute("rm -r %s" % path.join(loc,"_darcs"))
    execute("darcs init --repodir %s" % loc)

def relpath(path):
    return path.replace(os.getcwd(), "")

def ask(msg):
    a = raw_input("%s [Yn]? " % msg)
    while True:
        if a in ("", "y"):
            return True
        elif a is "n":
            return False
        a = raw_input("invalid answer. please type 'y' or 'n' ")

def printCommands(cmds):
    print "\n".join([f.__doc__.strip() for f,c in cmds])

def execute(cmd):
    proc = subprocess.Popen(cmd, shell=True, stderr=subprocess.PIPE)
    proc.wait()
    if proc.returncode != 0:
        raise ExecError("%s exited with error code %i\n%s"
                        % (cmd, proc.returncode, proc.stderr.read()))

def error(err):
    print err
    sys.exit(1)

def system(name):
    return name == "any" or sys.platform.startswith(name)

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
    try:
        fn(*sys.argv[2:])
    except TypeError:
        print "Invalid command."
        print "Possible commands are:"
        printCommands(commands())
        sys.exit(1)

if __name__ == '__main__':
    main()
