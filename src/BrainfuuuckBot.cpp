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

#include "BrainfuuuckBot.h"

#include "BrainfuckJob.h"
#include "UI.h"

BrainfuuuckBot::BrainfuuuckBot(QObject* parent) :
    QObject(parent)
{
    connect(&m_jobManager,&BrainfuckJobManager::jobFinished,this,&BrainfuuuckBot::_brainfuckJobFinished);
}

BrainfuuuckBot::~BrainfuuuckBot()
{}

bool BrainfuuuckBot::started()
{
    p_botApi = new Telegram::Bot(m_botApiKey,1000);
    if (m_proxy.type() != QNetworkProxy::NoProxy)
        p_botApi->setProxy(m_proxy);

    connect(p_botApi,&Telegram::Bot::message,this,&BrainfuuuckBot::_handleNewMessage);

    m_botUser = p_botApi->getMe();
    qInfo() << "Staring process using API key for following bot: "<<m_botUser;

    return true;
}

void BrainfuuuckBot::_handleNewMessage(const Telegram::Message& message)
{
    if (message.type() != Telegram::Message::TextType)
        return;

    // /start, /help, /tapeSize commands should work both in group and private chats
    if (message.text().startsWith(UI::helpCmd())) {
        _sendReply(UI::helpMessage(),message,true);
        return;
    }

    if (message.text().startsWith(UI::startCmd())) {
        _sendReply(UI::startMessage(),message);
        return;
    }

    if (message.text().startsWith(UI::tapeSizeCmd())) {
        _sendReply(UI::tapeSizeMessage().arg(BrainfuckJob::tapeSize()),message);
        return;
    }

    // For other cases - we need to distinguish between group and private chats
    if (message.from().id() == message.chat().id()) {
        _handleUserPrivateMessage(message);
        return;
    } else {
        _handleChatMessage(message);
        return;
    }
}

void BrainfuuuckBot::_brainfuckJobFinished(BrainfuckJob* job)
{
    _sendReply(job->outputText(),job->originalMessage(),true);
    job->deleteLater();
}

void BrainfuuuckBot::_handleUserPrivateMessage(const Telegram::Message& message)
{
    if (message.text().startsWith("/") && message.from().id()) {
        _handleBotAdminComamnd(message);
        return;
    }

    if (message.text().startsWith("/")) {
        _sendReply(UI::unknownCommandMessage(),message);
        return;
    }

    BrainfuckJob* brainfuckJob = new BrainfuckJob;
    brainfuckJob->setOriginalMessage(message);
    brainfuckJob->setBrainfuckInput(message.text());
    m_jobManager.appendJob(brainfuckJob);
}

void BrainfuuuckBot::_handleChatMessage(const Telegram::Message& message)
{
    if (message.text().startsWith(UI::chatExecuteCmd())) {
        QString code = message.text().remove(UI::chatExecuteCmd());
        BrainfuckJob* brainfuckJob = new BrainfuckJob;
        brainfuckJob->setOriginalMessage(message);
        brainfuckJob->setBrainfuckInput(code);
        m_jobManager.appendJob(brainfuckJob);
        return;
    }

    if (message.text().startsWith("/")) {
        _sendReply(UI::unknownCommandMessage(),message);
        return;
    }
}

void BrainfuuuckBot::_handleBotAdminComamnd(const Telegram::Message& message)
{
    if (message.text().startsWith(UI::versionCmd())) {
        _sendReply(APP_VERSION,message);
        return;
    }

    _sendReply(UI::unknownCommandMessage(),message);
}

/*
 *********************************************************************************************************************
 * Some service stuff...
 */

void BrainfuuuckBot::_sendReply(const QString &text, const Telegram::Message &message)
{
    p_botApi->sendMessage(message.chat().id(),text,message.id());
}

void BrainfuuuckBot::_sendReply(const QString& text,const Telegram::Message& message, bool markdown)
{
    p_botApi->sendMessage(message.chat().id(),text,markdown,false,message.id());
}
