#pragma once
#include <QObject>
#include "SignalPreprocessModule.h"

namespace Bio
{
    class SignalPreprocessViewModel : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(bool processed READ processed NOTIFY processedChanged)
    public:
        explicit SignalPreprocessViewModel(QObject *parent = nullptr);

        Q_INVOKABLE void preprocess(const QVector<double> &signal);

        bool processed() const;

    signals:
        void processedChanged();

    private:
        SignalPreprocessModule m_model;
        bool m_processed = false;
    };
}