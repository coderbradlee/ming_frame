#!/usr/bin/python
import socket,sys
sock=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
sock.connect(('www.renesola.com',80))
sock.setblocking(0)
a='a'*10000000
b='b'*10000000
n1=sock.send(a)
n2=0
try:
	n2=sock.send(b)
except socket.error as ex:
	print ex
print n1
print n2
sock.close()