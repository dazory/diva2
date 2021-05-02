
# Algorithm Testing
각각의 module을 이어서 algorithm test를 수행할 수 있다.

## Module
module은 다음과 같이 구성된다.
- inputs
    - input_datas[]<br>
        e.g., 
        - `input_datas[2]={gps_data, imu_data};`
        - `data[0],data[1]`
- body
    - function<br>
        e.g., <br>
        - `function(input_datas);`
        - `function=KalmanFilter`
    - settings<br>
        e.g.,
        - `function(input_datas, settings);`
        - `argv[0]=GPS, agrv[1]=IMU`
- output
    - output_datas[]<br>
        e.g., 
        - `output_datas[] = function(input_datas, settings);`
        - `
