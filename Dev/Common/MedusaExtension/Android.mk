LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := MedusaExtension

LOCAL_MODULE_FILENAME := libMedusaExtension

#BEGIN_AUTO_GENERATE_SRC_FILES
LOCAL_SRC_FILES :=\
Analytics/Analytics.cpp \
Analytics/android/TalkingDataAnalyzer.cpp \
Analytics/android/UmengAnalyzer.cpp \
Analytics/win/TalkingDataAnalyzer.cpp \
Analytics/win/UmengAnalyzer.cpp \
BusinessPlatform/BusinessPlatformFactory.cpp \
BusinessPlatform/BusinessPlatformLoginEventArg.cpp \
BusinessPlatform/BusinessPlatformPayEventArg.cpp \
BusinessPlatform/DevBusinessPlatform.cpp \
BusinessPlatform/android/NdBusinessPlatform.cpp \
BusinessPlatform/win/NdBusinessPlatform.cpp
#END_AUTO_GENERATE_SRC_FILES

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/Analytics \
					$(LOCAL_PATH)/BusinessPlatform 
					
LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/Analytics \
					$(LOCAL_PATH)/BusinessPlatform 
					
					
LOCAL_WHOLE_STATIC_LIBRARIES := MedusaCore

include $(BUILD_STATIC_LIBRARY)

$(call import-module,Common/MedusaCore)
