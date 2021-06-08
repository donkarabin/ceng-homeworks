from socket import socket, AF_INET, SOCK_DGRAM, timeout
from sys import argv, getsizeof
import time
import pickle
import hashlib
import os

SEGMENT_SIZE = 1000

if __name__ == "__main__":
    dest_addr = argv[1]
    dest_port = int(argv[2])
    dest = (dest_addr, dest_port)
    listen_addr = argv[3]
    listen_port = int(argv[4])
    listen = (listen_addr, listen_port)
    #dest_addr = "10.10.3.2"
    #dest_port = 1600
    #dest = (dest_addr, dest_port)
    #listen_addr = "10.10.3.1"
    #listen_port = 1603
    #listen = (listen_addr, listen_port)
    filename = argv[5]

    # read the data file into an array
    data = []
    with open(filename, 'rb') as file:
        file_size = os.stat(filename).st_size
        packet_number = file_size/1000
        print(packet_number)
        left = file_size%1000
        for i in range(packet_number):
            data.append(file.read(1000))
        if left != 0:
            data.append(file.read(1000))
    data.append("END")
    # open socket connections
    send_sock = socket(AF_INET, SOCK_DGRAM)
    recv_sock = socket(AF_INET, SOCK_DGRAM)

    recv_sock.bind(listen)
    recv_sock.settimeout(0.2)

    seq = 1
    base = 1
    done = False
    window = []
    windowSize = 20
    startTime = time.time()
    lastackreceived = time.time()
    while(not done) or window:
        if(seq<base+windowSize) and not done:
            packet = []
            #sent packet contains sequence number, payload, and the checksum calculated using sequence number and payload
            packet.append(seq)
            packet.append(data[seq-1])
            h = hashlib.md5()
            h.update(pickle.dumps(packet))
            packet.append(h.digest())
            dumped_packet = pickle.dumps(packet)
            send_sock.sendto(dumped_packet, dest)
            print("sent data", seq)
            seq += 1
            if packet not in window:
                window.append([packet, seq])
            try:
                #wait for ack.
                receivedPacket, address = recv_sock.recvfrom(4096)
                rcvpkt = []
                rcvpkt = pickle.loads(receivedPacket)
                c = rcvpkt[-1]
                del rcvpkt[-1]
                h = hashlib.md5()
                h.update(pickle.dumps(rcvpkt))
                #check if the checksum is correct.
                if c == h.digest():
                    seq = rcvpkt[0]
                    print("Received ack for", rcvpkt[0])
                    #if eof terminate
                    if(data[seq-1] == "END"):
                        done = True
                        break
                    #slide the window
                    while rcvpkt[0] > base and window:
                        lastackreceived = time.time()
                        del window[0]
                        base = base + 1
                else:
                    print("error detected")

            except:
                #sif ack is not received in time. send n packets where n < windowSize
                print("there")
                if(time.time()-lastackreceived>0.2):
                   for i in range(base, len(window)):
                        send_sock.sendto(pickle.dumps(window[i][0]), dest)

           

