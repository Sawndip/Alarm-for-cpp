#include <time.h>
#include "alarm.h"

using namespace std;

void currentTime_()
{
    struct tm  *tp;
    time_t time_ = time(NULL);
    tp = localtime(&time_);
    printf("%d:%d:%d\n",tp->tm_hour,tp->tm_min,tp->tm_sec);
}

class AnotherAlarm : public Alarm {
  void OnAlarm(const boost::system::error_code& e){
    if (e != boost::asio::error::operation_aborted){
        std::cout << "Hello, Another Alarm! ";
        currentTime_();
        cout << "\n";
    }
  }
};

int main()
{
    AnotherAlarm alarm;
    alarm.SetFromNow(2);
    sleep(1);
    alarm.UpdateFromNow(2);
    usleep(300);    alarm.UpdateFromNow(4);
    usleep(100);    alarm.UpdateFromNow(2);
    usleep(200);    alarm.Cancel();
    usleep(243);    alarm.UpdateFromNow(20);
    usleep(233);    alarm.UpdateFromNow(2);
    usleep(5000);
    return 0;
}
