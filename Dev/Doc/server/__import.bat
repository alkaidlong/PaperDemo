@echo off
rem ---------------------------------------------------
rem  �������޸�MySQL���û������������� = ���Ҳ�Ҫ���ո�
rem ---------------------------------------------------
set 	user=root
set 	pwd=root
set 	host=192.168.2.105
rem ---------------------------------------------------


color 2B

mysql -u%user% -p%pwd% -h%host% < d_game.sql
echo d_game.sql

mysql -u%user% -p%pwd% -h%host% < d_login.sql
echo d_login.sql

mysql -u%user% -p%pwd% -h%host% < d_log.sql
echo d_log.sql


pause