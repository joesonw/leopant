import socket
from packet import Packet

sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
sock.connect(("127.0.0.1",8011));


while(1):
	head = sock.recv(8);
	if head:
		size=int("0x"+head.strip(),16);
		data = sock.recv(size);
		print data
		ary=Packet.unpack(data)
		print ary
