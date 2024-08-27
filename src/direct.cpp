#include "rclcpp/rclcpp.hpp"
#include "dynamixel/dxl.hpp"
#include <iostream>
#include <chrono>

void updateVelocity(int& g1, int& g2, int& v1, int& v2);
int main(void)
{
    Dxl dxl;           
    if(!dxl.open()) { std::cout << "dxl open error"<< std::endl; return -1; }

    int vel1 = 0, vel2 = 0;
    int goal1 = 0, goal2 = 0; 
    while(true)
    {
        if (dxl.kbhit())
        {
            char c = Dxl::getch();
            switch(c) {
                case 'w': goal1 = 50; goal2 = -50; break;  //전진
                case 's': goal1 = -50; goal2 = 50; break;  //후진
                case ' ': goal1 = 0; goal2 = 0; break;     //정지
                case 'a': goal1 = -50; goal2 = -50; break; //좌회전
                case 'd': goal1 = 50; goal2 = 50; break;   //우회전
                default: goal1 = 0; goal2 = 0; break;      //정지
            }
        }
        updateVelocity(goal1, goal2, vel1, vel2);
        std::cout << vel1 << " : " << vel2 << std::endl;
        dxl.setVelocity(vel1, vel2); 
        //usleep(50*1000);
        rclcpp::sleep_for(std::chrono::milliseconds(10));
    }

    dxl.close();
    return 0;
}

void updateVelocity(int& goal1, int& goal2, int& vel1, int& vel2)
{
    if(goal1 > vel1) vel1 += 5;
    else if(goal1 < vel1) vel1 -= 5;
    else vel1 = goal1;

    if(goal2 > vel2) vel2 += 5;
    else if(goal2 < vel2) vel2 -= 5;
    else vel2 = goal2;
}