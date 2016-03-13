/*
 * singleton.h
 *
 * Copyright (C) 2014 William Markezana <william.markezana@meas-spec.com>
 *
 */

#ifndef SINGLETON_H
#define SINGLETON_H

#include <cstdlib>

template<typename T> class singleton
{
private:
	static T *_singleton;
protected:
	singleton() {}
	~singleton() {}
public:
	static T *shared_instance()
	{
		if (NULL == _singleton)
		{
			_singleton = new T;
		}
		return (static_cast<T*>(_singleton));
	}

	static void kill()
	{
		if (NULL != _singleton)
		{
			delete _singleton;
			_singleton = NULL;
		}
	}
};

template<typename T> T *singleton<T>::_singleton = NULL;

#endif
