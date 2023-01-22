#pragma once


template<typename T>
//Get a 2 digit percent of type
//Useful for unsigned in 
T percent(T num, T denum)
{
	while (num > 255)
	{
		num >>= 2;
		denum >>= 2;
	}

	num *= 100;

	return num / denum;
}