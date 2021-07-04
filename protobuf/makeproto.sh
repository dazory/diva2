# chmod +x makeproto.sh
protoc --cpp_out=./ sensors.proto
protoc --proto_path=./ --python_out=./ sensors.proto
