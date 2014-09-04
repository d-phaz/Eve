
#pragma once
#ifndef __EVE_CORE_MACRO_H__
#define __EVE_CORE_MACRO_H__


/**
* \macro EVE_DISABLE_COPY
* disable copy constructor and assignation operator for target class making them private
*/
#define EVE_DISABLE_COPY( targetClass )			\
private:										\
	targetClass(targetClass& arg);				\
	void operator=(const targetClass& arg);


#endif // __EVE_CORE_MACRO_H__
