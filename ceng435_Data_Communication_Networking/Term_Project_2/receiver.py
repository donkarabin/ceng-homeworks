from socket import socket, AF_INET, SOCK_DGRAM
from sys import argv, stdout
import time
import pickle
import hashlib


if __name__ == "__main__":
	dest_addr = argv[1]
	dest_port = int(argv[2])
	dest = (dest_addr, dest_port)
	listen_addr = argv[3]
	listen_port = int(argv[4])
	listen = (listen_addr, listen_port)
	#dest_addr = "10.10.7.2"
	#dest_port = 1602
	#dest = (dest_addr, dest_port)
	#listen_addr = "10.10.7.1"
	#listen_port = 1601
	#listen = (listen_addr, listen_port)
	
	#open udp sockets
	send_sock = socket(AF_INET, SOCK_DGRAM)
	recv_sock = socket(AF_INET, SOCK_DGRAM)
	recv_sock.settimeout(5)
	print("ready")
	recv_sock.bind(listen)
	ACK = 1
	ack = []
	expecting_seq = 1
	f = open("output.txt", "wb+")
	endoffile = False
	lastpktreceived = time.time()	
	starttime = time.time()
while True:
	
	try:
		#terminate condition
		if expecting_seq == 5000:
			break
		#receive packet from source. check if checksum is equal to the checksum sent in the package.
		rcvpkt = []
		message, address = recv_sock.recvfrom(4096)
		rcvpkt = pickle.loads(message)
		c = rcvpkt[-1]
		del rcvpkt[-1]
		h = hashlib.md5()
		h.update(pickle.dumps(rcvpkt))
		
		if c == h.digest():
			#check if sent packet contains the expected data. if yes send ack packet.
			if(rcvpkt[0] == expecting_seq):
				print("Received inorder", expecting_seq)
				if rcvpkt[1] != "END":
					f.write(rcvpkt[1])
				elif rcvpkt[1] == "END":
					endoffile = True
				expecting_seq += 1
				sndpkt = []
				sndpkt.append(expecting_seq)
				h = hashlib.md5()
				h.update(pickle.dumps(sndpkt))
				sndpkt.append(h.digest())
				send_sock.sendto(pickle.dumps(sndpkt), dest)
				if endoffile:
					break
			#if not drop the packet and send an ack packet with the expected sequence number
			else:
				print("Received out of order", rcvpkt[0])
				sndpkt = []
				sndpkt.append(expecting_seq)
				h = hashlib.md5()
				h.update(pickle.dumps(sndpkt))
				sndpkt.append(h.digest())
				send_sock.sendto(pickle.dumps(sndpkt), dest)
				print("Ack", expecting_seq)

		else:
			print("error detected")
	except:
		if endoffile:
			if(time.time()-lastpktreceived>5):
				break
endtime = time.time()
print 'FILE TRANFER SUCCESSFUL'
endtime = time.time()
print "TIME TAKEN " , str(endtime - starttime)


with open("times.txt", "a+") as outputFile:
	outputFile.write(str(endtime-starttime)+"\n")

