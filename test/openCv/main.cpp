// #include "opencv2/opencv.hpp"
// #include <iostream>  
  
// using namespace cv;  
// using namespace std;  
  
  
  
// int main(int, char**)  
// {  

//     VideoCapture cap(0);  
//     if (!cap.isOpened())  
//     {  
//         printf("카메라를 열수 없습니다. \n");  
//     }  
  
  
//     Mat frame;  
//     namedWindow("camera1", 1);  
   
  
//     for (;;)  
//     {  
  
//         cap >> frame;  
  
//         imshow("camera1", frame);  
  
//         if (waitKey(20) >= 0) break;  
//     }  
  
  
//     return 0;  
// }  