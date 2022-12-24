#include "imgui.h"
#include "OpencvWindow.h"

OpencvWindow::OpencvWindow() {
}

OpencvWindow::~OpencvWindow() {
	read_flag = false;
	cap.release();
}


void OpencvWindow::readOpenCV() {
	if (!cap.read(frame))
	{
		printf("Can not load Cameras\n");
		read_flag = false;
	}
	else
	{
		width = frame.cols;
		height = frame.rows;
		channel = frame.channels();

		//获取图像指针
		int pixellength = width * height * channel;
		GLubyte* pixels = new GLubyte[pixellength];
		memcpy(pixels, frame.data, pixellength * sizeof(char));

		// 首先删除贴图再使用GL指令生成贴图，获取贴图ID
		glDeleteTextures(1, &textureID);
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
		//纹理放大缩小使用线性插值
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(textureID, 0);

		free(pixels);
	}
}


void OpencvWindow::ShowOpencvWindow(std::variant<const char*, int> source, bool* p_open) {
	int device_num = NULL;
	const char* source_url = "";

	const char* title = "";

	if (std::holds_alternative<const char*>(source)) {
		source_url = std::get<0>(source);
		title = source_url;
	}
	if (std::holds_alternative<int>(source)) {
		device_num = std::get<1>(source);
		char title_s[10];
		_itoa_s(device_num, title_s, 10);
		title = title_s;
	}
	
	static bool no_close = false;
	if (no_close) p_open = NULL;
	if (!p_open) {
		read_flag = false;
		cap.release();
	}
	// ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
	// ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1);
	ImGui::Begin(title, p_open, 0);
	
	if (ImGui::Button("StartCV", ImVec2(100, 20))) {
		if (std::holds_alternative<const char*>(source))
			cap.open(source_url);
		if (std::holds_alternative<int>(source))
			cap.open(device_num);

		if (!cap.isOpened()) {
			printf("could not red this video file or device\n");
			read_flag = false;
		}
		else {
			read_flag = true;
		}
	}
	ImGui::SameLine();
	if (ImGui::Button("StopCV", ImVec2(100, 20))) {
		read_flag = false;
		cap.release();
	}

	if (read_flag) {
		readOpenCV();
	}	

	ImTextureID image_id = (GLuint*)textureID;
	ImGui::Image(image_id, ImGui::GetContentRegionAvail());

	ImGui::End();
}
