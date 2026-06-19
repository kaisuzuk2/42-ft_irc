from helper import *

## i invitee
## t topic
## k key
## o operator
## l limit
                          


## i
def mode_no_param():
    alice = Client(nick, passwd)
    alice.send("MODE")
    r = alice.recv()
    ok("mode_no_param", r, "461")
    alice.close()

def mode_no_such_channel():
    alice = Client(nick, passwd)
    alice.send("MODE #nochan")
    r = alice.recv()
    ok("mode_no_such_channel", r, "403")
    alice.close()

def mode_unknown():
    channel = "#test"
    alice = Client(nick, passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"MODE {channel} +x")
    r = alice.recv()
    ok("mode_unknown", r, "472")
    alice.close()

def mode_not_on_channel():
    channel = "#test"
    bo = "bob"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    bob.send(f"JOIN {channel}")
    bob.recv()
    alice.send(f"MODE {channel} +i")
    r = alice.recv()
    ok("mode_not_on_channel", r, "482")
    alice.close()
    bob.close()

def mode_show():
    channel = "#test"
    alice = Client(nick, passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"MODE {channel}")
    r = alice.recv()
    ok("mode_show", r, "324")
    alice.close()

def mode_invite_only():
    channel = "#test"
    bo = "bob"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"MODE {channel} +i")
    alice.recv()
    bob.send(f"JOIN {channel}")
    r = bob.recv()
    ok("mode_invite_only", r, "473")
    alice.close()
    bob.close()

def mode_invite_only_with_invite():
    channel = "#test"
    bo = "bob"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"MODE {channel} +i")
    alice.recv()
    alice.send(f"INVITE {bo} {channel}")
    alice.recv()
    bob.recv()
    bob.send(f"JOIN {channel}")
    r = bob.recv()
    ok("mode_invite_only_with_invite", r, "JOIN")
    alice.close()
    bob.close()

def mode_invite_only_invite_nobody():
    channel = "#test"
    alice = Client(nick, passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"MODE {channel} +i")
    alice.recv()
    alice.send(f"INVITE nobody {channel}")
    r = alice.recv()
    ok("mode_invite_only_invite_nobody", r, "401")
    alice.close()

def mode_invite_only_invite_no_channel():
    bo = "bob"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    alice.send(f"INVITE {bo} #nochan")
    r = alice.recv()
    ok("mode_invite_only_invite_no_channel", r, "403")
    alice.close()
    bob.close()

def mode_invite_only_not_operator():
    channel = "#test"
    bo = "bob"
    ch = "charlie"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    charlie = Client(f"{ch}", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    bob.send(f"JOIN {channel}")
    bob.recv()
    alice.recv()
    alice.send(f"MODE {channel} +i")
    alice.recv()
    bob.recv()
    bob.send(f"INVITE {ch} {channel}")
    r = bob.recv()
    ok("mode_invite_only_not_operator", r, "482")
    alice.close()
    bob.close()
    charlie.close()

def mode_invite_only_unset():
    channel = "#test"
    bo = "bob"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"MODE {channel} +i")
    alice.recv()
    alice.send(f"MODE {channel} -i")
    alice.recv()
    bob.send(f"JOIN {channel}")
    r = bob.recv()
    ok("mode_invite_only_unset", r, "JOIN")
    alice.close()
    bob.close()

## t
def mode_topic():
    channel = "#test"
    bo = "bob"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"MODE {channel} +t")
    alice.recv()
    bob.send(f"JOIN {channel}")
    bob.recv()
    alice.recv()
    bob.send(f"TOPIC {channel} :hello")
    r = bob.recv()
    ok("mode_topic", r, "482")
    alice.close()
    bob.close()

def mode_topic_operator():
    channel = "#test"
    alice = Client(nick, passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"MODE {channel} +t")
    alice.recv()
    alice.send(f"TOPIC {channel} :hello")
    r = alice.recv()
    ok("mode_topic_operator", r, "TOPIC")
    alice.close()

def mode_topic_unset():
    channel = "#test"
    bo = "bob"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"MODE {channel} +t")
    alice.recv()
    alice.send(f"MODE {channel} -t")
    alice.recv()
    bob.send(f"JOIN {channel}")
    bob.recv()
    alice.recv()
    bob.send(f"TOPIC {channel} :hello")
    r = bob.recv()
    ok("mode_topic_unset", r, "TOPIC")
    alice.close()
    bob.close()

## k
def mode_key():
    channel = "#test"
    bo = "bob"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"MODE {channel} +k pass")
    alice.recv()
    bob.send(f"JOIN {channel}")
    r = bob.recv()
    ok("mode_key_set", r ,"475")
    alice.close()
    bob.close()

def mode_key_join_with_key():
    channel = "#test"
    bo = "bob"
    key = "pass"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"MODE {channel} +k {key}")
    alice.recv()
    bob.send(f"JOIN {channel} {key}")
    r = bob.recv()
    ok("mode_key_join_with_key", r, "JOIN")
    alice.close()
    bob.close()

def mode_key_unset():
    channel = "#test"
    bo = "bob"
    key = "pass"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"MODE {channel} +k {key}")
    alice.recv()
    alice.send(f"MODE {channel} -k {key}")
    alice.recv()
    bob.send(f"JOIN {channel}")
    r = bob.recv()
    ok("mode_key_unset", r, "JOIN")
    alice.close()
    bob.close()

