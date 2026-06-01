/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMode.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-31 23:30:24 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-31 23:30:24 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/CmdMode.hpp"

/*
RFC 1495
パラメータ: <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>]
            [<ban mask>]

RFC 2812
パラメーター: <channel> *( ( "-" / "+" ) *<modes> *<modeparams> )

[Note]
パラメーターを取るモードについては、1コマンドあたり最大3つまでという変更数の上限があることに注意してください。

[Mode] RFC 2811 4
    O - 「チャンネルクリエーター」ステータスを付与する
o - チャンネルオペレーター権限を付与・剥奪する
    v - 発言権限を付与・剥奪する

    a - 匿名チャンネルフラグを切り替える
i - 招待制チャンネルフラグを切り替える
    m - モデレートチャンネルを切り替える
n - チャンネル外のクライアントからチャンネルへのメッセージ禁止を切り替える
    q - クワイエットチャンネルフラグを切り替える
    p - プライベートチャンネルフラグを切り替える
    s - シークレットチャンネルフラグを切り替える
    r - サーバーreop チャンネルフラグを切り替える
t - チャンネルオペレーターのみトピック設定可能フラグを切り替える

k - チャンネルキー（パスワード）を設定・削除する
l - チャンネルへのユーザー数制限を設定・削除する

    b - ユーザーを締め出すためのBANマスクを設定・削除する
    e - BANマスクを上書きする例外マスクを設定・削除する
    I - 招待制フラグを自動的に上書きする招待マスクを設定・削除する
*/

CmdMode::CmdMode()
    : ACommand("MODE", 1, 0, false)
{}

CmdMode::~CmdMode() {}

bool CmdMode::_applyKeyMode(Channel *ch, bool ading, size_t &paramIdx, const std::vector<std::string> &params, std::string &outParam)
{
    
}

bool CmdMode::_applyFlagMode(Channel *ch, char c, bool adding)
{
    unsigned int mode;
    switch(c)
    {
        case 'i':
            mode = MODE_INVITE_ONLY;
            break;
        case 'n':
            mode = MODE_NO_EXTERNAL;
            break;
        case 't':
            mode = MODE_TOPIC_OP;
            break;
        default:
            return (false);
    }
    if (ch->_isModeSet(mode) == adding)
        return (false);
    adding ? ch->_setMode(mode) : ch->_unsetMode(mode);
    return (true);
}

bool CmdMode::_applyMode(FtIRCd &serverInstance, Client &client, Channel *ch, char c, bool adding, size_t &paramIdx, const std::vector<std::string> &params, std::string &outParam)
{
    switch(c)
    {
        case 'i':
        case 'n':
        case 't':
            return (_applyFlagMode(ch, c, adding));
        case 'k':
            return (_applyKeyMode(ch, adding, paramIdx, params, outParam));
    }
}

// ### TODO: ユーザーのmodeに対応すべきか　特別なエラー処理すべきか　とりあえずチャンネル専用にする
void CmdMode::_execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params)
{
    const std::string &cname = params[0];
    Channel *ch;

    ch = serverInstance._getChannels()._find(cname);
    if (!ch)
    {
        client._writeNumeric(ERR_NOSUCHCHANNEL, serverInstance._getServername(), cname + " :No such channel");
        return ;
    }

    if (params.size() == 1)
    {
        ch->_displayModes(client, serverInstance._getServername());
        return ;
    }

    // ### TODO: メンバーじゃないか
    // ### TODO: オペレータかどうか

    const std::string &modeStr = params[1];
    bool adding;
    size_t paramIdx;
    char lastSign;
    std::string appliedStr;
    std::string appliedParams;

    adding = true;
    paramIdx = 2;
    lastSign = '\0';

    for (size_t i = 0; i < modeStr.size(); ++i)
    {
        char c = modeStr[i];
        if (c == '+')
        {
            adding = true;
            continue ;
        }
        if (c == '-')
        {
            adding = false;
            continue ;
        }

        std::string outParam;
        if (_applyMode(serverInstance, client, ch, c, adding, paramIdx, params, outParam)) // ### TODO: 引数が多い　なんとかならないか
            _appendMode(c, adding, outParam, appliedStr, appliedParams, lastSign); // ### TODO: 引数が多い　なんとかならないか
    }



}