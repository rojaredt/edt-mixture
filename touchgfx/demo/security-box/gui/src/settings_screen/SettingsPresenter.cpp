#include <gui/settings_screen/SettingsView.hpp>
#include <gui/settings_screen/SettingsPresenter.hpp>

SettingsPresenter::SettingsPresenter(SettingsView& v)
    : view(v)
{
}

void SettingsPresenter::activate()
{

}

void SettingsPresenter::deactivate()
{

}

void SettingsPresenter::clearUnlockLog()
{	
	model->pushData(3);
}