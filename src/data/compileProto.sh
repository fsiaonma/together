protoc --proto_path=./ --cpp_out=./compiledData/ ./Response.proto 
protoc --proto_path=./ --cpp_out=./compiledData/ ./UserResponse.proto
protoc --proto_path=./ --cpp_out=./compiledData/ ./UserData.proto
protoc --proto_path=./ --cpp_out=./compiledData/ ./RoomResponse.proto
protoc --proto_path=./ --cpp_out=./compiledData/ ./RoomData.proto
protoc --proto_path=./ --cpp_out=./compiledData/ ./MessageData.proto
protoc --proto_path=./ --cpp_out=./compiledData/ ./data.proto

