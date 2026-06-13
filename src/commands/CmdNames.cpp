/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdNames.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-06-13 00:55:29 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-06-13 00:55:29 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/CmdNames.hpp"

/*
RFC 1459
パラメータ:  [<channel>{,<channel>}]

RFC 2812
パラメーター: [ <channel> *( "," <channel> ) [ <target> ] ]

[Note]
NAMESコマンドを使用することで、ユーザーは自分に見えるすべてのニックネームを一覧表示できます。
何が見えて何が見えないかの詳細については、「Internet Relay Chat: Channel Management」[IRC-CHAN] を参照してください。
<channel> パラメーターは情報を返すチャンネルを指定します。無効なチャンネル名に対するエラー返信はありません。
<channel> パラメーターが指定されない場合、すべてのチャンネルとその参加者の一覧が返されます。(inspircdでは、サーバーの負荷が高い処理になるため、処理しない)
このリストの末尾に、いずれのチャンネルにも参加していないか、
可視チャンネルにいない可視ユーザーの一覧が「*」チャンネルにいるものとして表示されます。
<target> パラメーターが指定された場合、リクエストはそのサーバーに転送され、そのサーバーが返信を生成します。
<target> パラメーターにはワイルドカードが使用できます。
*/

CmdNames::CmdNames() 
    : ACommand("NAMES", 0, 0, false)
{}

CmdNames::~CmdNames() {}

void CmdNames::_execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params)
{
    if (params.empty())
    {
        
    }   
    

}