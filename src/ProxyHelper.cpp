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

#include "ProxyHelper.h"

bool ProxyHelper::isValidProxy(const QString& input)
{
    static QRegExp proxyPattern("^(http|socks5)://.*:([0-6]\\d\\d\\d\\d|\\d\\d\\d\\d)$");
    return proxyPattern.exactMatch(input);
}

QNetworkProxy ProxyHelper::proxyFromString(QString inputString)
{
    QNetworkProxy result;

    if (inputString.isEmpty()) {
        result.setType(QNetworkProxy::NoProxy);
        return result;
    }

    //Get proxy type
    QRegExp protocolRegExp("^.*(?=://)");
    if (protocolRegExp.indexIn(inputString) < 0) { //No protocol specified
        qWarning() << tr("Error parsing proxy protocol!");
        return QNetworkProxy();
    }
    QString protocol = protocolRegExp.cap(0);
    if (protocol == QStringLiteral("http")) {
        result.setType(QNetworkProxy::HttpProxy);
        inputString.remove(QRegExp("^http://"));
    } else if (protocol == QStringLiteral("socks5")) {
        result.setType(QNetworkProxy::Socks5Proxy);
        inputString.remove(QRegExp("^socks5://"));
    } else {
        qWarning() << tr("Unknown proxy protocol %1. Disabling proxy.").arg(protocol);
        return QNetworkProxy();
    }

    //Get proxy server
    QRegExp hostNameRegExp("^.*(?=:)");
    if (hostNameRegExp.indexIn(inputString) < 0) {
        //Probably some syntax error, return sth
        qWarning() << "Error parsing proxy host. Disabling proxy...";
        return QNetworkProxy();
    }

    result.setHostName(hostNameRegExp.cap(0));
    inputString.remove(hostNameRegExp);
    if (!inputString.startsWith(":")) {
        //Probably no port specified, return sth
        qWarning() << "Error parsing proxy port. Disabling proxy...";
        return QNetworkProxy();
    }

    inputString.remove(QRegExp("^:"));
    bool ok = false;
    qint32 proxyPort = inputString.toInt(&ok);
    if (!ok) {
        //Error in port input
        qWarning() << "Another error parsing proxy port. Disabling proxy...";
        return QNetworkProxy();
    }

    result.setPort(proxyPort);

    return result;
}

QString ProxyHelper::stringFromProxy(const QNetworkProxy& proxy)
{
    QString proxyType;
    switch (proxy.type()) {
    case QNetworkProxy::HttpProxy:
    case QNetworkProxy::HttpCachingProxy:
        proxyType = "http";
        break;
    case QNetworkProxy::Socks5Proxy:
        proxyType = "socks5";
        break;
    case QNetworkProxy::DefaultProxy:
    case QNetworkProxy::FtpCachingProxy:
    case QNetworkProxy::NoProxy:
        return QString();
    }

    return QString("%1://%2:%3")
            .arg(proxyType)
            .arg(proxy.hostName())
            .arg(proxy.port());
}
