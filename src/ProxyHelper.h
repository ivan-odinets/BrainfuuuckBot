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

#ifndef PROXYHELPER_H
#define PROXYHELPER_H

#include <QCoreApplication>
#include <QNetworkProxy>

class ProxyHelper
{
    Q_DECLARE_TR_FUNCTIONS(CommandLineParser);
public:
    static bool              isValidProxy(const QString& input);
    static QNetworkProxy     proxyFromString(QString input);
    static QString           stringFromProxy(const QNetworkProxy& proxy);
};

#endif // PROXYHELPER_H
