#include "bot.hpp"

void bot::start(int fd)
{

  std::string sen1 = ":ircserv 704   val *  :*** WELCOME YIRC_BoT ***\r\n";

  send(fd, sen1.c_str(), sen1.size(), 0);
  sen1 = ":ircserv 704 \t\t QUIT             ex: QUIT :Gone to have lunch \r\n";
  send(fd, sen1.c_str(), sen1.size(), 0);
  sen1 = ":ircserv 704 \t\t PART             ex:  PART #twilight_zone \r\n";
  send(fd, sen1.c_str(), sen1.size(), 0);
  sen1 = ":ircserv 704 \t\t PRIVMSG          ex: PRIVMSG Angel slm\r\n";
  send(fd, sen1.c_str(), sen1.size(), 0);
  sen1 = ":ircserv 704 \t\t JOIN               ex: JOIN #foobar \r\n";
  send(fd, sen1.c_str(), sen1.size(), 0);
  sen1 = ":ircserv 704 \t\t NOTICE               ex: NOTICE #chan message\r\n";
  send(fd, sen1.c_str(), sen1.size(), 0);
  sen1 = ":ircserv 704 \t\t TOPIC               ex:   TOPIC #test new_topic\r\n";
  send(fd, sen1.c_str(), sen1.size(), 0);
  sen1 = ":ircserv 704 \t\t KICK               ex: KICK #Finnish John\r\n";
  send(fd, sen1.c_str(), sen1.size(), 0);
  sen1 = ":ircserv 704 \t\t  OPER                         ex:foo bar\r\n";
  send(fd, sen1.c_str(), sen1.size(), 0);
   sen1 = ":ircserv 704   val *  :*** YIRC_BoT commands ***\r\n";
  send(fd, sen1.c_str(), sen1.size(), 0);
  sen1 = ":ircserv 704 \t\t chan               ex: BOT chan :to get the number of channels\r\n";
  send(fd, sen1.c_str(), sen1.size(), 0);
  sen1 = ":ircserv 704 \t\t chan               ex: BOT random  :to random  channel\r\n";
  send(fd, sen1.c_str(), sen1.size(), 0);
}

void bot::channel_list(int fd)
{
  std::string sen1(":ircserv 704 val *  : there are ");
  sen1 = sen1 + std::to_string(map_channels.size()) + " channel/s\r\n";
  send(fd, sen1.c_str(), sen1.size(), 0);
}

void bot::random_join(user *user_)
{
  std::map<std::string, class channel *>::iterator it;
  it = map_channels.begin();
  if (map_channels.size() > 0)
  {
    std::advance(it, rand() % map_channels.size());
    std::string random_key = it->first;

    std::vector<std::string> splited_line;
    splited_line.push_back("JOIN");
    splited_line.push_back(random_key);
    check_JOIN(splited_line, user_);
  }
}
bot::bot()
{
}

bot::~bot()
{
}
