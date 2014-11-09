import socket
import sys
from thread import *

HOST = '10.237.27.1'   # Symbolic name meaning all available interfaces
PORT = 12345

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print 'Socket created'

try:
    s.bind((HOST, PORT))
except socket.error , msg:
    print 'Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
    sys.exit()

print 'Socket bind complete'

s.listen(10)
print 'Socket now listening'

#Function for handling connections
# def clientthread(conn):
#     #Sending message to connected client
#     conn.send('Welcome to the server. Receving Data...\n') #send only takes string

#     #infinite loop so that function do not terminate and thread do not end.
#     while True:

#         #Receiving from client
#         data = conn.recv(1024)
#         reply = 'Message Received at the server!\n'
#         print data
#         if not data:
#             break

#         conn.sendall(reply)

#     conn.close()

g = Game("testBoard.txt")

#now keep talking with the client
while len(g.players.keys()) < 2:
    #wait to accept a connection
    conn, addr = s.accept()
    print 'Connected with ' + addr[0] + ':' + str(addr[1])

    #start new thread
    conn.recv(1024)
    g.addPlayer(conn)
    # start_new_thread(clientthread ,(conn,))

while True:

    g.sendInfo()

    g.getMoves()

    g.playTurn()

s.close()