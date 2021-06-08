import socket
import threading
import sys
import time
import datetime

def sender_func(receiver_ip,port,fname):
    #initiate socket
    sender_sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
    f=open(fname + "-RTT.txt","w")
    end_to_endarr=[]
    rttarray=[]
    print("Sending Messages from " + fname )
    #send 1000 message
    for i in range (1000):
        #take sending time
        send_time=time.time()
        #taking actual time with datetime library
        actual=datetime.datetime.now()
        #sending that time as message
        sender_sock.sendto(actual.strftime("%Y:%m:%d:%H:%M:%S:%f"),(receiver_ip, port))
        #take return message
        message,address= sender_sock.recvfrom(1024)
        #take response time
        response_time=time.time()
        #take end-to-end delay
        ete=float(message)
        end_to_endarr.append(ete)
        #measure RTT
        RTT=(response_time-send_time)*1000
        rttarray.append(RTT)
        #print("RTT to message no:" + str(i) + " is : " , RTT)
        
        #writing to files
        f.write(str(RTT) + "\n")
    f.close()
    #finding average RTT and end_to_end delays and writing it o files
    average= sum(rttarray)/len(rttarray)
    print("Average RTT : " , average)
    f=open(fname + "-average-RTT.txt","w")
    f.write(str(average))
    f.close()
    average_ete= sum(end_to_endarr)/len(end_to_endarr)
    print("Average END-TO-END : ", average_ete)
    f=open(fname + "-average-end_TO_end.txt","w")
    f.write(str(average_ete))
    f.close()

    sender_sock.sendto("end",(receiver_ip, port))

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
        sent_time=datetime.datetime.strptime(message,'%Y:%m:%d:%H:%M:%S:%f')
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
    receiver_thread_from_s = threading.Thread(target = receiver_func, args= ("10.10.2.1",3001))
    receiver_thread_from_s.start()
    receiver_thread_from_d = threading.Thread(target = receiver_func, args= ("10.10.5.1",3006))
    receiver_thread_from_d.start()

    receiver_thread_from_s.join()
    receiver_thread_from_d.join()


    sender_thread_to_r1= threading.Thread(target=sender_func, args= ("10.10.8.1",3008,"r2-to-r1"))
    sender_thread_to_r1.start()
    sender_thread_to_r3= threading.Thread(target=sender_func, args= ("10.10.6.2",3009,"r2-to-r3"))
    sender_thread_to_r3.start()

    sender_thread_to_r1.join()
    sender_thread_to_r3.join()