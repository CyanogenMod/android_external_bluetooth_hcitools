LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := hcitool
LOCAL_SRC_FILES := hcitool.c
LOCAL_C_INCLUDES := $(KERNEL_HEADERS) $(LOCAL_PATH)/lib
LOCAL_MODULE_TAGS := optional
LOCAL_STATIC_LIBRARIES := libbluez
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_MODULE := hciconfig
LOCAL_SRC_FILES := hciconfig.c csr.c
LOCAL_C_INCLUDES := $(KERNEL_HEADERS) $(LOCAL_PATH)/lib
LOCAL_MODULE_TAGS := optional
LOCAL_STATIC_LIBRARIES := libbluez
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_MODULE := libbluez
LOCAL_SRC_FILES := lib/bluetooth.c lib/hci.c lib/sdp.c
LOCAL_C_INCLUDES := $(LOCAL_PATH)/lib
include $(BUILD_STATIC_LIBRARY)

HCITOOLS_GPL_SRC_TARGET: $(HOST_OUT_EXECUTABLES)/pigz
	@echo "Copying hcitools source code to system/vendor/gpl"
	@mkdir -p $(TARGET_OUT)/vendor/gpl
	tar --exclude=".git" -cf  $(TARGET_OUT)/vendor/gpl/hcitools.tar external/bluetooth/hcitools
	$(HOST_OUT_EXECUTABLES)/pigz -9 -f --no-time -R $(TARGET_OUT)/vendor/gpl/hcitools.tar

ALL_DEFAULT_INSTALLED_MODULES += HCITOOLS_GPL_SRC_TARGET
