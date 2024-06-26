#!/bin/bash

dir=$(dirname "$0")/../m4

function process_url
{
while read url; do
	echo "==========================="
	filename=$(basename $url)
	echo "Checking for new version of $filename at $url"
	filename="${dir}/${filename}"
	if wget -qO "${filename}.new" $url; then
		if diff -sq "${filename}" "${filename}.new"; then
			echo "No new version found"
		else
			# files differ
			mv "${filename}.new" "${filename}"
			echo "New version found:"
			head -n10 "${filename}"
		fi
	else
		echo "Update check failed"
	fi
	rm "${filename}.new" 2>/dev/null
done
}


grep autoconf-archive $dir/* -l | grep -o "m4/ax.*.m4" | sed "s|m4/|https://git.savannah.gnu.org/gitweb/?p=autoconf-archive.git;a=blob_plain;f=m4/|" | process_url
#cat <<EOT | process_url
#https://git.savannah.gnu.org/gitweb/?p=autoconf-archive.git;a=blob_plain;f=m4/ax_cxx_compile_stdcxx.m4
#https://git.savannah.gnu.org/gitweb/?p=autoconf-archive.git;a=blob_plain;f=m4/ax_prefix_config_h.m4
#https://git.savannah.gnu.org/gitweb/?p=autoconf-archive.git;a=blob_plain;f=m4/ax_pthread.m4
#https://git.savannah.gnu.org/gitweb/?p=autoconf-archive.git;a=blob_plain;f=m4/ax_int128.m4
#https://git.savannah.gnu.org/gitweb/?p=autoconf-archive.git;a=blob_plain;f=m4/ax_gcc_func_attribute.m4
#EOT

# https://raw.githubusercontent.com/malb/m4rie/master/m4/ax_m4ri_flags.m4 <= has hardcoded M4RIE_M4RI_CFLAGS, needs manual updating
