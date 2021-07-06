
//DIVA_QT 참고
#include "LiDAR_Sensing.h"

LiDAR_Sensing::LiDAR_Sensing()
{
    cloud.reset(new pcl::PointCloud<pcl::PointXYZ>);
    cloud_filtered.reset(new pcl::PointCloud<pcl::PointXYZ>);
}

void LiDAR_Sensing::stop()
{
    stop_flag = true;
    writeFile.close();
}

void LiDAR_Sensing::resetCount(){
    count = 0;
}
void LiDAR_Sensing::addCount(){
    count++;
}
int LiDAR_Sensing::getCount(){
    return count;
}

void LiDAR_Sensing::WritePCD(std::vector<double> xyz_lut, uint8_t *buf)
{
    //std::cout<<"WritePCD"<<std::endl;
    for (int icol = 0; icol < OS1::columns_per_buffer; icol++)
    {
        const uint8_t *col_buf = OS1::nth_col(icol, buf);
        const uint16_t m_id = OS1::col_measurement_id(col_buf);
        const int idx = H * m_id;

        for (uint8_t ipx = 0; ipx < H; ipx++)
        {
            const uint8_t *px_buf = OS1::nth_px(ipx, col_buf);
            uint32_t r = OS1::px_range(px_buf);
            int ind = 3 * (idx + ipx);
            pcl::PointXYZ LiDAR_point;
            LiDAR_point.x = r  * 0.001f * xyz_lut[ind + 0]; //leaf size 설정 -> downsampling 0.001f(787kB) 
            LiDAR_point.y = r  * 0.001f * xyz_lut[ind + 1]; //0.01f -> 1cm (787kB) 
            LiDAR_point.z = r  * 0.001f * xyz_lut[ind + 2];
            if (getCount() > W * H)
            {
                break;
            }

            cloud->push_back(LiDAR_point);
            addCount();
        }
    }
}

string read_metadata(const string &meta_file)
{
    stringstream buf{};
    ifstream ifs{};
    ifs.open(meta_file);
    buf << ifs.rdbuf();
    ifs.close();

    if (!ifs)
    {
        exit(EXIT_FAILURE);
    }

    return buf.str();
}



