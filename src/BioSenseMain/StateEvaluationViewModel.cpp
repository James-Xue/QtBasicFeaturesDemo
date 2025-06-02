#include "StateEvaluationViewModel.h"

namespace Bio
{
    StateEvaluationViewModel::StateEvaluationViewModel(QObject *parent)
        : QObject(parent)
    {
    }

    void StateEvaluationViewModel::evaluate(const QVector<double> &signal)
    {
        //m_state = m_model.evaluate(signal);
        emit stateChanged();
    }

    QString StateEvaluationViewModel::state() const
    {
        return m_state;
    }
}
