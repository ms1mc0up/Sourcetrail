#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

#include "component/ComponentManager.h"
#include "Project.h"
#include "utility/messaging/MessageListener.h"
#include "utility/messaging/type/MessageLoadProject.h"
#include "utility/messaging/type/MessageLoadSource.h"

class GuiFactory;
class MainView;
class Storage;

class Application
	: public MessageListener<MessageLoadProject>
	, public MessageListener<MessageLoadSource>
{
public:
	static std::shared_ptr<Application> create(GuiFactory* guiFactory);

	~Application();

	void loadProject(const std::string& projectSettingsFilePath);
	void loadSource(const std::string& sourceDirectoryPath);

private:
	Application();

	virtual void handleMessage(MessageLoadProject* message);
	virtual void handleMessage(MessageLoadSource* message);

	std::shared_ptr<Project> m_project;
	std::shared_ptr<Storage> m_storage;

	std::shared_ptr<MainView> m_mainView;
	std::shared_ptr<ComponentManager> m_componentManager;
};

#endif // APPLICATION_H
