#include <ros/ros.h> 
#include <serial/serial.h>  //ROS已经内置了的串口包 
#include <std_msgs/String.h> 
#include <std_msgs/Empty.h> 
#include <sensor_msgs/Imu.h>

serial::Serial ser; //声明串口对象 
//回调函数 
void write_callback(const std_msgs::String::ConstPtr& msg) 
{ 
    ROS_INFO_STREAM("Writing to serial port" <<msg->data); 
    ser.write(msg->data);   //发送串口数据 
} 
int main (int argc, char** argv) 
{ 
    //初始化节点 
    ros::init(argc, argv, "serial_output_node"); 
    //声明节点句柄 
    ros::NodeHandle nh; 
    //订阅主题，并配置回调函数 
    ros::Subscriber write_sub = nh.subscribe("write_serial", 1000, write_callback); 
    //发布主题 
    ros::Publisher read_pub = nh.advertise<sensor_msgs::Imu>("/IMU_data", 1000); 
    try 
    { 
        //设置串口属性，并打开串口 
        ser.setPort("/dev/ttyUSB2"); 
        ser.setBaudrate(115200); 
        serial::Timeout to = serial::Timeout::simpleTimeout(1000); 
        ser.setTimeout(to); 
        ser.open(); 
    } 
    catch (serial::IOException& e) 
    { 
        ROS_ERROR_STREAM("Unable to open port "); 
        return -1; 
    } 
    //检测串口是否已经打开，并给出提示信息 
    if(ser.isOpen()) 
    { 
        ROS_INFO_STREAM("Serial Port initialized"); 
    } 
    else 
    { 
        return -1; 
    } 
    //指定循环的频率 
    ros::Rate loop_rate(50); 
    while(ros::ok()) 
    { 
        if(ser.available())
        { 
            //ROS_INFO_STREAM("Reading from serial port\n"); 
            std_msgs::String result; 
            
            result.data = ser.read(ser.available()); 
            // //cout << "len: " << strlen(result.data) << endl; 
            //ROS_INFO_STREAM("Read: " << result.data);
            // //ROS_INFO_STREAM("\n" << result.data[0] << result.data[1] << result.data[2] << "\n");
            // // ROS_INFO_STREAM("szIMUInfo: " << szIMUInfo);; 
            // // ROS_INFO_STREAM("len: " << result.data.length());

            //condition judge   #INSPVAXA
            if(!strncmp(result.data.c_str(), "%RAWIMUSA", 9))
            {
                //ROS_INFO_STREAM(result.data);
                //char szIMUInfo[1024];
                //sprintf(szIMUInfo, "%s", result.data.c_str());
                char *p, *q, *val[64];
                int n  = 0;
                for(p = const_cast<char *>(result.data.c_str()); *p && n < 64; p = q + 1)
                {
                    if((q = strchr(p, ',')) || (q=strchr(p, '*')))
                    {
                        val[n++] = p;
                        *q = '\0';
                    }
                    else
                    {
                        break;
                    }
                }
                if(n < 17)
                {
                    continue;
                }
                // for(int i = 0; i < n; i++)
                // {
                //     ROS_INFO_STREAM("\t" << val[i]);
                // }

                sensor_msgs::Imu imu_data;
            
                imu_data.header.stamp = ros::Time::now();
                imu_data.header.frame_id = "imu_link";
                // imu_data.orientation.x = atof(val[3]);
                // imu_data.orientation.y = atof(val[3]);
                // imu_data.orientation.z = atof(val[3]);
                // imu_data.orientation.w = atof(val[3]);  //13
                float tmp_value = 1000.0;
                imu_data.angular_velocity.x = atof(val[10])/tmp_value;
                imu_data.angular_velocity.y = atof(val[9])/tmp_value;
                imu_data.angular_velocity.z = atof(val[8])/tmp_value;

                imu_data.linear_acceleration.x = atof(val[7])/tmp_value;//8 求导
                imu_data.linear_acceleration.y = atof(val[6])/tmp_value;//9
                imu_data.linear_acceleration.z = atof(val[5])/tmp_value;//10
                read_pub.publish(imu_data); 
            }
            else
            {
                continue;
            }


            //result.data --> sensor_msg::Imu


            //read_pub.publish(result); 
        } 

        //处理ROS的信息，比如订阅消息,并调用回调函数 
        ros::spinOnce(); 
        loop_rate.sleep(); 
    } 
} 




#if 0
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <serial/serial.h> 
#include <JY901.h>
# include <sensor_msgs/Imu.h>
#include <sstream>

serial::Serial ser; //声明串口对象 

//回调函数 
void write_callback(const std_msgs::String::ConstPtr& msg) 
{ 
    ROS_INFO_STREAM("Writing to serial port" <<msg->data); 
    ser.write(msg->data);   //发送串口数据 
} 

