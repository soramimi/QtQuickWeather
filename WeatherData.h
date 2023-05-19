#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <QObject>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QQmlContext>

class WeatherData : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString cityName READ cityName NOTIFY dataChanged)
    Q_PROPERTY(double temperature READ temperature NOTIFY dataChanged)
	Q_PROPERTY(double humidity READ humidity NOTIFY dataChanged)
	Q_PROPERTY(double pressure READ pressure NOTIFY dataChanged)
private:
    void handleNetworkData(QNetworkReply *reply);

    QNetworkAccessManager *net_manager_;
    QString city_name_;
    double temperature_;
	double pressure_;
	double humidity_;
	int ser_ = 0;
public:
    WeatherData();

    QString cityName() const;
    double temperature() const;
	double humidity() const;
	double pressure() const;

    Q_INVOKABLE void updateWeatherData();

signals:
    void dataChanged();

};


#endif // WEATHERDATA_H
