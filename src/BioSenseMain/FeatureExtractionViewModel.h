#pragma once
#include <QObject>
#include "FeatureExtractionModule.h"

namespace Bio
{
    class FeatureExtractionViewModel : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(double heartRate READ heartRate NOTIFY featuresChanged)
        Q_PROPERTY(int rPeakCount READ rPeakCount NOTIFY featuresChanged)
        // ...可添加更多属性...

    public:
        explicit FeatureExtractionViewModel(QObject *parent = nullptr);

        Q_INVOKABLE void extract(const QVector<double>& signal);

        double heartRate() const;
        int rPeakCount() const;

    signals:
        void featuresChanged();

    private:
        FeatureExtractionModule m_model;
        double m_heartRate = 0.0;
        int m_rPeakCount = 0;
    };
}