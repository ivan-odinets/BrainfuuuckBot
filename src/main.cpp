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

#include <QCoreApplication>

#include <cstdlib>
#include <time.h>

#include "AppConfig.h"
#include "BrainfuuuckBot.h"
#include "CommandLineParser.h"

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);

int main(int argc, char *argv[])
{
    qInstallMessageHandler(myMessageOutput);
    std::srand(std::time(nullptr));

    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName(APP_NAME);
    QCoreApplication::setOrganizationName("OdinSoft");
    QCoreApplication::setApplicationVersion(APP_VERSION);

    CommandLineParser parser;
    parser.process(app);

    AppConfig appConfig(parser.configFile());
    appConfig.updateConfigFile(parser);

    if (appConfig.token().isEmpty()) {
        qCritical() << "Telegram BotAPI Token must be specified.";
        return -1;
    }

    //Setup connection to telegram API
    BrainfuuuckBot bot;

    bot.setApiKey(appConfig.token());
    if (appConfig.validProxyConfigured())
        bot.setProxy(appConfig.proxy());

    if (appConfig.botAdmin() == 0)
        qWarning() << "Bot administrator is not set, so administration commands will not work!";
    else
        bot.setBotAdmin(appConfig.botAdmin());

    //Start Bot
    if (!bot.started()) {
        qCritical() << "Can not start bot due to some errors.";
        return -1;
    }

    return app.exec();
}

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    Q_UNUSED(context);
    const char *function = context.function ? context.function : "";
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "[DEBUG]   : %s ( %s )\n", localMsg.constData(), function);
        break;
    case QtInfoMsg:
        fprintf(stderr, "[INFO]    : %s\n", localMsg.constData());
        break;
    case QtWarningMsg:
        fprintf(stderr, "[WARNING] : %s\n", localMsg.constData());
        break;
    case QtCriticalMsg:
        fprintf(stderr, "[CRITICAL]: %s\n", localMsg.constData());
        break;
    case QtFatalMsg:
        fprintf(stderr, "[FATAL]   : %s\n", localMsg.constData());
        break;
    }
}
