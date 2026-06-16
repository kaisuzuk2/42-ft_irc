from helper import *

def connection():
    alice = Client(nick, passwd)
    ok("connection -> 001", alice.r, "001")
    alice.close()

def wrong_passwd():
    alice = Client(nick ,"wrongpass")
    ok("wrong_passwd -> 464", alice.r, "464")
    alice.close()

def invalid_toolong_nick():
    alice = Client("toolongnick", passwd)
    ok("invalid_toolong_nick -> 432", alice.r, "432")
    alice.close()

def invalid_special_nick():
    alice = Client("hello!", passwd)
    ok("invalid_special_nick -> 432", alice.r, "432")
    alice.close()

def special_nick():
    alice = Client("[]\\`_^{|", passwd)
    ok("special_nick -> 001", alice.r, "001")
    alice.close()

def nick_starts_with_number():
    alice = Client("1abc", passwd)
    ok("nick starts with number -> 432", alice.r, "432")
    alice.close()

def nick_number_in_second():
    alice = Client("a1bc", passwd)
    ok("nick number in second -> 001", alice.r, "001")
    alice.close()




def run():
    section("CONNECTION")
    connection()
    wrong_passwd()
    invalid_toolong_nick()
    invalid_special_nick()
    special_nick()
    nick_starts_with_number()
    nick_number_in_second()