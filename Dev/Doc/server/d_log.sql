-- MySQL dump 10.13  Distrib 5.5.8, for Win32 (x86)
--
-- Host: 10.208.11.131    Database: d_log
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
-- Current Database: `d_log`
--

/*!40000 DROP DATABASE IF EXISTS `d_log`*/;

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `d_log` /*!40100 DEFAULT CHARACTER SET utf8 */;

USE `d_log`;

--
-- Table structure for table `t_message_log`
--

DROP TABLE IF EXISTS `t_message_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_message_log` (
  `f_PlayerAccount` varchar(128) DEFAULT NULL,
  `f_TimeStamp` int(10) unsigned DEFAULT NULL,
  `f_PlayerID` bigint(20) unsigned DEFAULT NULL,
  `f_PlayerName` varchar(128) DEFAULT NULL,
  `f_MsgName` enum('DumpPlayerDataRequest','CreatePlayerRequest','ChangeAuraRequest','UpgradeSkillRequest','ChangeEquipRequest','SellEquipRequest','UpgradeEquipRequest','ChangeForceIndexRequest','ExchangeSoulToHeroRequest','HeroBreakRequest','HeroInheritRequest','HireHeroRequest','TrainHeroRequest','TrainHeroAcceptRequest','BuyItemRequest','UseItemRequest','GetMailGiftRequest','RefreshPlayerDataRequest','ChallengeMissionRequest','MissionCheckOutRequest','UpgradePetRequest','PVPRequest','ExchangeAuraRequest','ExchangePVPScoreRequest','PVPForcedHerosRequest','FragmentRobMatchRequest','GetPVPAwardRequest','OtherPlayerDataRequest','RankListRequest','RefreshPVPScoreRequest','ChangeRuneRequest','DrawRuneRequest','UpgradeRuneRequest') DEFAULT NULL,
  `f_ResCode` int(11) DEFAULT NULL,
  `f_Elapsed` double DEFAULT NULL,
  `f_Forward` varchar(1024) DEFAULT NULL,
  `f_Post` varchar(1024) DEFAULT NULL,
  `f_Specific` varchar(1024) DEFAULT NULL,
  `f_item_type` int(11) DEFAULT NULL,
  `f_item_id` int(10) unsigned DEFAULT NULL,
  `f_item_uuid` bigint(20) unsigned DEFAULT NULL,
  `f_int32_0` int(11) DEFAULT NULL,
  `f_int32_1` int(11) DEFAULT NULL,
  `f_int32_2` int(11) DEFAULT NULL,
  `f_int32_3` int(11) DEFAULT NULL,
  `f_int32_4` int(11) DEFAULT NULL,
  `f_int32_5` int(11) DEFAULT NULL,
  `f_int32_6` int(11) DEFAULT NULL,
  `f_int32_7` int(11) DEFAULT NULL,
  `f_int32_8` int(11) DEFAULT NULL,
  `f_int32_9` int(11) DEFAULT NULL,
  `f_int64_0` bigint(20) DEFAULT NULL,
  `f_int64_1` bigint(20) DEFAULT NULL,
  `f_int64_2` bigint(20) DEFAULT NULL,
  `f_int64_3` bigint(20) DEFAULT NULL,
  `f_int64_4` bigint(20) DEFAULT NULL,
  `f_int64_5` bigint(20) DEFAULT NULL,
  `f_int64_6` bigint(20) DEFAULT NULL,
  `f_int64_7` bigint(20) DEFAULT NULL,
  `f_int64_8` bigint(20) DEFAULT NULL,
  `f_int64_9` bigint(20) DEFAULT NULL,
  `f_float_0` float DEFAULT NULL,
  `f_float_1` float DEFAULT NULL,
  `f_float_2` float DEFAULT NULL,
  `f_float_3` float DEFAULT NULL,
  `f_float_4` float DEFAULT NULL,
  `f_float_5` float DEFAULT NULL,
  `f_float_6` float DEFAULT NULL,
  `f_float_7` float DEFAULT NULL,
  `f_float_8` float DEFAULT NULL,
  `f_float_9` float DEFAULT NULL,
  `f_string_0` varchar(1024) DEFAULT NULL,
  `f_string_1` varchar(1024) DEFAULT NULL,
  `f_string_2` varchar(1024) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping routines for database 'd_log'
--
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2014-07-16 17:33:30
