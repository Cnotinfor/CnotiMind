#ifndef MEMORYMODEL_H
#define MEMORYMODEL_H

#include <QAbstractTableModel>

class MemoryModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit MemoryModel(QObject *parent = 0);

signals:

public slots:

};

#endif // MEMORYMODEL_H
