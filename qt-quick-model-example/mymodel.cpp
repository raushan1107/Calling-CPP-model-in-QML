#include "mymodel.h"

#include <QByteArray>
#include <QTimer>
#include <cstdlib>      // Still needed for RAND_MAX if you use it in other places, but not directly for random generation here.
#include <random>       // NEW: For std::mt19937, std::random_device, std::uniform_real_distribution
#include <chrono>       // NEW: For std::chrono::system_clock (to seed random)
#include <QDebug>       // Optional: For console output, useful for debugging

MyModel::MyModel(QObject *parent)
    : QAbstractListModel{parent}
{
    m_data
        << Data("Denmark", "file:denmark.jpg", 5.6)
        << Data("Sweden", "file:sweden.jpg", 9.6)
        << Data("Iceland", "file:iceland.jpg", 0.3)
        << Data("Norway", "file:norway.jpg", 5.1)
        << Data("Finland", "file:finland.jpg", 5.4);

    QTimer *growthTimer = new QTimer(this);
    connect(growthTimer, &QTimer::timeout, this, &MyModel::growPopulation);
    growthTimer->start(2000);
}

int MyModel::rowCount( const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;

    return m_data.count();
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if ( !index.isValid() )
        return QVariant();

    const Data &data = m_data.at(index.row());
    if ( role == NameRole ){
        return data.name;
    }
    else if ( role == FlagRole )
        return data.flag;
    else if ( role == PopulationRole )
        return data.population;
    else
        return QVariant();
}

QHash<int, QByteArray> MyModel::roleNames() const
{
    static QHash<int, QByteArray> mapping {
        {NameRole, "name"},
        {FlagRole, "flag"},
        {PopulationRole, "population"}
    };
    return mapping;
}

void MyModel::duplicateData(int row)
{
    if (row < 0 || row >= m_data.count())
        return;

    const Data data = m_data[row];
    const int rowOfInsert = row + 1;

    beginInsertRows(QModelIndex(), rowOfInsert, rowOfInsert);
    m_data.insert(rowOfInsert, data);
    endInsertRows();
}

void MyModel::removeData(int row)
{
    if (row < 0 || row >= m_data.count())
        return;

    beginRemoveRows(QModelIndex(), row, row);
    m_data.removeAt(row);
    endRemoveRows();
}

void MyModel::growPopulation()
{
    // --- FIX START ---
    // Use C++11 standard library random number generation instead of qrand()
    // These static variables are initialized only once when the function is first called.
    static std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
    // Create a uniform real distribution to get a random double between 0.0 and 1.0
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);

    const double baseGrowthRate = 0.01; // This is equivalent to your original 0.01

    const int count = m_data.count();
    for (int i = 0; i < count; ++i) {
        // Generate a random factor between 0.0 and 1.0 using the distribution
        m_data[i].population += m_data[i].population * distribution(generator) * baseGrowthRate;
    }
    // --- FIX END ---

    const QModelIndex startIndex = index(0, 0);
    const QModelIndex endIndex   = index(count - 1, 0);

    emit dataChanged(startIndex, endIndex, QVector<int>() << PopulationRole);
}
