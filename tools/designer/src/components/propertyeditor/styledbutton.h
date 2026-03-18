/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the Qt Designer of the Qt Toolkit.
**
** Licensees holding valid Qt Preview licenses may use this file in
** accordance with the Qt Preview License Agreement provided with the
** Software.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
** information about Qt Commercial License Agreements.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef STYLEBUTTON_H
#define STYLEBUTTON_H

#include <QtGui/QPushButton>

namespace qdesigner_internal {

class StyledButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(QBrush brush READ brush WRITE setBrush)
    Q_ENUMS(ButtonType)

public:
    enum ButtonType {ColorButton, PixmapButton};

    StyledButton (QWidget *parent = 0, ButtonType type = ColorButton);
    virtual ~StyledButton () {}

    void setButtonType(ButtonType type);
    const QBrush &brush();
    void setBrush(const QBrush &b);

    QString pixmapFileName() const;

signals:
    void changed();

public slots:
    virtual void onEditor();

protected:
    void paintEvent (QPaintEvent *event);

private:
    QString buildImageFormatList() const;
    bool openPixmap();

    ButtonType btype;
    QString pixFile;
    QBrush mBrush;
};

}  // namespace qdesigner_internal

#endif // STYLEBUTTON_H
