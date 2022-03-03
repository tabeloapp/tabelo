/*
    SPDX-FileCopyrightText: 2022 naracanto https://naracanto.github.io

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "main_window.h"

#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QMenuBar>

#include <KActionCollection>
#include <KLocalizedString>
#include <KStandardAction>
#include <KToggleAction>

#include "main_window_area.h"
#include "main_window_child.h"


MainWindow::MainWindow(QWidget *parent)
    : KXmlGuiWindow(parent)
    , m_windowArea{new MainWindowArea}
{
    m_windowArea->setViewMode(QMdiArea::TabbedView);
    m_windowArea->setDocumentMode(true);
    m_windowArea->setTabsClosable(true);
    m_windowArea->setTabsMovable(true);
    setCentralWidget(m_windowArea);

    setupActions();
}


void MainWindow::setupActions()
{
    //
    // File

    KStandardAction::openNew(this, &MainWindow::newDocument, actionCollection());
    KStandardAction::open(this, &MainWindow::openDocument, actionCollection());

    m_actionRecentDocuments = KStandardAction::openRecent(this, &MainWindow::openDocumentFromFile, actionCollection());

    KStandardAction::save(this, &MainWindow::saveDocument, actionCollection());
    KStandardAction::saveAs(this, &MainWindow::saveDocumentAs, actionCollection());
    KStandardAction::quit(qApp, &QCoreApplication::quit, actionCollection());


    //
    // Settings

    auto *actionShowMenubar = KStandardAction::showMenubar(menuBar(), &QMenuBar::setVisible, actionCollection());


    // Standard window options
    setupGUI(Default, QLatin1String("tabelo_ui.rc"));

    // Initialization
    actionShowMenubar->setChecked(!menuBar()->isHidden());
}


void MainWindow::newDocument()
{
    auto *document = createDocument();
    document->show();
}


void MainWindow::openDocument()
{
    for (const QUrl &url : QFileDialog::getOpenFileUrls(this, i18n("Open Document")))
        openDocumentFromFile(url);
}


void MainWindow::openDocumentFromFile(const QUrl &fileName)
{
    qDebug() << "Document to open:" << fileName.toString();
}


void MainWindow::saveDocument()
{

}


void MainWindow::saveDocumentAs()
{

}


MainWindowChild *MainWindow::createDocument()
{
    MainWindowChild *child = new MainWindowChild;
    m_windowArea->addSubWindow(child);

    return child;
}
