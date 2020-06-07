#include "alarm.h"
#include <boost/bind.hpp>
#include <thread>

using namespace std;

// void currentTime()
// {
//     struct tm  *tp;
//     time_t time_ = time(NULL);
//     tp = localtime(&time_);
//     printf("%d:%d:%d\n",tp->tm_hour,tp->tm_min,tp->tm_sec);
// }

class Alarm;

Alarm::Alarm(){
    // cout << "Start ";
    // currentTime();
}

void Alarm::SetFromNow(int time){
    thread th(&Alarm::SetFromNowImp, this, time);
    th.detach();
}

void Alarm::UpdateFromNow(int time){
    thread th(&Alarm::UpdateFromNowImp, this, time);
    th.detach();
}

void Alarm::Cancel(){
    // cout << "\nCanceled ";
    // currentTime();
    t->cancel();
}

void Alarm::SetFromNowImp(int time){
    // cout << "Set " << time << "ms later ";
    // currentTime();
    boost::asio::io_service io;
    t = new boost::asio::deadline_timer(io);
    t->expires_from_now(boost::posix_time::milliseconds(time));
    t->async_wait(boost::bind(&Alarm::OnAlarm, this, boost::asio::placeholders::error));
    io.run();
}

void Alarm::UpdateFromNowImp(int time){
    // cout << "Update " << time << "ms later ";
    // currentTime();
    if( t->expires_from_now(boost::posix_time::milliseconds(time))<=0 ){
		// cout << "Already Expired. \n";
        boost::asio::io_service io;
        t = new boost::asio::deadline_timer(io);
        t->expires_from_now(boost::posix_time::milliseconds(time));
        t->async_wait(boost::bind(&Alarm::OnAlarm, this, boost::asio::placeholders::error));
        io.run();
    }
    else{
        t->async_wait(boost::bind(&Alarm::OnAlarm, this, boost::asio::placeholders::error));
    }
}

void Alarm::OnAlarm(const boost::system::error_code& e)
{
    if (e != boost::asio::error::operation_aborted){
        // std::cout << "Hello, world! ";
        // currentTime();
        // cout << "\n";s
    }
}