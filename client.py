import socket

sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
sock.connect(("127.0.0.1",8011));
'''
data=sock.recv(8);
print data
'''
while(1):
	head=sock.recv(8);
	if head!="":
		size=int("0x"+head.strip(),16)
		body=sock.recv(size);
		print body
