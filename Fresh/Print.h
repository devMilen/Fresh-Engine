#pragma once
#include <iostream>
#include "assert.h"
#include "Animation.h"

class Print
{
public:
	template<class T, unsigned int size>
	void Vec(std::vector<T>& vec, const char* name)
	{
		std::cout << "-------------------std::vector: " << name << "-----------------------" << std::endl;
		for (const T& val : vec)
			std::cout << val << ", ";
		std::cout << std::endl;
		std::cout << "-------------------END OF: " << name << "-----------------------" << std::endl;
	}

	template<class T>
	void Vec2D(const std::vector<std::vector<T>>& vec2D, const char* name)
	{
		std::cout << "-------------------2D vector: " << name << "-----------------------" << std::endl;
		for (size_t i = 0; i < vec2D.size(); ++i)
		{
			std::cout << "Row " << i << ": ";
			for (const T& val : vec2D[i])
				std::cout << val << ", ";
			std::cout << std::endl;
		}
		std::cout << "-------------------END OF: " << name << "-----------------------" << std::endl;
	}

	template<class T, unsigned int size>
	void Arr(std::array<T, size>& arr, const char* name)
	{
		std::cout << "-------------------std::array: " << name << "-----------------------" << std::endl;
		for (const T& val : arr)
			std::cout << val << ", ";
		std::cout << std::endl;
		std::cout << "-------------------END OF: " << name << "-----------------------" << std::endl;
	}

	template<class T, unsigned int size, unsigned int secSize>
	void Arr2D(std::array<std::array<T, size>, secSize>& arr, const char* name)
	{
		std::cout << "-------------------2D std::array: " << name << "-----------------------" << std::endl;
		for (size_t i = 0; i < secSize; ++i)
		{
			std::cout << "Row " << i << ": ";
			for (size_t j = 0; j < size; ++j)
				std::cout << arr[i][j] << ", ";
			std::cout << std::endl;
		}
		std::cout << "-------------------END OF: " << name << "-----------------------" << std::endl;
	}

	template<class T, unsigned int size>
	void CArr(const T* arr, const char* name)
	{
		std::cout << "-------------------C-style array: " << name << "-----------------------" << std::endl;
		for (unsigned int i = 0; i < size; ++i)
			std::cout << arr[i] << ", ";
		std::cout << std::endl;
		std::cout << "-------------------END OF: " << name << "-----------------------" << std::endl;
	}


	static void Info(const Animation& anim, const char* name);
	static void Info(const Transform& anim, const char* name);
	static void Info(const Sprite& sprite, const char* name);
};
