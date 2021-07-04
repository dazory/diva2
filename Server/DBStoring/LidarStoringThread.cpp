// 참고: https://github.com/kka-na/DIVA_Qt
// 참고: https://www.tutorialspoint.com/postgresql/postgresql_c_cpp.htm

#include "LidarStoringThread.h"

using namespace std;

LidarStoringThread::LidarStoringThread(){}

void LidarStoringThread::run(){
    char * sql;
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
   
   try {
      //Connect Database
      connection C("dbname = diva2db user = diva2 password = 1234 \
      hostaddr = 127.0.0.1 port = 5432");
      if (C.is_open()) {
         cout << "Opened database successfully: " << C.dbname() << endl;
      } else {
         cout << "Can't open database" << endl;
      }

      string path = "/home/cvlab2/DIVA2/diva2/Server/DIVA2_DATA/"+timestamp+"_0/JSON/lidar_data.json";

      //Create SQL statement
      sql = "create table LIDAR_DATA(token text primary key references frame (frame_token), fileformat text, filename text);";
      
      //Create a transactional object
      work W(C);

      //Execute SQL query
      W.exec( sql );
      W.commit();

      Json::Value Lidar_datas;
      ifstream scene_in(path.c_str());
      if(scene_in.is_open()) scene_in>>Lidar_datas;
      std::string temp1;
      std::string temp2;
      std::string temp3;
      
      //JSON parsing & DB Storing
      for(int i=0; i<Lidar_datas.size(); i++){
         temp1=std::string((Lidar_datas[i]["token"].asString()).c_str());
         temp2=std::string((Lidar_datas[i]["fileformat"].asString()).c_str());
         temp3=std::string((Lidar_datas[i]["filename"].asString()).c_str());

         //Create a transactional object
         work W(C);
	      std::string query_string;
            query_string.append("insert into LIDAR_DATA values('"); 
            
            //Set table
            query_string.append(temp1);
            query_string.append("','");
            query_string.append(temp2);
            query_string.append("','");
            query_string.append(temp3);
            query_string.append("');");

         //Execute SQL query
         W.exec(query_string);
         W.commit();
      }
      
      cout << "[DBStoring] lidar successfully" << endl;

      //Disconnect Database
      C.disconnect ();
   } catch (const std::exception &e) {
      cerr << e.what() << std::endl;
   }

}

void LidarStoringThread::stop(){
    stop_flag = true;
}