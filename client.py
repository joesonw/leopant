import socket

sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
sock.connect(("127.0.0.1",8011));

while(1):
	msg=raw_input("")
	sock.send("%8s"%hex(len(msg))[2:])
	sock.send(msg)
