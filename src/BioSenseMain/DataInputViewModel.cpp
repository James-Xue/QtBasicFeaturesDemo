#include "DataInputViewModel.h"

namespace Bio
{
    DataInputViewModel::DataInputViewModel(QObject *parent)
        : QObject(parent)
    {
    }

    void DataInputViewModel::importFile(const QString &path)
    {
        m_model.ImportFile(path);
        m_hasData = true; // 可根据实际情况判断
        emit dataChanged();
    }

    bool DataInputViewModel::hasData() const
    {
        return m_hasData;
    }
}