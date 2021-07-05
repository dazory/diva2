#ifndef LIDARVTKWIDGET_H
#define LIDARVTKWIDGET_H


#include <QObject>
#include <QWidget>
#include <QThread>
#include <QVTKWidget.h>
#include <QVTKInteractor.h>
#include <QMetaType>

#include <Eigen/Eigen>
#include <atomic>
#include <cassert>
#include <cmath>
#include <deque>
#include <functional>
#include <iostream>
#include <mutex>
#include <vector>
#include <memory>
#include <QOpenGLWidget>


/*
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);
*/

#include <vtkActor.h>
#include <vtkCallbackCommand.h>
#include <vtkCamera.h>
#include <vtkCellArray.h>
#include <vtkDoubleArray.h>
#include <vtkImageActor.h>
#include <vtkImageChangeInformation.h>
#include <vtkImageData.h>
#include <vtkImageMapToColors.h>
#include <vtkImageMapper.h>
#include <vtkImageMapper3D.h>
#include <vtkImageProperty.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkLookupTable.h>
#include <vtkMath.h>
#include <vtkMatrix4x4.h>
#include <vtkObjectFactory.h>
#include <vtkPointData.h>
#include <vtkPointSource.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkTransform.h>
#include <vtkVertexGlyphFilter.h>

#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/common/transforms.h>
#include <pcl/console/parse.h>


class lidarVTKWidget : public QVTKWidget
{
    Q_OBJECT
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    lidarVTKWidget(QWidget *parent = 0);
    void initialVtkWidget();

    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
    pcl::PointCloud<pcl::PointXYZ>::Ptr defcloud;

public slots:
    void display_lidar(pcl::PointCloud<pcl::PointXYZ>::Ptr);
    void display_pcd(QString fileName);
    void init();
};

#endif // LIDARVTKWIDGET_H

//    Eigen::Affine3f transform;
//     vtkSmartPointer<vtkRenderWindow> render_window;
//     vtkSmartPointer<vtkRenderWindowInteractor> render_window_interactor;