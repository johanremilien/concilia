#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "speakingtimerecorder.h"
#include "speakingtimeanalyser.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    SpeakingTimeRecorder speakingTimeRecorder;
    engine.rootContext()->setContextProperty("recorder", &speakingTimeRecorder);

    SpeakingTimeAnalyser speakingTimeAnalyser;
    engine.rootContext()->setContextProperty("analyser", &speakingTimeAnalyser);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
