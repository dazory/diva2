# references: https://en.wikipedia.org/wiki/SocketCAN
# chmod +x setSocketCan_test.sh
# sh setSocketCan_test.sh
sudo modprobe can_dev
sudo modprobe can
sudo modprobe can_raw

# sudo modprobe vcan
# sudo ip link add dev vcan0 type vcan
# sudo ip link set up vcan0
# ip link show vcan0

sudo ip link set can0 type can bitrate 500000
sudo ip link set up can0