import socket

class Client:
	def __init__(self):
		sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

		TARGET = "10.237.27.1"
		PORT = 12345

		sock.connect((TARGET, PORT))
		sock.sendall(name)

	def rcv():
		data = sock.recv(2048)
		return data

	def send(data):
		sock.sendall(data)


