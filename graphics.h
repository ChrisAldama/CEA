#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QImage>
#include <QSize>
#include <array>
#include <QColor>
#include "board.h"
#include "stimuli.h"

namespace Graphics
{
    using colorMap = std::array<QColor, static_cast<int>(Board::CellType::OUT) + 2>;
    colorMap defaultColors();
    QImage draw(const Board::Tissue &tissue, const QSize &size, const colorMap &colors = defaultColors());
    QImage plot(const VVector &output, const Stimuli &st, const QSize &s);


}

#endif // GRAPHICS_H
