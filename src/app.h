#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>

#include "WidgetPlaying.h"

class app : public QWidget {
  Q_OBJECT
private:
  QVBoxLayout layout_main;
  QTabWidget widget_main;
  WidgetPlaying widget_playing;

public:
  app();
  ~app();

public slots:

signals:
};