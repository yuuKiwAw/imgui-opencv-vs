#pragma once
#include <GLFW/glfw3.h>
#include "opencv.hpp"
#include <thread>
#include <mutex>
#include <variant>

class OpencvWindow {
private:
	int width = 0;
	int height = 0;
	int channel = 0;
	cv::Mat frame;
	cv::VideoCapture cap;
	bool read_flag = false;
	
	GLuint textureID;
	
	void readOpenCV();

public:
	OpencvWindow();
	~OpencvWindow();
	void ShowOpencvWindow(std::variant<const char*, int> source, bool* p_open);
};
