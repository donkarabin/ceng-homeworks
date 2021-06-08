1949940 Yusif Aliyev               05.01.2020 - 06:20 


#Scripts are in the "scripts" folder
#Experiment results are in the "experiments" folder

------------------------------------------------------------------------------------------------------------------------------------------

Firstly, configureR1.sh and configureR2.sh executed on the devices.


Commands :
	python s.py   # s.py script on S Node
	python r1.py  # r1.py script on R1 Node
	python r2.py  # r2.py script on R2 Node
	python r3.py  # r3.py script on R3 Node
	python d.py   # d.py script on D Node
------------------------------------------------------------------------------------------------------------------------------------------

# s.py and d.py designed as Clients and they send messages to the r1,r2,r3 nodes and calculate RTT values and End-to-end delays.
 
# r1.py and r3.py designed as Servers they receieve messages from s,d,r2 nodes.

# r2.py designed as both Server and Client and it sends messages to r1,r3 nodes at the same time receives messages from s and d nodes and calculate RTT values and End-to-end delays.

------------------------------------------------------------------------------------------------------------------------------------------

After execution, s,d and r2 nodes creates .txt files that :

 s node creates : 's-to-r1-RTT.txt' that has RTT values of 1000 messages between s and r1 nodes.
 		   
		  's-to-r1.-average-RTT.txt that has average RTT value of that 1000 messages

		  's-to-r1-average-end-TO-end.txt' that has average end-to-end delay values of transfer from s to r1.
			
	          ####################################################################################################

		  's-to-r2-RTT.txt' that has RTT values of 1000 messages between s and r2 nodes.
 		   
		  's-to-r2.-average-RTT.txt that has average RTT value of that 1000 messages

		  's-to-r2-average-end-TO-end.txt' that has average end-to-end delay values of transfer from s to r2.

                  ####################################################################################################
			
		  's-to-r3-RTT.txt' that has RTT values of 1000 messages between s and r3 nodes.
 		   
		  's-to-r3.-average-RTT.txt that has average RTT value of that 1000 messages

		  's-to-r3-average-end-TO-end.txt' that has average end-to-end delay values of transfer from s to r3.

		  #####################################################################################################

 d node creates : 'd-to-r1-RTT.txt' that has RTT values of 1000 messages between d and r1 nodes.
 		   
		  'd-to-r1.-average-RTT.txt that has average RTT value of that 1000 messages

		  'd-to-r1-average-end-TO-end.txt' that has average end-to-end delay values of transfer from d to r1.

		  #####################################################################################################

		  'd-to-r2-RTT.txt' that has RTT values of 1000 messages between d and r2 nodes.
 		   
		  'd-to-r2.-average-RTT.txt that has average RTT value of that 1000 messages

		  'd-to-r2-average-end-TO-end.txt' that has average end-to-end delay values of transfer from d to r2.

                  ####################################################################################################
			
		  'd-to-r3-RTT.txt' that has RTT values of 1000 messages between d and r3 nodes.
 		   
		  'd-to-r3.-average-RTT.txt that has average RTT value of that 1000 messages

		  'd-to-r3-average-end-TO-end.txt' that has average end-to-end delay values of transfer from d to r3.

		  #####################################################################################################	

r2 node creates : 'r2-to-r1-RTT.txt' that has RTT values of 1000 messages between r2 and r1 nodes.
 		   
		  'r2-to-r1.-average-RTT.txt that has average RTT value of that 1000 messages

		  'r2-to-r1-average-end-TO-end.txt' that has average end-to-end delay values of transfer from r2 to r1.

		  #####################################################################################################

		  'r2-to-r3-RTT.txt' that has RTT values of 1000 messages between r2 and r3 nodes.
 		   
		  'r2-to-r3.-average-RTT.txt that has average RTT value of that 1000 messages

		  'r2-to-r3-average-end-TO-end.txt' that has average end-to-end delay values of transfer from r2 to r3.

----------------------------------------------------------------------------------------------------------------------------------------------

# Implemented Multi-Threading at all nodes in order to send and receive messages simultaneously. After examninig the .txt files, I realized
that the average RTT value is nearly 70-200 ms at the nodes, but average end-to-end delay is nearly 1 ms on all of the nodes. I chechked send
and the receive times ov the clients and servers and saw that it is true, the time between sending and receiving is ~1 ms for all nodes and it is not possible because, if RTT value is 70 ms , it should be nearly 70/2= 35 ms. I think it is the time synchronisation problem between the nodes. Also I tried for hours(nearly 5-6 hours) to fix this problems by modifying the "ntp.conf" file at /etc destination , and added there different servers like server 0.ubuntu.pool.ntp.org
		       server 1.ubuntu.pool.ntp.org
		       server 2.ubuntu.pool.ntp.org
		       server 3.ubuntu.pool.ntp.org
 and lots of other servers and restarted the ntp by " sudo service ntp reload " command for lots of time but, I could not achieve to fix it. So, I hope that you can try my codes at synchronised machines and I beleive that they will work. Additionally, after I configured the ntp.conf
files of S and R1 nodes,  I mistakenly brake some things , that will resulted in the miscalculations of the RTT values between the node S and R1 (~0.47 ms), but others are working properly.
