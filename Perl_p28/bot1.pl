use Net::IRC;

$server = 'irc.freenode.net';
$channel = '#blergh';
$botnick = 'MegaMikeBot';
$password = 'foobar';
$botadmin = 'M-Saunders';

$irc = new Net::IRC;

$conn = $irc->newconn(Nick => $botnick,
	Server => $server, Port => 6667);

$conn->add_global_handler('376', \&on_connect);
$conn->add_global_handler('disconnect', \&on_disconnect);
$conn->add_global_handler('kick', \&on_kick);
$conn->add_global_handler('msg', \&on_msg);

$irc->start;

sub on_connect {
	$self = shift;
	$self->privmsg('nickserv',                              ����<<<����                                 ������                                                          �����������  �����������������������������  ���                    ���                                                          �����������                  �������������