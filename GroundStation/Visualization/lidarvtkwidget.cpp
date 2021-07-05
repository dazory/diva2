#include "lidarvtkwidget.h"

lidarVTKWidget::lidarVTKWidget(QWidget* parent) : QVTKWidget(parent){
}

void lidarVTKWidget::initialVtkWidget(){
    defcloud.reset( new pcl::PointCloud<pcl::PointXYZ>);
    viewer.reset(new pcl::visualization::PCLVisualizer("viewer", false));
    this->SetRenderWindow(viewer->getRenderWindow());
    viewer->setupInteractor(this->GetInteractor(), this->GetRenderWindow());
    viewer->addPointCloud(defcloud, "cloud");
    viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "cloud");
    viewer->addCoordinateSystem(1.0, "cloud");
    viewer->setBackgroundColor(0.05, 0.05, 0.05, 0);

    //카메라 방향 설정
    viewer->setCameraPosition(40,0,40,0,0,0,0,0,1);
    this->show();
}

void lidarVTKWidget::display_lidar(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud){
    viewer->updatePointCloud(cloud, "cloud");
    this->update();
    while (!viewer->wasStopped ()) {
       viewer->spinOnce ();
    }
}

void lidarVTKWidget::display_pcd(QString fileName){
    std::string file_name = fileName.toStdString();
    pcl::io::loadPCDFile(fileName.toStdString(), *defcloud);
    //pcl::transformPointCloud(*defcloud, *defcloud, transform);
    viewer->updatePointCloud(defcloud, "cloud");
    this->update();
    while (!viewer->wasStopped ()) { // Display the visualiser until 'q' key is pressed
       viewer->spinOnce ();
    }
}


void lidarVTKWidget::init(){
    this->initialVtkWidget();
}
