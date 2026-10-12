#include "core/AppClock.h"

bool      AppClock::s_mocked = false;
QDateTime AppClock::s_mock;

QDateTime AppClock::now()
{
    return s_mocked ? s_mock : QDateTime::currentDateTime();
}

void AppClock::setMock(const QDateTime& dt)
{
    s_mock   = dt;
    s_mocked = true;
}

void AppClock::clearMock()
{
    s_mocked = false;
    s_mock   = QDateTime();
}

bool AppClock::isMocked()
{
    return s_mocked;
}
