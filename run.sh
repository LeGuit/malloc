#!/bin/sh
make
export DYLD_LIBRARY_PATH=.
export DYLD_INSERT_LIBRARIES=libft_malloc_x86_64_Darwin.so
export DYLD_FORCE_FLAT_NAMESPACE=1
echo "before Hello\n-----------\n"
./a.out
echo "after Hello\n-----------\n"
