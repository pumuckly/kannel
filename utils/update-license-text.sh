#!/bin/sh
#
# update-license -- update prefix blocks with LICENSE text
#
# Run this script in gateway root directory to update the 
# current LICENSE text file to all source code files.
#

# to avoid sed errors like:
# RE error: illegal byte sequence
export LC_ALL=C

old="2001-2018 Kannel Group"
new="2001-2019 Kannel Group"

prog=`basename $0`
files=`find . -type f ! -name "${prog}" ! -path "*/.svn/*" ! -path "./addons/*" | xargs fgrep -lr "${old}"`
for i in $files; do
  echo ${i}
  cat ${i} | sed "s/${old}/${new}/" > ${i}.new
  mv ${i}.new ${i}
done
