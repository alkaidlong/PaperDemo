-- MySQL dump 10.13  Distrib 5.5.8, for Win32 (x86)
--
-- Host: 10.208.11.131    Database: d_game
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
-- Current Database: `d_game`
--

/*!40000 DROP DATABASE IF EXISTS `d_game`*/;

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `d_game` /*!40100 DEFAULT CHARACTER SET utf8 COLLATE utf8_bin */;

USE `d_game`;

--
-- Table structure for table `t_activity`
--

DROP TABLE IF EXISTS `t_activity`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_activity` (
  `f_PlayerID` bigint(20) unsigned NOT NULL,
  `f_WineMask` int(10) unsigned DEFAULT '0',
  `f_SevenDayMask` int(10) unsigned DEFAULT '0',
  `f_UpgradeMask` int(10) unsigned DEFAULT '0',
  `f_SignContinueTimes` int(10) unsigned DEFAULT '0',
  `f_SignModel` int(10) unsigned DEFAULT '1',
  `f_SignTime` int(10) unsigned DEFAULT '0',
  `f_CardTime` int(10) unsigned DEFAULT '0',
  PRIMARY KEY (`f_PlayerID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `t_arua`
--

DROP TABLE IF EXISTS `t_arua`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_arua` (
  `f_ID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `f_PlayerID` bigint(20) unsigned NOT NULL,
  `f_HeroID` bigint(20) unsigned NOT NULL DEFAULT '0',
  `f_AuraItemID` int(11) NOT NULL,
  `f_AuraLevel` smallint(5) unsigned NOT NULL DEFAULT '1',
  `f_ArmedPos` tinyint(4) DEFAULT '-1',
  PRIMARY KEY (`f_ID`),
  KEY `f_PlayerID` (`f_PlayerID`)
) ENGINE=InnoDB AUTO_INCREMENT=72339069014638594 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `t_awardmail`
--

DROP TABLE IF EXISTS `t_awardmail`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_awardmail` (
  `f_PlayerID` bigint(20) unsigned DEFAULT NULL,
  `f_MailID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `f_Type` int(10) unsigned DEFAULT NULL,
  `f_Time` int(20) unsigned DEFAULT NULL,
  `f_Status` int(10) unsigned DEFAULT NULL,
  `f_ItemID` int(10) unsigned DEFAULT NULL,
  `f_Content` varchar(1024) DEFAULT NULL,
  UNIQUE KEY `f_MailID` (`f_MailID`)
) ENGINE=InnoDB AUTO_INCREMENT=6397 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `t_bloodybattle`
--

DROP TABLE IF EXISTS `t_bloodybattle`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_bloodybattle` (
  `f_PlayerID` bigint(20) NOT NULL,
  `f_InRankContinueDays` int(10) unsigned DEFAULT '0',
  `f_LastDayStarNumMax` int(10) unsigned DEFAULT '0',
  `f_LastDayIsInRank` tinyint(1) DEFAULT '0',
  PRIMARY KEY (`f_PlayerID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `t_chapter`
--

DROP TABLE IF EXISTS `t_chapter`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_chapter` (
  `f_ChaperItemID` smallint(5) unsigned NOT NULL,
  `f_PlayerID` bigint(20) unsigned NOT NULL,
  `f_ChapterAwardMask` tinyint(4) DEFAULT '0',
  `f_CurMission` smallint(5) unsigned DEFAULT NULL,
  `f_IsFinishGuide` tinyint(1) DEFAULT '0',
  PRIMARY KEY (`f_ChaperItemID`,`f_PlayerID`),
  KEY `f_PlayerID` (`f_PlayerID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `t_cron`
--

