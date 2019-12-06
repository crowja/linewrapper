#! /bin/bash

# Updates a Doxygen @date tag line in a file. Copy of the original
# file has the same name but suffixed with a "~", for example
# "myfile.c~".

fname=$1

# Ensure we can work with the specified file
if [[ ! -f ${fname} || ! -r ${fname} || ! -w ${fname} ]]; then
  echo "Error setting timestamp for file \"${fname}\"" >&2
  exit 1
fi

# Set the timestamp
timestamp=$(date)

# Copy the original file
cp ${fname} ${fname}~

# A little extra going on here, hence the two seds. The first sed
# only acts when a Doxygen @date tag has no trailing text and
# ends at the end of line; when that happens it simply tacks on a
# single whitespace. The second sed looks for "@date ..."
# and replaces everything after the trailing whitespace with the new
# timestamp text. The replacements attempt to preserve indentation
# and the choice of @date or \date. TODO Probably a cleaner way of
# doing this.

cat ${fname}~ \
  | sed -e "s/\([ ]*\*[ \*]*[@\\]date\)$/\1 /g" \
  | sed -e "s/\([ ]*\*[ \*]*[@\\]date \).*/\1${timestamp}/g" \
  > ${fname}

if [ $? -eq 0 ]; then
  exit 0
else
  mv ${fname}~ ${fname}
  echo "Error setting timestamp for file \"${fname}\"" >&2
  exit 1
fi
