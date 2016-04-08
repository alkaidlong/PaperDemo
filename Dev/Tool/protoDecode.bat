
type ..\Client\Paper\FileList.bin | protoc.exe --decode=Medusa.CoreProto.FileList --proto_path=../Client/Proto/Core/ ../Client/Proto/Core/FileList.proto >..\Client\Paper\FileList.cfg
type ..\Client\Paper\FileSystem.bin | protoc.exe --decode=Medusa.CoreProto.FileSystem --proto_path=../Client/Proto/Core/ ../Client/Proto/Core/FileSystem.proto >..\Client\Paper\FileSystem.cfg


pause