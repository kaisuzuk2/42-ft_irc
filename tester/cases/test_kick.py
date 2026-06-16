from helper import *

### TODO: ERR_USERNOTINCHANNEL            ERR_NOTONCHANNEL

def kick_no_param():
    alice = Client(nick, passwd)
    alice.send("KICK")
    r = alice.recv()
    ok("kick_no_param", r, "461")
    alice.close()

def kick_no_user():
    channel = "#test1"
    alice = Client(nick, passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"KICK {channel}")
    r = alice.recv()
    ok("kick_no_user", r, "461")
    alice.close()

def kick_empty_user():
    channel = "test1"
    alice = Client(nick, passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"KICK {channel} :")
    r = alice.recv()
    ok("kick_empty_user", r, "401")
    alice.close()

def kick_no_such_channel():
    alice = Client(nick, passwd)
    alice.send("KICK #nochan bob")
    r = alice.recv()
    ok("kick_no_such_channel", r, "403")
    alice.close()

def kick_no_such_user():
    channel = "#test"
    alice = Client(nick, passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"KICK {channel} nobody")
    r = alice.recv()
    ok("kick_no_such_user", r, "401")
    alice.close()

def kick():
    channel = "#test"
    alice = Client(nick, passwd)
    bob = Client("bob", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    bob.send(f"JOIN {channel}")
    bob.recv()
    alice.send(f"KICK {channel} bob")
    r = bob.recv()
    ok_all("kick", r, ["KICK", f"{nick}"])
    alice.close()
    bob.close()

def kick_with_comment():
    channel = "#test"
    alice = Client(nick, passwd)
    bob = Client("bob", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    bob.send(f"JOIN {channel}")
    bob.recv()
    alice.send(f"KICK {channel} bob :see you!")
    r = bob.recv()
    ok_all("kick_with_comment", r, ["KICK", "see you!"])
    alice.close()
    bob.close()

def kick_not_operator():
    channel = "#test"
    alice = Client(nick, passwd)
    bob = Client("bob", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    bob.send(f"JOIN {channel}")
    bob.recv()
    bob.send(f"KICK {channel} {nick}")
    r = bob.recv()
    ok("kick_not_operator", r, "482")
    alice.close()
    bob.close()

def kick_multiple_users():
    channel = "#test"
    alice = Client(nick, passwd)
    bob = Client("bob", passwd)
    charlie = Client("charlie", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    bob.send(f"JOIN {channel}")
    bob.recv()
    charlie.send(f"JOIN {channel}")
    charlie.recv()
    alice.send(f"KICK {channel} bob,charlie")
    r_bob = bob.recv()
    r_charlie = charlie.recv()
    ok("kick_multiple_users(bob)", r_bob, "KICK")
    ok("kick_multiple_users(charlie)", r_charlie, "KICK")
    alice.close()
    bob.close()
    charlie.close()

def kick_multiple_channels_users():
    channel1 = "#test1"
    channel2 = "#test2"
    bo = "bob"
    ch = "charlie"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    charlie = Client(f"{ch}", passwd)
    alice.send(f"JOIN {channel1},{channel2}")
    alice.recv()
    bob.send(f"JOIN {channel1}")
    bob.recv()
    charlie.send(f"JOIN {channel2}")
    charlie.recv()
    alice.send(f"KICK {channel1},{channel2} {bo},{ch}")
    r_bob = bob.recv()
    r_ch = charlie.recv()
    ok(f"kick_multiple_channels_users({bo})", r_bob, "KICK")
    ok(f"kick_multiple_channels_users({ch})", r_ch, "KICK")
    alice.close()
    bob.close()
    charlie.close()

def kick_mismatch_channels_users():
    channel1 = "#test1"
    channel2 = "#test2"
    bo = "bob"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    alice.send(f"JOIN {channel1},{channel2}")
    alice.recv()
    bob.send(f"JOIN {channel1}")
    bob.recv()
    alice.recv()
    alice.send(f"KICK {channel1},{channel2} {bo}")
    r = alice.recv()
    ok("kick_mismatch_channels_users", r, "461")
    alice.close()
    bob.close()



def run():
    section("KICK")
    kick_no_param()
    kick_no_user()
    kick_empty_user()
    kick_no_such_channel()
    kick_no_such_user()
    kick()
    kick_with_comment()
    kick_not_operator()
    kick_multiple_users()
    kick_multiple_channels_users()
    kick_mismatch_channels_users()