def mode_key_wrong_key_unset():
    channel = "#test"
    alice = Client(nick, passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"MODE {channel} +k pass")
    alice.recv()
    alice.send(f"MODE {channel} -k wrongpass")
    r = alice.recv()
    ok("mode_key_wrong_key_unset", r, "467")
    alice.close()

## o
def mode_operator():
    channel = "#test"
    bo = "bob"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    bob.send(f"JOIN {channel}")
    bob.recv()
    alice.recv()
    alice.send(f"MODE {channel} +o {bo}")
    alice.recv()
    bob.recv()
    alice.send(f"NAMES {channel}")
    r = alice.recv()
    ok_all("mode_operator", r, [f"@{nick}", f"@{bo}"])
    alice.close()
    bob.close()

def mode_operator_unset():
    channel = "#test"
    bo = "bob"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    bob.send(f"JOIN {channel}")
    bob.recv()
    alice.recv()
    alice.send(f"MODE {channel} +o {bo}")
    alice.recv()
    bob.recv()
    alice.send(f"MODE {channel} -o {bo}")
    alice.recv()
    bob.recv()
    bob.send(f"MODE {channel} +t")
    r = bob.recv()
    ok("mode_operator_unset", r, "482")
    alice.close()
    bob.close()

def mode_operator_can_kick():
    channel = "#test"
    bo = "bob"
    ch = "charlie"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    charlie = Client(f"{ch}", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    bob.send(f"JOIN {channel}")
    bob.recv()
    alice.recv()
    charlie.send(f"JOIN {channel}")
    charlie.recv()
    bob.recv()
    alice.recv()
    alice.send(f"MODE {channel} +o {bo}")
    alice.recv()
    bob.recv()
    charlie.recv()
    bob.send(f"KICK {channel} {ch}")
    r = charlie.recv()
    ok("mode_operator_can_kick", r, "KICK")
    alice.close()
    bob.close()
    charlie.close()

def mode_operator_unset_cannot_kick():
    channel = "#test"
    bo = "bob"
    ch = "charlie"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    charlie = Client(f"{ch}", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    bob.send(f"JOIN {channel}")
    bob.recv()
    alice.recv()
    charlie.send(f"JOIN {channel}")
    charlie.recv()
    alice.recv()
    bob.recv()
    alice.send(f"MODE {channel} +o {bo}")
    alice.recv()
    bob.recv()
    charlie.recv()
    alice.send(f"MODE {channel} -o {bo}")
    alice.recv()
    bob.recv()
    charlie.recv()
    bob.send(f"KICK {channel} {ch}")
    r = bob.recv()
    ok("mode_operator_unset_cannot_kick", r, "482")
    alice.close()
    bob.close()
    charlie.close()

def mode_operator_no_such_user():
    channel = "#test"
    alice = Client(nick, passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"MODE {channel} +o nobody")
    r = alice.recv()
    ok("mode_operator_no_such_user", r, "401")
    alice.close()

def mode_operator_not_on_channel():
    channel = "#test"
    bo = "bob"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"MODE {channel} +o {bo}")
    r = alice.recv()
    ok("mode_operator_not_on_channel", r, "441")
    alice.close()
    bob.close()

## l
def mode_limit():
    channel = "#test"
    bo = "bob"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"MODE {channel} +l 1")
    alice.recv()
    bob.send(f"JOIN {channel}")
    r = bob.recv()
    ok("mode_limit", r, "471")
    alice.close()
    bob.close()

def mode_limit_unset():
    channel = "#test"
    bo = "bob"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"MODE {channel} +l 1")
    alice.recv()
    alice.send(f"MODE {channel} -l")
    alice.recv()
    bob.send(f"JOIN {channel}")
    r = bob.recv()
    ok("mode_limit_unset", r, "JOIN")
    alice.close()
    bob.close()

def mode_limit_change():
    channel = "#test"
    bo = "bob"
    alice = Client(nick, passwd)
    bob = Client(f"{bo}", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    alice.send(f"MODE {channel} +l 1")
    alice.recv()
    bob.send(f"JOIN {channel}")
    bob.recv()
    alice.send(f"MODE {channel} +l 2")
    alice.recv()
    bob.send(f"JOIN {channel}")
    r = bob.recv()
    ok("mode_limit_change", r, "JOIN")
    alice.close()
    bob.close()





def run():
    section("MODE")
    mode_no_param()
    mode_no_such_channel()
    mode_unknown()
    mode_not_on_channel()
    mode_show()
    mode_invite_only()
    mode_invite_only_with_invite()
    mode_invite_only_invite_nobody()
    mode_invite_only_invite_no_channel()
    mode_invite_only_not_operator()
    mode_invite_only_unset()
    mode_topic()
    mode_topic_operator()
    mode_topic_unset()
    mode_key()
    mode_key_join_with_key()
    mode_key_unset()
    mode_key_wrong_key_unset()
    mode_operator()
    mode_operator_unset()
    mode_operator_can_kick()
    mode_operator_unset_cannot_kick()
    mode_operator_no_such_user()
    mode_operator_not_on_channel()
    mode_limit()
    mode_limit_unset()
    mode_limit_change()