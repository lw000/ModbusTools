#include "server_dialogsettings.h"

#include <QListWidget>
#include <QStackedWidget>

#include <server.h>

#include "server_widgetsettingsscript.h"
#include <gui/server_outputview.h>
#include <gui/script/server_scriptmanager.h>

mbServerDialogSettings::Strings::Strings() //:
    //title(QStringLiteral("Settings")),
    //cachePrefix(QStringLiteral("Ui.Dialogs.SystemSettings."))
{
}

const mbServerDialogSettings::Strings &mbServerDialogSettings::Strings::instance()
{
    static const Strings s;
    return s;
}

mbServerDialogSettings::mbServerDialogSettings(QWidget *parent) :
    mbCoreDialogSettings(parent)
{
    m_listWidget->addItem(QStringLiteral("Script"));
    m_script = new mbServerWidgetSettingsScript(m_stackedWidget);
    m_stackedWidget->addWidget(m_script);
}

void mbServerDialogSettings::fillForm(const MBSETTINGS &m)
{
    const mbServer::Strings &ssrv = mbServer::Strings::instance();
    const mbServerOutputView::Strings &sout = mbServerOutputView::Strings::instance();
    const mbServerScriptManager::Strings &sscr = mbServerScriptManager::Strings::instance();
    mbCoreDialogSettings::fillForm(m);

    m_script->setScriptEnable            (m.value(ssrv.settings_scriptEnable         ).toBool      ());
    m_script->setScriptUseOptimization   (m.value(ssrv.settings_scriptUseOptimization).toBool      ());
    m_script->setScriptLoopPeriod        (m.value(ssrv.settings_scriptLoopPeriod     ).toInt       ());
    m_script->setScriptGenerateComment   (m.value(sscr.settings_scriptGenerateComment).toBool      ());
    m_script->setScriptWordWrap          (m.value(sscr.settings_wordWrap             ).toBool      ());
    m_script->setScriptUseLineNumbers    (m.value(sscr.settings_useLineNumbers       ).toBool      ());
    m_script->setScriptTabSpaces         (m.value(sscr.settings_tabSpaces            ).toInt       ());
    m_script->setScriptEditorFont        (m.value(sscr.settings_font                 ).toString    ());
    m_script->scriptSetEditorColorFormars(m.value(sscr.settings_colorFormats         ).toString    ());
    m_script->setScriptOutputFont        (m.value(sout.font                          ).toString    ());
    m_script->scriptSetManualExecutables (m.value(ssrv.settings_scriptManual         ).toStringList());
    m_script->scriptSetDefaultExecutable (m.value(ssrv.settings_scriptDefault        ).toString    ());
}

void mbServerDialogSettings::fillData(MBSETTINGS &m)
{
    const mbServer::Strings &ssrv = mbServer::Strings::instance();
    const mbServerOutputView::Strings &sout = mbServerOutputView::Strings::instance();
    const mbServerScriptManager::Strings &sscr = mbServerScriptManager::Strings::instance();
    mbCoreDialogSettings::fillData(m);
    m[ssrv.settings_scriptEnable         ] = m_script->scriptEnable            ();
    m[ssrv.settings_scriptUseOptimization] = m_script->scriptUseOptimization   ();
    m[ssrv.settings_scriptLoopPeriod     ] = m_script->scriptLoopPeriod        ();
    m[sscr.settings_scriptGenerateComment] = m_script->scriptGenerateComment   ();
    m[sscr.settings_wordWrap             ] = m_script->scriptWordWrap          ();
    m[sscr.settings_useLineNumbers       ] = m_script->scriptUseLineNumbers    ();
    m[sscr.settings_tabSpaces            ] = m_script->scriptTabSpaces         ();
    m[sscr.settings_font                 ] = m_script->scriptEditorFont        ();
    m[sscr.settings_colorFormats         ] = m_script->scriptEditorColorFormars();
    m[sout.font                          ] = m_script->scriptOutputFont        ();
    m[ssrv.settings_scriptManual         ] = m_script->scriptManualExecutables ();
    m[ssrv.settings_scriptDefault        ] = m_script->scriptDefaultExecutable ();

}
