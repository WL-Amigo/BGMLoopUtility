#include "includes/BytesToIntUtility.hpp"

BytesToIntUtility::BytesToIntUtility()
{

}

quint32 BytesToIntUtility::toUInt32(const QByteArray &data, bool bigEndian){
    Q_ASSERT(data.size() == 4);
    quint32 ret = 0;
    const char* dataPtr = data.data();
    ret = *(reinterpret_cast<const quint32*>(dataPtr));
    return ret;
}

quint16 BytesToIntUtility::toUInt16(const QByteArray& data, bool bigEndian){
    Q_ASSERT(data.size() == 2);
    quint16 ret = 0;
    const char* dataPtr = data.data();
    ret = *(reinterpret_cast<const quint16*>(dataPtr));
    return ret;
}

qint16 BytesToIntUtility::toInt16(const QByteArray& data, bool bigEndian){
    Q_ASSERT(data.size() == 2);
    qint16 ret = 0;
    const char* dataPtr = data.data();
    ret = *(reinterpret_cast<const qint16*>(dataPtr));
    return ret;
}
