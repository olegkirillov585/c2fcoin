#!/bin/bash

now=$(date +"%m_%d_%Y")

# Check if is root
if [ "$(whoami)" != "root" ]; then
  echo "Script must be run as user: root"
  exit -1
fi

echo && echo "going to root directory"
cd ~/

echo && echo "Stopping daemon..."
c2fcoin-cli stop

echo && echo "downloading update"
wget https://github.com/MasterNodesPro/C2FCoin/releases/download/v1.1.0/c2fcoin-linux-ubuntu1604-v1.1.0.zip -O c2fcoin-v1.1.0.zip

mkdir c2fcoinbackup
cd c2fcoinbackup
mkdir $now

backuppath=~/c2fcoinbackup/$now

echo && echo "backing up wallet.dat masternode.conf c2fcoin.conf to $(backuppath)"
cd ../.c2fcoin
cp wallet.dat $backuppath
cp masternode.conf $backuppath
cp c2fcoin.conf $backuppath

cd ~/

echo && echo "unzipping daemons"
unzip c2fcoin-v1.1.0.zip -d ~/c2fcoin-release
cd c2fcoin-release
chmod +x c2fcoind
chmod +x c2fcoin-cli
chmod +x c2fcoin-tx
chmod +x c2fcoin-qt

echo && echo "moving to /usr/bin"
sudo mv c2fcoin-cli /usr/local/bin/c2fcoin-cli
sudo mv c2fcoin-tx /usr/local/bin/c2fcoin-tx
sudo mv c2fcoind /usr/local/bin/c2fcoind

echo && echo "cleaning up"
cd ~/
rm c2fcoin-release -rf
rm c2fcoin-v1.1.0.zip

echo && echo "starting daemon"
c2fcoind