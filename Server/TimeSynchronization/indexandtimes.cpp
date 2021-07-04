// 참고: https://github.com/kka-na/DIVA_Qt

#include "indexandtimes.h"

IndexAndTimes::IndexAndTimes(string fpath)
{
    dir = fpath;
    rf = new ReadFiles(fpath);
    gps_csv = rf->read_csv(rf->get_path(is_GPS));
    cam_csv = rf->read_csv(rf->get_path(is_CAM));
    lidar_csv = rf->read_csv(rf->get_path(is_LiDAR));
    imu_csv = rf->read_csv(rf->get_path(is_IMU));
    can_csv = rf->read_csv(rf->get_path(is_CAN));
}

int IndexAndTimes::get_hhmmsssss(string str){ return stoi(str.substr(8,9));}

int IndexAndTimes::find_cam_idx_by_ts(int now, string comp_timestamp){
    int cam_start_idx = now;
    for(int i=now; i<int(cam_csv.size()); i++){
        int difference = get_hhmmsssss(comp_timestamp) - get_hhmmsssss(cam_csv[i][0]);
        if(difference<0) difference = -difference;
        if(difference <= 60){ //20hz
            cam_start_idx = i;
            break;
        }
    }
    return cam_start_idx;
}

int IndexAndTimes::find_lidar_idx_by_ts(int now, string comp_timestamp){
    int lidar_start_idx = 0;
    for(int i=now; i<int(lidar_csv.size()); i++){
        int difference = get_hhmmsssss(comp_timestamp) - get_hhmmsssss(lidar_csv[i][0]);
        if(difference<0) difference = - difference;
        if(difference <= 110){ //10hz
            lidar_start_idx = i;
            break;
        }
    }
    return lidar_start_idx;

}

int IndexAndTimes::find_gps_idx_by_ts(int now, string comp_timestamp){
    int gps_start_idx = now;
    for(int i=now; i<gps_csv.size(); i++){
        int difference = get_hhmmsssss(comp_timestamp) - get_hhmmsssss(gps_csv[i][0]);
        if(difference < 0) difference = - difference;
        if(difference <= 110){ //10hz
            gps_start_idx = i;
            break;
        }
    }
    return gps_start_idx;
}

int IndexAndTimes::find_imu_idx_by_ts(int now, string comp_timestamp){
    int imu_start_idx = now;
    for(int i=now; i<imu_csv.size(); i++){
        int difference = get_hhmmsssss(comp_timestamp) - get_hhmmsssss(imu_csv[i][0]);
        if(difference < 0) difference = -difference;
        if(difference <= 110){ //about 10hz 
            imu_start_idx = i;
            break;
        }
    }
    return imu_start_idx;
}

int IndexAndTimes::find_can_idx_by_ts(int now, string comp_timestamp){
    int can_start_idx = now;
    for(int i=now; i<can_csv.size(); i++){
        int difference = get_hhmmsssss(comp_timestamp) - get_hhmmsssss(can_csv[i][0]);
        if(difference<0) difference = -difference;
        if(difference <= 260){//about 4hz
            can_start_idx = i;
            break;
        }
    }
    return can_start_idx;
}


int IndexAndTimes::find_cam_start_idx(){
    int cam_start_idx = 0;
    for(int i=0; i<cam_csv.size(); i++){
        int difference = s_ts - get_hhmmsssss(cam_csv[i][0]);
        if(difference < 0 && -difference <= 60){
            cam_start_idx = i;
            break;
        }
    }
    return cam_start_idx;

}

int IndexAndTimes::find_lidar_start_idx(){
    int lidar_start_idx = 0;
    for(int i=0; i<lidar_csv.size(); i++){
        int difference = s_ts - get_hhmmsssss(lidar_csv[i][0]);
        if(difference < 0 && -difference <= 110){
            lidar_start_idx = i;
            break;
        }
    }
    return lidar_start_idx;

}

int IndexAndTimes::find_gps_start_idx(){
    int gps_start_idx = 0;
    for(int i=0; i<gps_csv.size(); i++){
        int difference = s_ts - get_hhmmsssss(gps_csv[i][0]);
        if(difference < 0 && -difference <= 110){
            gps_start_idx = i;
            break;
        }
    }
    return gps_start_idx;
}
int IndexAndTimes::find_imu_start_idx(){
    int imu_start_idx = 0;
    for(int i=0; i<imu_csv.size(); i++){
        int difference = s_ts - get_hhmmsssss(imu_csv[i][0]);
        if(difference < 0 && -difference <= 45){
            imu_start_idx = i;
            break;
        }
    }
    return imu_start_idx;
}
int IndexAndTimes::find_can_start_idx(){
    int can_start_idx = 0;
    for(int i=0; i<can_csv.size(); i++){
        int difference = s_ts - get_hhmmsssss(can_csv[i][0]);
        if(difference < 0 && -difference <= 60){
            can_start_idx = i;
            break;
        }
    }
    return can_start_idx;
}


