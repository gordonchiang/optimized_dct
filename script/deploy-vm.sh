#!/bin/bash

root_dir=$( cd "$(dirname "${BASH_SOURCE[0]}")" || exit ; cd ../; pwd -P ) # https://stackoverflow.com/questions/24112727/relative-paths-based-on-file-location-instead-of-current-working-directory

# Execute commands on local from root directory of repo
cd "$root_dir" || exit;
echo;

# Compile locally


# ssh into vm nd make a folder in /tmp
echo "Creating folder ~/optimized_dct on remote";
ssh root@localhost -p 5555 "cd /tmp; mkdir -p ~/optimized_dct";
echo;

cd ..\vm

scp to put it on instead
