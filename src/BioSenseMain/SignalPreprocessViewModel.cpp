#include "SignalPreprocessViewModel.h"

namespace Bio
{
    SignalPreprocessViewModel::SignalPreprocessViewModel(QObject *parent)
        : QObject(parent)
    {
    }

    void SignalPreprocessViewModel::preprocess(const QVector<double> &signal)
    {
        //m_model.preprocess(signal);
        m_processed = true; // 可根据实际情况判断
        emit processedChanged();
    }

    bool SignalPreprocessViewModel::processed() const
    {
        return m_processed;
    }
}