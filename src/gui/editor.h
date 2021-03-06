// This file is part of the SpeedCrunch project
// Copyright (C) 2004-2005 Ariya Hidayat <ariya@kde.org>
// Copyright (C) 2007 Ariya Hidayat <ariya@kde.org>
// Copyright (C) 2007-2009 Helder Correia <helder.pereira.correia@gmail.com>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; see the file COPYING.  If not, write to
// the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
// Boston, MA 02110-1301, USA.

#ifndef GUI_EDITOR_H
#define GUI_EDITOR_H

#include "gui/textedit.h"

#include <memory>

class HNumber;

class QEvent;
class QKeyEvent;
class QWheelEvent;
class QWidget;

class Editor : public TextEdit
{
    Q_OBJECT

public:
    explicit Editor( QWidget * parent = 0 );
    ~Editor();

    bool autoCalcEnabled() const;
    bool autoCompleteEnabled() const;
    void clearHistory();
    int cursorPosition() const;
    void doBackspace();
    void highlight();
    QStringList history() const;
    QStringList historyResults() const;
    char radixChar() const;
    void setAnsAvailable( bool );
    void setAutoCalcEnabled( bool );
    void setAutoCompletionEnabled( bool );
    void setCursorPosition( int pos );
    void setText( const QString & );
    void setHistory( const QStringList & history );
    void setHistoryResults( const QStringList & results );
    QSize sizeHint() const;
    void stopAutoCalc();
    void stopAutoComplete();
    QString text() const;

signals:
    void autoCalcEnabled( const QString & );
    void autoCalcDisabled();
    void returnPressed();

public slots:
    void appendHistory( const QString & result, const QString & expression );
    void appendHistory( const QStringList & h, const QStringList & r );
    void cancelConstantCompletion();
    void evaluate();
    void insertConstant( const QString & );
    void insert( const QString & );

protected slots:
    void autoCalc();
    void autoCalcSelection();
    void autoComplete( const QString & item );
    void checkAutoCalc();
    void checkAutoComplete();
    void startSelAutoCalcTimer();
    void checkMatching();
    void doMatchingLeft();
    void doMatchingPar();
    void doMatchingRight();
    void historyBack();
    void historyForward();
    void triggerAutoComplete();
    void triggerEnter();

protected:
    QString formatNumber( const HNumber & value ) const;
    void keyPressEvent( QKeyEvent * );
    void wheelEvent( QWheelEvent * );

private:
    struct Private;
    const std::auto_ptr<Private> d;

    Editor();
    Editor( const Editor & );
    Editor & operator=( const Editor & );
};

class EditorCompletion : public QObject
{
    Q_OBJECT

public:
    EditorCompletion( Editor * );
    ~EditorCompletion();

    bool eventFilter( QObject *, QEvent * );
    void showCompletion( const QStringList & );

signals:
    void selectedCompletion( const QString & );

public slots:
    void doneCompletion();
    void selectItem( const QString & ); // WORKAROUND 76

protected slots:
    void fade( int );

private:
    struct Private;
    const std::auto_ptr<Private> d;

    EditorCompletion( const EditorCompletion & );
    EditorCompletion & operator=( const EditorCompletion & );
};

class ConstantCompletion : public QObject
{
    Q_OBJECT

public:
    ConstantCompletion( Editor * );
    ~ConstantCompletion();

    bool eventFilter( QObject *, QEvent * );
    void showCompletion();

signals:
    void selectedCompletion( const QString & item );
    void canceledCompletion();

public slots:
    void doneCompletion();

protected slots:
    void showCategory();
    void showConstants();
    void slide( int );

private:
    struct Private;
    const std::auto_ptr<Private> d;

    ConstantCompletion( const ConstantCompletion & );
    ConstantCompletion & operator=( const ConstantCompletion & );
};

#endif