DROP TABLE IF EXISTS `t_cron`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_cron` (
  `f_BegTime` datetime DEFAULT NULL,
  `f_EndTime` datetime DEFAULT NULL,
  `f_DurationSeconds` int(10) unsigned DEFAULT NULL,
  `f_TaskName` varchar(128) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `t_enemy`
--

DROP TABLE IF EXISTS `t_enemy`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_enemy` (
  `f_PlayerID` bigint(20) unsigned DEFAULT '0',
  `f_EnemyID` bigint(20) unsigned DEFAULT '0',
  `f_Time` int(20) unsigned DEFAULT '0',
  `f_Ships` int(10) unsigned DEFAULT '0',
  KEY `f_PlayerID` (`f_PlayerID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `t_equip`
--

DROP TABLE IF EXISTS `t_equip`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_equip` (
  `f_ID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `f_PlayerID` bigint(20) unsigned NOT NULL,
  `f_HeroID` bigint(20) unsigned NOT NULL DEFAULT '0',
  `f_EquipItemID` int(11) NOT NULL,
  `f_EquipLevel` int(10) unsigned NOT NULL DEFAULT '1',
  PRIMARY KEY (`f_ID`),
  KEY `f_PlayerID` (`f_PlayerID`)
) ENGINE=InnoDB AUTO_INCREMENT=72339069014638737 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `t_fragment`
--

DROP TABLE IF EXISTS `t_fragment`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_fragment` (
  `f_PlayerID` bigint(20) unsigned NOT NULL,
  `f_AuraItemID` int(10) unsigned NOT NULL,
  `f_Num` int(10) unsigned DEFAULT NULL,
  PRIMARY KEY (`f_PlayerID`,`f_AuraItemID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `t_gmaddmail`
--

DROP TABLE IF EXISTS `t_gmaddmail`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_gmaddmail` (
  `f_MailID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `f_Type` int(10) unsigned NOT NULL,
  `f_Time` int(10) unsigned NOT NULL,
  `f_ItemID` int(10) unsigned DEFAULT NULL,
  `f_Content` varchar(1024) NOT NULL,
  PRIMARY KEY (`f_MailID`)
) ENGINE=InnoDB AUTO_INCREMENT=14 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `t_hero`
--

DROP TABLE IF EXISTS `t_hero`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_hero` (
  `f_ID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `f_PlayerID` bigint(20) unsigned DEFAULT NULL,
  `f_HeroItemID` int(11) NOT NULL,
  `f_MaxHP` float DEFAULT '0',
  `f_PhysicalAttack` float DEFAULT '0',
  `f_MagicalAttack` float DEFAULT '0',
  `f_PhysicalDefense` float DEFAULT '0',
  `f_MagicalDefense` float DEFAULT '0',
  `f_Potential` int(11) DEFAULT '0',
  `f_TrainTimes` int(10) unsigned DEFAULT '0',
  `f_ForceIndex` tinyint(4) DEFAULT NULL,
  `f_SkillLevel` smallint(5) unsigned DEFAULT '1',
  `f_Level` smallint(5) unsigned DEFAULT '1',
  `f_Exp` int(10) unsigned DEFAULT '0',
  `f_BreakTimes` tinyint(3) unsigned DEFAULT '0',
  PRIMARY KEY (`f_ID`),
  UNIQUE KEY `unionPlayerIDHeroItemID` (`f_PlayerID`,`f_HeroItemID`)
) ENGINE=InnoDB AUTO_INCREMENT=72339069014643124 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `t_item`
--

DROP TABLE IF EXISTS `t_item`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_item` (
  `f_PlayerID` bigint(20) unsigned NOT NULL,
  `f_ItemID` int(11) NOT NULL,
  `f_Num` int(10) unsigned DEFAULT '1',
  PRIMARY KEY (`f_PlayerID`,`f_ItemID`),
  KEY `f_PlayerID` (`f_PlayerID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `t_mail`
--

DROP TABLE IF EXISTS `t_mail`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_mail` (
  `f_PlayerID` bigint(20) unsigned NOT NULL DEFAULT '0',
  `f_MailID` int(10) unsigned NOT NULL DEFAULT '0',
  `f_Type` int(10) unsigned DEFAULT NULL,
  `f_Time` int(20) unsigned DEFAULT NULL,
  `f_Status` int(10) unsigned DEFAULT NULL,
  `f_Name` varchar(20) DEFAULT NULL,
  `f_Rank` int(10) unsigned DEFAULT NULL,
  `f_ItemID` int(10) unsigned DEFAULT NULL,
  `f_ItemNum` int(10) unsigned DEFAULT NULL,
  `f_Content` varchar(1024) DEFAULT NULL,
  KEY `f_PlayerID` (`f_PlayerID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `t_mission`
--

DROP TABLE IF EXISTS `t_mission`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_mission` (
  `f_MissionItemID` smallint(5) unsigned NOT NULL,
  `f_PlayerID` bigint(20) unsigned NOT NULL,
  `f_GotStar` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `f_TimesTodayLeft` smallint(5) unsigned NOT NULL DEFAULT '5',
  `f_ResetTimesToday` smallint(5) unsigned DEFAULT '0',
  `f_ChallengeTime` int(10) unsigned DEFAULT '0',
  PRIMARY KEY (`f_MissionItemID`,`f_PlayerID`),
  KEY `f_PlayerID` (`f_PlayerID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `t_order`
--

DROP TABLE IF EXISTS `t_order`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_order` (
  `f_PlayerID` bigint(20) unsigned NOT NULL,
  `f_OrderNO` varchar(128) COLLATE utf8_bin NOT NULL,
  `f_OrderStatus` int(10) unsigned NOT NULL,
  `f_ChargeLevel` int(10) unsigned NOT NULL,
  `f_CreateOrderTime` int(10) unsigned NOT NULL,
  PRIMARY KEY (`f_OrderNO`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `t_pet`
--

DROP TABLE IF EXISTS `t_pet`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_pet` (
  `f_PlayerID` bigint(20) unsigned NOT NULL,
  `f_PetItemID` int(11) unsigned NOT NULL,
  `f_Level` smallint(5) unsigned NOT NULL DEFAULT '0',
  `f_Exp` int(10) unsigned DEFAULT '0',
  `f_Flag` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`f_PlayerID`,`f_PetItemID`),
  UNIQUE KEY `f_PetItemID` (`f_PlayerID`,`f_PetItemID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `t_player`
--

DROP TABLE IF EXISTS `t_player`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_player` (
  `f_ID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `f_Account` varbinary(64) NOT NULL,
  `f_Name` varchar(32) NOT NULL,
  `f_Exp` int(10) unsigned NOT NULL DEFAULT '0',
  `f_Level` smallint(5) unsigned NOT NULL DEFAULT '1',
  `f_Money` int(11) unsigned NOT NULL DEFAULT '10000',
  `f_Diamond` int(11) unsigned NOT NULL DEFAULT '0',
  `f_PVEPower` int(11) unsigned NOT NULL DEFAULT '30',
  `f_PVPPower` int(11) unsigned NOT NULL DEFAULT '30',
  `f_VIPLevel` smallint(5) unsigned NOT NULL DEFAULT '0',
  `f_RMB` int(10) unsigned NOT NULL DEFAULT '0',
  `f_LoginAccumulativedDays` int(10) unsigned NOT NULL DEFAULT '1',
  `f_LoginContinuallyDays` int(10) unsigned NOT NULL DEFAULT '1',
  `f_LastLoginTime` datetime DEFAULT NULL,
  `f_CurChapter` smallint(5) unsigned NOT NULL,
  `f_HeroHireSadness` int(10) unsigned NOT NULL DEFAULT '0',
  `f_MiddleHireLeftCount` smallint(5) unsigned NOT NULL DEFAULT '1',
  `f_HighHireLeftCount` smallint(5) unsigned NOT NULL DEFAULT '1',
  `f_NormalHireLeftCount` smallint(5) unsigned NOT NULL DEFAULT '5',
  `f_CurMission` smallint(5) unsigned NOT NULL,
  `f_CurDrawRuneQuality` tinyint(3) unsigned NOT NULL DEFAULT '1',
  `f_DrawRuneLeftCount` smallint(5) unsigned NOT NULL DEFAULT '1',
  `f_PVPRewardMask` int(10) unsigned NOT NULL DEFAULT '0',
  `f_PVPRank` int(10) unsigned DEFAULT '0',
  `f_PVPScore` int(10) unsigned DEFAULT '0',
  `f_PVPLeftCountToday` int(10) unsigned DEFAULT '0',
  `f_PVPScoreRefreshTime` datetime NOT NULL,
  `f_CreateTime` datetime NOT NULL DEFAULT '2013-12-20 00:00:00',
  `f_PowerRefreshTime` datetime NOT NULL,
  `f_GuideHireTimes` smallint(5) unsigned NOT NULL DEFAULT '2',
  `f_MissionSweepTimes` int(10) unsigned DEFAULT '20',
  `f_GuideIDGroup` varchar(10240) DEFAULT NULL,
  `f_IsAllGuideFinish` tinyint(1) DEFAULT '0',
  `f_GetGMMailMaxID` int(10) unsigned DEFAULT '0',
  `f_CurBuyPVPPowerTimes` int(10) unsigned NOT NULL DEFAULT '0',
  `f_CurBuyPVEPowerTimes` int(10) unsigned NOT NULL DEFAULT '0',
  `f_GuideMask` int(10) unsigned NOT NULL DEFAULT '0',
  `f_VIPGiftMask` bigint(10) unsigned DEFAULT '0',
  `f_AccumulateRawDiamod` int(10) unsigned DEFAULT '0',
  `f_FirstChargeMask` bigint(20) unsigned DEFAULT '0',
  `f_ChargeRewardMask` bigint(20) unsigned DEFAULT '0',
  `f_MonthCardExpireTime` int(10) unsigned DEFAULT '0',
  PRIMARY KEY (`f_ID`),
  UNIQUE KEY `f_Account` (`f_Account`),
  UNIQUE KEY `f_Name` (`f_Name`)
) ENGINE=InnoDB AUTO_INCREMENT=72339069014639583 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `t_playernotice`
--

DROP TABLE IF EXISTS `t_playernotice`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_playernotice` (
  `f_NoticeID` bigint(15) unsigned NOT NULL AUTO_INCREMENT,
  `f_Type` int(10) unsigned DEFAULT NULL,
  `f_Time` int(10) unsigned DEFAULT NULL,
  `f_Name` varchar(20) DEFAULT NULL,
  `f_ConfigID` int(10) unsigned DEFAULT NULL,
  `f_Level` int(10) unsigned DEFAULT NULL,
  UNIQUE KEY `f_NoticeID` (`f_NoticeID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `t_rune`
--

DROP TABLE IF EXISTS `t_rune`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_rune` (
  `f_ID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `f_PlayerID` bigint(20) unsigned NOT NULL,
  `f_HeroID` bigint(20) unsigned NOT NULL DEFAULT '0',
  `f_RuneItemID` int(11) NOT NULL,
  `f_FrocePos` tinyint(4) NOT NULL DEFAULT '-1',
  `f_Energy` int(10) unsigned NOT NULL DEFAULT '0',
  `f_Level` smallint(5) unsigned NOT NULL DEFAULT '1',
  PRIMARY KEY (`f_ID`),
  KEY `f_PlayerID` (`f_PlayerID`)
) ENGINE=InnoDB AUTO_INCREMENT=72339069014638593 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `t_server_config`
--

DROP TABLE IF EXISTS `t_server_config`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_server_config` (
  `f_SystemNoticeVersion` int(11) NOT NULL DEFAULT '1',
  `f_PlayerNoticeMaxID` bigint(20) NOT NULL DEFAULT '0',
  `f_FirstLunchTime` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `t_soul`
--

DROP TABLE IF EXISTS `t_soul`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_soul` (
  `f_PlayerID` bigint(20) unsigned NOT NULL,
  `f_HeroItemID` int(11) NOT NULL,
  `f_Num` smallint(5) unsigned DEFAULT '0',
  PRIMARY KEY (`f_PlayerID`,`f_HeroItemID`),
  KEY `f_PlayerID` (`f_PlayerID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `t_systemnotice`
--

DROP TABLE IF EXISTS `t_systemnotice`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_systemnotice` (
  `f_NoticeID` bigint(15) unsigned NOT NULL AUTO_INCREMENT,
  `f_Color` int(10) unsigned DEFAULT NULL,
  `f_BeginTime` int(15) unsigned DEFAULT NULL,
  `f_EndTime` int(15) unsigned DEFAULT NULL,
  `f_NoticeContent` varchar(10240) DEFAULT NULL,
  `f_Frequency` int(15) NOT NULL DEFAULT '10',
  `f_Type` int(10) unsigned DEFAULT NULL,
  `f_NoticeTitle` varchar(1024) DEFAULT NULL,
  UNIQUE KEY `f_NoticeID` (`f_NoticeID`)
) ENGINE=InnoDB AUTO_INCREMENT=27 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping routines for database 'd_game'
--
/*!50003 DROP PROCEDURE IF EXISTS `change_force_index` */;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_general_ci ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `change_force_index`( IN hero_id_1 BIGINT UNSIGNED , IN hero_id_2 BIGINT UNSIGNED , IN hero_id_3 BIGINT UNSIGNED , IN hero_id_4 BIGINT UNSIGNED , IN hero_id_5 BIGINT UNSIGNED , IN hero_id_6 BIGINT UNSIGNED )
BEGIN
		IF hero_id_1 THEN
			UPDATE t_hero SET f_ForceIndex = 0 WHERE f_ID = hero_id_1;
		END IF; 
		
		IF hero_id_2 THEN
			UPDATE t_hero SET f_ForceIndex = 1 WHERE f_ID = hero_id_2;
		END IF; 
		
		IF hero_id_3 THEN
			UPDATE t_hero SET f_ForceIndex = 2 WHERE f_ID = hero_id_3;
		END IF; 
		
		IF hero_id_4 THEN
			UPDATE t_hero SET f_ForceIndex = 3 WHERE f_ID = hero_id_4;
		END IF; 
		
		IF hero_id_5 THEN
			UPDATE t_hero SET f_ForceIndex = 4 WHERE f_ID = hero_id_5;
		END IF; 
		
		IF hero_id_6 THEN
			UPDATE t_hero SET f_ForceIndex = 5 WHERE f_ID = hero_id_6;
		END IF; 
    END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_bin ;
/*!50003 DROP PROCEDURE IF EXISTS `check_out_hire_pet` */;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_general_ci ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `check_out_hire_pet`( IN player_id BIGINT UNSIGNED , IN diamond_cost INT , IN summon_type INT , IN add_sadness INT UNSIGNED , OUT error_code INT )
BEGIN
    
    	
	
	
	
	
	
	
	IF diamond_cost = 0 THEN
	
		IF summon_type = 1 THEN
		
			UPDATE t_player SET f_NormalHirePetLeftCount = f_NormalHirePetLeftCount - 1 , f_HeroHireSadness = f_HeroHireSadness + add_sadness WHERE f_ID = player_id;
		ELSEIF summon_type = 2 THEN
		
			UPDATE t_player SET f_MiddleHirePetLeftCount = f_MiddleHirePetLeftCount - 1 , f_HeroHireSadness = f_HeroHireSadness + add_sadness WHERE f_ID = player_id;
		ELSEIF summon_type = 3 THEN
		
			UPDATE t_player SET f_HighHirePetLeftCount = f_HighHirePetLeftCount - 1 , f_HeroHireSadness = f_HeroHireSadness + add_sadness WHERE f_ID = player_id;
		END IF; 
	ELSE
	
		UPDATE t_player SET f_Diamond = f_Diamond - diamond_cost , f_HeroHireSadness = f_HeroHireSadness + add_sadness WHERE f_ID = player_id;
	END IF; 
	
	SELECT 0 INTO error_code;
    END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_bin ;
/*!50003 DROP PROCEDURE IF EXISTS `cost_fragment` */;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_general_ci ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `cost_fragment`( IN player_id BIGINT UNSIGNED , IN item_id INT , IN num INT )
BEGIN
	DECLARE item_left INT DEFAULT 0;
	
	
	SELECT f_Num FROM t_fragment WHERE f_PlayerID = player_id AND f_AuraItemID = item_id INTO item_left;
	IF item_left > num THEN
	
		UPDATE t_fragment SET f_Num = f_Num - num WHERE f_PlayerID = player_id AND f_AuraItemID = item_id;
	ELSEIF item_left = num THEN
	
		DELETE FROM t_fragment WHERE f_PlayerID = player_id AND f_AuraItemID = item_id LIMIT 1;
	END IF;
    END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_bin ;
/*!50003 DROP PROCEDURE IF EXISTS `cost_hero_soul` */;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_general_ci ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `cost_hero_soul`( IN player_id BIGINT UNSIGNED , IN hero_item_id INT , IN num INT )
BEGIN
	DECLARE left_num INT DEFAULT 0;
	SELECT f_Num FROM t_soul WHERE f_PlayerID = player_id AND f_HeroItemID = hero_item_id INTO left_num;
	IF left_num THEN
		IF left_num > num THEN
		
			UPDATE t_soul SET f_Num = f_Num - num WHERE f_PlayerID = player_id AND f_HeroItemID = hero_item_id;
		ELSE
		
			DELETE FROM t_soul WHERE f_PlayerID = player_id AND f_HeroItemID = hero_item_id LIMIT 1;
		END IF;
	END IF;
    END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_bin ;
/*!50003 DROP PROCEDURE IF EXISTS `cost_item` */;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_general_ci ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `cost_item`( IN player_id BIGINT UNSIGNED , IN item_id INT , IN num INT )
BEGIN
    
	DECLARE item_left INT DEFAULT 0;
	
	
	SELECT f_Num FROM t_item WHERE f_PlayerID = player_id AND f_ItemID = item_id INTO item_left;
	IF item_left > num THEN
	
		UPDATE t_item SET f_Num = f_Num - num WHERE f_PlayerID = player_id AND f_ItemID = item_id;
	ELSEIF item_left = num THEN
	
		DELETE FROM t_item WHERE f_PlayerID = player_id AND f_ItemID = item_id LIMIT 1;
	END IF;
	
    END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_bin ;
/*!50003 DROP PROCEDURE IF EXISTS `create_aura` */;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_general_ci ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `create_aura`( IN player_id BIGINT UNSIGNED , IN aura_item_id INT , OUT aura_id BIGINT UNSIGNED )
BEGIN
	INSERT INTO t_arua(f_PlayerID,f_AuraItemID) VALUES(player_id,aura_item_id);
	SELECT LAST_INSERT_ID() INTO aura_id;
    END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_bin ;
/*!50003 DROP PROCEDURE IF EXISTS `create_equip` */;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_general_ci ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `create_equip`( IN player_id BIGINT UNSIGNED , IN equip_item_id INT , OUT equip_id BIGINT UNSIGNED )
BEGIN
	INSERT INTO t_equip(f_PlayerID,f_EquipItemID) VALUES(player_id,equip_item_id);
	SELECT LAST_INSERT_ID() INTO equip_id;
    END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_bin ;
/*!50003 DROP PROCEDURE IF EXISTS `create_hero` */;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_general_ci ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `create_hero`( IN player_id BIGINT UNSIGNED , IN hero_item_id INT , IN max_hp FLOAT ,
    IN physical_attack FLOAT , IN magical_attack FLOAT  , IN physical_defense FLOAT , IN magical_defense FLOAT , IN potential FLOAT ,in force_index tinyint,
      OUT hero_id BIGINT UNSIGNED )
BEGIN
		INSERT INTO t_hero( f_PlayerID , f_HeroItemID , f_MaxHP ,f_PhysicalAttack , f_MagicalAttack , f_PhysicalDefense , f_MagicalDefense , f_Potential , f_ForceIndex)
		VALUES( player_id , hero_item_id , max_hp , physical_attack , magical_attack , physical_defense , magical_defense , potential, force_index);
		SELECT LAST_INSERT_ID() INTO hero_id;
    END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_bin ;
/*!50003 DROP PROCEDURE IF EXISTS `create_player` */;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_general_ci ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `create_player`( 
			IN account VARCHAR(64) , IN nick_name VARCHAR(32) ,	
			IN chapter_id SMALLINT UNSIGNED , 			
			IN mission_id SMALLINT UNSIGNED , IN today_left SMALLINT UNSIGNED , 
			IN today_pvp_left INT UNSIGNED,
			OUT player_id BIGINT UNSIGNED )
BEGIN
	DECLARE v INT DEFAULT 0;
	INSERT INTO t_player( f_Account , f_Name , f_CurChapter , f_LastLoginTime , f_CurMission , f_PVPLeftCountToday , f_PVPScoreRefreshTime, f_CreateTime,f_PowerRefreshTime ) VALUES(account,nick_name,chapter_id , NOW() , mission_id , today_pvp_left , NOW(),now(),now() );
	SELECT LAST_INSERT_ID() INTO player_id;
	INSERT INTO t_chapter( f_ChaperItemID , f_PlayerID , f_CurMission ) VALUES(chapter_id,player_id,mission_id);
	INSERT INTO t_mission( f_MissionItemID , f_PlayerID , f_TimesTodayLeft ) VALUES( mission_id , player_id , today_left );
	
	
	SET v = 1;
	while v < 18 do
		INSERT INTO t_pet( f_PlayerID, f_PetItemID, f_Level, f_Exp) VALUES(player_id, v, 0, 0 );
		set v = v + 1;
	end while;
	
	SET v = 1;
	WHILE v < 21 DO
		INSERT INTO t_enemy( f_PlayerID,f_EnemyID, f_Time, f_Ships) VALUES(player_id, 0, 0, 0 );
		SET v = v + 1;
	END WHILE;
	
	SET v = 1;
	WHILE v < 51 DO
		INSERT INTO t_mail( f_PlayerID) VALUES(player_id);
		SET v = v + 1;
	END WHILE;
	
	INSERT INTO t_activity( f_PlayerID) VALUES(player_id);
	
	INSERT INTO t_bloodybattle( f_PlayerID) VALUES(player_id);
	
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_bin ;
/*!50003 DROP PROCEDURE IF EXISTS `create_rune` */;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_general_ci ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `create_rune`( IN player_id BIGINT UNSIGNED , IN rune_item_id INT , IN force_pos TINYINT , IN energy INT UNSIGNED , OUT rune_id BIGINT UNSIGNED )
BEGIN
	INSERT INTO t_rune(f_PlayerID,f_RuneItemID,f_FrocePos,f_Energy) VALUES( player_id , rune_item_id , force_pos , energy );
	SELECT LAST_INSERT_ID() INTO rune_id;
    END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_bin ;
/*!50003 DROP PROCEDURE IF EXISTS `load_playerIDs` */;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_general_ci ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `load_playerIDs`( IN load_num INT )
BEGIN
	SELECT f_ID FROM t_player ORDER BY f_LastLoginTime LIMIT load_num;
    END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_bin ;
/*!50003 DROP PROCEDURE IF EXISTS `mission_check_out` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `mission_check_out`( IN player_id BIGINT UNSIGNED , IN mission_id SMALLINT UNSIGNED, in cost_times SMALLINT UNSIGNED,in challengetime int unsigned)
BEGIN
	UPDATE t_mission SET f_TimesTodayLeft = f_TimesTodayLeft - cost_times , f_ChallengeTime =challengetime  WHERE f_PlayerID = player_id AND f_MissionItemID = mission_id;
    END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `open_next_chapter` */;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_general_ci ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `open_next_chapter`( IN player_id BIGINT UNSIGNED , IN chapter_id SMALLINT UNSIGNED , IN cur_mission_id SMALLINT UNSIGNED )
BEGIN
    
	INSERT t_chapter(f_PlayerID,f_ChaperItemID,f_CurMission) VALUES(player_id,chapter_id,cur_mission_id);
	UPDATE t_player SET f_CurChapter = chapter_id WHERE f_ID = player_id;
    END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_bin ;
/*!50003 DROP PROCEDURE IF EXISTS `open_next_mission` */;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_general_ci ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `open_next_mission`( IN player_id BIGINT UNSIGNED , IN mission_id SMALLINT UNSIGNED , IN time_today_left SMALLINT UNSIGNED , IN chapter_id SMALLINT UNSIGNED )
BEGIN
	INSERT INTO t_mission(f_PlayerID,f_MissionItemID,f_TimesTodayLeft) VALUES(player_id,mission_id,time_today_left);
	UPDATE t_player SET f_CurMission = mission_id WHERE f_ID = player_id;
	UPDATE t_chapter SET f_CurMission = mission_id WHERE f_PlayerID = player_id AND f_ChaperItemID = chapter_id;
    END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_bin ;
/*!50003 DROP PROCEDURE IF EXISTS `refresh_draw_rune` */;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_general_ci ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `refresh_draw_rune`( IN c SMALLINT UNSIGNED )
BEGIN
	UPDATE t_player SET f_DrawRuneLeftCount = c;
    END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_bin ;
/*!50003 DROP PROCEDURE IF EXISTS `refresh_hero` */;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_general_ci ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `refresh_hero`( IN refresh_type INT , IN c SMALLINT UNSIGNED )
BEGIN
	IF refresh_type = 1 THEN
		UPDATE t_player SET f_NormalHireLeftCount = c;
	ELSEIF refresh_type = 2 THEN
		UPDATE t_player SET f_MiddleHireLeftCount = c;
	ELSEIF refresh_type = 3 THEN
		UPDATE t_player SET f_HighHireLeftCount = c;
	END IF;
	
    END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_bin ;
/*!50003 DROP PROCEDURE IF EXISTS `refresh_wine_mask` */;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_general_ci ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `refresh_wine_mask`( IN c SMALLINT UNSIGNED )
BEGIN
	UPDATE t_server_config SET f_LastWineMaskRefreshTime = NOW();
	UPDATE t_activity SET f_WineMask = c;
    END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_bin ;
/*!50003 DROP PROCEDURE IF EXISTS `reset_config` */;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_general_ci ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `reset_config`( )
BEGIN
		
		DELETE FROM t_server_config;
		INSERT INTO t_server_config(f_FirstLunchTime) VALUES(NOW());
    END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_bin ;
/*!50003 DROP PROCEDURE IF EXISTS `reset_mission` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `reset_mission`(IN player_id BIGINT UNSIGNED , IN mission_id SMALLINT UNSIGNED, IN challenge_times SMALLINT UNSIGNED,IN reset_times INT UNSIGNED)
BEGIN
	UPDATE t_mission SET f_TimesTodayLeft = challenge_times , f_ResetTimesToday = reset_times  WHERE f_PlayerID = player_id AND f_MissionItemID = mission_id;
    END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `update_insert_fragment` */;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_general_ci ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `update_insert_fragment`( IN player_id BIGINT UNSIGNED , IN aura_item_id INT , IN num SMALLINT UNSIGNED )
BEGIN
	DECLARE item_id INT DEFAULT 0;
	SELECT f_AuraItemID FROM t_fragment WHERE f_PlayerID = player_id AND f_AuraItemID = aura_item_id INTO item_id;
	IF item_id THEN
	
		UPDATE t_fragment SET f_Num = f_Num + num WHERE f_PlayerID = player_id AND f_AuraItemID = aura_item_id;
	ELSE
	
		INSERT INTO t_fragment(f_PlayerID,f_AuraItemID,f_Num) VALUES(player_id,aura_item_id,num);
	END IF;
    END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_bin ;
/*!50003 DROP PROCEDURE IF EXISTS `update_insert_item` */;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_general_ci ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `update_insert_item`( In player_id BIGINT UNSIGNED , IN item_id INT , IN num INT UNSIGNED)
BEGIN
    
	DECLARE item_id_test INT DEFAULT 0;
	SELECT f_ItemID FROM t_item WHERE f_PlayerID = player_id AND f_ItemID = item_id INTO item_id_test;
	
	IF item_id_test THEN
		
		UPDATE t_item SET f_Num = f_Num + num WHERE f_PlayerID = player_id AND f_ItemID = item_id;
	ELSE
		
		INSERT t_item(f_PlayerID,f_ItemID,f_Num) VALUE(player_id,item_id,num);
	END IF;
	
    END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_bin ;
/*!50003 DROP PROCEDURE IF EXISTS `update_replace_soul` */;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_general_ci ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `update_replace_soul`( IN player_id BIGINT UNSIGNED , IN hero_item_id INT , IN num SMALLINT UNSIGNED )
BEGIN
	DECLARE item_id INT DEFAULT 0;
	SELECT f_HeroItemID FROM t_soul WHERE f_PlayerID = player_id AND f_HeroItemID = hero_item_id INTO item_id;
	IF item_id THEN
		UPDATE t_soul SET f_Num = f_Num + num WHERE f_PlayerID = player_id AND f_HeroItemID = hero_item_id;
	ELSE
		INSERT INTO t_soul(f_PlayerID,f_HeroItemID,f_Num) VALUES(player_id,hero_item_id, num);
	END IF;
    END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
ALTER DATABASE d_game CHARACTER SET utf8 COLLATE utf8_bin ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2014-07-16 17:33:30
