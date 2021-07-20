#!/bin/bash

# ./script/deploy-arm.sh mynetlinkid user1 "./test/8x16_128_byte 8 16"

netlink_id=$1
arm_user=$2 # There are 4 users on the machine: user1, user2, user3, user4
execution_args=$3 # e.g. "./test/8x8_64_byte 8 8"

root_dir=$( cd "$(dirname "${BASH_SOURCE[0]}")" || exit ; cd ../; pwd -P ) # https://stackoverflow.com/questions/24112727/relative-paths-based-on-file-location-instead-of-current-working-directory
arm_password="q6coHjd7P"

# Execute commands on local from root directory of repo
cd "$root_dir" || exit;
echo;

# ssh into remote and make a folder in /tmp
echo "Creating folder /tmp/${netlink_id}/ on remote";
ssh "$netlink_id"@seng440.ece.uvic.ca "cd /tmp; mkdir -p ${netlink_id}";
echo;

# Send local source code to remote
echo "Sending local source code to remote /tmp/${netlink_id}/ @ seng440.ece.uvic.ca";
scp -r ./src ./include ./test Makefile "$netlink_id"@seng440.ece.uvic.ca:/tmp/"$netlink_id";
echo;

## Commands to be executed on remote
# Compile remote source code
commands=()
commands+="echo;"
commands+="echo 'Compile on remote';"
commands+="cd /tmp/${netlink_id};"
commands+="make arm-neon;"
commands+="chmod 777 ./main.exe;"
commands+="echo;"

# Transfer executable and test files to ARM machine
commands+="echo 'Transfer files to ARM';"
commands+="lftp -c \"open -u ${arm_user},${arm_password} ${arm_user}@arm;\
  mkdir -p ${netlink_id}/test;\
  put -O ${netlink_id} main.exe;\
  mirror -R test ${netlink_id}/test\";"
commands+="echo;"

# Execute on ARM machine
commands+="echo 'Execute on ARM';"
commands+="eval \"{ sleep 1; echo ${arm_user};\
  sleep 1; echo ${arm_password};\
  echo 'cd ${netlink_id}';\
  echo 'chmod 777 main.exe';\
  echo './main.exe ${execution_args}';\
  sleep 1; }\"\
  | telnet arm;"
commands+="echo;"

# Clean
commands+="echo 'Clean up after deploy and execution';"
commands+="cd ..;"
commands+="rm -rf ${netlink_id};"

commands+="eval \"{ sleep 1;\
  echo ${arm_user};\
  sleep 1;\
  echo ${arm_password};\
  sleep 1;\
  echo 'rmdir ${netlink_id}';\
  sleep 1; }\"\
  | telnet arm;"
commands+="echo;"

# commands+="bash;"

# ssh into remote
echo "ssh into remote @ seng440.ece.uvic.ca and execute commands";
ssh -t "$netlink_id"@seng440.ece.uvic.ca "$commands";
echo;
