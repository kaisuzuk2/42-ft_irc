from helper import *

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

def join_with_topic():
    channel = "#test"
    bo = "bob"
    topic = "hello world"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"TOPIC {channel} :{topic}")
    alice.recv()
    bob.send(f"JOIN {channel}")
    r = bob.recv()
    ok_all("join_with_topic", r, ["332", f"{topic}"])
    alice.close()
    bob.close()

def join_with_names():
    channel = "#test"
    bo = "bob"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    bob.send(f"JOIN {channel}")
    r = bob.recv()
    ok_all("join_with_names", r, ["353", f"{bo}"])
    alice.close()
    bob.close()

def join_channel_too_long():
    channel = "#" + "a" * 50
    alice = Client(nick, passwd)
    alice.send(f"JOIN {channel}")
    r = alice.recv()
    ok("join_channel_too_long", r, "476")
    alice.close()

def join_channel_max_length():
    channel = "#" + "a" * 49
    alice = Client(nick, passwd)
    alice.send(f"JOIN {channel}")
    r = alice.recv()
    ok("join_channel_max_length", r, "JOIN")
    alice.close()

def join_channel_case_insensitive():
    bo = "bob"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    alice.send("JOIN #TEST")
    alice.recv()
    bob.send("JOIN #test")
    r = alice.recv()
    ok_all("join_channel_case_insensitive", r, [f"{bo}", "JOIN"])
    alice.close()
    bob.close()

def join_channel_invalid_char():
    alice = Client(nick, passwd)
    alice.send(f"JOIN :#te::::st")
    r = alice.recv()
    ok("join_channel_invalid_char", r, "476")
    alice.close()







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
    join_with_topic()
    join_with_names()
    join_channel_too_long()
    join_channel_max_length()  
    join_channel_case_insensitive()
    join_channel_invalid_char()