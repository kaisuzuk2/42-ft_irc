from helper import *

def quit():
    alice = Client(nick, passwd)
    alice.send("QUIT")
    r = alice.recv()
    ok("quit", r, "ERROR")

def quit_with_comment():
    message = "good bye!"
    alice = Client(nick, passwd)
    alice.send(f"QUIT :{message}")
    r = alice.recv()
    ok_all("quit_with_comment", r, ["ERROR", f"{message}"])

def quit_notify():
    channel = "#test"
    bo = "bob"
    message = "good bye!"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    bob.send(f"JOIN {channel}")
    bob.recv()
    alice.send(f"QUIT :{message}")
    r = bob.recv()
    ok_all("quit_notify", r, ["QUIT", f"{message}"])
    bob.close()

def run():
    section("QUIT")
    quit()
    quit_with_comment()
    quit_notify()
