#include "DataSaveViewModel.h"

namespace Bio
{
    DataSaveViewModel::DataSaveViewModel(QObject *parent)
        : QObject(parent)
    {
    }

    void DataSaveViewModel::save(const QString &path, const QVariant &data)
    {
        //m_saved = m_model.save(path, data);
        emit savedChanged();
    }

    bool DataSaveViewModel::saved() const
    {
        return m_saved;
    }
}