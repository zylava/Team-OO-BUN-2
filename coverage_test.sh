#!/bin/bash

make gcov
./gcov_test
gcov -r server.cpp connection.cpp
