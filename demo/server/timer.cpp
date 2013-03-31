#include "timer.h"

std::set<CSockTime, sortByTime> timeSet;

CSockTime::CSockTime() {}

CSockTime::CSockTime(int s, long time)
{
	sock = s;
	activeTime = time;
}

CSockTime::~CSockTime() {}

const int CSockTime::getSock() const
{
	return sock;
}

void CSockTime::setSock(const int s)
{
	sock = s;
}

const long CSockTime::getActiveTime() const
{
	return activeTime;
}

void CSockTime::setActiveTime(const long time)
{
	activeTime = time;
}

void update_timer(int sock, long nowTime)
{
	std::set<CSockTime, sortByTime>::iterator iter;
	for(iter = timeSet.begin(); iter != timeSet.end(); iter++)
    {
    	if (iter->getSock() == sock)
    	{
    		CSockTime temp(*iter);
    		timeSet.erase(iter++);
    		temp.setSock(sock);
    		temp.setActiveTime(nowTime);
    		timeSet.insert(iter, temp);
    		return ;
    	}
    }
    if (iter == timeSet.end())
    {
    	CSockTime t(sock, nowTime);
    	timeSet.insert(t);
    }
}

void del_timer(int sock)
{
    std::set<CSockTime, sortByTime>::iterator iter;

    for(iter = timeSet.begin(); iter != timeSet.end(); iter++)
    {
        if (iter->getSock() == sock)
        {
            timeSet.erase(iter++);
            break;
        }
    }
}

long find_timer(long current_msec, long keepalive_timeout)
{
	if (timeSet.size() == 0)
	{
		return TIMER_INFINITE;
	}
	long interval = timeSet.begin()->getActiveTime() + keepalive_timeout - current_msec;
	return (interval > 0 ? interval : 0);
}