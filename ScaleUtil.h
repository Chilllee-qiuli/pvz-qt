// ScaleUtil.h
#include <QPixmap>
#include <QGraphicsPixmapItem>

class ScaleUtil {
public:
    // 缩放图片并返回处理后的item
    static QGraphicsPixmapItem* scaledPixmap(const QString& path, double scale) {
        QPixmap pix(path);
        if (pix.isNull()) return nullptr;
        QPixmap scaled = pix.scaled(
            pix.width() * scale, 
            pix.height() * scale, 
            Qt::KeepAspectRatio, 
            Qt::SmoothTransformation  // 平滑缩放，避免锯齿
        );
        return new QGraphicsPixmapItem(scaled);
    }
};