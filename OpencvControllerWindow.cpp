#include "OpencvControllerWindow.h"
#include "imgui.h"
#include "OpencvWindow.h"

void OpencvControllerWindow::showOpencvControllerWindow() {
	ImGui::Begin("OpencvManager");

	{
		static int num = -1;
		ImGui::Text("Input Type:");
		ImGui::RadioButton("Source", &num, 0); ImGui::SameLine();
		ImGui::RadioButton("Device", &num, 1); ImGui::SameLine();
		ImGui::NewLine();
		
		if (num == 0) {
			static char source[128] = "D:\\\\video\\\\pbr-20221118\\\\3.avi";
			ImGui::InputText("", source, IM_ARRAYSIZE(source));

			if (ImGui::Button("Create")) {
				printf("%s\n", source);
			}
		}
		else if (num == 1) {
			static const char* item_list[] = {"0", "1"};
			static int item_type = 0;
			ImGui::Combo("",& item_type, item_list, IM_ARRAYSIZE(item_list), IM_ARRAYSIZE(item_list));

			ImGui::Button("Create");
		}
	}
	
	ImGui::End();
}