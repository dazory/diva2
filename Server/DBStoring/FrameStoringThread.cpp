// 참고: https://github.com/kka-na/DIVA_Qt
// 참고: https://www.tutorialspoint.com/postgresql/postgresql_c_cpp.htm

#include "FrameStoringThread.h"

using namespace std;

FrameStoringThread::FrameStoringThread(){}

void FrameStoringThread::run(){
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
      connection C("dbname = diva2db user = diva2 password = 1234 \
      hostaddr = 127.0.0.1 port = 5432");
      if (C.is_open()) {
         cout << "Opened database successfully: " << C.dbname() << endl;
      } else {
         cout << "Can't open database" << endl;
         //return 1;
      }
      string path = "/home/cvlab2/DIVA2/diva2/Server/DIVA2_DATA/"+timestamp+"_0/JSON/frame.json";

      /* Create SQL statement */
      sql = "create table FRAME(frame_token text primary key,token_next text);";
      
      /* Create a transactional object. */
      work W(C);

      /* Execute SQL query */
      W.exec( sql );
      W.commit();

      Json::Value Frames;
      ifstream scene_in(path.c_str());
      if(scene_in.is_open()) scene_in>>Frames;
      std::string temp1;
      std::string temp2;
      

      for(int i=0; i<Frames.size(); i++){

         temp1=std::string((Frames[i]["frame_token"].asString()).c_str());
         temp2=std::string((Frames[i]["token_next"].asString()).c_str());
         

         /* Create a transactional object. */
         work W(C);
	      std::string query_string;
         query_string.append("insert into FRAME values('"); 

	      // *****Set table*****
         query_string.append(temp1);
         query_string.append("','");
         query_string.append(temp2);
         query_string.append("');");

         /* Execute SQL query */
         W.exec(query_string);
         W.commit();
      }
      
      cout << "[DBStoring] frame successfully" << endl;
      C.disconnect ();
   } catch (const std::exception &e) {
      cerr << e.what() << std::endl;
   }

}

void FrameStoringThread::stop(){
    stop_flag = true;
}
