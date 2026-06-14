import socket

s = socket.create_connection(("127.0.0.1", 6667))

s.sendall(b"PASS pass\r\nNICK alice\r\n USER alice 0 * :alice\r\n")

response = s.recv(4096).decode()
response = s.recv(4096).decode()
print(response)