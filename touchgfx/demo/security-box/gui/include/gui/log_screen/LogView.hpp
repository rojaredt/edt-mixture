#ifndef LOG_VIEW_HPP
#define LOG_VIEW_HPP

#include <gui_generated/log_screen/LogViewBase.hpp>
#include <gui/log_screen/LogPresenter.hpp>

class LogView : public LogViewBase
{
public:
    LogView();
    virtual ~LogView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();
protected:
    int firstTime;
};

#endif // LOG_VIEW_HPP
