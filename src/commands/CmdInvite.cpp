/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdInvite.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-30 22:22:37 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-30 22:22:37 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/CmdInvite.hpp"

/*
RFC 1459
パラメータ:  <nickname> <channel>

RFC 2182
パラメーター: <nickname> <channel>

[Note]
パラメーター <nickname> は、対象チャンネル <channel> に招待される人物のニックネームです。
招待先のチャンネルが存在するか有効なチャンネルである必要はありません。
ただし、チャンネルが存在する場合、そのチャンネルのメンバーのみが他のユーザーを招待できます。
チャンネルに招待制フラグが設定されている場合、チャンネルオペレーターのみがINVITEコマンドを実行できます。
*/

CmdInvite::CmdInvite() 
    : ACommand("INVITE", 0, 0, false)
{}

CmdInvite::~CmdInvite() {}

void CmdInvite::_execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params)
{
    // invite
    // invite nicksample
    // パラメータが一つの場合無視する
    if (params.size() < 2)
    {
        // ### TODO: 招待されているリスト一覧を表示する
        client._writeNumeric()
    }
}