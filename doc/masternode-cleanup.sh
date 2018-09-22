#/bin/bash

# Check if is root
if [ "$(whoami)" != "root" ]; then
  echo "Script must be run as user: root"
  exit -1
fi

echo && echo "Stopping c2fcoin"
c2fcoin-cli stop

echo && echo "moving c2fcoin executables to another directory"
mv /usr/bin/c2fcoind /usr/local/bin/c2fcoind
mv /usr/bin/c2fcoin-tx /usr/local/bin/c2fcoin-tx
mv /usr/bin/c2fcoin-cli /usr/local/bin/c2fcoin-cli

echo && echo "starting c2fcoind"
c2fcoind