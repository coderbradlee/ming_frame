#!/usr/bin/python
import socket,sys
sock=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
sock.connect(('127.0.0.1',19999))
sock.setblocking(0)
a='a'*1000000
b='b'*1000000
n1=sock.send(a)
n2=0
try:
	n2=sock.send(b)
except socket.error as ex:
	print ex
print n1
print n2
sock.close()