from helper import *

### TODO: iモードの時のテスト
def invite_no_such_user():
    channel = "#test"
    alice = Client(nick, passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"INVITE nobody {channel}")
    r = alice.recv()
    ok("invite_no_such_user", r, "401")
    alice.close()

def invite_not_on_channel():
    channel = "#test"
    bo = "bob"
    ch = "charlie"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    charlie = Client(f"{ch}", passwd)
    bob.send(f"JOIN {channel}")
    bob.recv()
    alice.send(f"INVITE {ch} {channel}")
    r = alice.recv()
    ok_all("invite_not_on_channel", r, ["442", "You're not on that channel"])
    alice.close()
    bob.close()
    charlie.close()

def invite_user_on_channel():
    channel = "#test"
    bo = "bob"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    bob.send(f"JOIN {channel}")
    alice.recv()
    bob.recv()
    alice.send(f"INVITE {bo} {channel}")
    r = alice.recv()
    ok_all("invite_user_on_channel", r, ["443", f"{bo}", f"{channel}", "is already on channel"])
    alice.close()
    bob.close()

def invite_notify_me():
    channel = "#test"
    bo = "bob"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"INVITE {bo} {channel}")
    r = alice.recv()
    ok_all("invite_notify_me", r, ["341", f"{channel}", f"{bo}"])
    alice.close()
    bob.close()

def invite_notify():
    channel = "#test"
    bo = "bob"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"INVITE {bo} {channel}")
    r = bob.recv()
    ok_all("invite_notify", r, ["INVITE", f"{bo}", f"{channel}"])
    alice.close()
    bob.close()


def run():
    section("INVITE")
    invite_no_such_user()
    invite_not_on_channel()
    invite_user_on_channel()
    invite_notify_me()
    invite_notify()
