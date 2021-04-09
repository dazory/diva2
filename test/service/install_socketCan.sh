#########################################################
# references
#   - https://wiki.linklayer.com/index.php/SocketCAN
#########################################################

# Ubuntu의 경우 필요한 kernel module은 이미 포함되어있지만, can-utils는 추가로 설치해주어야 함
sudo apt-get install can-utils

# 관련된 커널모듈을 사용가능하게 만듦
sudo modprobe can
sudo modprobe vcan
sudo modprobe slcan
sudo modprobe can_dev # what?
sudo modprobe can_raw # what?

## SocketCAN with CANtact ##
# SocketCAN에서 CANtact을 사용하기 위해 slcand가 필요하다. 
# 아래 예시는 /dev/ttyACM0에 있는 CANtact과 연결되는 can0이라는 이름을 가진 새로운 device를 생성하는 command이다.
# -o가 시작될 때 device가 열리고, -c가 끝날 때 device가 종료되며, -s6으로 speed mode를 설정할 수 있다.
sudo slcan -o -c -s6 /dev/ttyACM0 can0
# device가 연결된 후, interface를 사용가능하게 허용
sudo ifconfig can0 up

## Virtual CAN Devices ##
# virtual CAN devices, 혹은 vcan devices는 어떤 하드웨어 없이 CAN bus를 시뮬레이션하는 데에 사용된다.
# 시뮬레이션, 테스트, bridging에 유용하다.
# 또한 실제 CAN device없이 can-utils를 사용할 수 있게 해준다.
sudo ip link set can0 type can bitrate 500000
sudo ip link set up can0
# or
sudo ip link add name vcan0 type vcan
sudo ip link set up vcan0
ip link show vcan0

## SocketCAN Utilities
# device가 사용가능 상태가 되면, 몇 가지 utilities를 사용할 수 있게 된다.
    ## candump
    # 실시간으로 bus에 있는 messages를 출력해줌
    # 실시간으로 device can0ㅔ 있는 모든 트래픽이 보고싶다면 아래 커맨드 실행:
    candump can0

### 그 외의 자세한 내용은 위 references 참고하길.
