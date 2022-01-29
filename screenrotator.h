#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QOrientationSensor>
#include <QProcess>
#include <KDEDModule>
#include <KPluginFactory>

class ScreenRotator : public KDEDModule
{
		Q_OBJECT

	public:
		ScreenRotator(QObject *parent, const QVariantList &);
		void updateOrientation();
		~ScreenRotator();

	private:
		QOrientationSensor *sensor;
		QOrientationReading::Orientation currentOrientation;
		QProcess helper;
};

#endif // MAINWINDOW_H
