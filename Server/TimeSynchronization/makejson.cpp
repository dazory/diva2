// 참고: https://github.com/kka-na/DIVA_Qt

#include "makejson.h"

MakeJson::MakeJson(string fpath)
{
    dir = fpath;
    iat = new IndexAndTimes(dir);

    gps_csv_size = iat->gps_csv.size();
    cam_csv_size = iat->cam_csv.size();
    lidar_csv_size = iat->lidar_csv.size();
    imu_csv_size = iat->imu_csv.size();
    can_csv_size = iat->can_csv.size();

    gps_start = iat->get_start_indexes()[1];
    cam_start = iat->get_start_indexes()[2];
    lidar_start = iat->get_start_indexes()[3];
    imu_start = iat->get_start_indexes()[4];
    can_start = iat->get_start_indexes()[5];

    cam_sensors = 2; // if 2 -> cam, lidar
    scene_count = iat->number_of_frames() / 200;
    if(iat->number_of_frames() % 200 > 0)
        scene_count++;
    gps_last = iat->gps_last;
    this_frame_start = 0;
    this_log_start = 0;
}

string MakeJson::generate_token(){
    srand((unsigned int)time(NULL));
    char hex_characters[] ="0123456789abcdef";
    char* token_char = new char[16]; //to store values in for loop
    string token_string="";

    for (size_t j = 0; j < 16; j++){
        token_char[j] = hex_characters[rand() % 16];
        token_string = token_string + token_char[j];
    }

    delete[] token_char;
    return token_string;
}

string MakeJson::generate_token_2()
{
    char hex_characters[] ="0123456789abcdef";
    char* token_char = new char[16]; //to store values in for loop
    string token_string="";

    for (size_t j = 0; j < 16; j++){
        token_char[j] = hex_characters[rand() % 16];
        token_string = token_string + token_char[j];
    }

    delete[] token_char;
    return token_string;
}

string MakeJson::generate_timestamp()
{
    time_t system_time;
    struct tm* systime;
    system_time = time(NULL);
    systime = localtime(&system_time);

    string tm_year = to_string(systime->tm_year + 1900);
    string tm_month = to_string(systime->tm_mon+1);
    string tm_date = to_string(systime->tm_mday);
    if(tm_date.size() == 1){
        tm_date = "0"+tm_date;
    }

    string timestamp;
    timestamp = tm_year + tm_month + tm_date;

    return timestamp;
}

//make Log json
Json::Value Logs;
bool MakeJson::Log(int car_id)
{
    string path = dir+"/JSON/log.json";
    ifstream in(path.c_str());
    if(in.is_open()) in >> Logs;

    Json::Value log;

    this_log_start = Logs.size();

    string vehicles[2] = { "i30", "n004" };
    string vehicle = vehicles[car_id]; //i30
    string date = generate_timestamp();

    log["token"] = generate_token();
    log["vehicle"] = vehicle;
    log["date_captured"] = date+"_"+to_string(this_log_start);
    log["location"] = "Incheon, South Korea";

    Logs.append(log);
    log.clear();

    Json::StyledWriter writer;
    ofstream out(path.c_str());
    out << writer.write(Logs);
    out.close();
    return true;
}

//make Sensor json
Json::Value Sensors;
bool MakeJson::Sensor(int sensors_num)
{
    string path = dir+"/JSON/sensor.json";
    Json::Value sensor;
    string sensor_name;

    for(int i=0; i<=sensors_num; i++){
        string token = generate_token_2();
        if(i ==1)
            sensor_name = "GPS";
        else if(i==2)
            sensor_name = "CAM";
        else if(i==3)
            sensor_name = "LiDAR";
        else if(i==4)
            sensor_name = "IMU";
        else if(i==5)
            sensor_name = "CAN";
        else{
            sensor_name = "NULL";
            token = "NULL";
        }
        sensor["sensor_token"] = token;
        sensor["Sensor"] = sensor_name;

        Sensors.append(sensor);
        sensor.clear();
    }

    Json::StyledWriter writer;
    ofstream out(path.c_str());
    out << writer.write(Sensors);
    out.close();
    return true;
}

