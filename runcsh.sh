#!/bin/sh
setenv DYLD_LIBRARY_PATH .
setenv DYLD_INSERT_LIBRARIES libft_malloc_x86_64_Darwin.so
setenv DYLD_FORCE_FLAT_NAMESPACE 1
