ifneq ($(strip $(MTK_VOICE_UNLOCK_SUPPORT))_$(strip $(MTK_VOW_SUPPORT)), no_no)
LOCAL_PATH := $(my-dir)

include $(CLEAR_VARS)

ifneq ($(strip $(MTK_VOICE_UNLOCK_USE_TAB_LIB)),yes)
LOCAL_PREBUILT_LIBS := libvoiceunlock.a
endif

ifeq ($(strip $(MTK_VOICE_UNLOCK_USE_TAB_LIB)),yes)
LOCAL_PREBUILT_LIBS := libvoiceunlocktablet.a
endif

include $(BUILD_MULTI_PREBUILT)
endif
