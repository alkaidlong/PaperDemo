export user=root
export pwd=root
export host=localhost
mysql -u$user -p$pwd -h$host < d_game.sql
echo d_game.sql

mysql -u$user -p$pwd -h$host < d_login.sql
echo d_login.sql

mysql -u$user -p$pwd -h$host < d_log.sql
echo d_log.sql