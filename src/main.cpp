#include <QApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include "uivalues.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QCoreApplication::setOrganizationName("%CompanyName:c%");
    QCoreApplication::setOrganizationDomain("%CompanyName:l%.%TopDomainName%");
    QCoreApplication::setApplicationName("%ProjectName%");

    UIValues uiValues;
    engine.rootContext()->setContextProperty("ui", &uiValues);

#if defined(Q_OS_ANDROID)
    engine.rootContext()->setContextProperty("Q_OS", "ANDROID");
#elif defined(Q_OS_LINUX)
    engine.rootContext()->setContextProperty("Q_OS", "LINUX");
#elif defined(Q_OS_WINDOWS)
    engine.rootContext()->setContextProperty("Q_OS", "WINDOWS");
#else
    engine.rootContext()->setContextProperty("Q_OS", "UNKNOWN");
#endif

    engine.load(QUrl(QStringLiteral("qrc:/qml/qml/main.qml")));

    return app.exec();
}
