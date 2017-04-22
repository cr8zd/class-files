#!/usr/bin/python3
# server.py

import argparse, signal, sys, socket, subprocess


#Parse command line arguments
#parser = argparse.ArgumentParser(description='Enter a valid port number.')
#parser.add_argument('port', metavar='P', type=int, help='port number to listen on')
#args = parser.parse_args()

hostNames = []

#Initialize server
#port = args.port
host = socket.gethostname()
serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serversocket.bind((host, 0))
serversocket.listen(5)
(host, port) = serversocket.getsockname()
print(host + " listening on port " + str(port))

serverinfo = open("serverinfo.txt", "w")
serverText = host + "\n" + str(port)
serverinfo.write(serverText)
serverinfo.close()

received = "!"

# host/guest pairing loop
while True:
	(clientsocket, address) = serversocket.accept()
	clientText = clientsocket.recv(10).decode("utf-8").strip()
	print(clientText)
	#Add a host to the hostNames list (a new host is becoming available)
	if clientText == "!host":
		print("server: entered '!host' if loop")
		#ask for host name
		clientsocket.send(received.encode("ascii"))
		username = clientsocket.recv(20).decode("utf-8").strip()
		hostNames.append((username, address))
		clientsocket.shutdown(socket.SHUT_RDWR)
		clientsocket.close()

	#Remove a host from the hostNames list (no longer waiting to host a game)
	elif clientText == "host!":
		clientsocket.send(received.encode("ascii"))
		username = clientsocket.recv(20).decode("utf-8").strip()
		for x, (user, addr) in enumerate(hostNames):
			if user == username:
				del hostNames[x]
				break
		clientsocket.shutdown(socket.SHUT_RDWR)
		clientsocket.close()
		
	elif clientText == "guest":
		#extract the usernames from the (username, address) list
		hostNamesOnly = ""
		for x in hostNames:
			hostNamesOnly += x[0]
			hostNamesOnly += " "
		# send the username list to the guest client
		clientsocket.send(hostNamesOnly.encode("ascii"))
		# wait for a response from guest, then send address info of selected host
		username = clientsocket.recv(20).decode("utf-8").strip()
		print("server: received choice " + username + " from guest.")
		for x, (user, addr) in enumerate(hostNames):
			if username == user:
				hostAddress = addr
				hostAddress = str(hostAddress)
				print("server: hostAddress is " + hostAddress)
				break
		clientsocket.send(hostAddress.encode("ascii"))
		clientsocket.shutdown(socket.SHUT_RDWR)
		clientsocket.close()


