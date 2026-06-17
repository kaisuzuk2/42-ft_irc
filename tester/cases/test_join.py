from helper import *

### TODO: key
### TODO: チャンネルの文字数
### TODO: チャンネルの大文字小文字
### TODO: チャンネル名に使える文字
def join_no_param():
    alice = Client(nick, passwd)
    alice.send("JOIN")
    r = alice.recv()
    ok("join_no_param", r, "461")
    alice.close()

def join_channel():
    alice = Client(nick, passwd)
    alice.send("JOIN #test")
    r = alice.recv()
    ok_all("join_channel", r, ["JOIN", "353", "366"])
    alice.close()

def join_invalid_channel():
    alice = Client(nick, passwd)
    alice.send("JOIN badchannel")
    r = alice.recv()
    ok("join_invalid_channel", r, "476")
    alice.close()

def join_invalid_channel_space():
    alice = Client(nick, passwd)
    alice.send("JOIN :#hello world")
    r = alice.recv()
    ok("join_invalid_channel_space", r, "476")
    alice.close()

def join_multiple_channel():
    alice = Client(nick, passwd)
    alice.send("JOIN #test1,#test2,#test3")
    r = alice.recv()
    ok_all("join_multiple_channel", r, ["JOIN :#test1", "JOIN :#test2", "JOIN :#test3"])
    alice.close()

def join_multiple_channel_one_invalid():
    alice = Client(nick, passwd)
    alice.send("JOIN #test1,badchannel,#test3")
    r = alice.recv()
    ok_all("join_multiple_channel_one_invalid", r, ["JOIN :#test1", "JOIN :#test3", "476"])
    alice.close()

def join_over_limit():
    alice = Client(nick, passwd)
    alice.send("JOIN #1,#2,#3,#4,#5,#6,#7,#8,#9,#10,#11")
    r = alice.recv()
    ok("join_over_limit", r, "405")
    alice.close()

def join_zero():
    alice = Client(nick, passwd)
    alice.send("JOIN #test1,#test2")
    alice.recv()
    alice.send("JOIN 0")
    r = alice.recv()
    ok_all("join_zero", r, ["PART #test1", "PART #test2"])
    alice.close()

def join_notify():
    channel = "#test1"
    alice = Client(nick, passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    bob = Client("bob", passwd)
    bob.send(f"JOIN {channel}")
    r = alice.recv()
    ok_all("join_notify", r, ["bob", f"JOIN :{channel}"])
    alice.close()
    bob.close()




def run():
    section("JOIN")
    join_channel()
    join_invalid_channel()
    join_invalid_channel_space()
    join_multiple_channel()
    join_multiple_channel_one_invalid()
    join_over_limit()
    join_zero()
    join_notify()