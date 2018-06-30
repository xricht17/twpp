#ifndef TWGLUE_HPP
#define TWGLUE_HPP

#include <functional>

struct TwGlue {

    TwGlue(const std::function<void()>& scan, const std::function<void()>& cancel) :
        m_scan(scan), m_cancel(cancel){}

    std::function<void()> m_scan;
    std::function<void()> m_cancel;

};

#endif // TWGLUE_HPP
