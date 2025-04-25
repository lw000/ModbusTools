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
#ifndef SERVER_PROJECT_H
#define SERVER_PROJECT_H

#include <QObject>

#include <project/core_project.h>

class mbServerPort;
class mbServerDevice;
class mbServerDataView;
class mbServerSimAction;
class mbServerScriptModule;

class mbServerProject : public mbCoreProject
{
    Q_OBJECT

public:
    explicit mbServerProject(QObject *parent = nullptr);
    ~mbServerProject();

public: // ports
    using mbCoreProject::portIndex;
    using mbCoreProject::portAdd;
    using mbCoreProject::portRemove;
    inline bool hasPort(mbServerPort* port) const { return mbCoreProject::hasPort(reinterpret_cast<mbCorePort*>(port)); }
    inline QList<mbServerPort*> ports() const { return QList<mbServerPort*>(*(reinterpret_cast<const QList<mbServerPort*>*>(&m_ports))); }
    inline int portIndex(mbServerPort* port) const { return mbCoreProject::portIndex(reinterpret_cast<mbCorePort*>(port)); }
    inline int portIndex(const QString& name) const { return mbCoreProject::portIndex(name); }
    inline mbServerPort* port(int i) const { return reinterpret_cast<mbServerPort*>(mbCoreProject::portCore(i)); }
    inline mbServerPort* port(const QString& name) const { return reinterpret_cast<mbServerPort*>(mbCoreProject::portCore(name)); }
    inline mbServerPort* portAt(int i) const { return reinterpret_cast<mbServerPort*>(mbCoreProject::portCoreAt(i)); }
    inline int portInsert(mbServerPort* port, int index = -1) { return mbCoreProject::portInsert(reinterpret_cast<mbCorePort*>(port), index); }
    inline int portAdd(mbServerPort* port) { return mbCoreProject::portAdd(reinterpret_cast<mbCorePort*>(port)); }
    inline int portRemove(mbServerPort* port) { return mbCoreProject::portRemove(reinterpret_cast<mbCorePort*>(port)); }
    inline bool portRename(mbServerPort* port, const QString& newName)  { return mbCoreProject::portRename(reinterpret_cast<mbCorePort*>(port), newName); }

public: // devices
    using mbCoreProject::deviceIndex;
    using mbCoreProject::deviceAdd;
    using mbCoreProject::deviceRemove;
    inline bool hasDevice(mbServerDevice* device) const { return mbCoreProject::hasDevice(reinterpret_cast<mbCoreDevice*>(device)); }
    inline QList<mbServerDevice*> devices() const { return QList<mbServerDevice*>(*(reinterpret_cast<const QList<mbServerDevice*>*>(&m_devices))); }
    inline int deviceIndex(mbServerDevice* device) const { return mbCoreProject::deviceIndex(reinterpret_cast<mbCoreDevice*>(device)); }
    inline int deviceIndex(const QString& name) const { return mbCoreProject::deviceIndex(name); }
    inline mbServerDevice *device(int i) const { return reinterpret_cast<mbServerDevice*>(mbCoreProject::deviceCore(i)); }
    inline mbServerDevice *device(const QString& name) const { return reinterpret_cast<mbServerDevice*>(mbCoreProject::deviceCore(name)); }
    inline mbServerDevice *deviceAt(int i) const { return reinterpret_cast<mbServerDevice*>(mbCoreProject::deviceCoreAt(i)); }
    inline int deviceInsert(mbServerDevice* device, int index = -1) { return mbCoreProject::deviceInsert(reinterpret_cast<mbCoreDevice*>(device), index); }
    inline int deviceAdd(mbServerDevice* device) { return mbCoreProject::deviceAdd(reinterpret_cast<mbCoreDevice*>(device)); }
    inline int deviceRemove(mbServerDevice* device) { return mbCoreProject::deviceRemove(reinterpret_cast<mbCoreDevice*>(device)); }
    inline bool deviceRename(mbServerDevice* device, const QString& newName)  { return mbCoreProject::deviceRename(reinterpret_cast<mbCoreDevice*>(device), newName); }

public: // dataViews
    using mbCoreProject::dataViewIndex;
    using mbCoreProject::dataViewAdd;
    using mbCoreProject::dataViewRemove;
    inline bool hasDataView(mbServerDataView* dataView) const { return mbCoreProject::hasDataView(reinterpret_cast<mbCoreDataView*>(dataView)); }
    inline QList<mbServerDataView*> dataViews() const { return QList<mbServerDataView*>(*(reinterpret_cast<const QList<mbServerDataView*>*>(&m_dataViews))); }
    inline int dataViewIndex(mbServerDataView* dataView) const { return mbCoreProject::dataViewIndex(reinterpret_cast<mbCoreDataView*>(dataView)); }
    inline int dataViewIndex(const QString& name) const { return mbCoreProject::dataViewIndex(name); }
    inline mbServerDataView* dataView(int i) const { return reinterpret_cast<mbServerDataView*>(mbCoreProject::dataViewCore(i)); }
    inline mbServerDataView* dataView(const QString& name) const { return reinterpret_cast<mbServerDataView*>(mbCoreProject::dataViewCore(name)); }
    inline mbServerDataView* dataViewAt(int i) const { return reinterpret_cast<mbServerDataView*>(mbCoreProject::dataViewCoreAt(i)); }
    inline int dataViewInsert(mbServerDataView* dataView, int index = -1) { return mbCoreProject::dataViewInsert(reinterpret_cast<mbCoreDataView*>(dataView), index); }
    inline int dataViewAdd(mbServerDataView* dataView) { return mbCoreProject::dataViewAdd(reinterpret_cast<mbCoreDataView*>(dataView)); }
    inline int dataViewRemove(mbServerDataView* dataView) { return mbCoreProject::dataViewRemove(reinterpret_cast<mbCoreDataView*>(dataView)); }
    inline bool dataViewRename(mbServerDataView* dataView, const QString& newName)  { return mbCoreProject::dataViewRename(reinterpret_cast<mbCoreDataView*>(dataView), newName); }

public: // sim actions
    inline bool hasSimAction(mbServerSimAction *simAction) const { return m_simActions.contains(simAction); }
    inline QList<mbServerSimAction*> simActions() const { return m_simActions; }
    inline int simActionIndex(mbServerSimAction *simAction) const { return m_simActions.indexOf(simAction); }
    inline mbServerSimAction *simAction(int i) const { return m_simActions.value(i); }
    inline mbServerSimAction *simActionAt(int i) const { return m_simActions.at(i); }
    inline int simActionCount() const { return m_simActions.count(); }
    int simActionInsert(mbServerSimAction *simAction, int index = -1);
    inline int simActionAdd(mbServerSimAction *simAction) { return simActionInsert(simAction); }
    void simActionsInsert(const QList<mbServerSimAction*> &simActions, int index = -1);
    inline void simActionsAdd(const QList<mbServerSimAction*> &simActions) { simActionsInsert(simActions); }
    void simActionsRemove(const QList<mbServerSimAction*> &simActions);
    int simActionRemove(int index);
    inline int simActionRemove(mbServerSimAction *simAction) { return simActionRemove(simActionIndex(simAction)); }

public: // script modules
    QString freeScriptModuleName(const QString& s = QString()) const;
    inline bool hasScriptModule(const QString& name) const { return m_hashScriptModules.contains(name); }
    inline bool hasScriptModule(mbServerScriptModule* scriptModule) const { return m_scriptModules.contains(scriptModule); }
    inline QList<mbServerScriptModule*> scriptModules() const { return m_scriptModules; }
    inline int scriptModuleIndex(mbServerScriptModule* scriptModule) const { return m_scriptModules.indexOf(scriptModule); }
    inline int scriptModuleIndex(const QString& name) const { return scriptModuleIndex(scriptModule(name)); }
    inline mbServerScriptModule* scriptModule(int i) const { return m_scriptModules.value(i); }
    inline mbServerScriptModule* scriptModule(const QString& name) const { return m_hashScriptModules.value(name, nullptr); }
    inline mbServerScriptModule* scriptModuleAt(int i) const { return m_scriptModules.at(i); }
    inline int scriptModuleCount() const { return m_scriptModules.count(); }
    int scriptModuleInsert(mbServerScriptModule* scriptModule, int index = -1);
    inline int scriptModuleAdd(mbServerScriptModule* scriptModule) { return scriptModuleInsert(scriptModule); }
    int scriptModuleRemove(int index);
    inline int scriptModuleRemove(const QString& name) { return scriptModuleRemove(scriptModuleIndex(name)); }
    inline int scriptModuleRemove(mbServerScriptModule* scriptModule) { return scriptModuleRemove(scriptModuleIndex(scriptModule)); }
    bool scriptModuleRename(mbServerScriptModule* scriptModule, const QString& newName);

Q_SIGNALS:
    void simActionAdded(mbServerSimAction *simAction);
    void simActionRemoving(mbServerSimAction *simAction);
    void simActionRemoved(mbServerSimAction *simAction);
    void simActionChanged(mbServerSimAction *simAction);

Q_SIGNALS:
    void scriptModuleAdded(mbServerScriptModule*);
    void scriptModuleRemoving(mbServerScriptModule*);
    void scriptModuleRemoved(mbServerScriptModule*);
    void scriptModuleChanged(mbServerScriptModule *scriptModule);

private Q_SLOTS:
    void slotSimActionChanged();
    void slotScriptModuleChanged();

private: // actions
    QList<mbServerSimAction*> m_simActions;

private: // script modules
    typedef QList<mbServerScriptModule*> ScriptModules_t;
    typedef QHash<QString, mbServerScriptModule*> HashScriptModules_t;
    ScriptModules_t m_scriptModules;
    HashScriptModules_t m_hashScriptModules;

};

#endif // SERVER_PROJECT_H
