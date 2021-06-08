import socket
import threading
import sys
import time
import datetime

def receiver_func (sender_ip,port):
    #initiate socket
    receiver_socket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
    #binding
    receiver_socket.bind((sender_ip,port))
    #infinity loop for listening
    print("Starts Listening... from port ",port)
    while True :
        #take message from clients
        message,address=receiver_socket.recvfrom(1024)
        #check if end of sequence
        if message=="end" :
            break
        #converting str to time object
        sent_time=datetime.datetime.strptime(message,"%Y:%m:%d:%H:%M:%S:%f")
        #take actual arrive time
        arrive=datetime.datetime.now()
        #compute end-to-end delay
        end_to_end=arrive-sent_time
        #convert to seconds
        end_to_end_second = end_to_end.total_seconds()*1000
        #print("End to end delay: {}ms".format(end_to_end_second))
        #send back to them
        message=str(end_to_end_second)
        receiver_socket.sendto(message,address)
    print("Data sent back succesfully")



if __name__ == "__main__":
    receiver_thread_from_s= threading.Thread(target=receiver_func, args= ("10.10.1.2",3000))
    receiver_thread_from_s.start()
    receiver_thread_from_r2= threading.Thread(target=receiver_func, args= ("10.10.8.1",3008))
    receiver_thread_from_r2.start()
    receiver_thread_from_d= threading.Thread(target=receiver_func, args= ("10.10.4.1",3005))
    receiver_thread_from_d.start()

    receiver_thread_from_s.join()
    receiver_thread_from_r2.join()
    receiver_thread_from_d.join()