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

#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QSettings>
#include <QNetworkProxy>

#include "CommandLineParser.h"

class AppConfig
{
public:
    AppConfig(const QString& settingsFile);
    ~AppConfig();

    void setPreserveConfig(bool state)           { m_preserveConfig = state; }

    void updateConfigFile(const CommandLineParser& parser);

    QSettings::Status   status() const;

    QString             token() const            { return m_botToken; }
    void                setToken(const QString& newToken);

    Telegram::User::Id  botAdmin() const         { return m_botAdmin; }
    void                setBotAdmin(Telegram::User::Id newAdminId);

    bool                validProxyConfigured() const;
    void                setProxy(const QNetworkProxy& proxy);
    QNetworkProxy       proxy() const            { return m_proxy; }

private:
    Q_DISABLE_COPY(AppConfig);
    QSettings*     p_settings;
    void           _loadValues();

    bool                m_preserveConfig;
    QString             m_botToken;
    Telegram::User::Id  m_botAdmin;
    QNetworkProxy       m_proxy;
};

#endif // APPCONFIG_H
