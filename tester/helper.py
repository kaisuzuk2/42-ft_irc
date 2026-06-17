import socket

port = 6667
ip = "127.0.0.1"
nick = "alice"
passwd = "pass"

GREEN = "\033[32m"
RED   = "\033[31m"
RESET = "\033[0m"  

##############################################################################

timeout = F"{RED}timeout!{RESET}"

def connect():
    s = socket.create_connection((f"{ip}", port))
    return (s)

def login(s, nick, passwd):
    s.sendall(f"PASS {passwd}\r\nNICK {nick}\r\nUSER {nick} 0 * :{nick}\r\n".encode())
    return (s.recv(4096).decode())

def ok(name, response, expected):
    if expected in response:
        print(f"{name.ljust(45)}: {GREEN}PASS{RESET}")
    else:
        print(f"{name.ljust(45)}: {RED}FAIL{RESET}")
        print(f"    expected: {expected}")
        print(f"    yours: {response[:100]}")

def ok_all(name, responce, expected_list):
    results = []
    failed = []
    for expected in expected_list:
        if expected in responce:
            results.append(f"{GREEN}PASS{RESET}")
        else:
            results.append(f"{RED}FAIL{RESET}")
            failed.append(expected)
    print(f"{name.ljust(45)}: {' '.join(results)}")
    for f in failed:
        print(f"    expected: {f}")
    if failed:
        print(f"    yours: {responce[:100]}")

def ok_timeout(name, response):
    if response == f"{timeout}":
        print(f"{name.ljust(45)}: {GREEN}PASS{RESET}")
    else:
        print(f"{name.ljust(45)}: {RED}FAIL{RESET}")
        print(f"    expected: {timeout}")
        print(f"    yours: {response[:100]}")

class Client:
    def __init__(self, nick, passwd):
        self.s = connect()
        self.r = login(self.s, nick, passwd)

    def send(self, cmd):
        self.s.sendall((cmd + "\r\n").encode())

    def recv(self):
        self.s.settimeout(2)
        try:
            self.r = self.s.recv(4096).decode()
        except socket.timeout:
            self.r = f"{timeout}"
        return (self.r)
    
    def close(self):
        self.s.close()

def section(name):
    width = 50
    print(f"\n{'=' * width}")
    print(f"    {name}")
    print(f"{'=' * width}")