int main(int argc, char **argv)
{
   	//初始化节点 
    ros::init(argc, argv, "serial_imu_node"); 
    //声明节点句柄 
    ros::NodeHandle nh; 
    //订阅主题，并配置回调函数 
    ros::Subscriber IMU_write_pub = nh.subscribe("imu_command", 1000, write_callback); 
    //发布主题, 消息格式使用sensor_msg::Imu标准格式（topic名称，队列长度）
    ros::Publisher IMU_read_pub = nh.advertise<sensor_msgs::Imu>("imu_data", 1000); 

    //打开串口
    try 
    { 
    //设置串口属性，并打开串口 
        ser.setPort("/dev/ttyUSB0"); 
        ser.setBaudrate(115200); 
        serial::Timeout to = serial::Timeout::simpleTimeout(1000); 
        ser.setTimeout(to); 
        ser.open(); 
    } 
    catch (serial::IOException& e) 
    { 
        ROS_ERROR_STREAM("Unable to open port "); 
        return -1; 
    } 

    //检测串口是否已经打开，并给出提示信息 
    if(ser.isOpen()) 
    { 
        ROS_INFO_STREAM("Serial Port initialized"); 
    } 
    else 
    { 
        return -1; 
    } 


    //消息发布频率
	ros::Rate loop_rate(100);
    while (ros::ok()){

		//处理从串口来的Imu数据
		//串口缓存字符数
	     unsigned char  data_size;
        if(data_size = ser.available()){ //ser.available(当串口没有缓存时，这个函数会一直等到有缓存才返回字符数
 
            unsigned char  tmpdata[data_size] ;
            ser.read(tmpdata, data_size);
            for (int i = 0; i< data_size; i++){
                JY901.CopeSerialData( tmpdata[i] );   //JY901 imu 库函数
            }

           //打包IMU数据
            sensor_msgs::Imu imu_data;
            
            imu_data.header.stamp = ros::Time::now();
            imu_data.header.frame_id = "base_link";
            imu_data.orientation.x = (float)JY901.stcAngle.Angle[0]/32768*180;
            imu_data.orientation.y = (float)JY901.stcAngle.Angle[1]/32768*180;
            imu_data.orientation.z = (float)JY901.stcAngle.Angle[1]/32768*180;
       
           imu_data.angular_velocity.x = (float)JY901.stcGyro.w[0]/32768*2000;
           imu_data.angular_velocity.y = (float)JY901.stcGyro.w[0]/32768*2000;
           imu_data.angular_velocity.z = (float)JY901.stcGyro.w[0]/32768*2000;
 
           imu_data.linear_acceleration.x = (float)JY901.stcAcc.a[0]/32768*16;
           imu_data.linear_acceleration.y = (float)JY901.stcAcc.a[1]/32768*16;
           imu_data.linear_acceleration.z = (float)JY901.stcAcc.a[2]/32768*16;
           
 
           //发布topic
           IMU_read_pub.publish(imu_data);
        }
        //处理ROS的信息，比如订阅消息,并调用回调函数 
        ros::spinOnce(); 
        loop_rate.sleep(); 
  }
  	return 0;
}

#endif 


#if 0
#include <string>
#include <ros/ros.h> // 包含ROS的头文件
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <boost/asio.hpp> //包含boost库函数
#include <boost/bind.hpp>
#include <math.h>
#include "std_msgs/String.h" //ros定义的String数据类型
#include <std_msgs/Float32.h>
using namespace std;
using namespace boost::asio; //定义一个命名空间，用于后面的读写操作
unsigned char buf[17]; //定义字符串长度，IMU返回的数据是17个字节一组，可用串口调试助手获得
std::string string_to_hex(const std::string& input)
{
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();
    std::string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = input[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    return output;
}
int main(int argc, char** argv)
{
    ros::init(argc, argv, "boost"); //初始化节点
    ros::NodeHandle n;
    ros::Publisher IMU_pub = n.advertise<std_msgs::Float32>("IMU_data", 1000); //定义发布消息的名称及sulv
    ros::Rate loop_rate(100);
    io_service iosev;
    serial_port sp(iosev, "/dev/ttyUSB0"); //定义传输的串口
    sp.set_option(serial_port::baud_rate(115200));
    sp.set_option(serial_port::flow_control());
    sp.set_option(serial_port::parity());
    sp.set_option(serial_port::stop_bits());
    sp.set_option(serial_port::character_size(8));
    while (ros::ok())
    {
        read (sp,buffer(buf));
        string str(&buf[0],&buf[17]); //将数组转化为字符串
        std_msgs::String msg;
        std::stringstream ss;
        ss << str;
        std_msgs::Float32 32; //定义机器人偏航角，单位为度数

        char higher;
        char lower;
        higher = buf[5];
        lower = buf[4];

        Yaw.data= (float)((higher * 256 + lower))/100;
        cout << Yaw << endl; //输出偏航角到终端
        msg.data = string_to_hex(ss.str());
        ROS_INFO("%s", msg.data.c_str()); //打印接受到的字符串
        IMU_pub.publish(Yaw); //发布消息
        
        ros::spinOnce();
        loop_rate.sleep();
    }
    iosev.run();
    return 0;
}


#endif
