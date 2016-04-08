::server

type ..\Client\Paper\FileList.cfg | protoc.exe --encode=Medusa.CoreProto.FileList --proto_path=../Client/Proto/Core/ ../Client/Proto/Core/FileList.proto >..\Client\Paper\FileList.bin
type ..\Client\Paper\FileSystem.cfg | protoc.exe --encode=Medusa.CoreProto.FileSystem --proto_path=../Client/Proto/Core/ ../Client/Proto/Core/FileSystem.proto >..\Client\Paper\FileSystem.bin

pause