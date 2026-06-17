from helper import *

def motd():
    alice = Client(nick, passwd)
    alice.send("MOTD")
    r = alice.recv()
    ok_all("motd", r, ["375", "372", "376"])
    alice.close()

def motd_on_connect():
    alice = Client(nick, passwd)
    ok_all("motd_on_conenct", alice.r, ["375", "372", "376"])
    alice.close()


def run():
    section("MOTD")
    motd()
    motd_on_connect()