#ifndef INFO_VIEW_HPP
#define INFO_VIEW_HPP

#include <gui_generated/info_screen/InfoViewBase.hpp>
#include <gui/info_screen/InfoPresenter.hpp>

class InfoView : public InfoViewBase
{
public:
    InfoView();
    virtual ~InfoView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // INFO_VIEW_HPP
