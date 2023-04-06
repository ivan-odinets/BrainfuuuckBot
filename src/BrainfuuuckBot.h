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

#ifndef BRAINFUUUCKBOT_H
#define BRAINFUUUCKBOT_H

#include <QObject>

#include "QtTelegramBot.h"

#include "BrainfuckJobManager.h"

class BrainfuuuckBot : public QObject
{
    Q_OBJECT
public:
    explicit BrainfuuuckBot(QObject* parent = nullptr);
    virtual ~BrainfuuuckBot();

    bool started();
    void setApiKey(const QString& key)           { m_botApiKey = key; }
    void setBotAdmin(qint32 userId)              { m_botAdmin = userId; }
    void setProxy(const QNetworkProxy& proxy)    { m_proxy = proxy; }

private slots:
    void _handleNewMessage(const Telegram::Message& message);

    void _brainfuckJobFinished(BrainfuckJob* job);

private:
    void _handleUserPrivateMessage(const Telegram::Message& message);
    void _handleChatMessage(const Telegram::Message& message);
    void _handleBotAdminComamnd(const Telegram::Message& message);

    BrainfuckJobManager m_jobManager;

    void _sendReply(const QString& text,const Telegram::Message& message);
    void _sendReply(const QString& text,const Telegram::Message& message, bool markdown);
    Telegram::Bot*      p_botApi;
    Telegram::User      m_botUser;
    QString             m_botApiKey;
    qint64              m_botAdmin;
    QNetworkProxy       m_proxy;
};

#endif // BRAINFUUUCKBOT_H
