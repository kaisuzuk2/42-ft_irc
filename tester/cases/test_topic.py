from helper import *

### TODO: tモード ERR_NOTONCHANNEL 
def topic_no_param():
    alice = Client(nick, passwd)
    alice.send("TOPIC")
    r = alice.recv()
    ok("topic_no_param", r, "461")
    alice.close()

def topic_no_channel():
    alice = Client(nick, passwd)
    alice.send("TOPIC #nochan")
    r = alice.recv()
    ok("topic_no_channel", r, "403")
    alice.close()

def topic_empty_channel():
    alice = Client(nick, passwd)
    alice.send("TOPIC :")
    r = alice.recv()
    ok("topic_empty_channel", r, "403")
    alice.close()

def topic_not_set():
    channel = "#test"
    alice = Client(nick, passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"TOPIC {channel}")
    r = alice.recv()
    ok_all("topic_not_set", r, ["331", "No topic is set"])
    alice.close()

def topic_set():
    channel = "#test"
    alice = Client(nick, passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"TOPIC {channel} :hello world")
    r = alice.recv()
    ok_all("topic_set", r, ["TOPIC", "hello world"])
    alice.close()

def topic_get():
    channel = "#test"
    topic = "hello world"
    alice = Client(nick, passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"TOPIC {channel} :{topic}")
    alice.recv()
    alice.send(f"TOPIC {channel}")
    r = alice.recv()
    ok_all("topic_get", r, ["332", f"{topic}"])
    alice.close()

def topic_clear():
    channel = "#test"
    alice = Client(nick, passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"TOPIC {channel} : hello world")
    alice.recv()
    alice.send(f"TOPIC {channel} :")
    alice.recv()
    alice.send(f"TOPIC {channel}")
    r = alice.recv()
    ok_all("topic_clear", r, ["331", "No topic is set"])
    alice.close()

def topic_notify():
    channel = "#test"
    topic = "hello world"
    alice = Client(nick, passwd)
    bob = Client("bob", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    bob.send(f"JOIN {channel}")
    bob.recv()
    alice.send(f"TOPIC {channel} :{topic}")
    r = bob.recv()
    ok_all("topic_notify", r, ["TOPIC", f"{topic}"])




def run():
    section("TOPIC")
    topic_no_param()
    topic_no_channel()
    topic_empty_channel()
    topic_not_set()
    topic_set()
    topic_get()
    topic_clear()
    topic_notify()