//make Frame json
Json::Value Frames;
bool MakeJson::Frame()
{
    string path = dir+"/JSON/frame.json";
    ifstream in(path.c_str());
    if(in.is_open()) in >> Frames;

    int frame_start = gps_start;

    gps_idx = gps_start;

    this_frame_start = Frames.size(); //for frame_data's frame_token

    int frame_idx = frame_start;

    Json::Value a_frame;

    for(int i=0; i<scene_count; i++){
        string token_prev = "";
        string token_curr = generate_token_2();

        while(1){

            if(frame_idx > frame_start+199){
                frame_start = frame_idx;
                break;
            }else if(frame_idx > gps_last){
                break;
            }

            string timestamp = iat->get_gps_timestamp(gps_idx);
            string token_next = generate_token_2();

            a_frame["frame index = "]=frame_idx;
            a_frame["frame_token"] = token_curr;
            a_frame["timestamp"] = timestamp;
            a_frame["token_prev"] = token_prev;


            if(frame_idx < gps_last+1 && frame_idx == frame_start+199)
                a_frame["token_next"] = "";
            else if(frame_idx < gps_last+1 && frame_idx == gps_last)
                a_frame["token_next"] = "";
            else
                a_frame["token_next"] = token_next;

            Frames.append(a_frame);
            a_frame.clear();

            token_prev = token_curr;
            token_curr = token_next;

            gps_idx++;
            frame_idx++;
        }

    }

    Json::StyledWriter writer;
    ofstream out(path.c_str());
    out << writer.write(Frames);
    out.close();
    return true;
}

//make Scene json
Json::Value Scenes;
bool MakeJson::Scene()
{
    string path = dir+"/JSON/scene.json";
    ifstream in(path.c_str());
    if(in.is_open()) in >> Scenes;

    Json::Value a_scene;
    int scene_idx = this_frame_start;
    int frames = 200;
    bool is_last = false;
    for(int i=0; i<scene_count; i++){
        num_of_scene++;
        a_scene["scene_token"] = generate_token_2();
        a_scene["log_token"] = Logs[this_log_start]["token"];

        if(((this_frame_start+iat->number_of_frames()+1) - (scene_idx)) < 200){ 
            frames = (this_frame_start+iat->number_of_frames()+1)-(scene_idx);
            is_last = true;
        }


        a_scene["nbr_frames"] = frames;
        a_scene["first_frame_token"] = Frames[scene_idx]["frame_token"];
        a_scene["last_frame_token"] = Frames[scene_idx+(frames-1)]["frame_token"];

        Scenes.append(a_scene);
        a_scene.clear();
        scene_idx+=200;
        if(is_last) break;
    }

    Json::StyledWriter writer;
    ofstream out(path.c_str()); //ios::app append
    out <<  writer.write(Scenes);
    out.close();
    return true;
}

//make Lidar json
Json::Value Lidar_data;
bool MakeJson::Lidar_Data()
{
    string path = dir+"/JSON/lidar_data.json";

    ifstream in(path.c_str());
    if(in.is_open()) in >> Lidar_data;
    Json::Value lidar;

    int frame_start = gps_start;
    int frame_idx = frame_start;
    int lidar_data_idx = frame_start;

    this_frame_data_start = Lidar_data.size();

    int lidar_idx = lidar_start;

    string ts_of_lidar_by_idx;

    string lidar_path = dir+"/LiDAR/PCD/LiDAR_";

    for(int i=0; i<num_of_scene; i++){
        while(1){

            if(lidar_data_idx > frame_start+199){
                frame_start = lidar_data_idx;
                break;
            }else if(lidar_data_idx > gps_last){
                break;
            }

            string gps_ts = iat->get_gps_timestamp(lidar_data_idx);

            for(int j=0; j<cam_sensors; j++){
                if(j==0){}//cam
                else{//lidar
                    lidar_idx = iat->find_lidar_idx_by_ts(lidar_idx, gps_ts);
                    if(lidar_idx > lidar_csv_size-1) continue;
                    ts_of_lidar_by_idx = iat->get_lidar_timestamp(lidar_idx);
                    
                    lidar["token"] = Frames[this_frame_start]["frame_token"];
                    lidar["sensor_token"] = Sensors[3]["sensor_token"];
                    lidar["filename"] = "LiDAR_"+ts_of_lidar_by_idx+".pcd";
                    lidar["fileformat"] = "pcd";
                    lidar["timestamp"] = ts_of_lidar_by_idx;

                    Lidar_data.append(lidar);
                    lidar.clear();
                }
            }
            
            lidar_data_idx++;
            this_frame_start++;
        }
        
    }

    Json::StyledWriter writer;
    ofstream out(path.c_str());
    out<<writer.write(Lidar_data);
    out.close();
    return true;

}

