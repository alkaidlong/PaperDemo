LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := PaperMessage

LOCAL_MODULE_FILENAME := libPaperMessage

#BEGIN_AUTO_GENERATE_SRC_FILES
LOCAL_SRC_FILES :=\
Message/GameMessageFactory.cpp \
Message/IMessageCenter.cpp \
Message/Player.cpp \
Message/Auth/AuthLoginRequest.cpp \
Message/Battle/ChallengeMissionRequest.cpp \
Message/Battle/MissionCheckOutRequest.cpp \
Message/Battle/MissionResetRequest.cpp \
Message/Battle/MissionSweepRequest.cpp \
Message/Battle/PVPCheckAndPlayerDataRequest.cpp \
Message/Custom/BaseCustomGameMessage.cpp \
Message/Logic/AccumlateChargeAwardRequest.cpp \
Message/Logic/AddBloodyBuffRequest.cpp \
Message/Logic/BeginBloodyRequest.cpp \
Message/Logic/BloodyRankListRequest.cpp \
Message/Logic/BloodySettlementRequest.cpp \
Message/Logic/BuyItemRequest.cpp \
Message/Logic/BuyPowerRequest.cpp \
Message/Logic/CardActivityRequest.cpp \
Message/Logic/ChangeAuraRequest.cpp \
Message/Logic/ChangeEquipRequest.cpp \
Message/Logic/ChangeForceIndexRequest.cpp \
Message/Logic/ChangeRuneRequest.cpp \
Message/Logic/CreatePlayerRequest.cpp \
Message/Logic/DrawRuneRequest.cpp \
Message/Logic/DumpPlayerDataRequest.cpp \
Message/Logic/ExchangeAuraRequest.cpp \
Message/Logic/ExchangePVPScoreRequest.cpp \
Message/Logic/ExchangeSoulToHeroRequest.cpp \
Message/Logic/FragmentRobMatchRequest.cpp \
Message/Logic/GetBloodyChallengeGroupRequest.cpp \
Message/Logic/GetCDKPackageRequest.cpp \
Message/Logic/GetChapterAwardRequest.cpp \
Message/Logic/GetMailGiftRequest.cpp \
Message/Logic/GetPVPAwardRequest.cpp \
Message/Logic/GuideFinishRequest.cpp \
Message/Logic/HeroBreakRequest.cpp \
Message/Logic/HeroInheritRequest.cpp \
Message/Logic/HireHeroRequest.cpp \
Message/Logic/OrderRequest.cpp \
Message/Logic/OrderStatusRequest.cpp \
Message/Logic/OtherPlayerDataRequest.cpp \
Message/Logic/PVPForcedHerosRequest.cpp \
Message/Logic/PVPRequest.cpp \
Message/Logic/RankListRequest.cpp \
Message/Logic/RefreshPlayerDataRequest.cpp \
Message/Logic/RefreshPVPScoreRequest.cpp \
Message/Logic/SellEquipRequest.cpp \
Message/Logic/SevenDayGiftRequest.cpp \
Message/Logic/SignActivityRequest.cpp \
Message/Logic/TrainHeroAcceptRequest.cpp \
Message/Logic/TrainHeroRequest.cpp \
Message/Logic/UpgradeActivityRequest.cpp \
Message/Logic/UpgradeEquipRequest.cpp \
Message/Logic/UpgradePetRequest.cpp \
Message/Logic/UpgradeRuneRequest.cpp \
Message/Logic/UpgradeSkillRequest.cpp \
Message/Logic/UseItemRequest.cpp \
Message/Logic/WineActivityRequest.cpp
#END_AUTO_GENERATE_SRC_FILES

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) 
                   
					
LOCAL_C_INCLUDES := $(LOCAL_PATH) 
                  
					
					
LOCAL_WHOLE_STATIC_LIBRARIES := PaperCore

include $(BUILD_STATIC_LIBRARY)

$(call import-module,Common/PaperCore)
