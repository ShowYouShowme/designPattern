#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <algorithm>

namespace ObserverPattern
{
    struct IObserver
    {
        virtual void update(float temp, float humidity, float pressure) = 0;
    };
    struct ISubject
    {
        virtual void registerObserver(std::shared_ptr<IObserver> observer) = 0;
        virtual void removeObserver(std::shared_ptr<IObserver> observer) = 0;
        virtual void notifyObservers() = 0;
    };
    class WeatherData : public ISubject
    {
    private:
        std::shared_ptr<std::vector<std::shared_ptr<IObserver>>> m_observers;
        float m_temperature;
        float m_humidity;
        float m_pressure;
    public:
        WeatherData()
        {
            this->m_observers = std::make_shared<std::vector<std::shared_ptr<IObserver>>>();
        }

        void registerObserver(std::shared_ptr<IObserver> observer)
        {
            this->m_observers->push_back(observer);
        }

        void removeObserver(std::shared_ptr<IObserver> observer)
        {
            auto it = std::find(this->m_observers->begin(), this->m_observers->end(), observer);
            if (it != this->m_observers->end())
            {
                this->m_observers->erase(it);
            }
        }

        void notifyObservers()
        {
            auto Fun = [this](std::shared_ptr<IObserver> observer)
            {
                observer->update(this->m_temperature, this->m_humidity, this->m_pressure);
            };
            std::for_each(this->m_observers->begin(), this->m_observers->end(), Fun);
        }

        void setMeasurements(float temperature, float humidity, float pressure)
        {
            this->m_temperature = temperature;
            this->m_humidity = humidity;
            this->m_pressure = pressure;
            this->notifyObservers();
        }
    };

    class CurrentConditionsDisplay : public IObserver
    {
    private:
        float m_temperature;
        float m_humidity;
    public:
        CurrentConditionsDisplay(std::shared_ptr<ISubject> subject)
        {
            subject->registerObserver(std::shared_ptr<CurrentConditionsDisplay>(this));
        }
        void update(float temp, float humidity, float pressure)
        {
            this->m_temperature = temp;
            this->m_humidity = humidity;
            std::cout << std::string("Current conditions: ") + std::to_string(this->m_temperature) + "F degrees and "
                + std::to_string(this->m_humidity) + "% humidity" + "\n";
        }
    };

    class ForecastDisplay : public IObserver
    {
    private:
        float m_currentPressure;
        float m_lastPressure;
    public:
        ForecastDisplay(std::shared_ptr<ISubject> subject)
        {
            this->m_currentPressure = 29.92f;
            subject->registerObserver(std::shared_ptr<ForecastDisplay>(this));
        }

        void update(float temp, float humidity, float pressure)
        {
            this->m_lastPressure = this->m_currentPressure;
            this->m_currentPressure = pressure;
            std::cout << std::string("Forecast: ") + "m_lastPressure:" + std::to_string(this->m_lastPressure)
                + " m_currentPressure:" + std::to_string(this->m_currentPressure) + "\n";
        }
    };

    class Client
    {
    public:
        static void main()
        {
            auto weatherData = std::make_shared<WeatherData>();
            auto currentDisplay = std::make_shared<CurrentConditionsDisplay>(weatherData);
            auto forecastDisplay = std::make_shared<ForecastDisplay>(weatherData);

            weatherData->setMeasurements(80, 65, 30.4f);
            weatherData->setMeasurements(82, 70, 29.2f);
            weatherData->setMeasurements(78, 90, 29.2f);
        }
    };
}

int main()
{
    ObserverPattern::Client::main();
    return 1;
}