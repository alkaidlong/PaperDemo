@echo off
rem ---------------------------------------------------
rem  在下面修改MySQL的用户名和密码配置 = 左右不要留空格
rem ---------------------------------------------------
set 	user=root
set 	pwd=root
set 	host=10.205.17.14
color 2B
echo d_game.sql
mysqldump -h%host% -u%user% -p%pwd%  -R -B -d --add-drop-database  d_game>./d_game.sql
echo d_login.sql
mysqldump -h%host% -u%user% -p%pwd%  -R -B -d --add-drop-database  d_login>./d_login.sql
echo d_log.sql
mysqldump -h%host% -u%user% -p%pwd%  -R -B -d --add-drop-database  d_log>./d_log.sql
pause