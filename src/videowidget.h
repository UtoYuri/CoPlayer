#ifndef MYVIDEOWIDGET_H
#define MYVIDEOWIDGET_H

#include <QVideoWidget>
#include <QToolButton>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QFileDialog>
#include <QMimeData>
#include <QStackedLayout>
#include <QListWidget>
#include <QScrollBar>
#include <QPropertyAnimation>
#include <QTimer>
#include <QDockWidget>
#include <QDesktopWidget>
#include <QDebug>


class VideoWidget : public QVideoWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget *parent = 0);
    ~VideoWidget();

    void initWidgetUi();    //构造界面
    void initVideoWidget(); //初始化

public slots:
    void openFile();    //打开文件
    void showButton();  //显示打开文件按钮
    void hideButton();  //隐藏打开文件按钮

    void removeMedia(); //移除媒体
    void addMedia(const QString &fileName); //添加媒体
    void toggleListWidget(bool show);  //显示播放列表

    void adjustWidget();    //适应窗口


protected:
    void paintEvent(QPaintEvent *); //重绘
    void keyPressEvent(QKeyEvent *event);   //按键事件
    void mousePressEvent(QMouseEvent *event);   //点击事件
    void wheelEvent(QWheelEvent *event);  //鼠标滚轮事件
    void dragEnterEvent(QDragEnterEvent *event);    //拖进事件
    void dropEvent(QDropEvent *event);  //拖放事件

signals:
    void play();    //开始/暂停播放
    void fullScreenToggled(bool fullScreen);    //切换全屏/半屏
    void fastForward(); //快进
    void rewind();  //快退
    void positionChanged(qint64 pos); //进度变化
    void volumeChanged(int increment);  //音量变化

    void playNewMedias(QStringList files); //播放新资源
    void deleteMedia(int index);    //移除指定资源
    void playMedia(int index);   //播放指定资源

private:
    bool m_bIsListShowing;
    QToolButton *m_pBtnOpenFile;
    QDockWidget *m_pVideoListWidget;
    QListWidget *m_pListWidget;
    QToolButton *m_pBtnRemove;
    QVBoxLayout *m_pVLayout;
    QHBoxLayout *m_pHLayout;
};

#endif // MYVIDEOWIDGET_H