string IndexAndTimes::find_latest_started(){
    int first_timestamps[number_of_sensors+1];
    latest_sensor = is_GPS;

    first_timestamps[is_GPS] =get_hhmmsssss(gps_csv[0][0]);
    first_timestamps[is_CAM] = get_hhmmsssss(cam_csv[0][0]);
    first_timestamps[is_LiDAR] = get_hhmmsssss(lidar_csv[0][0]);
    first_timestamps[is_IMU] =get_hhmmsssss(imu_csv[0][0]);
    first_timestamps[is_CAN] =get_hhmmsssss(can_csv[0][0]);

    int max = first_timestamps[latest_sensor];

    for(int i = latest_sensor+1; i <= number_of_sensors; i++){
        if(max < first_timestamps[i]){
            max = first_timestamps[i];
            latest_sensor = i;
        }
    }

    switch(latest_sensor){
        case is_GPS:
        return gps_csv[0][0];

        case is_CAM:
        latest_sensor = is_CAM;
        return cam_csv[0][0];

        case is_LiDAR:
        latest_sensor = is_LiDAR;
        return lidar_csv[0][0];

        case is_IMU:
        latest_sensor = is_IMU;
        return imu_csv[0][0];

        case is_CAN:
        latest_sensor = is_CAN;
        return can_csv[0][0];

    }
}

string IndexAndTimes::find_earliest_ended(){
    int  last_timestamps[number_of_sensors+1];
    earliest_sensor = is_GPS;

    last_timestamps[is_GPS] = get_hhmmsssss(gps_csv[gps_csv.size()-1][0]);
    last_timestamps[is_CAM] = get_hhmmsssss(cam_csv[cam_csv.size()-1][0]);
    last_timestamps[is_LiDAR] = get_hhmmsssss(lidar_csv[lidar_csv.size()-1][0]);
    last_timestamps[is_IMU] = get_hhmmsssss(imu_csv[imu_csv.size()-1][0]);
    last_timestamps[is_CAN] = get_hhmmsssss(can_csv[can_csv.size()-1][0]);

    int min = last_timestamps[earliest_sensor];
    for(int i=earliest_sensor+1; i<=number_of_sensors; i++){
        if(min>last_timestamps[i]){
            min = last_timestamps[i];
            earliest_sensor = i;
        }
    }

    switch(earliest_sensor){
        case is_GPS:
        return gps_csv[gps_csv.size()-1][0];

        case is_CAM:
        return cam_csv[cam_csv.size()-1][0];

        case is_LiDAR:
        return lidar_csv[lidar_csv.size()-1][0];

        case is_IMU:
        return imu_csv[imu_csv.size()-1][0];

        case is_CAN:
        return can_csv[can_csv.size()-1][0];
    }
}

int IndexAndTimes::number_of_frames(){
    int number_of_frames = 0;
    int gps_start =  find_gps_start_idx();
    string last_timestamp = find_earliest_ended();
    gps_last = find_gps_idx_by_ts(gps_start, last_timestamp);
    if(gps_last == gps_csv.size()-1) gps_last = gps_last-1;
    number_of_frames = gps_last - gps_start;
    return number_of_frames;
}


int* IndexAndTimes::get_start_indexes(){
   static int idxes[number_of_sensors+1];
   string start_timestamp = find_latest_started();
   s_ts = get_hhmmsssss(start_timestamp);

   idxes[is_GPS] = find_gps_start_idx();
   idxes[is_CAM] = find_cam_start_idx();
   idxes[is_LiDAR] = find_lidar_start_idx();
   idxes[is_IMU] = find_imu_start_idx();
   idxes[is_CAN] = find_can_start_idx();
return idxes;
}


// bool IndexAndTimes::txt_sensor_is_key_frame(int isSensor, int target_idx, int gps_idx){
//     vector<vector<string>> csvs;
//     bool is_key_frame = true;
//     int dev = 0;
//     if(isSensor == is_CAM){
//         csvs = cam_csv;
//         dev = 30;
//     }else if(isSensor == is_LiDAR){
//         csvs = lidar_csv;
//         dev = 55;
//     }
//     int comp = get_hhmmsssss(gps_csv[gps_idx][0]) - get_hhmmsssss(txts[target_idx]);
//     if(comp < 0) comp = -comp;
//     if(comp > dev) is_key_frame = false;
//     return is_key_frame;
// }

// bool IndexAndTimes::csv_sensor_is_key_frame(int isSensor, int target_idx, int gps_idx){
//     vector<vector<string>> csvs;
//     bool is_key_frame = true;
//     int dev = 0;

//     if(isSensor == is_CAM){
//         csvs = cam_csv;
//         dev = 30;
//     }else if(isSensor == is_LiDAR){
//         csvs = lidar_csv;
//         dev = 55;
//     }
//     else if(isSensor == is_IMU){
//         csvs = imu_csv;
//         dev = 25;
//     }else if(isSensor == is_CAN){
//         csvs = can_csv;
//         dev = 130;
//     }
//     int comp = get_hhmmsssss(gps_csv[gps_idx][0])- get_hhmmsssss(csvs[target_idx][0]);

//     if(comp <0) comp = -comp;
//     if(comp > dev) is_key_frame = false;

//     return is_key_frame;
// }

string IndexAndTimes::get_gps_timestamp(int gps_idx){
    return gps_csv[gps_idx][0];
}

string IndexAndTimes::get_cam_timestamp(int cam_idx){
    return cam_csv[cam_idx][0];
}

string IndexAndTimes::get_lidar_timestamp(int lidar_idx){
    return lidar_csv[lidar_idx][0];
}

string IndexAndTimes::get_imu_timestamp(int imu_idx){
    return imu_csv[imu_idx][0];
}

string IndexAndTimes::get_can_timestamp(int can_idx){
    return can_csv[can_idx][0];
}