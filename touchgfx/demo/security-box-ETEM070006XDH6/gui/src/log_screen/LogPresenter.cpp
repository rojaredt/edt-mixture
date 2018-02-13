#include <gui/log_screen/LogView.hpp>
#include <gui/log_screen/LogPresenter.hpp>

LogPresenter::LogPresenter(LogView& v)
: view(v)
{
}

void LogPresenter::activate()
{
  
}

void LogPresenter::deactivate()
{
  
}

void LogPresenter::readLoginRecord()
{
  model->pushData(210);
}

void LogPresenter::handleLLMessage(uint16_t *data)
{
  view.showLogList(data);
}