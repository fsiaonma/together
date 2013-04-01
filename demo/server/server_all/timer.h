#ifndef TIMER_INFINITE
#define TIMER_INFINITE -1
#endif

#ifndef _TIMER_H_
#define _TIMER_H_

#include <set>


class CSockTime
{
public:
	CSockTime();
	CSockTime(int s, long time);
	~CSockTime();
	const int getSock() const;
	void setSock(const int s);
	const long getActiveTime() const;
	void setActiveTime(const long time);
private:
	int sock;
	long activeTime;
};

// 按活动时间从小到大排序
class sortByTime
{
public:
	bool operator() (CSockTime const &_A, CSockTime const &_B) const
	{
		if (_A.getActiveTime() < _B.getActiveTime())
			return true;
		else
			return false;
	}
};

extern std::set<CSockTime, sortByTime> timeSet;

// 更新定时器(不存在则插入)
void update_timer(int sock, long nowTime);

// 删除定时器
void del_timer(int sock);

// 返回epoll_wait的超时时间,如果集合里面没有就返回TIMER_INFINITE(-1,无限等待),否则就返回最短的超时时间
long find_timer(long current_msec, long keepalive_timeout);


#endif
