-- MySQL dump 10.13  Distrib 5.5.8, for Win32 (x86)
--
-- Host: 10.208.11.131    Database: d_login
-- ------------------------------------------------------
-- Server version	5.5.8

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Current Database: `d_login`
--

/*!40000 DROP DATABASE IF EXISTS `d_login`*/;

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `d_login` /*!40100 DEFAULT CHARACTER SET utf8 */;

USE `d_login`;

--
-- Table structure for table `t_cdk`
--

DROP TABLE IF EXISTS `t_cdk`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_cdk` (
  `f_PackageType` int(10) unsigned NOT NULL DEFAULT '0',
  `f_PackageKey` char(40) NOT NULL,
  `f_PlayerID` bigint(20) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`f_PackageKey`),
  KEY `NewIndex1` (`f_PlayerID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `t_cdktype`
--

DROP TABLE IF EXISTS `t_cdktype`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_cdktype` (
  `f_PackageType` int(11) NOT NULL,
  `f_PackageContent` varchar(4096) NOT NULL,
  `f_BeginTime` int(10) unsigned NOT NULL DEFAULT '0',
  `f_EndTime` int(10) unsigned NOT NULL DEFAULT '0',
  `f_ServerID` int(10) unsigned DEFAULT '0',
  `f_PlatFormID` int(10) unsigned DEFAULT '0',
  PRIMARY KEY (`f_PackageType`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `t_token`
--

DROP TABLE IF EXISTS `t_token`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_token` (
  `f_Account` varbinary(64) NOT NULL,
  `f_Token` varbinary(64) NOT NULL,
  PRIMARY KEY (`f_Account`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping routines for database 'd_login'
--
/*!50003 DROP PROCEDURE IF EXISTS `account_token` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `account_token`( IN account varchar(64) , IN token VARCHAR(64) )
BEGIN
	REPLACE INTO t_token(f_Account,f_Token) VALUE( account, token );
    END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `cdk_valid` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `cdk_valid`( in player_id_arg BIGINT unsigned ,IN cdk CHAR(16) ,IN server_id INT UNSIGNED,IN platform_id INT UNSIGNED, OUT  package_content VARCHAR(4096) , OUT res INt )
BEGIN
	#ok, res = 0;
	#cdk cdk does't exist , res = 2;
	
	DECLARE player_id BIGINT UNSIGNED DEFAULT 0;
	DECLARE package_type INT UNSIGNED DEFAULT 0;
	DECLARE get_count int UNSIGNED DEFAULT 0;
	DECLARE serverid INT UNSIGNED DEFAULT 0;
	DECLARE platformid INT UNSIGNED DEFAULT 0;
	SELECT f_PlayerID , f_PackageType FROM t_cdk WHERE f_PackageKey = cdk INTO player_id , package_type;
	
	
	IF package_type = 0 THEN
		#cdk does't exist
		SELECT 2 INTO res;
	ELSE
		select count(*) from t_cdk where f_PackageType = package_type and f_PlayerID = player_id_arg into get_count;
		#SELECT get_count,player_id_arg,package_type;
		if get_count = 0  then 
			IF player_id = 0 THEN
				select f_PackageContent,f_ServerID,f_PlatFormID from t_cdktype where f_PackageType=package_type and UNIX_TIMESTAMP() >= f_BeginTime and UNIX_TIMESTAMP() <= f_EndTime into package_content,serverid,platformid;
				if ISNULL(package_content) then
					select 4 into res;
				else
					if platformid > 0 then
						if platform_id = platformid then
							if serverid > 0 then
								if server_id = serverid then
									update t_cdk set f_PlayerID = player_id_arg where f_PackageKey=cdk;
									select 0 into res;
								else
									select 7 into res;
								end if;
							else
								UPDATE t_cdk SET f_PlayerID = player_id_arg WHERE f_PackageKey=cdk;
								select 0 into res;
							end if;
						else
							select 6 into res;
						end if;
					else
						UPDATE t_cdk SET f_PlayerID = player_id_arg WHERE f_PackageKey=cdk;
						select 0 into res;
					end if;
				end if;#end of ISNULL(package_content)
			ELSE
				select 5 into res;
			END IF; # end of player_id = 0
		else
			select 3 into res;
		end if;#end of player_id = 0
	END IF;# end of package_type = 0
 
    END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2014-07-16 17:33:30
