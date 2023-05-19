#include "WeatherData.h"

WeatherData::WeatherData() : net_manager_(new QNetworkAccessManager(this))
{
	connect(net_manager_, &QNetworkAccessManager::finished, this, &WeatherData::handleNetworkData);
}

void WeatherData::handleNetworkData(QNetworkReply *reply)
{
	if (reply->error() == QNetworkReply::NoError) {
		QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
		QJsonObject json = doc.object();
		city_name_ = json["name"].toString();
		temperature_ = json["main"].toObject()["temp"].toDouble();
		humidity_ = json["main"].toObject()["humidity"].toDouble();
		pressure_ = json["main"].toObject()["pressure"].toDouble();
		emit dataChanged();
	}
	reply->deleteLater();
}

QString WeatherData::cityName() const
{
	return city_name_;
}

double WeatherData::temperature() const
{
	return temperature_;
}

double WeatherData::humidity() const
{
	return humidity_;
}

double WeatherData::pressure() const
{
	return pressure_;
}

void WeatherData::updateWeatherData()
{
    QString appid = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
	QUrl url("http://api.openweathermap.org/data/2.5/weather?zip=227-0062,JP&appid=" + appid + "&mode=json&_dummy_=" + QString::number(++ser_));
	net_manager_->get(QNetworkRequest(url));
}
