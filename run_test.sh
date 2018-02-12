#!/usr/bin/env sh
for var in $@; do
	tmp=$(mktemp -d)
	gcc -o $tmp/out $var -Llibft -lft -Ilibft/include -g
	export LD_PRELOAD="libft_malloc_x86_64_Linux.so"
	export DYLD_LIBRARY_PATH=$(pwd)
	export DYLD_INSERT_LIBRARIES="libft_malloc_x86_64_Darwin.so"
	export DYLD_FORCE_FLAT_NAMESPACE=1
	$tmp/out
	unset DYLD_LIBRARY_PATH
	unset DYLD_INSERT_LIBRARIES
	unset DYLD_FORCE_FLAT_NAMESPACE
	unset LD_PRELOAD
	echo $tmp
done
