*This project has been created as part of the 42 curriculum by kaisuzuk, ketomita.*

# Description
ft_ircは、C++98で実装したIRCサーバーです。

このプロジェクトの目的は、IRCプロトコルの仕様を読み解きながら、ソケット通信・I/O多重化・ネットワークプログラミングの理解を深めることです。
標準的なIRCクライアントで実際に接続・動作確認ができます。
本プロジェクトでは、ncコマンドで動作確認を行いました。

## IRCとは

## I/O多重化

## アーキテクチャ

## 対応コマンド

|カテゴリ|コマンド|
|----------|----------|
|接続|`PASS` `NICK` `USER` `QUIT`|
|チャンネル|`JOIN` `PART` `KICK` `INVITE` `TOPIC` `LIST` `NAMES`|
|メッセージ|`PRIVMSG` `NOTICE`|
|モード|`MODE` (`+i`, `+t`, `+k`, `+l`, `+n`, `+o`)|
|サーバー|`MOTD`|

# Instructions

## インストール
```bash
git clone <project>
```

## コンパイル
``` bash
make            # ビルド
make clean      # オブジェクトファイルの削除
make fclean     # バイナリも含めて削除
make re         # 再ビルド
```

## 実行
```bash
./ircserv <port> <password>
```
|引数|説明|
|-----|-----|
|port|待ち受けるポート番号(1024 - 65535)|
|password|クライアントが接続時に使用するパスワード|

## 接続
```bash
nc -C localhost <password>
```

# Resources

## Books
- [TCP/IPソケットプログラミング　C言語編](https://www.ohmsha.co.jp/book/9784274065194/)
- [UNIXネットワークプログラミング Vol.1](https://www.amazon.co.jp/UNIX%E3%83%8D%E3%83%83%E3%83%88%E3%83%AF%E3%83%BC%E3%82%AF%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%9F%E3%83%B3%E3%82%B0%E3%80%88Vol-1%E3%80%89%E3%83%8D%E3%83%83%E3%83%88%E3%83%AF%E3%83%BC%E3%82%AFAPI-%E3%82%BD%E3%82%B1%E3%83%83%E3%83%88%E3%81%A8XTI-W-%E3%83%AA%E3%83%81%E3%83%A3%E3%83%BC%E3%83%89-%E3%82%B9%E3%83%86%E3%82%A3%E3%83%BC%E3%83%B4%E3%83%B3%E3%82%B9/dp/4894712059)
- [Linuxプログラミングインタフェース](https://www.oreilly.co.jp/books/9784873115856/)

## RFC
- [RFC 1459](https://datatracker.ietf.org/doc/html/rfc1459)
- [RFC 2811](https://datatracker.ietf.org/doc/html/rfc2811)
- [RFC 2812](https://datatracker.ietf.org/doc/html/rfc2812)

## IRC
- [inspircd](https://www.inspircd.org/)

## AI
- RFCの翻訳
- inspircdのソースコード読解サポート
- クラス設計のサポート
- epoll・poll・selectなどI/O多重化とノンブロッキングに関する概念理解のための壁打ち
- テスト項目の洗い出しとpythonの文法チェック
- READMEの翻訳

# IRC Usage

## コマンドリファレンス

## 使用例

# Tester