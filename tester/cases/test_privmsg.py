from helper import *            

def privmsg_no_target():
    alice = Client(nick, passwd)
    alice.send("PRIVMSG")
    r = alice.recv()
    ok("privmsg_no_target", r, "461")
    alice.close()

def privmsg_no_message():
    alice = Client(nick, passwd)
    alice.send(f"PRIVMSG {nick}")
    r = alice.recv()
    ok("privmsg_no_message", r, "461")
    alice.close()

def privmsg_empty_message():
    alice = Client(nick, passwd)
    alice.send(f"PRIVMSG {nick} :")
    r = alice.recv()
    ok("privmsg_empty_message", r, "412")
    alice.close()

def privmsg_to_channel():
    channel = "#test"
    alice = Client(nick, passwd)
    bob = Client("bob", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    bob.send(f"JOIN {channel}")
    bob.recv()
    alice.send(f"PRIVMSG {channel} :Hello bob!")
    r = bob.recv()
    ok("privmsg_to_channel", r, "Hello bob!")
    alice.close()
    bob.close()

def privmsg_to_user():
    alice = Client(nick, passwd)
    bob = Client("bob", passwd)
    alice.send("PRIVMSG bob :hello bob")
    r = bob.recv()
    ok("privmsg_to_user", r, "hello bob")
    alice.close()
    bob.close()

def privmsg_to_nobody():
    alice = Client(nick, passwd)
    alice.send("PRIVMSG nobody :hello")
    r = alice.recv()
    ok("privmsg_to_nobody", r, "401")
    alice.close()

def privmsg_to_invalid_channel():
    alice = Client(nick, passwd)
    alice.send("PRIVMSG #badchannel :hello")
    r = alice.recv()
    ok("privmsg_to_invalid_channel", r, "403")
    alice.close()

def privmsg_to_multiple_channel():
    chan1 = "#test1"
    chan2 = "#test2"
    alice = Client(nick, passwd)
    bob = Client("bob", passwd)
    alice.send(f"JOIN {chan1},{chan2}")
    alice.recv()
    bob.send(f"JOIN {chan1},{chan2}")
    bob.recv()
    alice.send(f"PRIVMSG {chan1},{chan2} :hello")
    r = bob.recv()
    ok_all("privmsg_to_multiple_channel", r, [f"PRIVMSG {chan1}", f"PRIVMSG {chan2}"])
    alice.close()
    bob.close()




def run():
    section("PRIVMSG")
    privmsg_no_target()
    privmsg_no_message()
    privmsg_empty_message()
    privmsg_to_channel()
    privmsg_to_user()
    privmsg_to_nobody()
    privmsg_to_invalid_channel()
    privmsg_to_multiple_channel()