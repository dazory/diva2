// #include "Module_Input_CAM.h"

// Module_Input_CAM::Module_Input_CAM()
// : fps(30)
// {

// }
// Module_Input_CAM::~Module_Input_CAM(){

// }
    
// // GET Functions
// vector<Mat> Module_Input_CAM::getImages(){return images;}
// string Module_Input_CAM::getVideoFullName(){return videoFullName;}

// // SET Functions
// void Module_Input_CAM::setImagesWithFileNames(vector<string> fullFileNames){
//     // 참고: https://www.it-note.kr/24 [IT 개발자 Note]
//     printf("[Module_Input_CAM::displayImages] start (fileNames.size=%d)\n",fullFileNames.size());

//     images.clear();
    
//     for(int i=0; i<fullFileNames.size(); i++){
//         string fn = string(fullFileNames.at(i));
//         Mat image = imread(fn, 1);
//         images.push_back(image);
//         // printf("    [%d] fn=%s, image_size=%dx%d\n", i, fn.c_str(), image.cols, image.rows);
//     }
//     printf("[Module_Input_CAM::displayImages] end (images.size=%d)\n",images.size());

// }
    
// // DISPLAY Functions
// void Module_Input_CAM::displayImages(){
//     printf("[Module_Input_CAM::displayImages] start (images.size=%d)\n",images.size());
//     for(int i=0; i<images.size(); i++){
//         string title=to_string(i);
//         // printf("cols=%d, rows=%d\n", images[i].cols, images[i].rows);
//         imshow(title,images[i]);
//         waitKey(0);
//     }
// }
// void Module_Input_CAM::displayImage(int i){
//     printf("[Module_Input_CAM::displayImage] start (%dx%d)\n",images[i].cols, images[i].rows);
    
//     string title=to_string(i);
//     imshow(title,images[i]);
//     waitKey(0);
// }
    
// // functions
// void Module_Input_CAM::saveImages2video(string strFileName){
//     printf("[Module_Input_CAM::saveImages2video] start (strFileName=%s)\n", strFileName.c_str());
//     // [Load Video Writer]
//     VideoWriter writer;
//     writer.open(strFileName, VideoWriter::fourcc('M','J','P','G')
//                 , fps, cv::Size(images[0].cols, images[0].rows), true);
//     printf("[Module_Input_CAM::saveImages2video] open VideoWriter: Video(%dx%d,fps=%d)\n", images[0].cols, images[0].rows, fps);
//     if(!writer.isOpened()){
//         printf("[Module_Input_CAM::saveImages2video] Can't write video! check setting\n");
//         exit(-1);
//     }
//     // [Add Images to Video Writer]
//     for (auto img : images){
//         if(img.cols==0 || img.rows==0){
//             printf("[Module_Input_CAM::saveImages2video] Couldn't load image file ... \n");
//             break;
//         }
//         writer.write(img);
//     }
//     writer.release();
// }