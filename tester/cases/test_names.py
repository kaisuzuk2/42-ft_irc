from helper import *

def names_no_param():
    alice = Client(nick, passwd)
    alice.send("NAMES")
    r = alice.recv()
    ok("names_no_param", r, "366")
    alice.close()

def names_no_such_channel():
    alice = Client(nick, passwd)
    alice.send("NAMES #nochan")
    r = alice.recv()
    ok("names_no_such_channel", r, "366")
    alice.close()

def names():
    channel = "#test"
    bo = "bob"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    bob.send(f"JOIN {channel}")
    bob.recv()
    alice.recv()
    alice.send(f"NAMES {channel}")
    r = alice.recv()
    ok_all("names", r, ["353", "366", f"{bo}", f"{nick}"])
    alice.close()
    bob.close()

def names_multiple_channel():
    chan1 = "#test1"
    chan2 = "#test2"
    alice = Client(nick, passwd)
    alice.send(f"JOIN {chan1},{chan2}")
    alice.recv()
    alice.send(f"NAMES {chan1},{chan2}")
    r = alice.recv()
    ok_all("names_multiple_channel", r, ["353", "366", f"{chan1}", f"{chan2}"])
    alice.close()

def names_operator():
    channel = "#test"
    alice = Client(nick, passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"NAMES {channel}")
    r = alice.recv()
    ok("names_operator", r, f"@{nick}")
    alice.close()




def run():
    section("NAMES")
    names_no_param()
    names_no_such_channel()
    names()
    names_multiple_channel()
    names_operator()