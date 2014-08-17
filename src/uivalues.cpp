#include "uivalues.h"

#ifdef Q_OS_ANDROID
#include <QAndroidJniObject>
#endif

#include <QScreen>
#include <QSettings>
#include <QDebug>
#include <QGuiApplication>

UIValues::UIValues(QObject *parent) :
    QObject(parent),
    m_dpi(0),
    m_isTablet(false)
{
    QSettings settings;
    m_firstRun = settings.value("firstRun", true).toBool();

#ifdef Q_OS_ANDROID
    m_dpi = QAndroidJniObject::callStaticMethod<jint>("%TopDomainName:l%/%CompanyName:l%/%ProjectName:l%/%ProjectName:c%",
                                                      "getDPI", "()I");

    m_isTablet = QAndroidJniObject::callStaticMethod<jboolean>("%TopDomainName:l%/%CompanyName:l%/%ProjectName:l%/%ProjectName:c%",
                                                               "isTablet", "()Z");
#else
    m_dpi = QGuiApplication::primaryScreen()->physicalDotsPerInch();
#endif

    m_dpMultiplier = (float) m_dpi / 160;
}

void UIValues::showMessage(const QString &message)
{
#ifdef Q_OS_ANDROID
    QAndroidJniObject::callStaticMethod<void>("%TopDomainName:l%/%CompanyName:l%/%ProjectName:l%/%ProjectName:c%",
                                              "toast", "(Ljava/lang/String;)V",
                                              QAndroidJniObject::fromString(message).object<jstring>());
#else
    qDebug() << Q_FUNC_INFO << "Not implemented yet";
    qDebug() << message;
#endif
}

QString UIValues::getBestIconSize(int height) const
{
    if (height < 42)
        return "ldpi/";
    else if (height < 60)
        return "mdpi/";
    else if (height < 84)
        return "hdpi/";
    else if (height < 120)
        return "xhdpi/";
    else if (height < 168)
        return "xxhdpi/";
    else if (height < 216)
        return "xxxhdpi/";
    else
        return "";
}

bool UIValues::firstRun() const
{
    return m_firstRun;
}

void UIValues::setFirstRun(bool firstRun)
{
    if (m_firstRun == firstRun)
        return;

    m_firstRun = firstRun;
    emit firstRunChanged();
}

int UIValues::dpi() const
{
    return m_dpi;
}

void UIValues::setDpi(int dpi)
{
    if (m_dpi == dpi)
        return;

    m_dpi = dpi;
    emit dpiChanged();

    setDpMultiplier((float) m_dpi / 160);
}

float UIValues::dpMultiplier() const
{
    return m_dpMultiplier;
}

void UIValues::setDpMultiplier(float dpMultiplier)
{
    if (m_dpMultiplier == dpMultiplier)
        return;

    m_dpMultiplier = dpMultiplier;
    emit dpMultiplierChanged();
}

bool UIValues::isTablet() const
{
    return m_isTablet;
}

void UIValues::setIsTablet(bool isTablet)
{
    if (m_isTablet == isTablet)
        return;

    m_isTablet = isTablet;
    emit isTabletChanged();
}
