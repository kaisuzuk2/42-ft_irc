from helper import *

def notice_no_param():
    alice = Client(nick, passwd)
    alice.send("NOTICE")
    r = alice.recv()
    ok_timeout("notice_no_param", r)
    alice.close()

def notice_no_message():
    alice = Client(nick, passwd)
    alice.send(f"NOTICE {nick}")
    r = alice.recv()
    ok_timeout("notice_no_message", r)
    alice.close()

def notice_empty_message():
    alice = Client(nick, passwd)
    alice.send(f"NOTICE {nick} :")
    r = alice.recv()
    ok_timeout("notice_empty_message",r)
    alice.close()

def notice_to_nobody():
    alice = Client(nick, passwd)
    alice.send("NOTICE nobody")
    r = alice.recv()
    ok_timeout("notice_to_nobody", r)
    alice.close()

def notice_to_invalid_channel():
    alice = Client(nick, passwd)
    alice.send("NOTICE #badchannel")
    r = alice.recv()
    ok_timeout("notice_to_invalid_channel", r)
    alice.close()

def notice_to_user():
    bo = "bob"
    message = "hello!"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    alice.send(f"NOTICE {bo} :{message}")
    r = bob.recv()
    ok_all("notice_to_user", r, ["NOTICE", f"{message}"])
    alice.close()
    bob.close()

def notice_to_channel():
    channel = "#test"
    bo = "bob"
    message = "hello channel!"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    bob.send(f"JOIN {channel}")
    bob.recv()
    alice.send(f"NOTICE {channel} :{message}")
    r = bob.recv()
    ok_all("notice_to_channel", r, ["NOTICE", f"{message}"])
    alice.close()
    bob.close()

def run():
    section("NOTICE")
    notice_no_param()
    notice_no_message()
    notice_empty_message()
    notice_to_nobody()
    notice_to_invalid_channel()
    notice_to_user()
    notice_to_channel()
