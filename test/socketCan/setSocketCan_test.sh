# references: https://en.wikipedia.org/wiki/SocketCAN
# chmod +x setSocketCan_test.sh
# sh setSocketCan_test.sh
modprobe can
modprobe can_raw
modprobe vcan
# sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0
ip link show vcan0