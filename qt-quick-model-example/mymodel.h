#ifndef MYMODEL_H
#define MYMODEL_H
#include <QAbstractListModel>
#include <QColor>

struct Data {
    Data() {}
    Data( const QString& name, const QString& flag, double population )
        : name(name), flag(flag), population(population) {}
    QString name;
    QString flag;
    double population;
};


class MyModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        NameRole = Qt::UserRole,
        FlagRole,
        PopulationRole
    };
    int rowCount(const QModelIndex& parent) const override;
    QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;
    QHash<int, QByteArray> roleNames() const override;

    explicit MyModel(QObject *parent = nullptr);

public slots:
    void duplicateData(int row);
    void removeData(int row);

private slots:
    void growPopulation();

private: //members
    QVector< Data > m_data;

};

#endif // MYMODEL_H
