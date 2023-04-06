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

#include "CommandLineParser.h"

#include <QDir>

CommandLineParser::CommandLineParser() :
    m_configFileOption(QStringList{    "c", "config"            },   tr("Specify <config> file to use")),
    m_preserveConfig(QStringList{      "k", "preserve-config"   },   tr("Do not touch config file.")),
    m_botTokenOption(QStringList{      "t", "token"             },   tr("Set bot token.")),
    m_botAdminOption(QStringList{      "a", "admin"             },   tr("Set bot administrator userId.")),
    m_networkProxy(QStringList{        "p", "proxy"             },   tr("Specify <proxy> to use in following format http|socks5://<server>:<port>"))
{
    // -h/ --help
    addHelpOption();
    // -v/ --version
    addVersionOption();

    // -c/ --config
    m_configFileOption.setValueName("config");
    m_configFileOption.setDefaultValue(QString());
    addOption(m_configFileOption);

    // -k/ --preserve-config
    addOption(m_preserveConfig);

    // -t/ --token
    m_botTokenOption.setValueName("token");
    m_botTokenOption.setDefaultValue(QString());
    addOption(m_botTokenOption);

    // -a/ --admin
    m_botAdminOption.setValueName("admin");
    m_botAdminOption.setDefaultValue("0");
    addOption(m_botAdminOption);

    // -p/ --proxy
    m_networkProxy.setValueName("proxy");
    m_networkProxy.setDefaultValue(QString());
    addOption(m_networkProxy);
}
