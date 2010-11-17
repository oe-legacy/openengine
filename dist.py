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

def commands():
    return ((update,  "update"),
            (data,    "data"),
            (install, "install"),
            (darcs,   "darcs"),
            (commit,  "commit"),
            (mkproj,  "mkproj"),
            (mkext,   "mkext"),
            (usage,    "help"))

def update(*args):
    """
    update  [dist] -- default target. update all repositories.
    """
    dists = get_dists(*args)
    if dists:
        run_repo(parse(*dists)["darcs"]) # run all dists
    run_repo(parse(*args)["darcs"]) # run rest

def commit(*args):
    """
    commit [user]  -- commit to the development repositories.
    """
    user = None
    if len(args) > 0 and not args[0].endswith(".dist"):
        user = args[0]
        args = args[1:]
    dists = get_dists(*args)    
    if dists:
        commit_repo(user, parse(*dists)["darcs-dev"]) # run dist
    commit_repo(user, parse(*args)["darcs-dev"]) # run rest

def data(*args):
    """
    data    [dist] -- fetch all data and libraries for your platform.
    """
    dists = get_dists(*args)
    if dists:
        d = [ (p, r) for s, p, r in parse(*dists)["data"] if system(s)]
        if d: run_data(d)
        else: print "Found no data entries for platform %s." % sys.platform
    d = [ (p, r) for s, p, r in parse(*args)["data"] if system(s)]
    if d: run_data(d)
    else: print "Found no data entries for platform %s." % sys.platform

def add_to_default(distfile,url):
    default = "default.dist"
    absfile = path.join(os.getcwd(),distfile)
    found = False
    if os.path.exists(default):
        es = parse(default)
        for (fil,u) in es['dist']:
            if fil == absfile:
                found = True
                print "This project is already installed!"                    
    if not found:
        f = open(default,"a")
        f.write("dist /%s %s\n" % (distfile, url))
        f.close()
            
    
def install(dist):
    """
    install <dist> -- install the distribution <dist>
    """
    if dist.startswith("proj:"):
        add_to_default("projects/%s/%s.dist" % (dist[5:],dist[5:]),
                       "http://openengine.dk/code/projects/%s/%s.dist" % (dist[5:], dist[5:]))
        file = "default.dist"
    else:
        file = dist #.split("/")[-1]
        add_to_default(dist,"http://err")
        # if os.path.exists(file):
        #     if not ask("The file allready exist do you want to overwrite it",
        #                default=False):
        #         error("Aborted install. Please move the existing distribution file and try again.")
        # print "Installing distribution to %s" % file

        # req = urllib2.Request(dist)
        # try: urllib2.urlopen(req)
        # except urllib2.URLError, e:
        #     error("Could not fetch dist file: %s, error: %s" % (dist,e))
        # except ValueError, e:
        #     pass

        # urllib.urlretrieve(dist, file)
    
    if ask("Would you like to update the distribution repositories"):
        update(file)
    if ask("Would you like to fetch the distribution data"):
        data(file)

def darcs(*args):
    """
    darcs   <cmd>  -- run darcs command on all extensions, projects and openengine
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
    mkext   <name> -- create new extension extensions/<name> from the ExampleExtension
    """
    mkrepo(name, "extensions", "http://openengine.dk/code/extensions/ExampleExtension")
    filesubst("ExampleExtension", name,
              "extensions/"+name+"/README.txt",
              "extensions/"+name+"/CMakeLists.txt")

def mkproj(name):
    """
    mkproj  <name> -- create new project projects/<name> from the ExampleProject
    """
    mkrepo(name, "projects", "http://openengine.dk/code/projects/ExampleProject")
    filesubst("ExampleProject", name,
              "projects/"+name+"/README.txt",
              "projects/"+name+"/CMakeLists.txt",
              "projects/"+name+"/main.cpp",
              "projects/"+name+"/ExampleProject.dist")
    os.rename("projects/"+name+"/ExampleProject.dist",
              "projects/"+name+"/"+name+".dist")
    install("projects/"+name+"/"+name+".dist")

