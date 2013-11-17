import socket
from packet import Packet

sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
#sock.connect(("68.62.87.97",48011))
sock.connect(("127.0.0.1",8011))
data1={}
data2={}
data1["request_type"]=3
data1["room"]="Hall"
msg1=Packet.pack(data1)
data2["request_type"]=4
data2["target"]="room"
data2["room"]="Hall"
data2["message"]="hello world"
msg2=Packet.pack(data2)
sock.send("%8s"%(hex(len(msg1))[2:]));
sock.send(msg1)
sock.send("%8s"%(hex(len(msg2))[2:]));
sock.send(msg2)
while(1):
	head = sock.recv(8);
	if head:
		size=int("0x"+head.strip(),16);
		data = sock.recv(size);
		ary=Packet.unpack(data)
		print ary
