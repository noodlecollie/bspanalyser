#include "textutil.h"

namespace TextUtil
{
    QFont monospacedFont(int size)
    {
        QFont font("Courier", size);
        font.setStyleHint(QFont::Monospace);
        return font;
    }
}