def filesubst(k, v, *fs):
    for f in fs:
        fd = open(f, 'r')
        st = fd.read()
        fd.close()
        fd = open(f, 'w')
        fd.write(st.replace(k, v))
        fd.close()

def usage():
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

def get_windows_username():
    #check for username file if it exist read it
    if os.path.isfile("daimi.username.txt"):
        f = open("daimi.username.txt", "r")
        username = f.readline()
        f.close()
    else: #otherwise ask user for input, and make one
        print 'daimi.username.txt not found'
        answer=raw_input('Please enter your daimi user name: ')
        f = open("daimi.username.txt", "w")
        f.writelines(answer)
        f.close()
        username = answer
    #add @ for USERNAME@
    username += '@'
    return username

def commit_repo(user, repos):
    """
    push changes to repositories
    """
    if system("win"):	
        user = get_windows_username();
    else:
        if user: user = user + "@"
        else: user = ""
    for p,r in repos:
        print "Commiting %s to %s" % (relpath(p), r)
        execute("darcs push %s%s --repodir %s" % (user, r, p))

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

def get_dists(*args):
    """
    Find all dists refered in args
    """
    ds = parse(*args)['dist']
    dists = get_dists_helper(ds,[])
    dists.append("src\\basic.dist")
    #print dists
    return dists

def get_dists_helper(ds,dists):
    for distfile, dist in ds:
        fp = distfile #path.join(dir,dist.split("/")[-1])
        if fp not in dists:
            if not path.isfile(fp):
                print "== Download the dist (%s) to tmp!" % (dist)
                req = urllib2.Request(dist)
                try: urllib2.urlopen(req)
                except urllib2.URLError, e:
                    error("Could not fetch dist file: %s, error: %s" % (dist,e))
                except ValueError, e:
                    pass
                tmpfld = "tmp"
                if not path.isdir(tmpfld):
                   os.makedirs(tmpfld)                
                file = path.join(tmpfld,dist.split("/")[-1])
                urllib.urlretrieve(dist, file)
                dists.append( file )
            else:
                dists.append( fp )
                get_dists_helper(parse(fp)['dist'], dists)                
    return dists

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
    entries = { "darcs":[], "darcs-dev":[], "data":[], "dist":[]}
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
                elif e[0] == "darcs-dev":
                    typ = "darcs-dev"
                    elm = (p, e[2])
                elif e[0] == "dist":
                    typ = "dist"
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
    if sys.version_info[1] < 5:
        for m in tar:
            tar.extract(m, dir)
    else:
        tar.extractall(dir)
    tar.close()

def unzip(file, dir):
    zip = zipfile.ZipFile(file)
    for n in zip.namelist():
        if n.endswith('/') and not path.isdir(path.join(dir,n)):
            os.makedirs(path.join(dir, n))
        else:
            out = open(path.join(dir, n), "wb")
            out.write(zip.read(n))
            out.close()

def mkrepo(name, dir, repo):
    loc = path.join(dir, name)
    # flags = darcs_version().startswith("2") and "--old-fashioned-inventory" or ""
    flags = "" # We will not create darcs-1 repos any more \o/
    print "Creating new repository at: %s" % loc
    execute("darcs get %s --repodir %s" % (repo, loc))
    execute("rm -r %s" % path.join(loc,"_darcs"))
    execute("darcs init %s --repodir %s" % (flags, loc))

def relpath(path):
    return path.replace(os.getcwd(), "")

def ask(msg, default=True):
    a = raw_input("%s [%s]? " % (msg, default and "Yn" or "yN"))
    while True:
        if a is "":
            return default
        elif a is "y":
            return True
        elif a is "n":
            return False
        a = raw_input("invalid answer. please type 'y' or 'n' ")

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

def darcs_version():
    return subprocess.Popen("darcs --version",shell=True,stdout=subprocess.PIPE).communicate()[0]

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
