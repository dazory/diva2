// 참고: https://github.com/kka-na/DIVA_Qt

#include "readfiles.h"

ReadFiles::ReadFiles(string fpath)
{
    dir = fpath;
}

string ReadFiles::get_path(int i){
    //size는 파일 이름의 길이와 관련
    int size = 30;
    string sensor;
    if(i == is_GPS){
        sensor = "GPS";
    }else if(i==is_CAM){
        sensor = "CAM";
    }else if(i==is_LiDAR){
        sensor = "LiDAR";
        size = 32;
    }else if(i == is_IMU){
        sensor = "IMU";
    }else{
        sensor = "CAN";
    }

    char *file_name= new char[size];
    FILE *fp;

    //가장 최근에 기록된 장치들의 raw data 파일을 불러옴
    string path = dir+"/"+sensor;
    string sys_cmd = "cd "+path+" && ls -tr | grep i30 | tail -1 ";
    const char * path_c = sys_cmd.c_str();
    fp = popen(path_c, "r");

    if(NULL == fp){
        perror("fail");
        return 0;
    }

    fgets(file_name, size, fp);

    string sp = file_name;
    string result = path + "/"+sp;

    return result;
}

//csv 파일 읽어오는 함수
//csv : comma separated version 컴마로 구분된 파일
vector<vector<string>> ReadFiles::read_csv(string csv_file){
    ifstream in(csv_file.c_str());
    int c=0;
    string line, field;
    vector< vector<string> > arr;  // the 2D array
    vector<string> v;

    while (getline(in, line))
    {
        v.clear();
        stringstream ss(line);

        while (getline(ss, field, ','))  // break line into comma delimitted fields
        {
            v.push_back(field);  // add each field to the 1D array
        }

        arr.push_back(v);  // add the 1D array to the 2D array
    }

    return arr;

}