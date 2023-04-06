# BrainfuuuckBot

BrainfuuuckBot - telegram bot for interpreting brainfuck code.

Bot is working both in private chats and in groups. Working version of this bot - [telegram](https://t.me/brainfuuuck_bot).

Currently this bot has no multithreading or queuing system or anything like this.

**Version: 0.0.1**

## Compiling & usage

First of all - create bot in Telegram. Check telegram docs [here](https://core.telegram.org/bots#6-botfather).

For  Debian:
```
git clone git@github.com:ivan-odinets/BrainfuuuckBot.git
cd BrainfuuuckBot
git submodule init
git submodule update
sudo  apt-get  install  qtbase5-dev  qtbase5-dev-tools  qt5-qmake  libqt5core5a  libqt5network5 libqt5sql5
debuild  -b  -uc  -us
```
And than install package using dpkg

For other linux:
```
git clone git@github.com:ivan-odinets/BrainfuuuckBot.git
cd BrainfuuuckBot
git submodule init
git submodule update
qmake
make
cd bin
./brainfuuuck-bot --help
```

## License
[GNU General Public License v3.0](https://choosealicense.com/licenses/gpl-3.0/)
