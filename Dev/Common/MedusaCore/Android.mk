LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := MedusaCore

LOCAL_MODULE_FILENAME := libMedusaCore

#BEGIN_AUTO_GENERATE_SRC_FILES
LOCAL_SRC_FILES :=\
Core/Algorithm/Pack/GuillotineBinPack.cpp \
Core/Algorithm/Pack/SkylineBinPack.cpp \
Core/Coder/CoderFactory.cpp \
Core/Coder/LZMA/LZMADecoder.cpp \
Core/Coder/LZMA/LZMAEncoder.cpp \
Core/Coder/XOR/XORDecoder.cpp \
Core/Coder/XOR/XOREncoder.cpp \
Core/Coder/XXTEA/XXTEAEncryptor.cpp \
Core/Compress/ZipReader.cpp \
Core/Config/ServerConfig.cpp \
Core/Config/ServerList.cpp \
Core/Event/ThreadEventDispatcher.cpp \
Core/Event/UIEventDispatcher.cpp \
Core/Event/EventArg/IEventArg.cpp \
Core/Event/Trigger/ITrigger.cpp \
Core/Geometry/Color3.cpp \
Core/Geometry/Color4.cpp \
Core/Geometry/EulerAngle.cpp \
Core/Geometry/GeometryFactory.cpp \
Core/Geometry/Matrix2.cpp \
Core/Geometry/Matrix3.cpp \
Core/Geometry/Matrix4.cpp \
Core/Geometry/Matrix43.cpp \
Core/Geometry/Quaternion.cpp \
Core/Geometry/Moveable/DefaultMoveable.cpp \
Core/Geometry/Moveable/TransformMoveable.cpp \
Core/Geometry/Transform/TransformFactory.cpp \
Core/IO/Directory.cpp \
Core/IO/File.cpp \
Core/IO/FileId.cpp \
Core/IO/FileIdStorage.cpp \
Core/IO/FileInfo.cpp \
Core/IO/Path.cpp \
Core/IO/FileList/FileCoderList.cpp \
Core/IO/FileList/FileList.cpp \
Core/IO/FileSystem/FileSystem.cpp \
Core/IO/FileSystem/FileSystemNameItem.cpp \
Core/IO/FileSystem/FileSystemOrderItem.cpp \
Core/IO/FileSystem/FileSystemTagItem.cpp \
Core/IO/FileSystem/Accessor/IFileSystemAccessor.cpp \
Core/IO/FileSystem/Accessor/android/AndroidFileSystemAccessor.cpp \
Core/IO/FileSystem/Accessor/posix/PosixFileSystemAccessor.cpp \
Core/IO/Pack/Package.cpp \
Core/IO/Pack/PackageFile.cpp \
Core/IO/Pack/PackageHeader.cpp \
Core/IO/Stream/FileStream.cpp \
Core/IO/Stream/IStream.cpp \
Core/IO/Stream/MemoryStream.cpp \
Core/IO/Stream/ProxyStream.cpp \
Core/IO/Updater/FileUpdater.cpp \
Core/Log/CallbackLogger.cpp \
Core/Log/FileLogger.cpp \
Core/Log/ILogger.cpp \
Core/Log/Log.cpp \
Core/Log/android/AndroidTraceLogger.cpp \
Core/Log/linux/LinuxConsoleLogger.cpp \
Core/Log/win/WindowsConsoleLogger.cpp \
Core/Log/win/WindowsTraceLogger.cpp \
Core/Math/MathHeader.cpp \
Core/Math/MathStrategy.cpp \
Core/Math/Random.cpp \
Core/Math/Model/IScrollMathModel.cpp \
Core/Math/Model/SpringScrollMathModel.cpp \
Core/Message/BaseCustomMessage.cpp \
Core/Message/IMessage.cpp \
Core/Message/MessageDispatcher.cpp \
Core/Message/MessageEventArg.cpp \
Core/Message/Handler/IMessageHandler.cpp \
Core/Message/Handler/MockMessageHandler.cpp \
Core/Message/Handler/TcpMessageHandler.cpp \
Core/Net/HTTP/HTTPClient.cpp \
Core/Net/HTTP/HTTPFileDownloader.cpp \
Core/Net/HTTP/HTTPMemoryDownloader.cpp \
Core/Net/HTTP/IHTTPDownloader.cpp \
Core/Net/Socket/ISocket.cpp \
Core/Pattern/DefaultRunnable.cpp \
Core/Pattern/DeprecationManager.cpp \
Core/Pattern/ILoadable.cpp \
Core/Pattern/Component/ComponentCache.cpp \
Core/Pattern/Component/ComponentList.cpp \
Core/Pattern/Component/IComponent.cpp \
Core/Pattern/Dependency/DependencyEffectiveValue.cpp \
Core/Pattern/Dependency/DependencyObject.cpp \
Core/Pattern/Dependency/DependencyProperty.cpp \
Core/Pattern/Dependency/DependencyPropertyMetaData.cpp \
Core/Pattern/Property/PropertyChangedEventArg.cpp \
Core/Pattern/RTTI/RTTIClass.cpp \
Core/Pattern/RTTI/RTTIObject.cpp \
Core/Profile/AutoStopWatch.cpp \
Core/Profile/ProfileManager.cpp \
Core/Profile/ProfileNode.cpp \
Core/Profile/StopWatch.cpp \
Core/Proto/Client/AnimationModel.pb.cc \
Core/Proto/Client/AppCompatibility.pb.cc \
Core/Proto/Client/CoreDefines.pb.cc \
Core/Proto/Client/EnvironmentTag.pb.cc \
Core/Proto/Client/FileList.pb.cc \
Core/Proto/Client/FileSystem.pb.cc \
Core/Proto/Client/FileUpdateList.pb.cc \
Core/Proto/Client/FuckyString.pb.cc \
Core/Proto/Client/Geometry.pb.cc \
Core/Proto/Client/LayerEditor.pb.cc \
Core/Proto/Client/RandomName.pb.cc \
Core/Proto/Client/ServerConfig.pb.cc \
Core/Proto/Client/ServerList.pb.cc \
Core/Proto/Client/StringTable.pb.cc \
Core/Proto/Client/UpdateServer.pb.cc \
Core/Script/ScriptManager.cpp \
Core/Script/ScriptModule.cpp \
Core/Script/ScriptObject.cpp \
Core/String/StringParser.cpp \
Core/String/FuckyString/FuckyString.cpp \
Core/String/FuckyString/FuckyStringNode.cpp \
Core/String/RandomName/RandomName.cpp \
Core/String/StringTable/StringNameItem.cpp \
Core/String/StringTable/StringOrderItem.cpp \
Core/String/StringTable/StringTable.cpp \
Core/System/EnvironmentTag.cpp \
Core/System/android/Environment.cpp \
Core/System/android/System.cpp \
Core/System/ios/wwanconnect.cc \
Core/System/linux/Environment.cpp \
Core/System/linux/System.cpp \
Core/System/win/Environment.cpp \
Core/System/win/System.cpp \
Core/Utility/DateTime.cpp \
Core/Utility/Guid.cpp \
Core/Utility/HashUtility.cpp \
Core/Utility/MD5.cpp \
Core/Utility/TimeSpan.cpp \
Core/Utility/Utility.cpp \
Core/Utility/Version.cpp \
CoreLib/Common/angelscript/add_on/autowrapper/generateheader.cpp \
CoreLib/Common/angelscript/add_on/contextmgr/contextmgr.cpp \
CoreLib/Common/angelscript/add_on/debugger/debugger.cpp \
CoreLib/Common/angelscript/add_on/scriptany/scriptany.cpp \
CoreLib/Common/angelscript/add_on/scriptarray/scriptarray.cpp \
CoreLib/Common/angelscript/add_on/scriptbuilder/scriptbuilder.cpp \
CoreLib/Common/angelscript/add_on/scriptdictionary/scriptdictionary.cpp \
CoreLib/Common/angelscript/add_on/scriptfile/scriptfile.cpp \
CoreLib/Common/angelscript/add_on/scriptgrid/scriptgrid.cpp \
CoreLib/Common/angelscript/add_on/scripthandle/scripthandle.cpp \
CoreLib/Common/angelscript/add_on/scripthelper/scripthelper.cpp \
CoreLib/Common/angelscript/add_on/scriptmath/scriptmath.cpp \
CoreLib/Common/angelscript/add_on/scriptmath/scriptmathcomplex.cpp \
CoreLib/Common/angelscript/add_on/scriptstdstring/scriptstdstring.cpp \
CoreLib/Common/angelscript/add_on/scriptstdstring/scriptstdstring_utils.cpp \
CoreLib/Common/angelscript/add_on/serializer/serializer.cpp \
CoreLib/Common/angelscript/add_on/weakref/weakref.cpp \
CoreLib/Common/angelscript/source/as_atomic.cpp \
CoreLib/Common/angelscript/source/as_builder.cpp \
CoreLib/Common/angelscript/source/as_bytecode.cpp \
CoreLib/Common/angelscript/source/as_callfunc.cpp \
CoreLib/Common/angelscript/source/as_callfunc_arm.cpp \
CoreLib/Common/angelscript/source/as_callfunc_arm_gcc.S \
CoreLib/Common/angelscript/source/as_callfunc_arm_xcode.S \
CoreLib/Common/angelscript/source/as_callfunc_mips.cpp \
CoreLib/Common/angelscript/source/as_callfunc_ppc.cpp \
CoreLib/Common/angelscript/source/as_callfunc_ppc_64.cpp \
CoreLib/Common/angelscript/source/as_callfunc_sh4.cpp \
CoreLib/Common/angelscript/source/as_callfunc_x64_gcc.cpp \
CoreLib/Common/angelscript/source/as_callfunc_x64_mingw.cpp \
CoreLib/Common/angelscript/source/as_callfunc_x64_msvc.cpp \
CoreLib/Common/angelscript/source/as_callfunc_x86.cpp \
CoreLib/Common/angelscript/source/as_callfunc_xenon.cpp \
CoreLib/Common/angelscript/source/as_compiler.cpp \
CoreLib/Common/angelscript/source/as_configgroup.cpp \
CoreLib/Common/angelscript/source/as_context.cpp \
CoreLib/Common/angelscript/source/as_datatype.cpp \
CoreLib/Common/angelscript/source/as_gc.cpp \
CoreLib/Common/angelscript/source/as_generic.cpp \
CoreLib/Common/angelscript/source/as_globalproperty.cpp \
CoreLib/Common/angelscript/source/as_memory.cpp \
CoreLib/Common/angelscript/source/as_module.cpp \
CoreLib/Common/angelscript/source/as_objecttype.cpp \
CoreLib/Common/angelscript/source/as_outputbuffer.cpp \
CoreLib/Common/angelscript/source/as_parser.cpp \
CoreLib/Common/angelscript/source/as_restore.cpp \
CoreLib/Common/angelscript/source/as_scriptcode.cpp \
CoreLib/Common/angelscript/source/as_scriptengine.cpp \
CoreLib/Common/angelscript/source/as_scriptfunction.cpp \
CoreLib/Common/angelscript/source/as_scriptnode.cpp \
CoreLib/Common/angelscript/source/as_scriptobject.cpp \
CoreLib/Common/angelscript/source/as_string.cpp \
CoreLib/Common/angelscript/source/as_string_util.cpp \
CoreLib/Common/angelscript/source/as_thread.cpp \
CoreLib/Common/angelscript/source/as_tokenizer.cpp \
CoreLib/Common/angelscript/source/as_typeinfo.cpp \
CoreLib/Common/angelscript/source/as_variablescope.cpp \
CoreLib/Common/google/protobuf/descriptor.cc \
CoreLib/Common/google/protobuf/descriptor.pb.cc \
CoreLib/Common/google/protobuf/descriptor_database.cc \
CoreLib/Common/google/protobuf/dynamic_message.cc \
CoreLib/Common/google/protobuf/extension_set.cc \
CoreLib/Common/google/protobuf/extension_set_heavy.cc \
CoreLib/Common/google/protobuf/generated_message_reflection.cc \
CoreLib/Common/google/protobuf/generated_message_util.cc \
CoreLib/Common/google/protobuf/message.cc \
CoreLib/Common/google/protobuf/message_lite.cc \
CoreLib/Common/google/protobuf/reflection_ops.cc \
CoreLib/Common/google/protobuf/repeated_field.cc \
CoreLib/Common/google/protobuf/service.cc \
CoreLib/Common/google/protobuf/text_format.cc \
CoreLib/Common/google/protobuf/unknown_field_set.cc \
CoreLib/Common/google/protobuf/wire_format.cc \
CoreLib/Common/google/protobuf/wire_format_lite.cc \
CoreLib/Common/google/protobuf/io/coded_stream.cc \
CoreLib/Common/google/protobuf/io/gzip_stream.cc \
CoreLib/Common/google/protobuf/io/printer.cc \
CoreLib/Common/google/protobuf/io/tokenizer.cc \
CoreLib/Common/google/protobuf/io/zero_copy_stream.cc \
CoreLib/Common/google/protobuf/io/zero_copy_stream_impl.cc \
CoreLib/Common/google/protobuf/io/zero_copy_stream_impl_lite.cc \
CoreLib/Common/google/protobuf/stubs/atomicops_internals_x86_gcc.cc \
CoreLib/Common/google/protobuf/stubs/atomicops_internals_x86_msvc.cc \
CoreLib/Common/google/protobuf/stubs/common.cc \
CoreLib/Common/google/protobuf/stubs/once.cc \
CoreLib/Common/google/protobuf/stubs/stringprintf.cc \
CoreLib/Common/google/protobuf/stubs/structurally_valid.cc \
CoreLib/Common/google/protobuf/stubs/strutil.cc \
CoreLib/Common/google/protobuf/stubs/substitute.cc \
CoreLib/Common/google/protobuf/testing/file.cc \
CoreLib/Common/google/protobuf/testing/googletest.cc \
CoreLib/Common/Unicode/ConvertUTF.cpp \
CoreLib/Common/zip/ioapi.cpp \
CoreLib/Common/zip/mztools.cpp \
CoreLib/Common/zip/unzip.cpp \
CoreLib/Common/zip/zip.cpp \
CoreLib/Common/7z/LzFind.c \
CoreLib/Common/7z/Lzma2Dec.c \
CoreLib/Common/7z/Lzma2Enc.c \
CoreLib/Common/7z/LzmaDec.c \
CoreLib/Common/7z/LzmaEnc.c \
CoreLib/android/uuid/clear.c \
CoreLib/android/uuid/compare.c \
CoreLib/android/uuid/copy.c \
CoreLib/android/uuid/gen_uuid.c \
CoreLib/android/uuid/isnull.c \
CoreLib/android/uuid/pack.c \
CoreLib/android/uuid/parse.c \
CoreLib/android/uuid/unpack.c \
CoreLib/android/uuid/unparse.c \
CoreLib/android/uuid/uuid_time.c
#END_AUTO_GENERATE_SRC_FILES

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
					$(LOCAL_PATH)/Core/Proto/Client \
                    $(LOCAL_PATH)/CoreLib/Common \
					$(LOCAL_PATH)/CoreLib/Common/zlib \
					$(LOCAL_PATH)/CoreLib/Common/zip \
					$(LOCAL_PATH)/CoreLib/Common/angelscript/include

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
					$(LOCAL_PATH)/Core/Proto/Client \
                    $(LOCAL_PATH)/CoreLib/Common \
					$(LOCAL_PATH)/CoreLib/Common/zlib \
					$(LOCAL_PATH)/CoreLib/Common/zip \
					$(LOCAL_PATH)/CoreLib/Common/angelscript/include
					
LOCAL_LDLIBS := -lGLESv2 \
                -llog \
                -lz

LOCAL_EXPORT_LDLIBS := -lGLESv2 \
						-llog \
						-lz
					   
LOCAL_CFLAGS += -std=c++11
LOCAL_CFLAGS    +=  -D_GLIBCXX_PERMIT_BACKWARD_HASH -DDEBUG

LOCAL_CPPFLAGS += -fexceptions
LOCAL_CPPFLAGS += -DUSE_FILE32API -DDEBUG

LOCAL_EXPORT_CFLAGS += -std=c++11
LOCAL_EXPORT_CFLAGS    +=  -D_GLIBCXX_PERMIT_BACKWARD_HASH  -DDEBUG

LOCAL_EXPORT_CPPFLAGS += -fexceptions
LOCAL_EXPORT_CPPFLAGS += -DUSE_FILE32API -DDEBUG

LOCAL_WHOLE_STATIC_LIBRARIES := iconv
LOCAL_WHOLE_STATIC_LIBRARIES += curl



include $(BUILD_STATIC_LIBRARY)


$(call import-module,Common/MedusaCore/CoreLib/android/iconv)
$(call import-module,Common/MedusaCore/CoreLib/android/libcurl)
