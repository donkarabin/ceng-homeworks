### 2237519 Kaan Kalaycıoğlu - 1949940 Yusif Aliyev ###

For experiment one run the scripts with the following commands in the same order:


python forward.py [source-node interface IP] [node port] [source-destination interface IP] [node port] [node-source interface IP] [node port] [node-destination interface IP] [node port]

python receiver.py [destination-node interface IP] [destination port] [node-destination interface IP] [listen port]

python sender.py [node-source interface IP] [node port] [source-node interface IP] [node port] input.txt


an example execution

python forward.py 10.10.3.1 1603 10.10.7.1 1601 10.10.3.2 1600 10.10.7.2 1602

python receiver.py 10.10.7.2 1602 10.10.7.1 1601

python sender.py 10.10.3.2 1600 10.10.3.1 1603 input.txt


we applied the following tc-netem commands for every node

for 5% packet loss:

sudo tc qdisc add dev eth0 root netem
sudo tc qdisc add dev eth1 root netem
sudo tc qdisc add dev eth2 root netem
sudo tc qdisc add dev eth3 root netem
sudo tc qdisc change dev eth0 root netem loss 5% delay 3ms 
sudo tc qdisc change dev eth1 root netem loss 5% delay 3ms 
sudo tc qdisc change dev eth2 root netem loss 5% delay 3ms 
sudo tc qdisc change dev eth3 root netem loss 5% delay 3ms

for 15% packet loss:

sudo tc qdisc add dev eth0 root netem
sudo tc qdisc add dev eth1 root netem
sudo tc qdisc add dev eth2 root netem
sudo tc qdisc add dev eth3 root netem
sudo tc qdisc change dev eth0 root netem loss 15% delay 3ms 
sudo tc qdisc change dev eth1 root netem loss 15% delay 3ms 
sudo tc qdisc change dev eth2 root netem loss 15% delay 3ms 
sudo tc qdisc change dev eth3 root netem loss 15% delay 3ms 

for 38% packet loss:

sudo tc qdisc add dev eth0 root netem
sudo tc qdisc add dev eth1 root netem
sudo tc qdisc add dev eth2 root netem
sudo tc qdisc add dev eth3 root netem
sudo tc qdisc change dev eth0 root netem loss 38% delay 3ms 
sudo tc qdisc change dev eth1 root netem loss 38% delay 3ms 
sudo tc qdisc change dev eth2 root netem loss 38% delay 3ms 
sudo tc qdisc change dev eth3 root netem loss 38% delay 3ms 
