#include "screenrotator.h"
#include <QProcess>
#include <KPluginFactory>

ScreenRotator::ScreenRotator(QObject *parent, const QVariantList &) :
  KDEDModule(parent)
{
	sensor = new QOrientationSensor(this);

	sensor->start();

	connect(sensor, &QOrientationSensor::readingChanged, this, &ScreenRotator::updateOrientation);

	updateOrientation();
}

void ScreenRotator::updateOrientation() {
	if (!sensor->reading()) return;
	currentOrientation = sensor->reading()->orientation();
	QString o;
	switch (currentOrientation) {
		case QOrientationReading::TopUp:
			o = "normal";
			break;
		case QOrientationReading::TopDown:
			o = "bottom-up";
			break;
		case QOrientationReading::LeftUp:
			o = "left-up";
			break;
		case QOrientationReading::RightUp:
			o = "right-up";
			break;
		default:
			o = "none";
			return;
	}

	helper.start("orientation-helper", {"-r", o});

}

ScreenRotator::~ScreenRotator()
{
	delete sensor;
}

K_PLUGIN_FACTORY(ScreenRotatorFactory,
                 registerPlugin<ScreenRotator>();)
#include "screenrotator.moc"
