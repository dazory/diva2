
<p align="center">
  <img width="150" align="center" src="https://user-images.githubusercontent.com/81455416/124372597-67521500-dcc6-11eb-99b5-149581fb9451.png" alt="diva2"/>

</p>

<div align="center" style="font-weight:bold;">자율주행차량의 실시간 다중센서데이터 수집·정제·분석 및 관제 통합 플랫폼 개발</div>

---


Manual : https://github.com/dazory/diva2/wiki


<br>


## 📋 Description

| 항목         | 내용                                                         |
| ------------ | ------------------------------------------------------------ |
| 프로젝트명   | 자율주행차량의 실시간 다중센서데이터 수집·정제·분석 및 관제 통합 플랫폼 개발 |
| 기간         | 2020.12.23 ~ 2021.06.18                                      |


<br>


## 🚘 System Configuration

DIVA2의 전체 시스템 구성도는 다음과 같습니다.
<p align="center">
  <img width="700" align="center" src="https://user-images.githubusercontent.com/81455416/124372626-98324a00-dcc6-11eb-98c4-526a60db8b69.png" alt="system-configuration"/>
</p>

- <b>Mobile Platform</b> : 차량에 장착된 PC로, 센서 데이터 취득 및 처리를 담당
- <b>Server</b> : 센서데이터를 통합 관리
- <b>Ground Station</b> : 차량 외부에 위치하며 실시간으로 차량 상태 관제 및 테스트를 담당


<br>


## ✨ Experiments

### ✨ Specifications

실험이 진행된 시스템 환경은 다음과 같습니다.

1. **Mobile Platform**

   ![mobile-platform](https://user-images.githubusercontent.com/81455416/124372603-72a54080-dcc6-11eb-80d9-a8990d7b8329.png)

   

   | **차량**   | 현대 i30                                                     |
   | ---------- | ------------------------------------------------------------ |
   | **카메라** | Logitech  C920                                               |
   | **LiDAR**  | Ouster  3D LiDAR OS1                                         |
   | **IMU**    | Microstrain  3DM-GX5-25                                      |
   | **GPS**    | Ublox  C94 M8P                                               |
   | **CAN**    | i30 내장                                                     |
   | **PC**     | CPU :  Intel® core™ i7-7820HK <br>CPU @2.90GHz  <br>RAM : 8G  <br>GPU :  NVIDIA® GeForce® GTX 1070 |

2. **Server**

   - 3.5GHz의 인텔 코어 i7 프로세서

   - 6개의 물리적 12개의 논리적 코어

   - 256GB의 메모리, 8GB 램

   - 네트워크 대역폭 : 1000Mbps (850Mbps)

     

3. **Ground Station**

   - CPU : Intel i5-1135G7

   - RAM : 16GB DDR4

   - GPU : Intel Iris Xe Graphics



### ✨ Demo

Ground Station의 주요 기능은 다음과 같습니다.
> - <b>Real-time Visualization</b> : Mobile Platform으로부터 실시간으로 데이터를 수신하여 차량의 상태를 시각화
> - <b>Playback</b> : Server에 저장된 데이터를 수신하여 차량의 상태를 시각화
> - <b>Algorithm Test</b> : Server에 저장된 데이터를 이용하여 알고리즘 테스트

1. **Real-time Visualization**

[![realtime-visualization](https://img.youtube.com/vi/LOaPA7vAb78/0.jpg)](https://youtu.be/LOaPA7vAb78?t=0s)

2. **Playback**

[![playback](https://img.youtube.com/vi/aTknWwIAsPE/0.jpg)](https://youtu.be/aTknWwIAsPE?t=0s)

3. **Algorithm Test**

   <p align="center">
     <img width="700" align="center" src="./storage/algorithm-test.gif" alt="algorithm-test"/>
   </p>


<br>


## 📁 Document Structure

```
├─ diva2
│  │  README.md
│  ├─ MobilePlatform
│  │      ├─ Sensing
│  │      └─ Visualization
│  ├─ Server
│  │      ├─ TimeSynchronization
│  │      └─ DBStoring
│  ├─ GroundStation
│  │      ├─ Playback
│  │      ├─ Visualization
│  │      └─ AlgorithmTest
│  ├─ build
│  └─ service
│          이미지
│          이미지
```

<br>


## 🚀 Usage

### 🚀Prerequisites

|       항목        |                             내용                             |
| :---------------: | :----------------------------------------------------------: |
|     개발환경      |                    Linux Ubuntu 18.04 LTS                    |
|  GUI 개발 플랫폼  |                          QT 5.12.5                           |
| 라이브러리·API 등 | [QT 5.12.5, CMake 3.10.2, OpenCV 3.2.0, OpenGL 4.4, QTI-4.0.47, PCL 1.11.1, VTK 7.1, mscl, PostgreSQL 10.17, protobuf 3.17.3,PostgreSQL 10.17 , tomcat*, zeromq, libmscl , libusb 1.0, flann 1.8, eigen3, boost, qhull*, freeglut3, protobuf 3.17.3, libpqxx, expect](https://www.notion.so/API-25736c98854646f28a9d14996fa229fb)  |



### 🚀 Run

1. Download and unzip [diva2](https://github.com/dazory/diva2/archive/refs/heads/main.zip) from this repository : https://github.com/dazory/diva2

2. ```shell
   cd diva2
   mkdir build && cd build
   cmake ..
   make
   ```

3. Now, you can see the executable files in each directory ...

   * Mobile Platform

     * Sensing

       ```shell
       cd diva2/build/MobilePlatform/Sensing
       ./MP_Sensing
       ```

     * Visualization

       ```shell
       cd diva2/build/MobilePlatform/Visualization
       ./MP_visualization
       ```

   * Server
 
     * TimeSynchronization

       ```shell
       cd diva2/build/Server/TimeSynchronization
       ./timesynchronization
       ```
       
     * DBStoring

       ```shell
       cd diva2/build/Server/DBStoring
       ./dbstoring
       ```


   * Ground Station

     * Algorithm
        [wiki](https://github.com/dazory/diva2/wiki/Ground-Station-Algorithm-Test) 확인 바람
     





## 🤝 Contributing

| <img src="https://avatars.githubusercontent.com/u/81455416?v=4" alt="img" style="zoom:25%;" /> | <img src="https://avatars.githubusercontent.com/u/77493215?s=48&v=4" alt="@ka-yeon" style="zoom:25%;" /> | <img src="https://avatars.githubusercontent.com/u/77220012?v=4" alt="Avatar" style="zoom:25%;" /> | <img src="https://avatars.githubusercontent.com/u/60495897?v=4" alt="Avatar" style="zoom:25%;" /> |
| ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| [dazory](https://github.com/dazory)                          | [ka-yeon](https://github.com/ka-yeon)                        | [airpod2](https://github.com/airpod2)                        | [yuntreee](https://github.com/yuntreee)                      |

and Thanks to [DIVA](https://github.com/kka-na/DIVA_QT) for the advance study.





## 📝 License



---

This file is generated by [dazory](https://github.com/dazory)
