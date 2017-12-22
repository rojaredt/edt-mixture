#include <gui/log_screen/LogView.hpp>
#include <gui/log_screen/LogPresenter.hpp>

LogPresenter::LogPresenter(LogView& v)
    : view(v)
{
}

void LogPresenter::activate()
{
  //readLoginRecord();
}

void LogPresenter::deactivate()
{

}

void LogPresenter::readLoginRecord()
{
	model->pushData(210);
}