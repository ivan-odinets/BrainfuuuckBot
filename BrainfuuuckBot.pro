SUBDIRS += src/BrainfuuuckBot.pro

TEMPLATE = subdirs
CONFIG += ordered warn_on qt debug_and_release 

DISTFILES += README.md \
    debian/brainfuuuck-bot.dirs \
    debian/brainfuuuck-bot.install \
    debian/brainfuuuck-bot.conf \
    debian/brainfuuuck-bot.service
