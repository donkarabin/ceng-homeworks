from socket import socket, AF_INET, SOCK_DGRAM
from sys import argv, stdout
import threading

#simple forwarder for nodes between source and destinaton. implemented using threads.
dest_addr_s = argv[1]
dest_port_s = argv[2]
destS = (dest_addr_s, dest_port_s)
dest_addr_d = argv[3]
dest_port_d = argv[4]
destD = (dest_addr_d, dest_port_d)
listen_addr_s = argv[5]
listen_port_s = int(argv[6])
listenS = (listen_addr_s, listen_port_s)
listen_addr_d = argv[7]
listen_port_d = int(argv[8])
listenD = (listen_addr_d, listen_port_d)

#destS = ("10.10.3.1", 1603)
#destD = ("10.10.7.1", 1601)
#listenS = ("10.10.3.2", 1600)
#listenD = ("10.10.7.2", 1602)
def receiveSforwardD():

    recv_sock_S = socket(AF_INET, SOCK_DGRAM)
    send_sock_D = socket(AF_INET, SOCK_DGRAM)
    #dest_port_s = int(argv[2])
    recv_sock_S.bind(listenS)
    recv_sock_S.settimeout(0.001)
    while True:
        try:
            message, address = recv_sock_S.recvfrom(4096)
            print("received from S")
            send_sock_D.sendto(message, destD)
            print("forwarded to D")
        except:
            print("socket S timed out")


def receiveDforwardS():

    send_sock_S = socket(AF_INET, SOCK_DGRAM)
    recv_sock_D = socket(AF_INET, SOCK_DGRAM)

    recv_sock_D.bind(listenD)
    recv_sock_D.settimeout(0.001)

    expecting_seq = 0

    while True:
        try:
            message, address = recv_sock_D.recvfrom(4096)
            print("received from D")
            send_sock_S.sendto(message, destS)
            print("forwarded to S")
        except:
            print("socket D timed out")


if __name__ == "__main__":
    
    forwardThread1 = threading.Thread(target=receiveSforwardD)
    forwardThread1.start()
    forwardThread2 = threading.Thread(target=receiveDforwardS)
    forwardThread2.start()

    forwardThread1.join()
    forwardThread2.join()
