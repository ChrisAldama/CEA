#include "graphics.h"
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QFont>

using namespace Board;


QImage Graphics::draw(const Board::Tissue &tissue, const QSize &size, const colorMap &colors)
{
    QImage image(size, QImage::Format_RGB888);
    QPainter painter(&image);
    int cellSize = (float(size.width()) / float(tissue.width));

    int x_c = 0;
    int y_c = 0;
    QPen pen(Qt::white);
    QFont font("Verdana");
    font.setPixelSize(cellSize*0.8);
    pen.setWidth(3);    
    painter.setPen(pen);
    painter.setFont(font);
    for(unsigned y = 0; y < tissue.height; ++y){
        x_c = 0;
        for(unsigned x = 0; x < tissue.width; ++x){
            const Board::Cell &cell =
                    tissue.buffer->operator [](x + y * tissue.height);
            int idx = static_cast<int>(cell.type);
            QColor color = colors[idx];
            painter.setBrush(QBrush(color));
            painter.drawRect(x_c, y_c, cellSize, cellSize);
            //QString str = QString::number(cell.data);
            //painter.drawText(x_c, y_c, cellSize, cellSize,Qt::AlignHCenter | Qt::AlignCenter,str);
            x_c += cellSize;
        }
        y_c += cellSize;
    }

    painter.end();
    return image;

}

constexpr int idx(const CellType type)
{
    return static_cast<int>(type);
}

Graphics::colorMap Graphics::defaultColors()
{
    static colorMap map;
    static bool init = false;
    if(!init){
        init = true;
        map[idx(CellType::None)] = QColor(Qt::black);
        map[idx(CellType::Axon)] = QColor(Qt::green);
        map[idx(CellType::Dendrite)] = QColor(Qt::red);
        map[idx(CellType::Body)] = QColor(Qt::gray);
        map[idx(CellType::IN)] = QColor(Qt::blue);
        map[idx(CellType::OUT)] = QColor(Qt::yellow);
    }

    return map;
}

QImage Graphics::plot(const VVector &output, const Stimuli &st, const QSize &s)
{

}
