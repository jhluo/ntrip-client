#include "FusionStyle.h"
#include <QStyleFactory>
#include <QtWidgets>

FusionStyle::FusionStyle():
    QProxyStyle(QStyleFactory::create("Fusion"))
{

}

void FusionStyle::polish(QWidget *widget)
{
    if (qobject_cast<QPushButton *>(widget)
            || qobject_cast<QComboBox *>(widget))
        widget->setAttribute(Qt::WA_Hover, true);
}

void FusionStyle::unpolish(QWidget *widget)
{
    if (qobject_cast<QPushButton *>(widget)
            || qobject_cast<QComboBox *>(widget))
        widget->setAttribute(Qt::WA_Hover, false);
}

int FusionStyle::pixelMetric(PixelMetric metric,
                                    const QStyleOption *option,
                                    const QWidget *widget) const
{
    switch (metric) {
    case PM_ScrollBarExtent:
        return QProxyStyle::pixelMetric(metric, option, widget) + 4;
    default:
        return QProxyStyle::pixelMetric(metric, option, widget);
    }
}

int FusionStyle::styleHint(StyleHint hint, const QStyleOption *option,
                                  const QWidget *widget,
                                  QStyleHintReturn *returnData) const
{
    switch (hint) {
    case SH_DitherDisabledText:
        return int(false);
    case SH_EtchDisabledText:
        return int(true);
    default:
        return QProxyStyle::styleHint(hint, option, widget, returnData);
    }
}


void FusionStyle::drawControl(ControlElement element,
                                     const QStyleOption *option,
                                     QPainter *painter,
                                     const QWidget *widget) const
{
    switch (element) {
    case CE_PushButtonLabel:
        {
            QStyleOptionButton myButtonOption;
            const QStyleOptionButton *buttonOption =
                    qstyleoption_cast<const QStyleOptionButton *>(option);
            if (buttonOption) {
                myButtonOption = *buttonOption;
                if (myButtonOption.palette.currentColorGroup()
                        != QPalette::Disabled) {
                    if (myButtonOption.state & (State_Sunken | State_On)) {
                        myButtonOption.palette.setBrush(QPalette::ButtonText,
                                myButtonOption.palette.brightText());
                    }
                }
            }
            QProxyStyle::drawControl(element, &myButtonOption, painter, widget);
        }
        break;
    default:
        QProxyStyle::drawControl(element, option, painter, widget);
    }
}

//void SnipStyle::setTexture(QPalette &palette, QPalette::ColorRole role,
//                                    const QPixmap &pixmap)
//{
//    for (int i = 0; i < QPalette::NColorGroups; ++i) {
//        QColor color = palette.brush(QPalette::ColorGroup(i), role).color();
//        palette.setBrush(QPalette::ColorGroup(i), role, QBrush(color, pixmap));
//    }
//}

//QPainterPath SnipStyle::roundRectPath(const QRect &rect)
//{
//    int radius = qMin(rect.width(), rect.height()) / 2;
//    int diam = 2 * radius;

//    int x1, y1, x2, y2;
//    rect.getCoords(&x1, &y1, &x2, &y2);

//    QPainterPath path;
//    path.moveTo(x2, y1 + radius);
//    path.arcTo(QRect(x2 - diam, y1, diam, diam), 0.0, +90.0);
//    path.lineTo(x1 + radius, y1);
//    path.arcTo(QRect(x1, y1, diam, diam), 90.0, +90.0);
//    path.lineTo(x1, y2 - radius);
//    path.arcTo(QRect(x1, y2 - diam, diam, diam), 180.0, +90.0);
//    path.lineTo(x1 + radius, y2);
//    path.arcTo(QRect(x2 - diam, y2 - diam, diam, diam), 270.0, +90.0);
//    path.closeSubpath();
//    return path;
//}
