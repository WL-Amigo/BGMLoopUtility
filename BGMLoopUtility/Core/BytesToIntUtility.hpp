#ifndef BYTESTOINTUTILITY_HPP
#define BYTESTOINTUTILITY_HPP

#include <QtCore>

class BytesToIntUtility
{
public:
    BytesToIntUtility();

    static quint32 toUInt32(const QByteArray &data, bool bigEndian = false);
    static quint16 toUInt16(const QByteArray& data, bool bigEndian = false);
    static qint16 toInt16(const QByteArray& data, bool bigEndian = false);
};

#endif // BYTESTOINTUTILITY_HPP
