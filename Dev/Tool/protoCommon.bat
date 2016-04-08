::protoc.exe ../../Protocol/Auth/*.proto --proto_path=../../Protocol/Auth/ --cpp_out=../../Client/Project/Paper/Game/Proto/Server/
::protoc.exe ../../Protocol/Logic/*.proto --proto_path=../../Protocol/Logic/ --proto_path=../../Protocol/Auth/ --cpp_out=../../Client/Project/Paper/Game/Proto/Server/
::protoc.exe ../../protocol/logic_proto/*.proto --proto_path=../../protocol/logic_proto/ --cpp_out=../../client/Project/FaceWar/FaceWar/Game/Proto/Server/
::protoc.exe ../../protocol/combat_proto/*.proto --proto_path=../../protocol/auth_proto/ --proto_path=../../protocol/combat_proto/ --cpp_out=../../client/Project/FaceWar/FaceWar/Game/Proto/Server/


::for /r ../../protocol/auth_proto/ %%i in (*.proto) do protoc.exe %%i --proto_path=D:\ --descriptor_set_out=%%icomp
::for /r ../../protocol/logic_proto/ %%i in (*.proto) do protoc.exe %%i --proto_path=D:\ --descriptor_set_out=%%icomp
::for /r ../../protocol/combat_proto/ %%i in (*.proto) do protoc.exe %%i --proto_path=D:\ -proto_path=../combat_proto/ --descriptor_set_out=%%icomp


::protoc.exe ../../Protocol/Auth/LoginToken.proto --proto_path=../../Protocol/Auth/ --cpp_out=../../Client/Project/Paper/Game/Proto/Server/
::protoc.exe ../../Protocol/Logic/PlayerInfo.proto --proto_path=../../Protocol/Logic/ --proto_path=../../Protocol/Auth/ --cpp_out=../../Client/Project/Paper/Game/Proto/Server/
::protoc.exe ../../Protocol/Logic/ServerPlayer.proto --proto_path=../../Protocol/Logic/ --proto_path=../../Protocol/Auth/ --cpp_out=../../Client/Project/Paper/Game/Proto/Server/

::Core
del /f /s /q /a ..\Common\MedusaCore\Core\Proto\Client\*.*
protoc.exe --proto_path=../Common/Proto/Core/ --cpp_out=../Common/MedusaCore/Core/Proto/Client/ ../Common/Proto/Core/AnimationModel.proto
protoc.exe --proto_path=../Common/Proto/Core/ --cpp_out=../Common/MedusaCore/Core/Proto/Client/ ../Common/Proto/Core/AppCompatibility.proto
protoc.exe --proto_path=../Common/Proto/Core/ --cpp_out=../Common/MedusaCore/Core/Proto/Client/ ../Common/Proto/Core/EnvironmentTag.proto
protoc.exe --proto_path=../Common/Proto/Core/ --cpp_out=../Common/MedusaCore/Core/Proto/Client/ ../Common/Proto/Core/FileList.proto
protoc.exe --proto_path=../Common/Proto/Core/ --cpp_out=../Common/MedusaCore/Core/Proto/Client/ ../Common/Proto/Core/FileSystem.proto
protoc.exe --proto_path=../Common/Proto/Core/ --cpp_out=../Common/MedusaCore/Core/Proto/Client/ ../Common/Proto/Core/FileUpdateList.proto
protoc.exe --proto_path=../Common/Proto/Core/ --cpp_out=../Common/MedusaCore/Core/Proto/Client/ ../Common/Proto/Core/FuckyString.proto
protoc.exe --proto_path=../Common/Proto/Core/ --cpp_out=../Common/MedusaCore/Core/Proto/Client/ ../Common/Proto/Core/Geometry.proto
protoc.exe --proto_path=../Common/Proto/Core/ --cpp_out=../Common/MedusaCore/Core/Proto/Client/ ../Common/Proto/Core/LayerEditor.proto
protoc.exe --proto_path=../Common/Proto/Core/ --cpp_out=../Common/MedusaCore/Core/Proto/Client/ ../Common/Proto/Core/RandomName.proto
protoc.exe --proto_path=../Common/Proto/Core/ --cpp_out=../Common/MedusaCore/Core/Proto/Client/ ../Common/Proto/Core/UpdateServer.proto
protoc.exe --proto_path=../Common/Proto/Core/ --cpp_out=../Common/MedusaCore/Core/Proto/Client/ ../Common/Proto/Core/ServerConfig.proto
protoc.exe --proto_path=../Common/Proto/Core/ --cpp_out=../Common/MedusaCore/Core/Proto/Client/ ../Common/Proto/Core/ServerList.proto
protoc.exe --proto_path=../Common/Proto/Core/ --cpp_out=../Common/MedusaCore/Core/Proto/Client/ ../Common/Proto/Core/StringTable.proto
protoc.exe --proto_path=../Common/Proto/Core/ --cpp_out=../Common/MedusaCore/Core/Proto/Client/ ../Common/Proto/Core/CoreDefines.proto
pause

::Client
del /f /s /q /a ..\Common\PaperCore\Proto\Client\*.*
protoc.exe --proto_path=../Common/Proto/Client/ --proto_path=../Common/Proto/Core/ --proto_path=../Common/Proto/Auth/ --proto_path=../Common/Proto/Logic/ --cpp_out=../Common/PaperCore/Proto/Client/ ../Common/Proto/Client/PaperCache.proto
protoc.exe --proto_path=../Common/Proto/Client/ --proto_path=../Common/Proto/Core/ --proto_path=../Common/Proto/Common/ --proto_path=../Common/Proto/Auth/ --proto_path=../Common/Proto/Logic/ --proto_path=../Common/Proto/Config/ --cpp_out=../Common/PaperCore/Proto/Client/ ../Common/Proto/Client/ClientPlayer.proto
pause

::Common
del /f /s /q /a ..\Common\PaperCore\Proto\Server\Common\*.*
pause


::Log
del /f /s /q /a ..\Common\PaperCore\Proto\Server\Log\*.*
pause


::Logic
del /f /s /q /a ..\Common\PaperCore\Proto\Server\Logic\*.*
protoc.exe ../Common/Proto/Logic/BaseProperty.proto --proto_path=../Common/Proto/Logic/ --cpp_out=../Common/PaperCore/Proto/Server/Logic/

pause

del /f /s /q /a ..\Common\PaperCore\Proto\Server\Config\*.*

protoc.exe ../Common/Proto/Config/SkillConfig.proto --proto_path=../Common/Proto/Logic/ --proto_path=../Common/Proto/Config/  --cpp_out=../Common/PaperCore/Proto/Server/Config/
protoc.exe ../Common/Proto/Config/RoleConfig.proto --proto_path=../Common/Proto/Logic/ --proto_path=../Common/Proto/Config/  --cpp_out=../Common/PaperCore/Proto/Server/Config/
protoc.exe ../Common/Proto/Config/BufferConfig.proto --proto_path=../Common/Proto/Logic/ --proto_path=../Common/Proto/Config/  --cpp_out=../Common/PaperCore/Proto/Server/Config/
pause