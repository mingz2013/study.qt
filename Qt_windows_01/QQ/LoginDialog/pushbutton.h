#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QPushButton>

/**
 * @brief The PushButton class
 * PushButton: 当鼠标左键弹起,并在按键范围内时响应。
 * PushButton hover normal pressed 没有用qss的原因：
 * 重写mousePressEvent，mouseReleaseEvent后，hover、pressed样式混乱。
 */
class PushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit PushButton(QString normal, QString hover, QString pressed, QWidget *parent = 0);
    explicit PushButton(QString background, QWidget *parent = 0);
signals:

public slots:

protected:
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    enum ButtonState {
        Normal,
        Hover,
        Pressed
    };

    ButtonState buttonState;

    QPixmap normalPixmap;
    QPixmap hoverPixmap;
    QPixmap pressPixmap;
};

#endif // PUSHBUTTON_H
