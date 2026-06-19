from helper import *    

def list_no_param():
    alice = Client(nick, passwd)
    alice.send("LIST")
    r = alice.recv()
    ok("list_no_param", r, "323")
    alice.close()

def list_no_such_channel():
    alice = Client(nick, passwd)
    alice.send("LIST #nochan")
    r = alice.recv()
    ok("list_no_such_channel", r, "323")
    alice.close()

def list_with_channel():
    channel = "#test"
    alice = Client(nick, passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send("LIST")
    r = alice.recv()
    ok_all("list_with_channel", r, ["322", f"{channel}", "323"])
    alice.close()

def list_with_topic():
    channel = "#test"
    topic = "hello world"
    alice = Client(nick, passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"TOPIC {channel} :{topic}")
    alice.recv()
    alice.send(f"LIST {channel}")
    r = alice.recv()
    ok_all("list_with_topic", r, ["322", "323", f"{channel}", f"{topic}"])
    alice.close()

def list_multiple_channel():
    chan1 = "#test1"
    chan2 = "#test2"
    chan3 = "#test3"
    alice = Client(nick, passwd)
    alice.send(f"JOIN {chan1},{chan2},{chan3}")
    alice.recv()
    alice.send(f"LIST {chan1},{chan3}")
    r = alice.recv()
    ok_all("list_multiple_channel", r, [f"{chan1}", f"{chan3}", "323"])
    alice.close()





def run():
    section("LIST")
    list_no_param()
    list_no_such_channel()
    list_with_channel()
    list_with_topic()
    list_multiple_channel()