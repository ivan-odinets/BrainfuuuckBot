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

#include "AppConfig.h"

#include <QDebug>
#include <QSettings>

#include "ProxyHelper.h"

static const QString BOT_TOKEN("token");
static const QString BOT_ADMIN("admin");
static const QString BOT_PROXY("proxy");

AppConfig::AppConfig(const QString& fileName) :
    p_settings(nullptr),m_preserveConfig(false)
{
    p_settings = (fileName.isEmpty()) ? new QSettings
            : new QSettings(fileName,QSettings::IniFormat);

    qDebug() << "Using settings file "<<p_settings->fileName();

    _loadValues();
}

AppConfig::~AppConfig()
{
    p_settings->sync();
    delete p_settings;
}

void AppConfig::_loadValues()
{
    m_botToken          = p_settings->value(BOT_TOKEN).toString();
    m_botAdmin          = p_settings->value(BOT_ADMIN).toString().toDouble();

    QString proxyString = p_settings->value(BOT_PROXY).toString();
    if (ProxyHelper::isValidProxy(proxyString)) {
        m_proxy = ProxyHelper::proxyFromString(proxyString);
    }
}

void AppConfig::updateConfigFile(const CommandLineParser& parser)
{
    m_preserveConfig = parser.preserveConfig();

    if (parser.botAdmin() != 0)             setBotAdmin(parser.botAdmin());
    if (!parser.token().isEmpty())          setToken(parser.token());

    if (parser.validProxyConfigured())      setProxy(parser.proxy());
}

QSettings::Status AppConfig::status() const
{
    return p_settings->status();
}

void AppConfig::setToken(const QString& newToken)
{
    m_botToken = newToken;
    if (!m_preserveConfig)   p_settings->setValue(BOT_TOKEN,newToken);
}

void AppConfig::setBotAdmin(Telegram::User::Id newAdminId)
{
    m_botAdmin = newAdminId;
    if (!m_preserveConfig)   p_settings->setValue(BOT_ADMIN,newAdminId);
}

bool AppConfig::validProxyConfigured() const
{
    return m_proxy.type() != QNetworkProxy::NoProxy;
}

void AppConfig::setProxy(const QNetworkProxy& proxy)
{
    m_proxy = proxy;
    if (!m_preserveConfig)   p_settings->setValue(BOT_PROXY,ProxyHelper::stringFromProxy(proxy));
}
