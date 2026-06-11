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

#include <climits>
#include <sstream>

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

bool CmdMode::_applyKeyMode(const std::string &servername, Client &client, Channel *ch, bool adding, size_t &paramIdx, const std::vector<std::string> &params, std::string &outParam)
{
    if (paramIdx >= params.size()) 
    {
        client._writeNumeric(ERR_INVALIDMODEPARAM, servername, ch->_getName() + " k * :You must specify a parameter for the key mode. Syntax: <key>.");
        return (false);
    }
    if (adding)
    {
        if (!ch->_isModeSet(MODE_KEY))  
        {
            outParam = params[paramIdx];
            ch->_setMode(MODE_KEY);
            ch->_setKey(outParam);
            ++paramIdx;
            return (true);
        }
        paramIdx++;
        return (false);
    }
    else
    {
        if (!ch->_isModeSet(MODE_KEY))
            return (false);
        if (params[paramIdx] != ch->_getKey())
        {
            client._writeNumeric(ERR_KEYSET, servername, ch->_getName() + " :Channel key already set");
            ++paramIdx;
            return (false);
        }
        ch->_setKey("");
        ch->_unsetMode(MODE_KEY);
        ++paramIdx;
        return (true);
    }
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

bool CmdMode::_applyLimitMode(const std::string &servername, Client &client, Channel *ch, bool adding, size_t &paramIdx, const std::vector<std::string> &params, std::string &outParam)
{
    char *endptr;
    long limit;
    std::string limitValStr;

    if (adding)
    {
        if (paramIdx >= params.size())
        {
            client._writeNumeric(ERR_INVALIDMODEPARAM, servername, ch->_getName() + " l * :You must specify a parameter for the limit mode. Syntax: <limit>.");
            return (false);
        }

        errno = 0;
        endptr = NULL;
        limitValStr = params[paramIdx];
        limit = std::strtol(limitValStr.c_str(), &endptr, 10);
        if (limitValStr.c_str() == endptr || limit <= 0 || errno == ERANGE || limit > UINT_MAX)
        {
            client._writeNumeric(ERR_INVALIDMODEPARAM, servername,  ch->_getName() + " l " + limitValStr + " :Invalid limit mode parameter. Syntax: <limit>.");
            ++paramIdx;
            return (false);
        }
        if (ch->_isModeSet(MODE_LIMIT) && ch->_getLimit() == static_cast<unsigned int>(limit))
        {
            ++paramIdx;
            return (false);
        }

        std::ostringstream oss;
        oss << limit;
        outParam = oss.str();
        ++paramIdx;
        ch->_setLimit(static_cast<unsigned int>(limit));
        ch->_setMode(MODE_LIMIT);
        return (true);
    }
    else
    {
        if (!ch->_isModeSet(MODE_LIMIT))
            return (false);
        ch->_setLimit(0);
        ch->_unsetMode(MODE_LIMIT);
        return (true);
    }
}

bool CmdMode::_applyOperMode(FtIRCd &serverInstance, Client &client, Channel *ch, bool adding, size_t &paramIdx, const std::vector<std::string> &params, std::string &outParam)
{
    Client *target;

    if (paramIdx >= params.size())
    {
        client._writeNumeric(ERR_INVALIDMODEPARAM, serverInstance._getServername(), ch->_getName() + " o * :You must specify a parameter for the op mode. Syntax: <nick>.");
        return (false);
    }

    const std::string &nick = params[paramIdx];
    target = serverInstance._getClients()._findByNick(nick, false);
    if (!target)
    {
        client._writeNumeric(ERR_NOSUCHNICK, serverInstance._getServername(), nick + " :No such nick");
        ++paramIdx;
        return (false);
    }
    if (!ch->_hasMember(target))
    {
        client._writeNumeric(ERR_USERNOTINCHANNEL, serverInstance._getServername(), nick + " " + ch->_getName() + " :They are not on that channel");
        ++paramIdx;
        return (false);
    }

    if (ch->_isOper(target) == adding)
    {
        ++paramIdx;
        return (false);
    }

    outParam = nick;
    ++paramIdx;
    ch->_setOper(target, adding);
    return (true);
}

bool CmdMode::_applyMode(FtIRCd &serverInstance, Client &client, Channel *ch, char c, bool adding, size_t &paramIdx, const std::vector<std::string> &params, std::string &outParam)
{
    switch(c)
    {
        case 'i':
        case 'n':
        case 't':
            return (this->_applyFlagMode(ch, c, adding));
        case 'k':
            return (this->_applyKeyMode(serverInstance._getServername(), client, ch, adding, paramIdx, params, outParam));
        case 'l':
            return (this->_applyLimitMode(serverInstance._getServername(), client, ch, adding, paramIdx, params, outParam));
        case 'o':
            return (this->_applyOperMode(serverInstance, client, ch, adding, paramIdx, params, outParam));
        default:
            client._writeNumeric(ERR_UNKNOWNMODE, serverInstance._getServername(), std::string(1, c) + " :is unknown mode char to me for " + ch->_getName());
            return (false);
    }
}

void CmdMode::_appendMode(char c, bool adding, const std::string &outParam, std::string &appliedStr, std::string &appliedParams, char &lastSign)
{
    char sign;

    sign = adding ? '+' : '-';
    if (sign != lastSign)
    {
        appliedStr += sign;
        lastSign = sign;
    }
    appliedStr += c;
    if (!outParam.empty())
        appliedParams += " " + outParam;
}

void CmdMode::_execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params)
{
    const std::string &cname = params[0];
    Channel *ch;

    ch = serverInstance._getChannels()._find(cname);
    if (!ch)
    {
        // client._writeNumeric(ERR_NOSUCHCHANNEL, serverInstance._getServername(), cname + " :No such channel");
        client._writeNumeric(Numerics::NoSuchChannel(cname), serverInstance._getServername());
        return ;
    }

    if (params.size() == 1)
    {
        ch->_displayModes(client, serverInstance._getServername());
        return ;
    }

    if (!ch->_hasMember(&client))
    {
        client._writeNumeric(ERR_NOTONCHANNEL, serverInstance._getServername(), cname + " :You're not on that channel");
        return;
    }

    if (!ch->_isOper(&client))
    {
        client._writeNumeric(ERR_CHANOPRIVSNEEDED, serverInstance._getServername(), cname + " :You're not channel operator");
        return;
    }

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
    if (!appliedStr.empty())
        ch->_broadcast(":" + client._getPrefix() + " MODE " + ch->_getName() + " " + appliedStr + appliedParams, NULL, false);
}