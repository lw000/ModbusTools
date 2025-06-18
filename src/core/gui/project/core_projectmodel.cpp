/*
    Modbus Tools

    Created: 2023
    Author: Serhii Marchuk, https://github.com/serhmarch

    Copyright (C) 2023  Serhii Marchuk

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#include "core_projectmodel.h"

#include <QMimeData>

#include <project/core_project.h>
#include <project/core_port.h>
#include <project/core_device.h>

#include <gui/core_ui.h>

mbCoreProjectModel::Strings::Strings() :
    mimeTypeDevice(QStringLiteral("application/x-modbustools-device"))

{
}

const mbCoreProjectModel::Strings &mbCoreProjectModel::Strings::instance()
{
    static const Strings s;
    return s;
}

mbCoreProjectModel::mbCoreProjectModel(QObject* parent) :
    QAbstractItemModel (parent)
{
    m_project = nullptr;
    m_settings.useNameWithSettings = mbCoreUi::Defaults::instance().settings_useNameWithSettings;
}

QVariant mbCoreProjectModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        switch (orientation)
        {
        case Qt::Horizontal:
            switch(section)
            {
            case 0: return QStringLiteral("Name");
            }
            break;
        default:
            break;
        }
    }
    return QVariant();
}

int mbCoreProjectModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 1;
}

bool mbCoreProjectModel::hasChildren(const QModelIndex &parent) const
{
    return rowCount(parent) > 0;
}

Qt::ItemFlags mbCoreProjectModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags f = QAbstractItemModel::flags(index);
    return f;
}

Qt::DropActions mbCoreProjectModel::supportedDropActions() const
{
    return Qt::MoveAction | Qt::CopyAction;
}

QStringList mbCoreProjectModel::mimeTypes() const
{
    return {mbCoreProjectModel::Strings::instance().mimeTypeDevice};
}

QMimeData *mbCoreProjectModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();
    if (indexes.size() == 1)
    {
        QModelIndex index = indexes.first();
        if (mbCoreDevice *dev = this->getDeviceByIndex(index))
        {
            QByteArray encoded;
            QDataStream stream(&encoded, QIODevice::WriteOnly);
            mbCorePort *port = getPortByIndex(indexes.first());
            stream << port->name() << index.row();
            mimeData->setData(mbCoreProjectModel::Strings::instance().mimeTypeDevice, encoded);
        }
    }
    return mimeData;
}

bool mbCoreProjectModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if (!data->hasFormat(mbCoreProjectModel::Strings::instance().mimeTypeDevice))
        return false;
    QByteArray encoded = data->data(mbCoreProjectModel::Strings::instance().mimeTypeDevice);
    QDataStream stream(&encoded, QIODevice::ReadOnly);
    QString srcPortName;
    int srcIndex;
    stream >> srcPortName >> srcIndex;
    mbCoreProject *prj = projectCore();
    if (!prj)
        return false;
    mbCorePort *srcPort = prj->portCore(srcPortName);
    mbCoreDevice *device = prj->deviceCore(srcIndex);
    if (!srcPort || !device)
        return false;
    QModelIndex portIndex = parent;
    if (!portIndex.isValid())
        portIndex = index(row, column);
    mbCorePort *dstPort = portCore(portIndex);
    if (!dstPort)
    {
        dstPort = prj->portCore(prj->portCount()-1);
        if (!dstPort)
            return false;
    }
    return dropDevice(action, srcPort, srcIndex, dstPort, row);
}

void mbCoreProjectModel::setUseNameWithSettings(bool use)
{
    if (m_settings.useNameWithSettings != use)
    {
        beginResetModel();
        m_settings.useNameWithSettings = use;
        endResetModel();
    }
}

QModelIndex mbCoreProjectModel::portIndex(mbCorePort *port) const
{
    if (m_project)
    {
        int i = m_project->portIndex(port);
        return createIndex(i, 0, port);
    }
    return QModelIndex();
}

mbCorePort *mbCoreProjectModel::portCore(const QModelIndex &index) const
{
    if (index.parent().isValid() || !m_project)
        return nullptr;
    return reinterpret_cast<mbCorePort*>(index.internalPointer());
}

mbCorePort *mbCoreProjectModel::getPortByIndex(const QModelIndex &index) const
{
    return portCore(index);
}

mbCoreDevice *mbCoreProjectModel::getDeviceByIndex(const QModelIndex &/*index*/) const
{
    return nullptr;
}

void mbCoreProjectModel::portAdd(mbCorePort *port)
{
    int i = m_project->portIndex(port);
    beginInsertRows(QModelIndex(), i, i);
    connect(port, &mbCorePort::changed, this, &mbCoreProjectModel::portChanged);
    endInsertRows();
}

void mbCoreProjectModel::portRemove(mbCorePort *port)
{
    int i = m_project->portIndex(port);
    beginRemoveRows(QModelIndex(), i, i);
    port->disconnect(this);
    endRemoveRows();
}

QString mbCoreProjectModel::portName(const mbCorePort *port) const
{
    if (useNameWithSettings())
        return port->extendedName();
    return port->name();
}

void mbCoreProjectModel::portChanged()
{
    mbCorePort* p = static_cast<mbCorePort*>(sender());
    QModelIndex index = portIndex(p);
    Q_EMIT dataChanged(index, index);
}