//make Cam json
Json::Value Cam_data;
bool MakeJson:: Cam_Data()
{
    this_frame_start =0;
    string path = dir+"/JSON/cam_data.json";

    ifstream in(path.c_str());
    if(in.is_open()) in >> Cam_data;
    Json::Value cam;

    int frame_start = gps_start;
    int frame_idx = frame_start;
    int cam_data_idx = frame_start;
    this_frame_data_start = Cam_data.size();

    int cam_idx = cam_start;

    string ts_of_cam_by_idx;

    string cam_path =  dir+"/CAM/JPG/CAM_";

    for(int i=0; i<num_of_scene; i++){
        while(1){
            if(cam_data_idx > frame_start+199){
                frame_start = cam_data_idx;
                break;
            }else if(cam_data_idx > gps_last){
                break;
            }

            string gps_ts = iat->get_gps_timestamp(cam_data_idx);
            
            for(int j=0; j<cam_sensors; j++){
                if(j==0){
                    cam_idx = iat->find_cam_idx_by_ts(cam_idx, gps_ts);
                    if(cam_idx > cam_csv_size-1) continue;
                    ts_of_cam_by_idx = iat->get_cam_timestamp(cam_idx);

                    cam["token"] = Frames[this_frame_start]["frame_token"];
                    cam["sensor_token"] = Sensors[2]["sensor_token"];
                    cam["filename"] = "CAM_"+ts_of_cam_by_idx+".jpg";
                    cam["fileformat"] = "jpg";
                    cam["timestamp"] = ts_of_cam_by_idx;
 
                    Cam_data.append(cam);
                    cam.clear();
                }
                else{}
            }

            cam_data_idx++;
            this_frame_start++;


        }
    }

    Json::StyledWriter writer;
    ofstream out(path.c_str());
    out<<writer.write(Cam_data);
    out.close();
    return true;

}

//make Gps json
Json::Value Gps_data;
bool MakeJson::Gps_Data()
{
    this_frame_start =0;
    string path = dir+"/JSON/gps_data.json";
    ifstream in(path.c_str());
    if(in.is_open()) in >> Gps_data;
    Json::Value gpses;

    int gps_data_start = gps_start;
    int gps_data_idx = gps_data_start;
    int where_frame_started = this_frame_data_start;

    for(int i=0; i<num_of_scene; i++){
        while(1){
            if(gps_data_idx > gps_data_start+199){
                gps_data_start = gps_data_idx;
                break;
            }else if(gps_data_idx > gps_last){
                break;
            }

            gpses["token"] = Frames[this_frame_start]["frame_token"];
            gpses["sensor_token"] = Sensors[1]["sensor_token"];
            gpses["timestamp"] = iat->get_gps_timestamp(gps_data_idx);
            this->Get_LLA(gps_data_idx);
            gpses["latitude"] = latitude;//위도
            gpses["longitude"] = longitude;//고도
            gpses["HorizontalDilutionOfPrecision"] = HorizontalDilutionOfPrecision;//수평위치오차

            Gps_data.append(gpses);
            gpses.clear();

            gps_data_idx++;
            this_frame_start++;
            
        }
        
    }

    Json::StyledWriter writer;
    ofstream out(path.c_str());
    out<<writer.write(Gps_data);
    out.close();
    return true;
}

