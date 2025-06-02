#pragma once
#include <QObject>
#include "StateEvaluationModule.h"

namespace Bio
{
    class StateEvaluationViewModel : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString state READ state NOTIFY stateChanged)
    public:
        explicit StateEvaluationViewModel(QObject *parent = nullptr);

        Q_INVOKABLE void evaluate(const QVector<double> &signal);

        QString state() const;

    signals:
        void stateChanged();

    private:
        StateEvaluationModule m_model;
        QString m_state;
    };
}