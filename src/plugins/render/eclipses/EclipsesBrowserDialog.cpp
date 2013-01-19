//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2012 Rene Kuettner <rene@bitkanal.net>
//

#include "EclipsesBrowserDialog.h"

#include "MarbleModel.h"
#include "MarbleClock.h"
#include "MarbleDebug.h"

#include "EclipsesModel.h"
#include "EclipsesItem.h"

#include "ui_EclipsesBrowserDialog.h"

namespace Marble {

EclipsesBrowserDialog::EclipsesBrowserDialog( const MarbleModel *model,
                                        QWidget *parent )
    : QDialog( parent ),
    m_marbleModel( model ),
    m_year( 1 )
{
    initialize();
}

EclipsesBrowserDialog::~EclipsesBrowserDialog()
{
    delete m_eclModel;
}

void EclipsesBrowserDialog::setYear( int year )
{
    m_year = year;
    m_browserWidget->spinBoxYear->setValue( year );
}

int EclipsesBrowserDialog::year() const
{
    return m_year;
}

void EclipsesBrowserDialog::accept()
{
    QItemSelectionModel *s = m_browserWidget->treeView->selectionModel();
    QModelIndex selected = s->currentIndex();

    if( selected.isValid() ) {
        EclipsesItem *item = static_cast<EclipsesItem*>( selected.internalPointer() );
        emit buttonShowClicked( m_eclModel->year(), item->index() );
    }

    QDialog::accept();
}

void EclipsesBrowserDialog::updateEclipsesBrowserForYear( int year )
{
    if( year == 0 ) {
        // since year 0 make no sense, we proceed to the next valid year
        setYear( ( m_year > 0 ) ? -1 : 1 );
        return;
    }

    m_eclModel->setYear( year );
    updateButtonStates();
}

void EclipsesBrowserDialog::updateButtonStates()
{
    QItemSelectionModel *s = m_browserWidget->treeView->selectionModel();
    m_browserWidget->buttonShow->setEnabled( s->hasSelection() );
}

void EclipsesBrowserDialog::initialize()
{
    m_browserWidget = new Ui::EclipsesBrowserDialog();
    m_browserWidget->setupUi( this );

    m_browserWidget->treeView->setExpandsOnDoubleClick( false );

    m_eclModel = new EclipsesModel( m_marbleModel );
    m_browserWidget->treeView->setModel( m_eclModel );

    connect( m_browserWidget->buttonShow, SIGNAL(clicked()),
             this, SLOT(accept()) );
    connect( m_browserWidget->buttonClose, SIGNAL(clicked()),
             this, SLOT(reject()) );
    connect( m_browserWidget->spinBoxYear, SIGNAL(valueChanged(int)),
             this, SLOT(updateEclipsesBrowserForYear(int)) );
    connect( m_browserWidget->treeView->selectionModel(),
             SIGNAL(selectionChanged(const QItemSelection&,
                                     const QItemSelection&)),
             this, SLOT(updateButtonStates()) );
    connect( m_browserWidget->buttonSettings, SIGNAL(clicked()),
             SIGNAL(buttonSettingsClicked()) );

    setYear( m_marbleModel->clock()->dateTime().date().year() );

    update();
}

} // namespace Marble

#include "EclipsesBrowserDialog.moc"

