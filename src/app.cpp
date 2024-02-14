#include "app.h"

app::app() {

  setStyleSheet("\
			QWidget{background:rgb(212, 251, 206);}\
      \
      ");

  widget_main.addTab(&widget_playing, "Playing");
  widget_main.show();

  layout_main.addWidget(&widget_main);
  setLayout(&layout_main);
}

app::~app() {
}