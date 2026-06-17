from helper import *

def nick_no_param():
    alice = Client(nick, passwd)
    alice.send("NICK")
    r = alice.recv()
    ok("nick_no_param", r, "461")
    alice.close()

def nick_empty():
    alice = Client(nick, passwd)
    alice.send("NICK :")
    r = alice.recv()
    ok_all("nick_empty", r, ["431", "No nickname given"])
    alice.close()

def nick_change():
    alice = Client(nick, passwd)
    alice.send("NICK newnick")
    r = alice.recv()
    ok("nick_change", r, "NICK")
    alice.close()

def nick_duplicate():
    alice = Client(nick, passwd)
    bob = Client("bob", passwd)
    bob.send(f"NICK {nick}")
    r = bob.recv()
    ok_all("nick_duplicate", r, ["433", f"{nick}", "Nickname is already in use"])
    alice.close()
    bob.close()

def nick_change_notify():
    channel = "#test"
    newnick = "newnick"
    alice = Client(nick, passwd)
    bob = Client("bob", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    bob.send(f"JOIN {channel}")
    bob.recv()
    alice.send(f"NICK {newnick}")
    r = bob.recv()
    ok_all("nick_change_notify", r, ["NICK", f"{newnick}"])
    alice.close()
    bob.close()



def run():
    section("NICK")
    nick_no_param()
    nick_empty()
    nick_change()   
    nick_duplicate()
    nick_change_notify()
