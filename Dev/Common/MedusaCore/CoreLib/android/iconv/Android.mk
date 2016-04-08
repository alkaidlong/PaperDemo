LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_CFLAGS := \
  -Wno-multichar \
  -D_ANDROID \
  -DLIBDIR="c" \
  -DBUILDING_LIBICONV \
  -DIN_LIBRARY
  
LOCAL_MODULE := iconv
LOCAL_MODULE_FILENAME := libiconv

LOCAL_SRC_FILES := iconv/iconv.c \
                   iconvcharset/lib/localcharset.c \
                   iconv/relocatable.c

LOCAL_C_INCLUDES += $(LOCAL_PATH)/include \
                    $(LOCAL_PATH)/iconvcharset \
                    $(LOCAL_PATH)/iconvcharset/include

LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/include \
                    $(LOCAL_PATH)/iconvcharset \
                    $(LOCAL_PATH)/iconvcharset/include

include $(BUILD_STATIC_LIBRARY)