//make Imu json
Json::Value Imu_data;
bool MakeJson::Imu_Data()
{
    this_frame_start =0;
    string path = dir+"/JSON/imu_data.json";
    ifstream in(path.c_str());
    if(in.is_open()) in >> Imu_data;

    Json::Value imus;
    Json::Value gyroscope;
    Json::Value acceleration;
    Json::Value magnetic;

    int imu_data_start = imu_start;
    int gps_data_idx = gps_start;
    int imu_data_idx = imu_data_start;
    int where_frame_started = this_frame_data_start;
    int this_frame_count = 0;
    int imu_idx_by_ts;

    for(int i=0; i<num_of_scene; i++){
        while(1){
            if(this_frame_count == 200){
                this_frame_count = 0;
                break;
            }else if(gps_data_idx > gps_last){
                break;
            }
            imu_data_idx = iat->find_imu_idx_by_ts(imu_data_idx, iat->get_gps_timestamp(gps_data_idx));
            imus["token"] = Frames[this_frame_start]["frame_token"];
            imus["sensor_token"] = Sensors[4]["sensor_token"];
            imus["timestamp"] = iat->get_imu_timestamp(imu_data_idx);
            this->Get_GAM(imu_data_idx);

            imus["scaledaccelx"] = scaledaccelx;
            imus["scaledaccely"] = scaledaccely;
            imus["scaledaccelz"] = scaledaccelz;

            Imu_data.append(imus);
            gyroscope.clear();
            acceleration.clear();
            magnetic.clear();
            imus.clear();

            gps_data_idx++;
            this_frame_count++;
            this_frame_start++;
        }

    }

    Json::StyledWriter writer;
    ofstream out(path.c_str());
    out<<writer.write(Imu_data);
    out.close();
    return true;
}

//make Can json
Json::Value Can_data;
bool MakeJson::Can_Data()
{
    this_frame_start =0;
    string path = dir+"/JSON/can_data.json";
    ifstream in(path.c_str());
    if(in.is_open()) in >> Can_data;
    Json::Value cans;

    int gps_data_idx = gps_start;
    int this_frame_count = 0;

    int can_data_start = can_start;
    int can_data_idx = can_data_start;
    int can_data_real_idx = can_data_start;

    int where_frame_started = this_frame_data_start;

    for(int i=0; i<num_of_scene; i++){
        while(1){
            if(this_frame_count == 200){
                this_frame_count = 0;
                break;
            }else if(gps_data_idx > gps_last){
                break;
            }
            can_data_idx = iat->find_can_idx_by_ts(can_data_idx, iat->get_gps_timestamp(gps_data_idx));
            cans["token"] = Frames[this_frame_start]["frame_token"];
            cans["sensor_token"] = Sensors[5]["sensor_token"];
            cans["timestamp"] = iat->get_can_timestamp(can_data_idx);
            this->Get_HSGT(can_data_idx);
            cans["handleAngle"] = handleAngle;
            cans["turnLight"] = turnLight;
            cans["vehicleSpeed"] = vehicleSpeed;
            cans["gear"] = gear;
            Can_data.append(cans);
            cans.clear();

            this_frame_count++;
            gps_data_idx++; 
            this_frame_start++;
            
        }
        
    }

    Json::StyledWriter writer;
    ofstream out(path.c_str());
    out<<writer.write(Can_data);
    out.close();
    return true;
}

// bool MakeJson::Check_Directory()
// {
//     QDir root((QString::fromLocal8Bit(dir.c_str())).append("/JSON2"));
//     if(root.exists()) return true;
//     return false;
// }

void MakeJson::Get_LLA(int gps_idx){
    latitude, longitude, HorizontalDilutionOfPrecision= "";

    long double raw_latitude = stold(iat->gps_csv[gps_idx][1]); // latitude
    latitude = to_string(Convert_to_dd(raw_latitude));

    long double raw_longitude = stold(iat->gps_csv[gps_idx][2]); // longitude
    longitude = to_string(Convert_to_dd(raw_longitude));

    HorizontalDilutionOfPrecision = iat->gps_csv[gps_idx][3];//HorizontalDilutionOfPrecision
}

long double MakeJson::Convert_to_dd(long double raw){

    int dd = (int)(raw/100);
    long double ddddd = raw - (long double)(dd*100);
    ddddd /= 60;

    return (long double)dd+ddddd;
}

void MakeJson::Get_GAM(int imu_idx){ 

    scaledaccelx, scaledaccely, scaledaccelz = "";

    scaledaccelx = iat->imu_csv[imu_idx][1]; //scaledaccelx
    scaledaccely = iat->imu_csv[imu_idx][2]; //scaledaccely
    scaledaccelz = iat->imu_csv[imu_idx][3]; //scaledaccelz

}

void MakeJson::Get_HSGT(int can_idx){

    handleAngle, turnLight, vehicleSpeed, gear = "";

    handleAngle = iat->can_csv[can_idx][1]; //handleangle
    turnLight = iat->can_csv[can_idx][2]; //turnlight
    vehicleSpeed = iat->can_csv[can_idx][3]; //speed
    gear = iat->can_csv[can_idx][4]; //gear
}