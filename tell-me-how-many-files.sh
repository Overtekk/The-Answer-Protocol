#!/bin/bash

HPP_FILES=0
CPP_FILES=0
H_FILES=0
TOTAL=0

HPP_FILES=$(find src includes -type f -name "*.hpp" | wc -l)
H_FILES=$(find src includes -type f -name "*.h" | wc -l)
CPP_FILES=$(find src includes -type f -name "*.cpp" | wc -l)
TOTAL=$((CPP_FILES + HPP_FILES + H_FILES))

echo "There are $HPP_FILES .hpp files, $H_FILES .h files and $CPP_FILES .cpp files. So a total of $TOTAL files!"
