#!/bin/bash

export G_DEBUG=gc-friendly
export G_SLICE=always-malloc
export GLIBCPP_FORCE_NEW=1
export GLIBCXX_FORCE_NEW=1
valgrind --tool=memcheck --leak-check=full --leak-resolution=high --track-origins=yes --show-leak-kinds=definite,indirect --suppressions=/usr/share/glib-2.0/valgrind/glib.supp ./../out/bin/test
