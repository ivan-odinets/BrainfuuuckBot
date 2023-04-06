/*
 **********************************************************************************************************************
 *
 * This file is part of BrainfuuuckBot project
 *
 * Copyright (c) 2023 Ivan Odinets <i_odinets@protonmail.com>
 *
 * BrainfuuuckBot is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version
 * 3 of the License, or (at your option) any later version.
 *
 * BrainfuuuckBot is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with BrainfuuuckBot; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H

#include <QCommandLineParser>

#include "QtTelegramBot/src/types/user.h"

#include "ProxyHelper.h"

class CommandLineParser : public QCommandLineParser
{
    Q_DECLARE_TR_FUNCTIONS(CommandLineParser);
public:
    CommandLineParser();
    ~CommandLineParser() {}

    QString configFile() const                 { return value(m_configFileOption); }
    bool    preserveConfig() const             { return isSet(m_preserveConfig); }

    bool          validProxyConfigured() const { return ProxyHelper::isValidProxy(proxyString()); }
    QNetworkProxy proxy() const                { return ProxyHelper::proxyFromString(proxyString()); }
    QString       proxyString() const          { return value(m_networkProxy); }

    QString token() const                      { return value(m_botTokenOption); }

    Telegram::User::Id botAdmin() const        { return value(m_botAdminOption).toLongLong(); }

private:
    QCommandLineOption   m_configFileOption;
    QCommandLineOption   m_preserveConfig;
    QCommandLineOption   m_botTokenOption;
    QCommandLineOption   m_botAdminOption;
    QCommandLineOption   m_networkProxy;
};

#endif // COMMANDLINEPARSER_H
