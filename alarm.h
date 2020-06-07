#ifndef ALARM_H
#define ALARM_H

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <time.h>

class Alarm{
public:
    Alarm();

    void SetFromNow(int time);
    void UpdateFromNow(int time);

    void SetFromNowImp(int time);
    void UpdateFromNowImp(int time);
    void Cancel();
    virtual void OnAlarm(const boost::system::error_code& e) = 0;

public:
    // boost::asio::io_service io_service_;
    boost::asio::deadline_timer *t;
};

#endif // ALARM_H
