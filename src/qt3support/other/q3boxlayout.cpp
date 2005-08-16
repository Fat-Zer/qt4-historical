/*!
    \class Q3HBoxLayout q3boxlayout.h
    \compat

    \brief The Q3HBoxLayout class lines up widgets horizontally.
    \sa Q3VBoxLayout
*/

/*!
    \fn Q3HBoxLayout::Q3HBoxLayout(QWidget *parent, int margin = 0, int spacing = -1, const char *name = 0)

    Constructs a new top-level horizontal box called \a name, with parent
    \a parent. The \a margin is the number of pixels between the edge of the
    widget and its managed children. The \a spacing is the default number of
    pixels between neighboring children. If \a spacing is -1 the value of margin
    is used for spacing.
*/

/*!
    \fn Q3HBoxLayout::Q3HBoxLayout(QLayout *parentLayout, int spacing = -1, const char *name = 0)

    Constructs a new horizontal box called \a name and adds it to
    \a parentLayout. The \a spacing is the default number of pixels between
    neighboring children. If \a spacing is -1, this Q3HBoxLayout will inherit
    its parent's spacing.
*/

/*!
    \fn Q3HBoxLayout::Q3HBoxLayout(int spacing = -1, const char *name = 0)

    Constructs a new horizontal box called \a name. You must add it to another
    layout. The \a spacing is the default number of pixels between neighboring
    children. If \a spacing is -1, this QHBoxLayout will inherit its parent's
    spacing(). 
*/

/*!
    \fn Q3HBoxLayout::Q3HBoxLayout()
    \internal
*/

/*!
    \fn Q3HBoxLayout::Q3HBoxLayout(QWidget *parent)
    \internal
*/

/*!
    \class Q3VBoxLayout q3boxlayout.h
    \compat

    \brief The Q3VBoxLayout class lines up widgets vertically.
    \sa Q3HBoxLayout
*/

/*!
    \fn Q3VBoxLayout::Q3VBoxLayout(QWidget *parent, int margin = 0, int spacing = -1, const char *name = 0)

    Constructs a new top-level vertical box called \a name, with parent
    \a parent. The \a margin is the number of pixels between the edge of the
    widget and its managed children. The \a spacing is the default number of
    pixels between neighboring children. If \a spacing is -1 the value of
    margin is used for spacing.
*/

/*!
    \fn Q3VBoxLayout::Q3VBoxLayout(QLayout *parentLayout, int spacing = -1, const char *name = 0)

    Constructs a new vertical box called \a name and adds it to
    \a parentLayout. The \a spacing is the default number of pixels between
    neighboring children. If \a spacing is -1, this Q3VBoxLayout will inherit
    its parent's spacing().
*/

/*!
    \fn Q3VBoxLayout::Q3VBoxLayout(int spacing = -1, const char *name = 0)

    Constructs a new vertical box called \a  name. You must add it to another
    layout. The \a spacing is the default number of pixels between neighboring
    children. If \a spacing is -1, this Q3VBoxLayout will inherit its parent's
    spacing().
*/

/*!
    \fn Q3VBoxLayout::Q3VBoxLayout()
    \internal
*/

/*!
    \fn Q3VBoxLayout::Q3VBoxLayout(QWidget *parent)
    \internal
*/
