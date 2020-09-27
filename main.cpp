#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "speakingtimeregister.h"
#include "speakingtimerecorder.h"
#include "speakingtimeanalyser.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qRegisterMetaType<ID>("ID");
    engine.rootContext()->setContextProperty("UNDEFINED_ID", UNDEFINED_ID);

    SpeakingTimeRegister speakingTimeRegister;
    engine.rootContext()->setContextProperty("SpeakingTimeRegister", &speakingTimeRegister);

    SpeakingTimeRecorder speakingTimeRecorder;
    engine.rootContext()->setContextProperty("SpeakingTimeRecorder", &speakingTimeRecorder);

    SpeakingTimeAnalyser speakingTimeAnalyser;
    engine.rootContext()->setContextProperty("SpeakingTimeAnalyser", &speakingTimeAnalyser);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) {
            QCoreApplication::exit(-1);
        }
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
