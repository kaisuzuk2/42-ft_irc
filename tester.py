import socket

nick = "alice"
passwd = "pass"

GREEN = "\033[32m"
RED   = "\033[31m"
RESET = "\033[0m"   # 色をリセット

##############################################################################
def connect():
    s = socket.create_connection(("127.0.0.1", 6667))
    return (s)

def login(s, nick, passwd):
    s.sendall(f"PASS {passwd}\r\nNICK {nick}\r\nUSER {nick} 0 * :{nick}\r\n".encode())
    return (s.recv(4096).decode())

def ok(name, response, expected):
    if expected in response:
        print(f"{name.ljust(30)}: {GREEN}PASS{RESET}")
    else:
        print(f"{name.ljust(30)}: {RED}FAIL{RESET}")
        print(f"    expected: {expected}")
        print(f"    yours: {response[:100]}")

class Client:
    def __init__(self, nick, passwd):
        self.s = connect()
        self.r = login(self.s, nick, passwd)

    def send(self, cmd):
        self.s.sendall((cmd + "\r\n").encode())

    def recv(self):
        self.r = self.s.recv(4096).decode()
        return (self.r)
    
    def close(self):
        self.s.close()

###########################################################################
# testcode


def connection():
    alice = Client(nick, passwd)
    ok("connection -> 001", alice.r, "001")
    alice.close()

def wrong_passwd():
    alice = Client(nick ,"wrongpass")
    ok("wrong pass -> 464", alice.r, "464")
    alice.close()

def invalid_toolong_nick():
    alice = Client("toolongnick", passwd)
    ok("long nick -> 432", alice.r, "432")
    alice.close()

def invalid_special_nick():
    alice = Client("hello!", passwd)
    ok("special nick -> 432", alice.r, "432")
    alice.close()

connection()
wrong_passwd()
invalid_toolong_nick()
invalid_special_nick()