#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"

bool show_about_dialog = false;

class ExampleLayer : public Walnut::Layer
{
public:
	virtual void OnUIRender() override
	{
		ImGui::Begin("Hello");
		ImGui::Button("Button");
		ImGui::End();

		ImGui::ShowDemoWindow();
	}
};

void ShowAboutDialog()
{
    if (show_about_dialog)
    {
        ImGui::Begin("About", &show_about_dialog, ImGuiWindowFlags_AlwaysAutoResize);

        ImGui::Text("Walnut");
        ImGui::Separator();
        ImGui::Text("Version: 1.0.0");
        ImGui::Text("Developed in: CPP");
        ImGui::Text("Website: https://github.dev/StudioCherno/Walnut/tree/master/Walnut");

        if (ImGui::Button("Close"))
        {
            show_about_dialog = false;
        }

        ImGui::End();
    }
}

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Walnut Example";

	Walnut::Application* app = new Walnut::Application(spec);
	app->PushLayer<ExampleLayer>();
	app->SetMenubarCallback([app]()
	{
		if (ImGui::BeginMenu("File")&&ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				app->Close();
			}else if(ImGui::MenuItem("About"))
			{
				//show a dialog
				show_about_dialog = true;
				ShowAboutDialog();
			}
			ImGui::EndMenu();
		}
	});
	return app;
}