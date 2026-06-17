from helper import *

def part_no_param():
    alice = Client(nick, passwd)
    alice.send("PART")
    r = alice.recv()
    ok("part_no_param", r, "461")
    alice.close()

def part_empty():
    alice = Client(nick, passwd)
    alice.send("PART :")
    r = alice.recv()
    ok("part_empty", r, "403")
    alice.close()

def part_no_such_channel():
    alice = Client(nick, passwd)
    alice.send("PART #nochan")
    r = alice.recv()
    ok("part_no_such_channel", r, "403")
    alice.close()

def part_not_on_channel():
    channel = "#test"
    bo = "bob"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    bob.send(f"JOIN {channel}")
    bob.recv()
    alice.send(f"PART {channel}")
    r = alice.recv()
    ok("part_not_on_channel", r, "442")
    alice.close()
    bob.close()

def part():
    channel = "#test"
    alice = Client(nick, passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"PART {channel}")
    r = alice.recv()
    ok_all("part", r, ["PART", f"{nick}"])
    alice.close()

def part_with_comment():
    channel = "#test"
    comment = "good bye!"
    alice = Client(nick, passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"PART {channel} :{comment}")
    r = alice.recv()
    ok_all("part_with_comment", r, ["PART", f"{comment}"])
    alice.close()

def part_multiple_channel():
    chan1 = "#test1"
    chan2 = "#test2"
    chan3 = "#test3"
    alice = Client(nick, passwd)
    alice.send(f"JOIN {chan1},{chan2},{chan3}")
    alice.recv()
    alice.send(f"PART {chan1},{chan2},{chan3}")
    r = alice.recv()
    ok_all("part_multiple_channel", r, [f"PART {chan1}", f"PART {chan2}", f"PART {chan3}"])
    alice.close()

def part_notify():
    channel = "#test"
    bo = "bob"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    bob.send(f"JOIN {channel}")
    bob.recv()
    alice.send(f"PART {channel}")
    r = bob.recv()
    ok("part_notify", r, "PART")
    alice.close()
    bob.close()

def run():
    section("PART")
    part_no_param()
    part_empty()
    part_no_such_channel()
    part_not_on_channel()
    part()
    part_with_comment()
    part_multiple_channel()
    part_notify()