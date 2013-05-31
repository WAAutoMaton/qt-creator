/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#ifndef BASEVCSSUBMITEDITORFACTORY_H
#define BASEVCSSUBMITEDITORFACTORY_H

#include "vcsbase_global.h"

#include <coreplugin/editormanager/ieditorfactory.h>

namespace VcsBase {

class VcsBaseSubmitEditor;
class VcsBaseSubmitEditorParameters;

// Parametrizable base class for editor factories creating instances of
// VcsBaseSubmitEditor subclasses.
class VCSBASE_EXPORT BaseVcsSubmitEditorFactory : public Core::IEditorFactory
{
    Q_OBJECT

protected:
    explicit BaseVcsSubmitEditorFactory(const VcsBaseSubmitEditorParameters *parameters);
    ~BaseVcsSubmitEditorFactory();

public:
    Core::IEditor *createEditor(QWidget *parent);

private:
    virtual VcsBaseSubmitEditor
        *createBaseSubmitEditor(const VcsBaseSubmitEditorParameters *parameters,
                                QWidget *parent) = 0;

    const VcsBaseSubmitEditorParameters *const m_parameters; // Not owned.
};

// Utility template to create an editor that has a constructor taking the
// parameter struct and a parent widget.

template <class Editor>
class VcsSubmitEditorFactory : public BaseVcsSubmitEditorFactory
{
public:
    explicit VcsSubmitEditorFactory(const VcsBaseSubmitEditorParameters *parameters)
        : BaseVcsSubmitEditorFactory(parameters)
    {
    }

private:
    VcsBaseSubmitEditor *createBaseSubmitEditor
        (const VcsBaseSubmitEditorParameters *parameters, QWidget *parent)
    {
        return new Editor(parameters, parent);
    }
};

} // namespace VcsBase

#endif // BASEVCSSUBMITEDITORFACTORY_H
