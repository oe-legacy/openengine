#!/bin/sh
etags `find . \( -iname '*.cpp' -or -iname '*.h' \) -and -not \( -path '*_darcs*' -or -path '*build*' \)`
