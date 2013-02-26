##################################################################
# author: Richard Luo                      
# date:   2012-05-08 19:56:40
#                                                                
##################################################################

LOCAL_PATH:= $(call my-dir)

source_files := $(wildcard $(LOCAL_PATH)/*.cpp)
source_files := $(patsubst $(LOCAL_PATH)/%,%,$(source_files))

include $(CLEAR_VARS)

LOCAL_MODULE := coho_list_test

LOCAL_SRC_FILES := $(source_files)

# LOCAL_C_FLAGS += -Winvalid-offsetof
# LOCAL_CFLAGS += -Wno-invalid-offsetof 

# LOCAL_C_INCLUDES += $(LOCAL_PATH)/include
LOCAL_C_INCLUDES += external/coho
# LOCAL_C_INCLUDES += frameworks/X-Live/src/common/xutils/include


LOCAL_SHARED_LIBRARIES += libcutils
LOCAL_SHARED_LIBRARIES += libutils 
LOCAL_SHARED_LIBRARIES += liblog

ifneq ($(TARGET_SIMULATOR),true)
LOCAL_C_INCLUDES += external/stlport/stlport 
LOCAL_C_INCLUDES += bionic		# very important!
LOCAL_SHARED_LIBRARIES += libstlport
endif

LOCAL_PRELINK_MODULE := false

LOCAL_MODULE_TAGS := eng

include $(BUILD_EXECUTABLE)
