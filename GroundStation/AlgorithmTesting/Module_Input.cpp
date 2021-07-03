#include "Module_Input.h"

bool has_extension(const char *str, const char *suffix);

Module_Input::Module_Input(int sensorType)
{
    this->sensorType = sensorType;
}

void Module_Input::setSensorType(int sensorType){
    printf("[Module_Input::setSensorType] start\n");
    this->sensorType = sensorType;
    printf("    sensorType:%d (GPS = 100; IMU = 101; CAM = 102; LIDAR = 103; CAN = 104;)\n", this->sensorType);
    printf("[Module_Input::setSensorType] end\n");
}

void Module_Input::setFileNamesWithDir(string strDirPath, string strExtension){
    printf("[Module_Input::setFileNamesWithDir] start\n");
    this->strExtension = strExtension;
    string tmp = strDirPath.substr(strDirPath.length() - 1, strDirPath.length());
    if(tmp!="/"){strDirPath=strDirPath+"/";}
    this->strDirPath = strDirPath;
    printf("    strDirPath:%s\n", this->strDirPath.c_str());
    printf("    strExtension:%s\n", this->strExtension.c_str());
    /* 참고:
        1. https://www.it-note.kr/24 [IT 개발자 Note]
    */

    this->fileNames.clear();

    DIR *dir; struct dirent *diread;

    if ((dir = opendir(strDirPath.c_str())) != nullptr) {
        while ((diread = readdir(dir)) != nullptr) 
        {
            if(strcmp(diread->d_name, ".") == 0 || strcmp(diread->d_name, "..") == 0) { continue; }
            if(has_extension(diread->d_name,this->strExtension.c_str())){
                this->fileNames.push_back(diread->d_name);
            }
        }
        closedir (dir);
    } else {
        perror ("[Module_Input::setFileNamesWithDir] Can't open the directory.");
        exit(EXIT_FAILURE);
    }
    printf("[Module_Input::setFileNamesWithDir] end (fileNames.size=%d)\n",this->fileNames.size());
}

void Module_Input::sortFileNames(){
    sort(fileNames.begin(), fileNames.end());
}


void Module_Input::setImages(){
    /* 참고:
        1. https://www.it-note.kr/24 [IT 개발자 Note]
    */
    printf("[Module_Input::setImages] start (fileNames.size=%d)\n",fileNames.size());

    images.clear();
    
    for(int i=0; i<fileNames.size(); i++){
        string fn = strDirPath+ string(fileNames.at(i));
        Mat image = imread(fn, 1);
        images.push_back(image);
        // printf("    [%d] fn=%s, image_size=%dx%d\n", i, fn.c_str(), image.cols, image.rows);
    }
    printf("[Module_Input::setImages] end (images.size=%d)\n",images.size());

}

void Module_Input::setFiles(){
    printf("[Module_Input::setImages] start (fileNames.size=%d)\n",fileNames.size());

    switch (sensorType)
    {
    case SensorIdx::lidar:
    { break; }
    case SensorIdx::cam:
    { 
        setImages();
        break;
    }
    case SensorIdx::can:
    { break; }
    case SensorIdx::imu:
    { break; }
    case SensorIdx::gps:
    { break; }
    default:
    { break; }
    }
}
    

void Module_Input::displayFileName(){
    printf("[Module_Input::displayFileName] start (fileNames.size=%d)\n",fileNames.size());
    for (auto file : fileNames){
        cout << file << endl;
    }
    printf("[Module_Input::displayFileName] end\n");
}

void Module_Input::displayImages(){
    printf("[Module_Input::displayImages] start (images.size=%d)\n",images.size());
    for(int i=0; i<images.size(); i++){
        string title=to_string(i);
        // printf("cols=%d, rows=%d\n", images[i].cols, images[i].rows);
        imshow(title,images[i]);
        waitKey(0);
    }
}

bool has_extension(const char *str, const char *suffix) {
    // 참고: https://github.com/nireo/kantaplus/blob/adce90b2a4e04d3bb838d06625382f7c34b00ac2/db.cpp
	if (!str || !suffix)
		return false;

	size_t lenstr = strlen(str);
	size_t lensuffix = strlen(suffix);

	if (lensuffix > lenstr)
		return false;
	return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

// vector<Mat> Module_Input::getImages(){
//     printf("[Module_Input::getImages] start-end (images.size=%d)\n",images.size());
//     return images;
// }


void Module_Input::image2video(string strFileName){
    VideoWriter writer;
    // 'm', 'p', '4', 'v')
    int fourCC = VideoWriter::fourcc('M','J','P','G');
    writer.open(strFileName, fourCC, fps, cv::Size(images[0].cols, images[0].rows), true);
    printf("[Module_Input::image2video] start : Video(%dx%d,fps=%d)\n", images[0].cols, images[0].rows, fps);
    if(!writer.isOpened()){
        printf("[Module_Input::image2video] Can't write video! check setting\n");
        exit(-1);
    }

    int cnt=0;
    for(int i=0; i<images.size(); i++){
        writer.write(images[i]);
        cnt++;
    }
    // for (auto img : images){
    //     if(img.cols==0 || img.rows==0){
    //         printf("[Module_Input::image2video] Couldn't load image file ... \n");
    //         break;
    //     }

    //     writer.write(img);
    //     cnt++;
    // }
    printf("[Module_Input::image2video] complete to write %d images to video\n",cnt);


    writer.release();
}

void Module_Input::displayVideos(string strFileName)
{
    printf("[Module_Input::displayVideos] start\n");
    VideoCapture cap(strFileName.c_str());
    if(!cap.isOpened())
    {
        cout << "Capture could not be opened succesfully" <<endl;
        exit(-1);
    }
    namedWindow("video");
    while (char(waitKey(1)) != 'q' && cap.isOpened()) {
        Mat frame;
        cap >> frame;

        if(frame.empty())
        {
            cout<<"Video over"<<endl;
            break;
        }
        imshow("Video", frame);
    }
    waitKey(0);
}

string Module_Input::getDateNameFromDir(){
    std::size_t pos = strDirPath.rfind('/');
    string fileDir= strDirPath.substr(0, pos);
    printf(">> %s\n", fileDir.c_str());
    pos = fileDir.rfind('/');
    fileDir= fileDir.substr(0, pos);
    printf(">> %s\n", fileDir.c_str());
    pos = fileDir.rfind('/');
    // fileDir= fileDir.substr(0, pos);
    std::string fileName = fileDir.substr(pos + 1);
    printf(">> %s\n", fileName.c_str());
    
    return fileName;
}